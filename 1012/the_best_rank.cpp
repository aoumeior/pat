#include <string>
#include <tuple>
#include <map>
#include <iostream>
#include <utility>
#include <vector>

struct single_score
{
    std::string student_id;
    std::tuple<int, int, int> cme;
    std::pair<char, int> cme_max;
    int average;
};

int main()
{
    size_t m, n;
    std::map<std::string, single_score> score_table;

    std::cin >> m >> n;
    single_score sc;

    std::vector<std::string> t{n};

    for (size_t i = 0; i < m; i++)
    {
        std::cin >> sc.student_id >> std::get<0>(sc.cme) >> std::get<1>(sc.cme) >> std::get<2>(sc.cme);
        sc.average = (std::get<0>(sc.cme) + std::get<1>(sc.cme) + std::get<2>(sc.cme)) / 3;

        sc.cme_max.first = 'A';
        sc.cme_max.second = sc.average;

        if (std::get<0>(sc.cme) > sc.cme_max.second)
        {
            sc.cme_max.first = 'C';
            sc.cme_max.second = std::get<0>(sc.cme);
        }

        if (std::get<1>(sc.cme) > sc.cme_max.second)
        {
            sc.cme_max.first = 'M';
            sc.cme_max.second = std::get<1>(sc.cme);
        }
        if (std::get<2>(sc.cme) > sc.cme_max.second)
        {
            sc.cme_max.first = 'E';
            sc.cme_max.second = std::get<2>(sc.cme);
        }

        score_table.insert({sc.student_id, sc});
    }

    size_t rank = 1;
    for (size_t i = 0; i < n; i++)
    {
        std::cin >> t[i];

        auto it = score_table.find(t[i]);
        if (it == score_table.end())
        {
            std::cout << "N/A" << std::endl;
            continue;
        }

        if (it->second.cme_max.first == 'E')
        {
            for (auto it1 : score_table)
            {
                if (it1.first == it->first)
                    continue;
                if (it->second.cme_max.second < std::get<2>(it1.second.cme))
                {
                    rank++;
                }
            }
        }

        if (it->second.cme_max.first == 'M')
        {
            for (auto it1 : score_table)
            {
                if (it1.first == it->first)
                    continue;
                if (it->second.cme_max.second < std::get<1>(it1.second.cme))
                {
                    rank++;
                }
            }
        }

        if (it->second.cme_max.first == 'C')
        {
            for (auto it1 : score_table)
            {
                if (it1.first == it->first)
                    continue;
                if (it->second.cme_max.second < std::get<0>(it1.second.cme))
                {
                    rank++;
                }
            }
        }

        if (it->second.cme_max.first == 'A')
        {
            for (auto it1 : score_table)
            {
                if (it1.first == it->first)
                    continue;
                if (it->second.average < it1.second.average)
                {
                    rank++;
                }
            }
        }

        std::cout << rank << ' ' << it->second.cme_max.first << std::endl;
        rank = 1;
    }
}