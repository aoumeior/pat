#include <iostream>
#include <cstdio>
#include <tuple>
#include <string>
#include <vector>
#include <cmath>
#include <string>

int main()
{
    std::vector<std::tuple<float, float, float>> table{3};
    float res = 1;
    std::string t;
    size_t odd_number = 0;

    for (size_t i = 0; i < 3; i++)
    {
        auto &[W, T, L] = table[i];
        std::cin >> W >> L >> T;
        float max_value = std::max(std::max(W, L), T);
        
        res *= max_value;
        if (max_value - W < 1e-6)
        {
            t += "W";
            odd_number++;
             continue;
        }

        if (max_value - L < 1e-6)
        {
            t += "T";
            continue;
        }
        if (max_value - T < 1e-6)
        {
            t += "L";
        }
    }

    res = (res * (odd_number % 2 == 1 ? 0.65 : 1) - 1) * 2;
    
    std::cout << t[0] << ' ' << t[1] << ' ' << t[2];
    std::printf(" %0.2f", res);
}