// 가장 큰 수 [[2023-10-25T15:38, 2023-10-25T17:32]]
// 0 또는 양의 정수가 주어짐, 정수를 이어서 만들 수 있는 가장 큰 수
// 예) [6, 10, 2] 라면 [6102, 6210, 1062, 1026, 2610, 2106]을 만들 수 있다. 여기서 가장 큰 수는 6210
// 주어지는 정수의 개수 N은 [1, 1e5]고, 정수 벡터로 주어짐
// 주어지는 정수 e 는 [0, 1e3]이다.
// 반환하는 가장 큰 정수는 문자열로

// 브루트 포스로?
// 가능한 모든 정수는 N!개가 나오겠지 당연히 이거 만드는데 O(N!) 여기서 큰거 찾는건 아마도 O(N) 그러니까 O(N! + N)인듯 이렇게 풀면 시간 초과가 나와야 정상
// >> 아마도? 가장 큰 수를 만들어내는 규칙이 있음 <<
// 정수를 e라고 하면 e의 자릿수가 모두 같다면 e들을 내림차순으로 그냥 정렬하면 그만임
// 근데 e의 자릿수가 달라서 문제임 심지어 [0, 1e3]이며, 0도 포함함.
// e의 최상위 자릿수를 e.max_digit 이라고 하면 e.max_digit 순으로 정렬하면 되지 않을까?

#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

struct Integer
{
public:
    Integer(int val): val(val) 
    {
        for (int i = this->val; i != 0; i /= 10) 
            this->all_digits.push(i % 10);
        return;
    };
public:
    int val;
    stack<int> all_digits;
public:
    friend bool operator<(const Integer& oth1, const Integer& oth2) 
    { 
        if (oth1.val == oth2.val) return false;

        stack<int> d1 = oth1.all_digits;
        stack<int> d2 = oth2.all_digits;

        auto cd1 = d1.top();
        auto cd2 = d2.top();

        while (true)
        {

            if (cd1 == cd2)
            {
                if (d1.size() <= 1) cd1 = cd1;
                else { d1.pop(); cd1 = d1.top(); }

                if (d2.size() <= 1) cd2 = cd2;
                else { d2.pop(); cd2 = d2.top(); }
            }
            else
            {
                return cd1 < cd2;
            }
        }
    };
};

string solution(vector<int> numbers)
{
    string answer = "";
    priority_queue < Integer, vector<Integer>, less<Integer>> pq;

    for (const auto& integers : numbers) 
        pq.push(Integer(integers));

    while (!pq.empty()) 
    { 
        // 처음 넣는데 숫자가 그냥 0이면 암것도 하지마셈
        if (answer.empty() && pq.top().val == 0) pq.pop();
        else 
        {
            answer += to_string(pq.top().val); 
            pq.pop(); 
        }
    }
    // 걍 전부다 0이면 0 해줘야함
    if (answer.empty()) answer = "0";
    return answer;
}

#include <iostream>

int main(void)
{

    vector<vector<int>> numbers_vec =
    {
        {6, 10, 2},
        {3, 30, 34, 5, 9},
        {30, 30},
        {0, 0, 0},
        {979, 97, 978, 81, 818, 817}
    };
    vector<string> answer_vec =
    {
        "6210",
        "9534330",
        "3030",
        "0",
        "9799797881881817"
    };
    int tc_cnt = numbers_vec.size();
    for (int i = 0; i < tc_cnt; ++i)
    {

        if (solution(numbers_vec[i]) == answer_vec[i]) 
            cout << "Correct\n";
        else 
            cout << "Incorrect: " << answer_vec[i] << " != " << solution(numbers_vec[i]) << "\n";
    }
    return 0;
}
