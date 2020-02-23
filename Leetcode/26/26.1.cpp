#include<algorithm>
#include<vector>

class Solution
{
public:
    int removeDuplicates(std::vector<int>& nums) {
            return removeDuplicates(nums.begin(), nums.end(), nums.begin()) - nums.begin();
    }
public:
    template<typename Init, typename OutIt>
    OutIt removeDuplicates(Init first, Init last, OutIt output)
    {
        while (first != last)
        {
            *output++ = *first;
            first = std::upper_bound(first, last, *first);
        }
        return output;
    }
};
