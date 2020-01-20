#include <utility>               // for pair
#include <vector>                // for vector
#include <iostream>              // for cin
#include <boost/multi_array.hpp> // for multi_array
#include <stdio.h>
#include <climits>
/*
    city number N
    road number M
    pair form C1 to C2: C1, C3

*/

/*
    number of rescue
*/

struct Emergency
{
    unsigned int from;
    unsigned int to;
    unsigned int road_length;
};

std::vector<Emergency> road_array;

int main()
{

    int city_number;
    int road_number;
    std::cin >> city_number;
    std::cin >> road_number;

    std::pair<int, int> from_to;
    std::cin >> from_to.first;
    std::cin >> from_to.second;

    int *city_rescuers = new int[city_number]{0};

    for (size_t i = 0; i < city_number; i++)
    {
        std::cin >> city_rescuers[i];
    }

    boost::multi_array<int, 2> adjoin_map(boost::extents[city_number][city_number]);

    for (int i = 0; i < city_number; i++)
    {
        for (int j = 0; j < city_number; j++)
        {
            if (i == j)
            {
                adjoin_map[i][j] = 0;
                continue;
            }
            adjoin_map[i][j] = 200;
        }
    }

    for (size_t i = 0; i < road_number; i++)
    {
        int from;
        int to;
        int road_size;
        std::cin >> from >> to >> road_size;
        adjoin_map[from][to] = road_size;
        adjoin_map[to][from] = road_size;
    }
    std::cout << "------------------" << std::endl;
    for (int i = 0; i < city_number; i++)
    {
        for (int j = 0; j < city_number; j++)
            printf("%20d ", adjoin_map[i][j]);
        printf("\n");
        printf("\n");
    }
    std::cout << "------------------" << std::endl;
    for (int k = 0; k < city_number; k++)
        for (int i = 0; i < city_number; i++)
            for (int j = 0; j < city_number; j++)
                if (adjoin_map[i][k] + adjoin_map[k][j] < adjoin_map[i][j])
                    adjoin_map[i][j] = adjoin_map[i][k] + adjoin_map[k][j];

    for (int i = 0; i < city_number; i++)
    {
        for (int j = 0; j < city_number; j++)
            printf("%20d", adjoin_map[i][j]);
        printf("\n");
    }
    return 0;
}