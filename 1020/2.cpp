#include <cstdio>
#include <vector>
#include <map>
using namespace std;


// 与后序中序转换为前序的代码相仿（无须构造二叉树再进行广度优先搜索～），只不过加一个变量index，
// 表示当前的根结点在二叉树中所对应的下标（从0开始），所以进行一次输出先序的递归过程中，
// 就可以把根结点下标index及所对应的值存储在map<int, int> level中，map是有序的会根据index从小到大自动排序，
// 这样递归完成后level中的值就是层序遍历的顺序
vector<int> post, in;
map<int, int> level;
void pre(int root, int start, int end, int index)
{
    if (start > end)
        return;
    int i = start;
    while (i < end && in[i] != post[root])
        i++;
    level[index] = post[root];
    pre(root - 1 - end + i, start, i - 1, 2 * index + 1);
    pre(root - 1, i + 1, end, 2 * index + 2);
}
int main()
{
    int n;
    scanf("%d", &n);
    post.resize(n);
    in.resize(n);
    for (int i = 0; i < n; i++)
        scanf("%d", &post[i]);
    for (int i = 0; i < n; i++)
        scanf("%d", &in[i]);
    pre(n - 1, 0, n - 1, 0);
    auto it = level.begin();
    printf("%d", it->second);
    while (++it != level.end())
        printf(" %d", it->second);
    return 0;
}