#include <numeric>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <functional>
#include <iostream>

int main(int argc, char const *argv[])
{

    std::vector<uint32_t> sq{1, 5, 321, 312};

    std::string base = "mm";

    base = std::accumulate(std::next(sq.rbegin()), sq.rend(), std::move(base), [](std::string base, uint32_t t) {
        return std::move(base) + std::to_string(t);
    });

    std::cout << base << std::endl;

    std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    int sum = std::accumulate(v.begin(), v.end(), 0);

    int product = std::accumulate(std::move_iterator<std::vector<int>::iterator>(v.begin()), std::move_iterator<std::vector<int>::iterator>(v.end()), 1, std::multiplies<int>());

    std::cout << product;

    std::for_each(v.begin(), v.end(), [](int t) -> void {
        std::cout << '"' << t << '"';
    });
    return 0;
}
