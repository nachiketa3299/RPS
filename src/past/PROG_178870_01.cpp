#include <string>
#include <vector>
#include <utility>

using namespace std;

vector<int> solution(vector<int> sequence, int k)
{

    using itype = decltype(sequence.begin());
    pair<itype, itype> min;
    min.first = sequence.begin();
    min.second = sequence.end() - 1;

    auto start = sequence.begin();
    auto end = start;

    int sum = *start;

    while (start != sequence.end())
    {
        if (sum == k)
        {
            if (end - start < min.second - min.first)
            {
                min.first = start; min.second = end;
            }

            if (start == end)
            {
                ++start; ++end; sum = *start;
            }
            else if (start < end)
            {
                sum -= *start; ++start;
            }
        }
        else if (sum < k)
        {
            if (end < sequence.end() - 1)
            {
                ++end; sum += *end;
            }
            else break;
        }
        else if (sum > k)
        {
            sum -= *start; ++start;
        }
    }


    vector<int> answer =
    {
        static_cast<int>(min.first - sequence.begin()),
        static_cast<int>(min.second - sequence.begin())
    };
    return answer;
}