#include<vector>
#include<algorithm>

class Solution {
public:
    int lengthOfLIS(std::vector<int>& nums) {
        int n=(int)nums.size();
        if (n == 0) return 0;
        std::vector<int> dp(n, 0);
        for (int i = 0; i < n; ++i) {
            dp[i] = 1;
            for (int j = 0; j < i; ++j) {
                if (nums[j] < nums[i]) {
                    dp[i] = std::max(dp[i], dp[j] + 1);
                }
            }
        }
        return *max_element(dp.begin(), dp.end());
    }
};