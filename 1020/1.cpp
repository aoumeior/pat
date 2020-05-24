#include <cstdio>
#include <cinttypes>
#include <cstdint>
#include <memory>
#include <vector>
#include <algorithm>

// 因为后序的最后一个总是根结点，令i在中序中找到该根结点，则i把中序分为两部分，左边是左子树，右边是右子树。
// 因为是输出先序（根左右），所以先打印出当前根结点，然后打印左子树，再打印右子树
// 左子树在后序中的根结点为root – (end – i + 1)，即为当前根结点-(右子树的个数+1)。
// 左子树在中序中的起始点start为start，末尾end点为i – 1.右子树的根结点为当前根结点的前一个结点root – 1，
// 右子树的起始点start为i+1，末尾end点为end。
struct Node
{
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
};

class tree_traversals
{
public:
    tree_traversals(const std::vector<uint32_t> &post, std::vector<uint32_t> &in, uint32_t size)
        : post_(post),
          in_(in),
          size_(size)
    {
    }

    const tree_traversals &operator()() const
    {
        pre(size_ - 1, 0, size_ - 1);
        return *this;
    }

    void printf_first() const
    {
        std::printf("%" PRIu32, first_[0]);
        for (size_t i = 1; i < size_; i++)
        {
            std::printf(" %" PRIu32, first_[i]);
        }
    }

private:
    void pre(int root, int start, int end) const
    {
        if (start > end)
            return;
        int i = start;
        while (i < end && in_[i] != post_[root])
        {
            i++;
        }
        first_.push_back(post_[root]);
        pre(root - 1 - end + i, start, i - 1);
        pre(root - 1, i + 1, end);
    }

private:
    const std::vector<std::uint32_t> &post_;
    const std::vector<std::uint32_t> &in_;
    std::uint32_t size_;
    mutable std::vector<std::uint32_t> first_;
};

int main(int argc, char const *argv[])
{
    std::uint32_t node_number;

    std::scanf("%" SCNu32, &node_number);

    std::vector<uint32_t> postorder_sequence(node_number);
    std::vector<uint32_t> inorder_sequence(node_number);

    for (size_t i = 0; i < node_number; i++)
    {
        std::scanf("%" SCNu32, &(postorder_sequence[i]));
    }

    for (size_t i = 0; i < node_number; i++)
    {
        std::scanf("%" SCNu32, &(inorder_sequence[i]));
    }

    auto cc = tree_traversals(postorder_sequence, inorder_sequence, node_number);
    cc().printf_first();

    return 0;
}