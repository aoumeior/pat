#include<string>
#include<cmath>
#include<algorithm>
#include<iostream>
#include<cinttypes>
#define nav_sign 10

const char sign_table[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-'};
std::string sum_format(int32_t a, int32_t b)
{
    if(a == 0 and b == 0 or (a + b) == 0)
    {
        return std::string("0");
    }
    std::string format_res;
    int32_t res = a + b;

    bool sign = true;
    if(res < 0)
    {
        sign = false;
        res = -res;
    }

    int32_t bediv = 10;
    int dounumber = 0;
    while (res != 0)
    {
        int t = res % bediv;
        format_res.push_back(sign_table[t]);
        res /= bediv;
        if( (format_res.size() - dounumber) % 3 == 0 and res != 0)
        {
            format_res.push_back(',');
            dounumber++;
        }
    }

    std::reverse(format_res.begin(), format_res.end());
    if(sign == false)
    {
        format_res.insert(format_res.begin(), sign_table[nav_sign]);
    }
    return format_res;
    
}

int main()
{
    int32_t a, b; 
    std::cin >> a >> b;
    std::cout << sum_format(a, b) << std::endl;
    return 0;
}