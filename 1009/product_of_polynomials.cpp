#include <map>
#include <iostream>
#include <vector>
#include <functional>
#include <cstdio>
#include <cmath>

constexpr float esp = 1e-8;
typedef std::map<int, float, std::greater<int>> polynomials;

int main()
{
    int m = 0;
    std::cin >> m;
    polynomials polynomials_0;

    for (size_t i = 0; i < m; i++)
    {
        int a;
        float b;
        std::cin >> a;
        std::cin >> b;
        polynomials_0.insert({a, b});
    }
    
    std::cin >> m;
    polynomials polynomials_1;

    for (size_t i = 0; i < m; i++)
    {
        int a;
        float b;
        std::cin >> a;
        std::cin >> b;
        polynomials_1.insert({a, b});
    }

    polynomials ret;
    for(auto t0 : polynomials_0)
    {
        for(auto t1 : polynomials_1)
        {
           if(ret.find(t0.first + t1.first) == ret.end())
           {
               ret.insert({t0.first + t1.first, t0.second * t1.second});
           }
           else
           {
                ret[t0.first + t1.first] += t0.second * t1.second;
                if(std::fabs(ret[t0.first + t1.first]) < esp)
                {
                    ret.erase(t0.first + t1.first);
                }
           }
        }
    }

    std::cout << ret.size();
    for(auto t : ret)
    {
        std::printf(" %d %0.1f", t.first, t.second);
    }

    return 0;
}