#include <iostream>

using namespace std;

int main()
{
	int X; cin >> X; // in [1, 10'000'000]

	int sum = 0;

	int start = 1;
	int count = 1;

	while (true)
	{
		while (sum < X)
		{
			sum += start;
			count ++;
		}
	}
}