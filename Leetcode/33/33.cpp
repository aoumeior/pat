#include <vector>
#include <algorithm>
#include <iterator>

class Solution
{
public:
    int search(std::vector<int> &nums, int target)
    {
        int mid = nums.size() / 2;

        if (nums[0] > nums[mid])
        {
            auto it = std::upper_bound(nums.begin() + mid, nums.end(), target);
            if (it != nums.end())
                return std::distance(it, nums.end());
        }
    }
};