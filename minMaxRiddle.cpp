#include<iostream>
#include<vector>
#include<unordered_map>
#include<stack>

template<typename K>
void printMap(const K& M)
{
    for(const auto& item:M)
    {
        std::cout << item.first << ": " << item.second << '\n';
    }
    std::cout << '\n';
}
void inverseMap(std::unordered_map<long, int>& UM1, std::unordered_map<int, long>& UM2)
{
    for(const auto& item:UM1)
    {
        if(UM2.count(item.second) > 0)
        {
            if(UM2[item.second] < item.first)
            {
                UM2[item.second] = item.first;
            }
        }
        else
        {
            UM2[item.second] = item.first;
        }
    }
}
void createMap(const std::vector<long>& arr, std::unordered_map<long, int>& UM1)
{
    const std::size_t size = arr.size();
    std::stack<int> S;
    std::size_t i = 0;
    for(; i < size; ++i)
    {
        if(S.empty() || arr[i] > arr[S.top()])
        {
            S.push(i);
        }
        else
        {
            while(!S.empty() && arr[S.top()] > arr[i])
            {
                int p = S.top();
                S.pop();
                UM1[arr[p]] = S.empty() ? i : (i - S.top() - 1);
            }
            S.push(i);
        }
    }
    while(!S.empty())
    {
        int p = S.top();
        S.pop();
        UM1[arr[p]] = S.empty() ? i : (i - S.top() - 1);
    }
}
std::vector<long> riddle(const std::vector<long>& arr)
{
    // Create number -> size(maximum window it can create)
    std::unordered_map<long, int> UM1;
    // Create max_window_size -> max_number
    std::unordered_map<int, long> UM2;
    const std::size_t size = arr.size();
    createMap(arr, UM1);
    //printMap(UM1);
    inverseMap(UM1, UM2);
    //printMap(UM2);
    std::vector<long> result;
    long prev = *std::min_element(arr.begin(), arr.end());
    for(int i = size; i > 0; --i)
    {
        if(UM2.count(i) > 0)
        {
            if(UM2[i] < prev)
            {
                result.emplace_back(prev);
            }
            else
            {
                result.emplace_back(UM2[i]);
                prev = UM2[i];
            }
        }
        else
        {
            result.emplace_back(prev);
        }
    }
    std::reverse(result.begin(), result.end());
    return result;
}
int main()
{
    std::vector<long> arr{3, 5, 4, 7, 6, 2};
    for(const auto& i:riddle(arr))
    {
        std::cout << i << " ";
    }
    std::cout << '\n';
    return 0;
}
