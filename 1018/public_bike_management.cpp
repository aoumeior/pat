#include <vector>
#include <tuple>
#include <iostream>
#include <climits>
#include <algorithm>

int main(int argc, char const *argv[])
{
    // 1 row
    int maximum_capacity;
    int total_number_of_stations;
    int index_of_problem_station;
    int number_of_roads;
    const int optimum_state = maximum_capacity / 2;
    {
        std::cin >> maximum_capacity >> total_number_of_stations >> index_of_problem_station >> number_of_roads;
    }

    // 2 row
    std::vector<int> remainder_bike{total_number_of_stations};

    for (auto &it : remainder_bike)
    {
        std::cin >> it;
        it = it - optimum_state; // need adjustment when 'it' is negative
    }
    // remainder
    std::vector<std::vector<std::pair<int, int>>> A2B_weight{total_number_of_stations};

    for (size_t i = 0; i < total_number_of_stations; i++)
    {
        int a, b, c;
        std::cin >> a >> b >> c;
        A2B_weight[a].push_back({b, c});
        A2B_weight[b].push_back({a, c});
    }

    //
    std::vector<int> stations{total_number_of_stations, INT_MAX};
    stations[0] = 0; // require total_number_of_stations > 0

    bool visit[total_number_of_stations] = {false};
    visit[0] = true;
    /* code */
    for (size_t i = 0; i < total_number_of_stations; i++)
    {

        std::pair<int, int> res = {0, INT_MAX};
        for (size_t j = 0; j < total_number_of_stations; j++)
        {
            if (visit[j] == false)
                continue;
            auto it = std::min_element(A2B_weight[j].begin(), A2B_weight[j].end(),
                                       [](const std::pair<int, int> &a, const std::pair<int, int> &b) {
                                           return a.second > b.second;
                                       });
            if (it != A2B_weight[j].end())
            {
                if (it->second < res.second)
                {
                    res.first = it->first;
                    res.second = it->second;
                }
            }
        }
        visit[res.first] = true;
        auto it = std::min_element(A2B_weight[res.first].begin(), A2B_weight[res.first].end(),
                                   [](const std::pair<int, int> &a, const std::pair<int, int> &b) {
                                       return a.second > b.second;
                                   });
        stations[it->first] = std::min(it->second, res.second);
        
    }

    /* code */
    return 0;
}