#include<iostream>
#include<vector>

int main()
{
    int positive_integer;
    std::cin >> positive_integer;

    std::vector<int> elevator_scheduling{positive_integer, 0};

    int t0 = 0, t1 =0;
    for (size_t i = 0; i < positive_integer; i++)
    {
        std::cin >> t1;
        elevator_scheduling[i] = t1 - t0;
        t0 = t1;
    }
    
    unsigned sum = 0;
    for (size_t i = 0; i < positive_integer; i++)
    {
        int t =  elevator_scheduling[i];

        if(t > 0)
        {
          sum += t * 6;
        }
        if(t < 0)
        {
          sum -= t * 4;
        }
    }
    sum += positive_integer * 5;

    std::cout << sum;
}