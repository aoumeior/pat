#include <vector>
#include <cstdint>
// 时间复杂度：O(n)，树形递归的大小可以达到 n。
// 空间复杂度：O(n)，递归树的深度可以达到 n。

class Solution
{
private:
    std::vector<uint32_t> memo;

public:
    int climbStairs(int n)
    {
        memo = std::vector<uint32_t>(n + 1);
        return climb_Stairs(0, n);
    }

private:
    int climb_Stairs(int i, int n)
    {
        if (i > n)
        {
            return 0;
        }
        if (i == n)
        {
            return 1;
        }

        if (memo[i] > 0)
            return memo[i];
        memo[i] = climb_Stairs(i + 1, n) + climb_Stairs(i + 2, n);
        return memo[i];
    }
};

int main()
{
    Solution solution;
    auto R = solution.climbStairs(35);
}