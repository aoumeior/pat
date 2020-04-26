#include <vector>
#include <limits>
#include <cmath>
#include <algorithm>

class Solution
{
public:
    void coinChange(std::vector<int> &coins, int amount, int c_index, int count, int &ans)
    {
        if (amount == 0)
        {
            ans = std::min(ans, count);
            return;
        }
        if (c_index == coins.size())
            return;

        for (int k = amount / coins[c_index]; k >= 0 && k + count < ans; k--)
        {
            coinChange(coins, amount - k * coins[c_index], c_index + 1, count + k, ans);
        }
    }

    int coinChange(std::vector<int> &coins, int amount)
    {
        if (amount == 0)
            return 0;
        std::sort(coins.rbegin(), coins.rend());
        int ans = std::numeric_limits<int>::max();
        coinChange(coins, amount, 0, 0, ans);
        return ans == std::numeric_limits<int>::max() ? -1 : ans;
    }
};