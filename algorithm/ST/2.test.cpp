#include <algorithm>
#include <iostream>
#include <ciso646>
#include <cmath>

float log2(float __x)
{
    static float __e = std::log(2.0f);
    return std::log(__x) / __e;
}
int main()
{

    std::cout << ((int)log2(9 - 1 - 1.0)) << std::endl;

    return 0;
}