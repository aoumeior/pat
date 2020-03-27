#include <iostream>

long prime_P = 61;
long prime_Q = 53;


int extended_euclidean(int y, int x)
{
	int t = 0, newt = 1;
	int r = x, newr = y;
	int temp;
	int quotient;
	while (newr != 0)
	{
		quotient = r / newr;
		temp = newt;
		newt = t - quotient * newt;
		t = temp;

		temp = newr;
		newr = r - quotient * newr;
		r = temp;
	}

	if (r > 1)
	{
		return -1213456;
	}
	if (t < 0)
	{
		t = t + x;
		return t;
	}
	if (t > 0)
		return t;
	else
		return -1245455;
}

int main()
{
    auto t = prime_P * prime_Q;
    long Euler = (prime_P - 1) * (prime_Q - 1);

    long e = 17;

    auto mm = extended_euclidean(17, 3120);

    std::cout << mm << std::endl;
}
