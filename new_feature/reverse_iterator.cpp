#include <iterator>
#include <array>
#include <iostream>

int main(int argc, char const *argv[])
{

    std::array<int, 32> a{0};

    std::reverse_iterator<std::array<int, 32>::iterator> fds = a.rbegin();

    fds[3] = 1;

    for (auto t : a)
    {
        std::cout << t << " ";
    }

    return 0;
}
