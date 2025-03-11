#include <iostream>
#include <string>
#include <vector>
#include <format>

using namespace std;



// 12:00 - 28 (28)

class Solution 
{
public:

    /// @return `true` if `s` is palindrome, `false` if not.
    bool isPalindrome(string s) 
	{
		// return isPalindromeRecursive(s, 0, s.size() - 1);
		return isPalindromeIterative(s);
    }

	bool isPalindromeIterative(const string& str)
	{

		auto start = str.begin();
		auto end = --str.end();

		while (start <= end)
		{
			if (!isalnum(*start))
			{
				++start;
				continue;
			}

			if (!isalnum(*end))
			{
				--end;
				continue;
			}

			if (tolower(*start) != tolower(*end))
			{
				return false;
			}
			else
			{
				++start;
				--end;
			}
		}

		return true;
	}

	bool isPalindromeRecursive(const string& str, size_t start, size_t end)
	{
		while ((!isalnum(str[start]) || isspace(str[start])) && start < str.size() - 1)
		{
			++start;
		}

		while ((!isalnum(str[end]) || isspace(str[end])) && end > start)
		{
			--end;
		}

		// cout << format("start: {}({}),  end: {}({})", start, str[start], end, str[end]) << endl;;

		if (start >= end)
		{
			return true;
		}
		else
		{

			// cout << "Comparing " << str[start] << " and " << str[end] << endl;

			if (tolower(str[start]) == tolower(str[end]))
			{

				return isPalindromeRecursive(str, start + 1, end - 1);
			}
			else 
			{
				return false;
			}
		}
	}
};

int main()
{
	auto s = Solution();

	auto v = vector<string>
	{
		"abcba",
		"A man, a plan, a canal: Panama",
		"race a car",
		" "
	};

	for(auto const& e : v)
	{
		cout << boolalpha << s.isPalindrome(e) << endl;
	}
}
