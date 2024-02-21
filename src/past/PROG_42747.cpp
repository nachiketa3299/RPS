/// H-Index -> 과학자의 생산성과 영향력을 나타내는 지표. (`h`)
/// 어떤 과학자가 발표한 논문 `n` 편중, `h`번 이상 인용된 논문이 `h`편 이상이고 나머지 논문이 `h`번 이하 인용되었다면, `h`의 최댓값이 이 과학자의 H-Index이다.

/// 논문의 수 `n` 은 [1, 1e3]
/// 논문 별 인용 횟수 `citation[n]s` 은 [0, 1e4]
/// 

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

///  인용 횟수를 담을 배열 `citations`가 주어질 때, H-Index를 반환하는 함수 `solution`을 작성한다.
///  @short `CiteData` 는 특정 인용 횟수를 가진 논문이 몇 개 있나 저장하는 구조체
struct CiteData
{
    int n_papers_cnt = 0; ///< 
    int acc_cited = 0;
    bool operator<(const CiteData& r) { return this->n_papers_cnt < r.n_papers_cnt;  }
};

using PaperIdx = int; ///< 논문의 인덱스
using N_Cited = int; ///< 인용된 횟수

/// @param[in] citatinos 논문의 인용 횟수를 담은 벡터. 크기는 `n`이다.
/// @return H-Index
int solution(vector<PaperIdx> citations) 
{
    int answer = 0;
    map<N_Cited, CiteData, greater<int>> cite_map;
    for (const auto& citation : citations)
    {
        cite_map[citation].n_papers_cnt++;
    }

    for (auto it = cite_map.begin(); it != cite_map.end(); ++it)
    {
        auto prev_it = prev(it);
        if (prev_it == cite_map.end()) it->second.acc_cited = it->second.n_papers_cnt;
        else
        {
            it->second.acc_cited = it->second.n_papers_cnt + prev_it->second.acc_cited;
        }

        /// `it->first` 번 인용된 논문이 `it->first`번 이상 인용된 논문의 누적합(`it->second.acc_cited`) 이하이다.
        if (it->first <= it->second.acc_cited)
        {
            answer = it->first;
            break;
        }
    }

    return answer;
}

int main()
{
    vector<vector<int>> tcs =
    {
        //{3, 0, 6, 1, 5},
        {0, 1, 2, 2, 2},
        {1, 4, 5},
        {5, 6, 7}
    };
    vector<int> answs =
    {
        //3,
        2,
        2,
        3
    };

    for (size_t i = 0; i < tcs.size(); ++i)
    {
        if (solution(tcs[i]) == answs[i]) cout << "Correct\n";
        else
        {
            cout << solution(tcs[i]) << " != " << answs[i] << "(answer)\n";
        }
    }

}