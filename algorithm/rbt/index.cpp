#include <string>

#include "rbt.hpp"

class undef
{

    undef(int t) {}
};

int main()
{
    // Node<int, undef> node0; // error : static_assert fail
    Node<int, std::string> node;

    __Tree<int, int> te;
    te.insert(1, 3);

}