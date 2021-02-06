#include <type_traits>
#include <cmath>
#include <cassert>

template <typename first, typename second>
struct pair
{
    first __first;
    second __second;

    pair(first f, second s) : __first(f), __second(s) {}
};

template <typename key, typename value>
class Node
{
    static_assert((std::is_default_constructible<value>::value or std::is_pod<value>::value), "value must has default constructor or trivaial default constructor");

public:
    enum class NodeColor : int
    {
        UNKNOW = -1,
        RED = 0,
        BLOCK = 1,
    };
    using keyType = key;
    using ValueType = value;
    using Self = Node;
    using SelfPointer = Node *;

public:
    keyType __key;
    ValueType __value;
    // default red , mutable
    mutable NodeColor __node_color = NodeColor::RED;

public:
    SelfPointer __parent;
    SelfPointer __left;
    SelfPointer __right;

public:
    const bool isRightNode() const noexcept
    {
        assert(__parent != nullptr);
        return __parent->__right == this;
    }
    const bool isLeftNode() const noexcept
    {
        assert(__parent != nullptr);
        return __parent->__left == this;
    }
    const NodeColor getParentNodeColor() const noexcept
    {
        SelfPointer parent = this->__parent;
        if (parent == nullptr)
            return NodeColor::UNKNOW;
        return parent->getCurrentNodeColor();
    }
    const NodeColor getBrothersNodeColor() const noexcept
    {
        SelfPointer parent = this->__parent;
        if (parent == nullptr)
            return NodeColor::UNKNOW;

        SelfPointer left = parent->__left;
        SelfPointer right = parent->__right;

        if (left == this)
        {
            if (right == nullptr)
            {
                return NodeColor::UNKNOW;
            }
            else
            {
                return right->getCurrentNodeColor();
            }
        }
        if (right == this)
        {
            if (left == nullptr)
            {
                return NodeColor::UNKNOW;
            }
            else
            {
                return left->getCurrentNodeColor();
            }
        }

        assert(false);
    }
    const NodeColor getCurrentNodeColor() const noexcept
    {
        return this->__node_color;
    }
    void reverseNodeColor() const noexcept
    {
        if (this->__node_color == NodeColor::RED)
        {
            this->__node_color = NodeColor::BLOCK;
            return;
        }

        this->__node_color = NodeColor::RED;
    }

    /*
    void reverseIfColorIsRead()const noexcept;
    */

    SelfPointer getBrotherNode()
    {
        assert(__parent != nullptr);
        return __parent->__left == this ? __parent->__right : __parent->__left;
    }
    void leftRotate(SelfPointer parent, bool leftOrRight /*默认插入left*/ = true) noexcept
    {
        assert(this->__left != nullptr);
        SelfPointer left = this->__left;
        SelfPointer leftF = (left == nullptr) ? nullptr : left->__right;
        leftOrRight ? parent->__left = left : parent->__right = left;
        left->__right = this;
        this->__left = leftF;
    }

    void rightRoate(SelfPointer parent, bool leftOrRight /*默认插入left*/ = true) noexcept
    {
        assert(this->__right != nullptr);

        SelfPointer right = this->__right;
        SelfPointer leftF = right == nullptr ? nullptr : right->__left;
        leftOrRight ? parent->__left = right : parent->__right = right;
        right->__left = this;
        this->__left = leftF;
    }

public:
    Node() : __parent(nullptr), __left{nullptr}, __right{nullptr}, __key{}, __value{} {}
    Node(SelfPointer parent, keyType key_, ValueType value_) : __parent{parent}, __left{nullptr}, __right{nullptr}, __key{key_}, __value{value_} {}
    ~Node() {}
};

template <typename key, typename value>
class __Tree
{
public:
    using keyType = key;
    using ValueType = value;
    using Self = __Tree;
    using SelfPointer = Self *;
    using NodeType = Node<keyType, ValueType>;
    using NodePoinerType = NodeType *;

public:
    __Tree()
        : __size{-1},
          __height{-1},
          __node{}
    {
        this->__node.reverseNodeColor();
    }

    template <typename Campare>
    pair<keyType &, ValueType &> _find(keyType key_, Campare campare) noexcept
    {
        NodeType *node = this->__find(&this->__node, key_, this->__node.__key, campare);
        assert(node != nullptr);
        return pair<keyType &, ValueType &>(node->__key, node->__value);
    }

    template <typename Campare>
    NodePoinerType __find(NodeType *node, keyType lkey, keyType rkey, Campare campare) noexcept
    {
        NodeType *n = campare(node, lkey, rkey);

        if (n == nullptr)
        {
            return node;
        }

        return __find(n, lkey, n->__key, campare);
    }

    void insert(keyType key_, ValueType value_)
    {

        /**
          * 
          * 节点是红色或黑色。
          * 根是黑色。
          * 所有叶子都是黑色（叶子是NIL节点）。
          * 每个红色节点必须有两个黑色的子节点。（从每个叶子到根的所有路径上不能有两个连续的红色节点。）
          * 从任一节点到其每个叶子的所有简单路径都包含相同数目的黑色节点（简称黑高）。
         */

        // 根据这情况三与四来看，父节点与叔叔节点是必须被访问到的。如果我们想在遍历的过程中拿到叔叔与父亲的指针，则我们很麻烦既要判断大小 然后去遍历左右子树，最后还要判断子树是否为空，很麻烦，先不去优化

        // 情况一：
        // 插入的新节点 N 是红黑树的根节点，这种情况下，我们把节点 N 的颜色由红色变为黑色.
        // 性质2（根是黑色）被满足。同时 N 被染成黑色后，红黑树所有路径上的黑色节点数量增加一个.
        // 性质5（从任一节点到其每个叶子的所有简单路径都包含相同数目的黑色节点）仍然被满足。
        if (__size == -1 && __height == -1)
        {
            __size = 1;
            __height = 1;

            this->__node.__key = key_;
            this->__node.__value = value_;
            return;
        }

        // 情况二：
        // N 的父节点是黑色，这种情况下，性质4（每个红色节点必须有两个黑色的子节点）和性质5没有受到影响，不需要调整。
        // 备注：这种情况下，我们需要知道父节点信息，但是父节点的信息可以通过遍历得出，但是 mscv 的节点中包含父节点的情况，
        // 因此可能会有更复杂的情况需要持续的找到父节点信息。

        NodePoinerType node = this->__find(&this->__node, key_, this->__node.__key, [](NodeType *n, keyType lkey, keyType rkey) {
            return lkey < rkey ? n->__left : n->__right;
        });

        NodePoinerType newNode = new NodeType(node, key_, value_);
        node->__key > key_ ? node->left = newNode : node->__right = newNode;

        assert(node->getCurrentNodeColor() != Node::NodeColor::UNKNOW);

        if (node->getCurrentNodeColor() == Node::NodeColor::BLOCK)
        {
            // 情况二就此结束了， 父节点为黑节点，子节点为红节点，整个“黑高” 未增加，满足红黑树性质。
            return;
        }

        // if 之后,当前插入的节点的父节点为红色，仍然分成两种情况，我们需要看当前节点的叔叔节点的颜色。

        // 情况三：
        // N 的父节点是红色（节点 P 为红色，其父节点必然为黑色），叔叔节点 U 也是红色。由于 P 和 N 均为红色，所以性质4被打破，此时需要进行调整。
        if (node->getBrothersNodeColor() == Node::NodeColor::RED)
        {
            node->reverseNodeColor();
            node->getBrotherNode()->reverseNodeColor();
            node->__parent->reverseNodeColor();

            node = node->__parent;
            if (node->__parent->getCurrentNodeColor() == Node::NodeColor::BLOCK)
            {
                return;
            }

            while (node->__parent->getCurrentNodeColor() != Node::NodeColor::BLOCK)
            {
                node->getBrotherNode()->reverseNodeColor();
                node->__parent->reverseNodeColor();
                node = node->__parent;
                if (node->__parent == nullptr)
                {
                    return;
                }
            }
        }

        // 情况四：
        // 此时 N 的父节点为红色，叔叔节点为黑色。节点 N 是 P 的右孩子，且节点 P 是 G 的左孩子。
        // 此时先对节点 P 进行左旋，调整 N 与 P 的位置。接下来按照情况五进行处理，以恢复性质4。

        if (node->isRightNode() and node->__parent->isLeftNode())
        {
            node->__parent->leftRotate(node->__parent->__parent);
        }

        // 情况五：
        // N 的父节点为红色，叔叔节点为黑色。N 是 P 的左孩子，且节点 P 是 G 的左孩子。
        // 此时对 G 进行右旋，调整 P 和 G 的位置，并互换颜色。经过这样的调整后，性质4被恢复，同时也未破坏性质5。
        node->__parent->__parent->rightRoate(node->__parent->__parent->__parent, 1);
    }

    // 应该先实现这个再实现插入
    ValueType &operator[](keyType key_) noexcept
    {
    }

    long long erase(const keyType &k) noexcept
    {
    }

private:
    long long __size;
    long long __height;
    NodeType __node;
};
