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
    te.insert(500, 3);
    te.insert(250, 3);
    te.insert(750, 3);

    // a. 红色节点，会遇到第三种，父亲是红色 且叔叔是红色， 一个问题需要解决：当叔叔节点为红色， 持续向上反转父节点为红色，直到叔叔节点是黑色
    te.insert(125, 3);

    te.insert(350, 3);

    // 和 a 情况相同
    te.insert(200, 3);

    te.insert(100, 3);

    te.insert(50, 3);
    te.insert(111, 3);
    te.insert(75, 3);
    te.insert(90, 3);

    te.insert(10, 3);
    te.insert(99, 3);
    te.insert(95, 3);

    te.erase(95);
}