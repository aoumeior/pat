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
    te.insert(50, 3);
    te.insert(1, 4);
    te.insert(100, 4);
    te.insert(75, 4);
    te.insert(125, 4);
}