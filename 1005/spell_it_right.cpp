#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include <algorithm>

std::vector<std::string> number_cover_word
{
    "zero",
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine"
};

int main()
{

    unsigned long long n, sum = 0;
    std::cin >> n;
    
    if(n == 0)
    {
        std::cout << number_cover_word[0];
        return 0;
    }

    while (n != 0)
    {
        sum += n % 10;
        n = n / 10;
    }
    
    std::vector<std::string> res;
    res.insert(res.begin(), number_cover_word[sum % 10]);

    sum = sum / 10;

    while (sum != 0)
    {
        res.insert(res.begin(), number_cover_word[sum % 10]);
        sum = sum / 10;
    }
    
    std::cout << *res.begin();
    
    std::for_each(res.begin() + 1, res.end(), [](const std::string& s){
        std::cout << " " << s;
    });
    
    return 0;
}