#include <bits/stdc++.h>

int main()
{
    std::int32_t k;
    std::cin >> k;

    int32_t i = 0;
    int32_t min = 0;
    std::vector<int32_t> subsequence(k);
    for (; i < k; i++)
    {
        std::cin >> subsequence[i];
        if (subsequence[i] < 0)
            min += subsequence[i];
    }

    int32_t sum = min;
    int32_t b = 0;
    int32_t e = 0;

    int32_t tsum = 0;
    int32_t b1 = 0;

    int32_t fu = 0;
    for (i = 0; i < k; i++)
    {
        tsum += subsequence[i];

        if (tsum < 0)
        {
            b1 = i + 1;
            tsum = 0;
        }
        else if (tsum > sum)
        {
            sum = tsum;
            b = b1;
            e = i;
        }
    }
    if (sum < 0)
    {
        int x = subsequence[0];
        int y = subsequence[k - 1];
        std::cout << "0 " << x << " " << y << std::endl;
    }
    else
        std::cout << sum << " " << subsequence[b] << " " << subsequence[e] << std::endl;
    return 0;
}