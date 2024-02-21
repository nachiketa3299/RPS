/*!
* @date 2023-10-31T12:58
* ALGOSPOT 삼각형 위의 최대 경로(TRIANGLEPATH)
* Dynamic Programming?
*/

/*!
* 6
* 1 2
* 3 7 4
* 9 4 1 7
* 2 7 5 9 4
*/

/*!
* 삼각형 모양으로 배치된 자연수들이 있다.
* 맨 위 숫자에서부터 시작해, 한 번에 한 칸씩 아래로 내려가 맨 아래줄로 내려가는 경로를 만든다.
* 경로는 아래줄로 내려갈 때마다 바로 아래 숫자, 혹은 오른쪽 아래 숫자로 내려갈 수 있다.
* 모든 경로 중 포함된 숫자의 최대 합을 찾는 프로그램을 작성한다.
* 
* 입력의 첫 줄에는 테스트 케이스의 수 `C` (`C` <= 50)가 주어진다.
* 테스트 케이스의 첫 줄에는 삼각형의 크기 `n` (2 <= `n` <= 100)이 주어진다.
* 그 후 `n` 줄에는 1 ~ `n` 개의 숫자로 삼각형 가로줄에 있는 숫자가 왼쪽부터 주어진다.
* 각 숫자는 1 이상 1e5 이하의 자연수이다.
* 
* 각 테스트 케이스마다 한 줄에 최대 경로의 숫자 합을 출력한다.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define CMP_LOWEST -1

class Triangle
{
private:
    /// @short 삼각형의 각 숫자들을 저장함.
    vector<vector<int>> t_numbers; 

    /// @short `p_cache[i][j]`는 `t_numbers[i][j]` 까지의 경로의 최댓값임. 
    /// @see @ref Triangle::populate_p_cache
    vector<vector<int>> p_cache;
public:
    /// @short 입력을 받아 삼각형을 구성하고, 최대 합 경로에 대한 캐시(@ref Triangle::p_cache)를 채운다.
    /// @param[in] n 삼각형 한 변의 크기
    Triangle(int n): t_numbers(n), p_cache(n) 
    {
        /// 입력을 마저 받는다
        for (int i = 0; i < n; ++i)
        {
            t_numbers[i].resize(i + 1);
            p_cache[i].resize(i + 1);
            for (int& t_number : t_numbers[i]) cin >> t_number;
        }
        /// 캐시를 채운다
        populate_p_cache();
        return;
    };

    /// @short 최대 합 경로에 대한 캐시를 채운다.
    void populate_p_cache()
    {
        /// 초깃값 설정. T(0, 0)까지 최대 합 경로는 당연히 T(0, 0)
        p_cache[0][0] = t_numbers[0][0];

        /// `i`행 `j`열에 있는 삼각형의 숫자는 `t_numbers[i][j]` 이다. (`i >= 0 && j >= 0 && i >= j`)
        /// `p_cache[i][j]`는 `t_numbers[i][j]` 까치 최대 합 경로이다.
        /// `p_cache[i][j]` 를 구할 때에는 두 가지를 고려해야 한다.
        /// - (1) 수직(`vu`)으로  내려온 경우 -> `p_cache[i - 1][j]`
        /// - (2) 대각선(`du`)으로 내려온 경우 -> `p_cache[i - 1][j - 1]`
        /// 그림으로 그려보면 아래와 같음. (`p_cache`를 `p`라고, `t_numbers`를 `t`라 한다)
        /// `p[0][0]=t[0][0]`
        /// `p[1][0]=max(-1, p[0][0]+t[1][0])`, `p[1][1]=max(p[0][0]+t[1][1], -1)`
        /// `p[2][0]=max(-1, p[1][0]+t[2][0])`, `p[2][1]=max(p[1][0]+t[2][1], p[1][1]+t[2][1])`, `p[2][2]=max(p[1][1]+t[2][2], -1)`
        /// `p[3][0]=max(-1, p[2][0]+t[3][0])`, `p[3][1]=max(p[2][0]+t[3][1], p[2][1]+t[3][1])`, `p[3][2]=max(p[2][1]+t[3][2], p[2][2]+t[3][2])`, `p[3][3]=max(p[2][2]+t[3][3], -1)`
        /// ...
        /// `p[i][j]=max(p[i-1][j-1]+t[i][j], p[i-1][j]+t[i][j])` 로 일반화 될 수 있다. 단, `i >= 0 && j >= 0 && i >= j` 가 아니라면 `p[i][j] = -1`
        /// @short **핵심은 이전에 대각선 경로 타고 내려왔을 때 최대 합 경로와 이전에 수직 경로 타고 내려왔을때 최대 합 경로 중 큰 것 사용해 현재 최대 합 경로를 구하는 것**.
        /// @note 경로에서 항상 최대 숫자를 선택한다고 해서 그 경로가 전체 경로중에서 최대 합을 가지는게 아님! (not a optimal substructure problem)
        /// @note 삼각형의 왼쪽 오른쪽 변에 걸쳐있는 항들에 대해서는 각각 `vu`와 `du`만 존재할 수 있음. 존재할 수 없는건 -1(`CMP_LOWEST`)로 초기화한다.

        /// 삼각형의 두번째 행부터 최대 합 경로를 채워나간다.
        for (int i = 1; i < p_cache.size(); ++i)
        {
            for (int j = 0; j < p_cache[i].size(); ++j)
            {
                int vu = is_valid_idx(i - 1, j)     ? p_cache[i - 1][j]     : CMP_LOWEST;
                int du = is_valid_idx(i - 1, j - 1) ? p_cache[i - 1][j - 1] : CMP_LOWEST;
                p_cache[i][j] = max(vu + t_numbers[i][j], du + t_numbers[i][j]);
            }
        }
    }
    bool is_valid_idx(int i, int j) const
    {
        return i >= 0 && j >= 0 && i >= j;
    }

    int get_max_path_sum() const
    {
        /// 캐시의 마지막 행에서 최댓값을 찾아 그 값을 반환하면 됨.
        return *max_element(p_cache.back().begin(), p_cache.back().end());
    }
};

int main()
{
    int C; cin >> C; ///< C [1, 50]
    for (size_t tc = 0; tc < C; ++tc)
    {
        int n; cin >> n; ///< n [2, 100]

        Triangle t(n); 
        cout << t.get_max_path_sum() << '\n';
    }
    return 0;
}