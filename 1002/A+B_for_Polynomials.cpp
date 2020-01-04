#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h> 
#include <iomanip>
int main()
{
	size_t i;
	std::map<int, double> A1;
	std::map<int, double> A2;
	std::vector<int> temp;
	std::cin >> i;
	for (int c = i; c > 0; c--)
	{
		int a;
		double b;
		std::cin >> a;
		std::cin >> b;
		A1.insert({ a, b });
	}
	std::cin >> i;
	for (int c = i; c > 0; c--)
	{
		int a;
		double b;
		std::cin >> a;
		std::cin >> b;
		A2.insert({ a, b });
	}

	for (auto& it : A1)
	{
		temp.push_back(it.first);
		if (A2.find(it.first) != A2.end())
		{
			it.second += A2[it.first];
			if (fabs(it.second) <= 0)
				A1.erase(it.first);
		}
	}

	for (auto& it : A2)
	{
		if (std::find(temp.begin(), temp.end(), it.first) != temp.end())
			continue;
		if (fabs(it.second) > 0)
			A1.insert({it.first,it.second});
	}

	std::cout << A1.size();
	std::for_each(A1.rbegin(), A1.rend(),
		[](std::pair<const int, double > it) {
		std::cout << ' ' << it.first << ' ' << std::fixed << std::setprecision(1) << it.second;
	});
}