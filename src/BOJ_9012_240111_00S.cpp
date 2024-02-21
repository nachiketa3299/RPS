// title: 백준 9012 괄호 S4
// date: 17:02 17:41 90
// 근데 보고 푼거라 다시 풀어야함. 스택에 대해 알 수 있는 좋은 문제였음.
#define PS_DEBUG
//#undef PS_DEBUG

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <stack>

#define P_S '('
#define P_E ')'

using namespace std;

void IsVPS(const string& str) {
    stack<char> no_empty;
    for (const auto& c: str) {
        switch(c) {
            case P_S:
                no_empty.push(c);
                break;
            case P_E:
                if (no_empty.empty()) {
                    cout << "NO\n";
                    return;
                }
                else {
                    no_empty.pop();
                    break;
                }
        }
    }
    if (no_empty.empty()) {
        cout << "YES\n";
        return;
    }
    else {
        cout << "NO\n";
        return;
    }
}

auto main() -> int
{
    {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr); cout.tie(nullptr);
    }

    int N; cin >> N;
    vector<string> tcs(N);
    for_each(tcs.begin(), tcs.end(), [](auto& str){ cin >> str; });
    function<void(const string&)> lmb = &IsVPS;
    for_each(tcs.cbegin(), tcs.cend(), lmb);
    return 0;
}