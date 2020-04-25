#include <vector>
#include <algorithm>

class Solution
{
public:
    int rob(std::vector<int> &nums)
    {
        if (nums.size() == 0)
            return 0;
        if (nums.size() == 1)
            return nums[0];

        std::vector<int> res(nums.size());
        res[0] = nums[0];
        res[1] = std::max(nums[0], nums[1]);
        for (int i = 2; i < nums.size(); i++)
        {
            res[i] = std::max(res[i - 2] + nums[i], res[i - 1]);
        }
        return res[nums.size() - 1];
    }
};

int main()
{
}