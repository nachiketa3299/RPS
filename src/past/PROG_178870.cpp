#include <string>
#include <vector>
#include <utility>

using namespace std;

vector<int> solution(vector<int> sequence, int k)
{
    pair<decltype(sequence.begin()), decltype(sequence.end())> min;
    min.first = sequence.begin();
    min.second = sequence.end() - 1;

    for (auto start = sequence.begin(); start != sequence.end(); ++start)
    {
        int sum = *start;
        for (auto end = start; end != sequence.end(); ++end)
        {
            if (sum == k && end - start < min.second - min.first)
            {
                min.first = start;
                min.second = end;
                break;
            }
            sum += *end;
        }
    }
    vector<int> answer = { *min.first, *min.second };
    return answer;
}

int main(void)
{
    vector<int> v = { 1, 2, 3, 4, 5 };
    int k = 7;
    solution(v, k);
}