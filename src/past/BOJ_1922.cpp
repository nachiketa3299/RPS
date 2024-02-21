///@date 2023-11-07 22:29 23:49 (80)
/// 백준 네트워크 연결(1922, G4)
/// https://www.acmicpc.net/problem/1922

/*!
* 모두가 자료를 공유하기 위해서, 모든 컴퓨터를 연결 상태로 만든다.
* 컴퓨터 A와 B가 연결되어 있다는 뜻은, A에서 B로의 경로가 존재한다는 뜻이다. (A->B->C)
* 컴퓨터를 연결하는 비용을 최소로 하고싶다.
* 각 컴퓨터를 연결하는 데 필요한 비용이 주어질 때, 모든 컴퓨터를 연결하는 데 필요한 최소비용을 출력한다.
* (모든 컴퓨터를 연결할 수 없는 경우는 없다.)
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

#define GetEdgeStart(etuple) get<0> (etuple)
#define GetEdgeEnd(etuple) get<1>(etuple)
#define GetEdgeWeight(etuple) get<2>(etuple)

typedef size_t                                          IndexType;
typedef size_t                                          StartIndexType;
typedef size_t                                          EndIndexType;
typedef int                                             WeightType;
typedef tuple<StartIndexType, EndIndexType, WeightType> WEdgeType;

class UnionFind
{
public:
    UnionFind(size_t ncnt): parent(ncnt)
    {
        for (size_t ni = 0; ni < ncnt; ++ni)
            parent[ni] = ni;
        return;
    }
    bool HasSameLastParent(IndexType ni1, IndexType ni2) const
    {
        const IndexType& lp_ni1 = FindLastParent(ni1);
        const IndexType& lp_ni2 = FindLastParent(ni2);

        if (lp_ni1 == lp_ni2)
            return true;
        return false;
    }
    void MergeNodes(IndexType ni1, IndexType ni2)
    {
        if (ni1 == ni2) 
            return;

        const IndexType& lp_ni1 = FindLastParent(ni1);
        const IndexType& lp_ni2 = FindLastParent(ni2);
        if (lp_ni1 > lp_ni2)    parent[lp_ni1] = lp_ni2;
        else                    parent[lp_ni2] = lp_ni1;
    }
private:
    IndexType FindLastParent(IndexType ni) const
    {
        if (ni == parent[ni])
            return parent[ni];
        return FindLastParent(parent[ni]);
    }
private:
    vector<IndexType> parent;
};

class Network
{
public:
    Network(size_t vcnt, size_t ecnt): vcnt(vcnt)
    {
        for (size_t i = 0; i < ecnt; ++i)
        {
            size_t tstart;  cin >> tstart;
            size_t tend;    cin >> tend;
            size_t tweight; cin >> tweight;

            if (tstart == tend) continue;

            WEdgeType tedge { tstart - 1, tend - 1, tweight };

            sorted_wedges.push_back(tedge);
        }
        sort
        (
            sorted_wedges.begin(), sorted_wedges.end(),
            [](const WEdgeType& e1, const WEdgeType& e2) 
            { 
                return GetEdgeWeight(e1) < GetEdgeWeight(e2); 
            }
        );
    }
    WeightType GetMinimumCost()
    {
        vector<WEdgeType> min_edges;

        UnionFind uf(vcnt);
        for (const WEdgeType& wedge : sorted_wedges)
        {
            if (uf.HasSameLastParent(GetEdgeStart(wedge), GetEdgeEnd(wedge)))
                continue;
            uf.MergeNodes(GetEdgeStart(wedge), GetEdgeEnd(wedge));
            min_edges.push_back(wedge);
        }

        WeightType weight_sum = 0;
        for (const WEdgeType& wedge : min_edges)
            weight_sum += GetEdgeWeight(wedge);

        return weight_sum;
    }
private:
    size_t vcnt;
    vector<WEdgeType> sorted_wedges;
};

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    size_t N; cin >> N; ///< 컴퓨터의 수 [1, 1e3]
    size_t M; cin >> M; ///< 연결 선의 수 [1, 1e5]
    Network network(N, M);
    cout << network.GetMinimumCost() << endl;

    return 0;
}
