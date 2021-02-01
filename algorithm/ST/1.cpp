#include <limits.h>
#include <stdlib.h>
#include <cmath>
#include <malloc.h>
#include <algorithm>

// bug: vscode: '__builtin_logf' isn't constexpr
float log2(float __x)
{
    static float __e = std::log(2.0f);
    return std::log(__x) / __e;
}
int rmq_init(int ***rmq, int raw[], size_t length);
int min(int, int);

int main()
{

    int **rmq = NULL;
    int raw[] = {4, 1, 3, 7, 5, 8};

    rmq_init(&rmq, raw, 6);
}

/// 预处理：

/// 设A[i]是要求区间最值的数列，F[i, j]表示从第i个数起连续2^j个数中的最大值。（DP的状态）

int rmq_init(int ***rmq, int raw[], size_t length)
{
    *rmq = (int **)malloc(sizeof(int *) * length + 1);

    (*rmq)[0] = (int *)malloc(sizeof(int) * length);

    for (int i = 0; i < length; i++)
    {
        (*rmq)[0][i] = raw[i];
    }

    for (int i = 1; i <= length; i++)
    {
        (*rmq)[i] = (int *)malloc(sizeof(int) * (1 + (int)log2(length - i + 0.0)));
        (*rmq)[i][0] = raw[i];
    }

    for (int j = 1; (1 << j) <= length; j++)
        for (int i = 1; i + (1 << j) - 1 <= length; i++)
            (*rmq)[i][j] = min((*rmq)[i][j - 1], (*rmq)[i + (1 << j - 1)][j - 1]);
}
// ST算法，是一个快速求区间最值的离线算法，预处理时间复杂度O（n*log(n)），查询O(1)，所以是一个很快速的算法。
// 当然这个问题用线段树同样能够解决，算法复杂度为：O(N)~O(logN)。
// https://www.cnblogs.com/yoke/p/6949838.html
int min(int left, int right)
{
    return left < right ? left : right;
}
