#include <string>
#include <stack>
using namespace std;

// 10:39 - 10:56 (17m)

class Solution 
{
public:
	// 1 <= s.length <= 10^4
	// s consists of parentheses only '()[]{}'
	bool isValid(string s) 
	{
		auto openingStack = stack<char>();

		for (auto const& c: s) 
		{
			if (c == '(' || c == '{' || c == '[') 
			{
				// 열리는 거면 다 넣는다
				openingStack.push(c);
			}
			else 
			{
				// 닫히는 것이 들어옴

				// 만일, s = "]]" 같이 열리는 것이 들어오지 않았는데 닫힌 것이 먼저 들어온 거면, 바로 유효하지 않음 처리
				// 이 시점에 스택이 비어 있음
				if (openingStack.empty()) 
				{
					return false;
				}

				// 가장 최근에 들어온 열린 것이 무엇인지 캡처
				auto const& recentOpening  = openingStack.top();
				auto isMatchingPairWithLatest = bool {};

				// 종류 별로 맞는 짝이 들어와야 함
				if (c == ')') 
				{
					isMatchingPairWithLatest = recentOpening == '(';
				}
				else if (c == '}') 
				{
					isMatchingPairWithLatest = recentOpening == '{';
				}
				else if (c == ']') 
				{
					isMatchingPairWithLatest = recentOpening == '[';
				}

				// 하나라도 쌍이 안 맞으면 전체가 오염된 것이므로, 더이상 볼 필요가 없음
				if (!isMatchingPairWithLatest) 
				{
					return isMatchingPairWithLatest;
				} 
				// 맞는 짝이 들어 온 거면 스택에서 제거함
				else 
				{
					openingStack.pop();
				}
			}
		}

		// 반복문을 무사히 빠져 나왔으면, 스택이 비어 있는지 확인 해야함
		// 스택이 비어 있지 않은 예는 s = "[[]" 임. 이건 유효하지 않음
		auto const isAllPairMatched = openingStack.empty();
		return isAllPairMatched;
	}
};
