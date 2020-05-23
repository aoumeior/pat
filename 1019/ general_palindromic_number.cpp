#include <cstdint>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <algorithm>

int main()
{
    std::uint64_t decimal = 121, base = 5;

    std::cin >> decimal >> base;
    std::vector<std::uint64_t> str;
    do
    {
        std::uint64_t t = decimal % base;

        str.push_back(t);
        decimal = decimal / base;

    } while (decimal != 0);

    auto status = true;
    for (size_t i = 0; i < str.size() / 2; i++)
    {
        if (str[i] != str[str.size() - i - 1])
        {
            status = false;
            break;
        }
    }

    if (status == true)
        std::cout << "Yes" << std::endl;
    else
        std::cout << "No" << std::endl;


    std::cout << str[str.size() - 1];
    for (size_t i = 1; i < str.size(); i++)
    {
        std::cout << ' '<< str[str.size() - i - 1] ;
    }
}