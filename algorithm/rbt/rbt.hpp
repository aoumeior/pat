#include <type_traits>
#include <cmath>
#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>

#define is ==
#define Color(x) (x) == nullptr ? NodeType::NodeColor::BLOCK : (x)->getCurrentNodeColor()

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
    void setLeftNode(SelfPointer node) noexcept
    {
        this->__left = node;
    }
    void setRightNode(SelfPointer node) noexcept
    {
        this->__right = node;
    }

    void onSwap(Node *n) noexcept
    {
        if (n == nullptr or n == this)
            return;
        std::swap(this->__key, n->__key);
        std::swap(this->__value, n->__value);
    }
    const bool isRoot() const noexcept
    {
        return this->__parent == nullptr;
    }
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
            return NodeColor::BLOCK;

        SelfPointer left = parent->__left;
        SelfPointer right = parent->__right;

        if (left == this)
        {
            if (right == nullptr)
            {
                return NodeColor::BLOCK;
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

    void settingNodeColorBlock() const noexcept
    {
        this->__node_color = NodeColor::BLOCK;
    }

    void settingNodeColorRed() const noexcept
    {
        this->__node_color = NodeColor::RED;
    }

    SelfPointer getLeftNode() noexcept
    {
        return this->__left;
    }

    SelfPointer getRightNode() noexcept
    {
        return this->__right;
    }

    bool hasTwoNode() const noexcept
    {
        return this->__right != nullptr or this->__left != nullptr;
    }

    bool hasNode() const noexcept
    {
        return this->__right != nullptr or this->__left != nullptr;
    }
    inline bool hasRight() const noexcept
    {
        this->__right == nullptr;
    }
    inline bool hasLeft() const noexcept
    {
        this->__left == nullptr;
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
    void tryReverserBrotherNodeColor() const noexcept
    {
        SelfPointer node = this->getBrotherNode();
        if (node == nullptr)
        {
            return;
        }
        node->reverseNodeColor();
    }
    bool isBlockNode() const noexcept
    {
        return this->__node_color == NodeColor::BLOCK;
    }

    void setNodeColor(NodeColor nodeColor) const noexcept
    {
        this->__node_color = nodeColor;
    }
    void onSwapNodeColor(Node *node)
    {
        auto t = node->getCurrentNodeColor();
        node->setNodeColor(this->getCurrentNodeColor());
        this->setNodeColor(t);
    }

    bool isRedNode() const noexcept
    {
        return this->__node_color == NodeColor::RED;
    }
    /*
    void reverseIfColorIsRead()const noexcept;
    */
    inline SelfPointer getParentNode() const noexcept
    {
        return this->__parent;
    }
    inline SelfPointer getBrotherNode() const noexcept
    {
        assert(__parent != nullptr);
        return __parent->__left == this ? __parent->__right : __parent->__left;
    }
    inline void setParentNode(SelfPointer node) noexcept
    {
        this->__parent = node;
    }
    SelfPointer leftRotate(SelfPointer parent, bool color /*默认插入left*/ = true) noexcept
    {
        if (color)
        {
            this->reverseNodeColor();
            __parent->reverseNodeColor();
        }

        SelfPointer g = __parent->getParentNode();

        __parent->__right = this->__left;
        if (__parent->__right not_eq nullptr)
            __parent->__right->setParentNode(__parent);

        this->__left = __parent;
        this->__left->setParentNode(this);

        if (g not_eq nullptr)
        {
            g->__left == __parent ? g->__left = this : g->__right = this;
            this->setParentNode(g);
            return nullptr;
        }
        this->setParentNode(nullptr);
        return this;
    }

    SelfPointer rightRoate(SelfPointer parent, bool color /*默认插入left*/ = true) noexcept
    {
        SelfPointer g = __parent->getParentNode();
        if (color)
        {
            this->reverseNodeColor();
            __parent->reverseNodeColor();
        }

        __parent->__left = this->__right;
        if (__parent->__left not_eq nullptr)
            __parent->__left->setParentNode(__parent);

        this->__right = this->__parent;
        this->__right->setParentNode(this);
        if (g not_eq nullptr)
        {
            g->__left == __parent ? g->__left = this : g->__right = this;

            this->setParentNode(g);
            return nullptr;
        }
        this->setParentNode(nullptr);
        return this;
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
          __node{new NodeType{}}
    {
        this->__node->reverseNodeColor();
    }

    Node<key, value> *getSuccessorNode(Node<key, value> *node)
    {

        if (node is nullptr)
            return nullptr;

        if (not node->hasRight()) // 如果该节点没有右子树,那么要分两种情况:
        // 如果node结点没有右子树,判断当前结点node是不是它父亲的左孩子，如果是，那么它父亲就是它的后继；
        {
            if (!node->hasRight() and not node->isRoot() and node->isLeftNode())
                return node;

            if (!node->hasRight() and not node->isRoot() and node->isRightNode())
            {
                node = node->getParentNode();
                assert(not node->isRoot());

                while (!node->isRoot())
                {
                    if (!node->isRoot() and node->getParentNode()->hasLeft() and node->isLeftNode())
                    {
                        return node->getParentNode();
                    }

                    node = node->getParentNode();
                }

                return node;
            }

            assert(false);
        }
        else
        {
            node = node->getRightNode();

            while (node not_eq nullptr)
            {
                if (not node->hasLeft())
                    return node;

                node = node->getLeftNode();
            }

            assert(false);
        }
    }

    template <typename Campare>
    pair<keyType &, ValueType &> _find(keyType key_, Campare campare) noexcept
    {
        NodeType *node = this->__find(this->__node, key_, this->__node->__key, campare);
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
          * 1. 节点是红色或黑色。
          * 2. 根是黑色。
          * 3. 所有叶子都是黑色（叶子是NIL节点）。
          * 4. 每个红色节点必须有两个黑色的子节点。（从每个叶子到根的所有路径上不能有两个连续的红色节点。）
          * 5. 从任一节点到其每个叶子的所有简单路径都包含相同数目的黑色节点（简称黑高）。
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

            this->__node->__key = key_;
            this->__node->__value = value_;
            return;
        }

        // 情况二：
        // N 的父节点是黑色，这种情况下，性质4（每个红色节点必须有两个黑色的子节点）和性质5没有受到影响，不需要调整。
        // 备注：这种情况下，我们需要知道父节点信息，但是父节点的信息可以通过遍历得出，但是 mscv 的节点中包含父节点的情况，
        // 因此可能会有更复杂的情况需要持续的找到父节点信息。

        NodePoinerType node = this->__find(this->__node, key_, this->__node->__key, [](NodeType *n, keyType lkey, keyType rkey) {
            return lkey < rkey ? n->__left : n->__right;
        });

        NodePoinerType newNode = new NodeType(node, key_, value_);

        auto isRight = node->__key < key_;
        isRight ? node->__right = newNode : node->__left = newNode;

        assert(node->getCurrentNodeColor() != NodeType::NodeColor::UNKNOW);
        this->__size++;
        if (node->getCurrentNodeColor() == NodeType::NodeColor::BLOCK)
        {
            // 情况二就此结束了， 父节点为黑节点，子节点为红节点，整个“黑高” 未增加，满足红黑树性质。
            return;
        }

        // if 之后,当前插入的节点的父节点为红色，仍然分成两种情况，我们需要看当前节点的叔叔节点的颜色。

        // 情况三：
        // N 的父节点是红色（节点 P 为红色，其父节点必然为黑色），叔叔节点 U 也是红色。由于 P 和 N 均为红色，所以性质4被打破，此时需要进行调整。
        if (node->getBrothersNodeColor() == NodeType::NodeColor::RED)
        {
            bool sonIsleft = false;

            node->reverseNodeColor();
            node->tryReverserBrotherNodeColor();

            node = node->getParentNode();
            if (node->isRoot())
                return;
            node->reverseNodeColor();
            sonIsleft = node->isLeftNode();
            // 避免级联红色

            while ((node = node->getParentNode())->getCurrentNodeColor() != NodeType::NodeColor::BLOCK)
            {
                if (node->isRoot())
                    return;
                if (node->getBrothersNodeColor() == NodeType::NodeColor::RED)
                {
                    node->reverseNodeColor();
                    node->tryReverserBrotherNodeColor();

                    node = node->getParentNode();
                    if (node->isRoot())
                        return;
                    node->reverseNodeColor();
                    sonIsleft = node->isLeftNode();
                    continue;
                }

                if (sonIsleft and
                    !node->isRoot() and
                    node->isLeftNode() and
                    node->getBrothersNodeColor() == NodeType::NodeColor::BLOCK)
                {
                    auto unknowRoot = node->rightRoate(nullptr, 1);

                    if (unknowRoot not_eq nullptr)
                    {

                        this->__node = unknowRoot;
                    }
                    return;
                }
            }

            return;
        }

        // 情况四：
        // 此时 N 的父节点为红色，叔叔节点为黑色。节点 N 是 P 的右孩子，且节点 P 是 G 的左孩子。
        // 此时先对节点 P 进行左旋，调整 N 与 P 的位置。接下来按照情况五进行处理，以恢复性质4。

        if (isRight and node->isRightNode())
        {
            auto unknowRoot = node->leftRotate(nullptr);

            if (unknowRoot not_eq nullptr)
            {

                this->__node = unknowRoot;
            }

            return;
        }

        if (!isRight and node->isRightNode())
        {

            node = node->__left;

            auto unknowRoot = node->rightRoate(nullptr, false);

            if (unknowRoot not_eq nullptr)
            {

                this->__node = unknowRoot;
            }

            unknowRoot = node->leftRotate(nullptr);

            if (unknowRoot not_eq nullptr)
            {

                this->__node = unknowRoot;
            }

            return;
        }
        // 情况五：
        // N 的父节点为红色，叔叔节点为黑色。N 是 P 的左孩子，且节点 P 是 G 的左孩子。
        // 此时对 G 进行右旋，调整 P 和 G 的位置，并互换颜色。经过这样的调整后，性质4被恢复，同时也未破坏性质5。
        node->rightRoate(nullptr);
    }

    // 应该先实现这个再实现插入
    ValueType &operator[](keyType key_) noexcept
    {
    }

    template <typename Campare>
    NodePoinerType __has(NodeType *node, keyType lkey, keyType rkey, Campare campare) noexcept
    {
        NodeType *n = campare(node, lkey, rkey);

        if (n == node or n == nullptr)
        {
            return n;
        }

        return __has(n, lkey, n->__key, campare);
    }

    long long erase(const keyType k) noexcept
    {

        NodePoinerType node = this->__has(this->__node, k, this->__node->__key,
                                          [](NodeType *n, keyType lkey, keyType rkey) {
                                              return lkey == rkey ? n : (lkey < rkey ? n->__left : n->__right);
                                          });
        std::cout << node->__key << node->__value;

        if (node->isRedNode() and not node->hasNode())
        {
            NodePoinerType parent = node->getParentNode();
            node->isLeftNode() ? (parent->__left = nullptr) : (parent->__right = nullptr);
            delete node;
        }

        if (node->isBlockNode() and not node->hasNode())
        {
            this->repairB(node);
        }

        if (/* node->getCurrentNodeColor() == NodeType::NodeColor::BLOCK and */
            (node->hasTwoNode()) and
            /* Color(node->getLeftNode()) == NodeType::NodeColor::BLOCK and
            Color(node->getRightNode()) == NodeType::NodeColor::BLOCK*/
        )
        {
            decltype(node) rawNode = getSuccessorNode(node);
            node->onSwap(rawNode);
            if (!rawNode->hasNode() and rawNode->isBlockNode())
            {

                repairB(rawNode);
                return;
            }

            node = rawNode;
        }

        if (/* node->getCurrentNodeColor() == NodeType::NodeColor::BLOCK and */
            (node->hasRight() ^ node->hasLeft()))
        {
            decltype(node) lr = node->getLeftNode() != nullptr ? node->getLeftNode() : node->getRightNode();
            assert(lr not_eq nullptr);

            if (lr->isRedNode())
            {
                lr->reverseNodeColor();
                lr->onSwap(node);
                lr->setParentNode(node->getParentNode());
                node->isLeftNode() ? node->getParentNode()->setLeftNode(lr) : rawNode->getParentNode()->setRightNode(lr);
                delete lr;
                return;
            }

            repairB(lr);
            return;
        }
    }

private:
    void repairB(NodePoinerType node)
    {

        // 兼容左右
        if (!node->isRoot() and
            node->getBrothersNodeColor() is NodeType::NodeColor::BLOCK and
            not node->getBrotherNode()->hasNode())
        {
            decltype(node) parent = node->getParentNode();
            node->isRightNode() ? parent->setRightNode(nullptr) : parent->setLeftNode(nullptr);
            
            if (parent->isRedNode())
            {
                node->getBrotherNode()->onSwapNodeColor(parent);
                delete node;
                return;
            }

            node->getBrotherNode()->reverseNodeColor();
            delete node;
        }

        if (!node->isRoot() and
            node->getBrothersNodeColor() is NodeType::NodeColor::BLOCK and
            node->getBrotherNode())
        {
            decltype(node) g = node->getParentNode();
            decltype(node) brother = node->getBrotherNode();
            decltype(node) brotherSonLeft = brother->getLeftNode();
            decltype(node) brotherSonRight = brother->getRightNode();
            decltype(node->getCurrentNodeColor()) brotherSonLeftColor = Color(brotherSonLeft);
            auto brotherSonRightColor = Color(brotherSonRight);
            auto brotherSonLeftColor = Color(brotherSonRight);

            if (node->isLeftNode())
            {
                if (brotherSonRightColor is NodeType::NodeColor::RED)
                {
                    brotherSonRight->rightRoate(null);
                }

                if (brotherSonLeftColor is NodeType::NodeColor::RED)
                {
                    brother->leftRotate(nullptr, false);
                    brotherSonRight->settingNodeColorBlock();
                    brother->onSwapNodeColor(g);
                    g->setRightNode(nullptr);
                    delete node;
                    return;
                }
            }

            assert(node->isRightNode());

            if (brotherSonLeftColor is NodeType::NodeColor::RED)
            {
                brotherSonLeft->rightRoate(null);
            }

            if (brotherSonRightColor is NodeType::NodeColor::RED)
            {
                brother->rightRoate(nullptr, false);
                brotherSonLeft->settingNodeColorBlock();
                brother->onSwapNodeColor(g);
                g->setRightNode(nullptr);
                delete node;
                return;
            }
        }

        if (!node->isRoot() and
            node->getBrothersNodeColor() is NodeType::NodeColor::RED)
        {

            NodePoinerType brother = node->getBrotherNode();
            NodePoinerType parent = node->getParentNode();

            brother->onSwapNodeColor(parent);

            if (brother->isRightNode())
            {
                brother->leftRotate(nullptr, false);
                parent->setLeftNode(nullptr);
            }
            else
            {
                brother->rightRoate(nullptr, false);
                parent->setRightNode(nullptr);
            }

            delete node;

            return;
        }
    }

private:
    long long __size;
    long long __height;
    NodePoinerType __node;
};
