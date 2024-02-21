#include <string>
#include <vector>
#include <utility>
using namespace std;

struct Sub_Seq
{
    vector<int>::iterator start;
    vector<int>::iterator end;
    size_t len() const { return distance(this->start, this->end); };
    bool is_same() const { return this->start == this->end; };
};

vector<int> solution(vector<int> sequence, int k)
{
    vector<int> answer; // 조건 만족하는 부분 수열의 시작 인덱스와 마지막 인덱스

    Sub_Seq sub_seq { sequence.begin(), sequence.end() };

    int sum = *(sub_seq.start);

    while (sub_seq.start != sequence.end())
    {
        if (sum > k)
        {
            sum -= *sub_seq.start;
            sub_seq.start++;
        }
        else if (sum == k)
        {

        }
        else if (sum < k)
        {
            sub_seq.end++;
            sum += *sub_seq.end;
        }
    }

    return answer;
}

int main(void)
{
    vector<int> seq { 1, 2, 3, 4, 5 }; // [5, 1e6]
    int k = 7; // [5, 1e9]

    solution(seq, k);
    return 0;
}
