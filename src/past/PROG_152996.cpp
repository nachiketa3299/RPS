/// @date 2023-11-02T19:35
/// 프로그래머스 152996(Lv2, 시소 짝궁) 

#include <string>
#include <vector>
#include <map>
#include <array>
#include <set>

using namespace std;

typedef int         WeightType;
typedef long long   CountType;
typedef int         LengthType;

/// 시소에 좌석은 2m, 3m, 4m 마다 있다.
/// @param[in] weights 사람들의 몸무게 목록. 길이는 [2, 1e5], 원소는 [1e2, 1e3]
/// @return *시소 짝궁* 쌍의 갯수
CountType solution(vector<WeightType> weights)
{
    /// @short 시소에 붙어있는 좌석의 거리 수치 (2m, 3m, 4m 로 고정 배열)
    array<LengthType, 3> seats = { 2, 3, 4 };

    /// @short 중복 없는 무게들의 집합 
    /// @details 예) `weights = { 100, 100, 200 }` 이면, `unique_weight = { 100, 200 }`
    set<WeightType> u_weights;

    /// @short 각 무게가 어떤 횟수로 들어있는지
    /// @details 예) `weights = { 100, 100, 200 }` 이면, `weight_cnts = { {100 : 2}, {200 : 1} }`
    map<WeightType, CountType> weight_cnts;

    /// (1) @ref unique_weight 와 @ref weight_cnts 채우기
    for (const WeightType& weight : weights) ///< O(N)
    {
        u_weights.insert(weight);
        weight_cnts[weight]++;
    }

    /// @short 가능한 순서쌍을 저장할 집합
    /// @details 예) `weights = { 100, 100, 200 }` 이면, `friends = {{100, 100}, {100, 200}}`

    set<pair<WeightType, WeightType>> homo_friends;
    set<pair<WeightType, WeightType>> hetero_friends;

    /// (2) 무게가 같은 녀석들이 여러명이면 동일한 쌍으로 `homo_friends` 에 넣어준다.
    /// 예를 들어 100 무게가 3번 등장한다면 (`weight_cnts[100] == 3`) `friends` 에 `{100, 100}`을 하나 추가.
    for (const auto& weight_cnt : weight_cnts) ///< O(N)
    {
        if (weight_cnt.second <= 1)
            continue;
        homo_friends.insert({ weight_cnt.first, weight_cnt.first });
    }

    /// (3) 짝이 될 수 있는 녀석들을 `hetero_friends` 에 넣어준다.
    for (const WeightType& u_weight : u_weights) ///< O(N)
    {
        /// 지금 순회하고 있는 `u_weight`가 `current_seat`에 앉아있다고 가정
        for (const auto& current_seat : seats) ///< O(3)
        {
            /// 짝의 후보가 `other_seat`에 앉아있다고 가정
            for (const auto& other_seat : seats) ///< O(3)
            {
                /// 같은 좌석에 앉는 것은 (2)에서 이미 처리하였으므로 넘긴다.
                if (current_seat == other_seat)
                    continue;
                /// 현재 좌석의 토크를 구하고, 다른 좌석의 거리로 나누었을때 나머지가 있다면 짝궁의 무게는 정수가 아닌, 불가능한 무게
                int torque = u_weight * current_seat;
                if (torque % other_seat != 0) 
                    continue;
                /// 가능한 짝궁의 무게가 실제로 `weights`에 있었는지 `weight_cnts`를 이용하여 판단
                WeightType candid_friend_weight = torque / other_seat;
                if (weight_cnts[candid_friend_weight] == 0)
                    continue;
                /// 있었다면 넣는다.
                hetero_friends.insert({ u_weight, candid_friend_weight });
            }
        }
    }

    /// `homo_friends = {{100, 100}}` 이고, `weights = { 100, 100, 100, 100 }` 이었으면, 4개 원소중 순서 없이 2개 뽑는것과 같음 4C2
    /// 일반화하면 `homo_friends = {{w, w}}` 면, `homo_cnt = weight_cnts[w]C2` (조합의 수)
    CountType homo_cnt = 0;
    for (const auto& hmf : homo_friends)
        homo_cnt += weight_cnts[hmf.first] * (weight_cnts[hmf.first] - 1) / 2;

    /// `hetero_friends`는 항상 짝수 크기임 왜냐하면 대칭으로 들어있기 때문. 예를 들어 (100, 200)이 들어있으면 (200, 100)이 들어있음.
    /// 때문에 100이 나온 횟수 * 200이 나온 횟수 에 2를 나누어 주어야 정상적인 갯수가 나옴.
    /// **근데 여기서 나누면 만약 저 값이 1일때 1 / 2 = 0 으로 짤리기 때문에 마지막에 한꺼번에 나누어 주어야 함**.
    CountType hetero_cnt = 0;
    for (const auto& htf : hetero_friends)
        hetero_cnt += weight_cnts[htf.first] * weight_cnts[htf.second];

    CountType answer = homo_cnt + hetero_cnt / 2;
    return answer;
}

#include "PGS.h"

int main()
{

    Solver<vector<int>, int> s =
    {
        {
            { {100, 180, 360, 100, 270}, 4},
            { {100, 100, 100, 100}, 6},
            { {100, 400}, 0},
            { {200, 100, 100, 200, 100}, 10}

        }
    };
    s();
}