#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>

bool isprime(int key);
int reverse(int key, int radix);

int main(void)
{
    int temp, radix;
    while (true)
    {
        std::scanf("%d", &temp);
        if (temp < 0)
        {
            break;
        }
        std::scanf("%d", &radix);
        if (!isprime(temp))
        {
            puts("No");
            continue;
        }
        temp = reverse(temp, radix);
        if (isprime(temp))
        {
            puts("Yes");
        }
        else
        {
            puts("No");
        }
    }
    return 0;
}

bool isprime(int key)
{
    if (key <= 1)
    {
        return false;
    }
    int upper = (int)std::sqrt(1.0 * key);
    for (int i = 2; i < upper + 1; i++)
    {
        if (key % i == 0)
        {
            return false;
        }
    }
    return true;
}

int reverse(int key, int radix)
{
    int rever = 0;
    while (key)
    {
        rever = rever * radix + key % radix;
        key /= radix;
    }
    return rever;
}