// title: 백준 11866 요세푸스 문제 0 S5
// date: 19:28 20:13 32 + 13 (45)
// 생각하기 싫어서 원형 큐를 그냥 구현함.
// 센티넬 노드... 가 좀 이상한 걸 주의해야함.
#define PS_DEBUG
//#undef PS_DEBUG

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
    Node(): val(0), next(nullptr), prev(nullptr) {};
    Node(int ival): val(ival), next(nullptr), prev(nullptr) {};
    int val;
    Node* next;
    Node* prev;
};

class YoSeq {
public:
    YoSeq(int N, int K): size_(N) {
        vector<Node*> tnodes(N);
        for (size_t i = 0; i < tnodes.size(); ++i)
            tnodes[i] = new Node(i + 1);

        if (N == 1) {
            tnodes[0]->prev = &sn_;
            tnodes[0]->next = &sn_;

            sn_.next = tnodes[0];
            sn_.prev = tnodes[0];
        }
        else if (N == 2) {
            tnodes[0]->next = tnodes[1];
            tnodes[0]->prev = &sn_;

            tnodes[1]->next = &sn_;
            tnodes[1]->prev = tnodes[0];

            sn_.next = tnodes[0];
            sn_.prev = tnodes[1];
        }
        else {

        for (size_t i = 0; i < tnodes.size(); ++i) {
            if (i == 0) {
                tnodes[i]->prev = &sn_;
                sn_.next = tnodes[i];
                tnodes[i]->next = tnodes[i + 1];
            }
            else if (i == tnodes.size() - 1) {
                tnodes[i]->next = &sn_;
                sn_.prev = tnodes[i];
                tnodes[i]->prev = tnodes[i - 1];
            }
            else {
                tnodes[i]->next = tnodes[i + 1];
                tnodes[i]->prev = tnodes[i - 1];

                tnodes[i + 1]->prev = tnodes[i];
                tnodes[i - 1]->next = tnodes[i];
            }
        }
        }
        base_pos_ = sn_.next;
    }
    int PopAt(size_t pos) {
        Node* to_pop = base_pos_;
        for (size_t i = 0; i < pos - 1; ++i) // 3 times 
            to_pop = (to_pop->next == &sn_) ? to_pop->next->next : to_pop->next;
        const auto ret = to_pop->val;

        base_pos_ = (to_pop->next == &sn_) ? to_pop->next->next : to_pop->next;

        auto* past_prev = to_pop->prev;
        auto* past_next = to_pop->next;

        past_prev->next = past_next;
        past_next->prev = past_prev;

        delete to_pop;
        size_--;
        return ret;
    }

    inline bool empty() const {
        return (sn_.next == &sn_ && sn_.prev == &sn_);
    }
private:
    Node sn_;
    size_t size_;
    Node* base_pos_;
};
void PrintYoSeq(const vector<int>& seq) {
    cout << '<';

    for (size_t i = 0; i < seq.size(); ++i) {
        cout << seq[i];
        if (i != seq.size() - 1) cout << ", ";
    }

    cout << '>';
}

auto main() -> int
{
    {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr); cout.tie(nullptr);
    }

    int N; cin >> N;
    int K; cin >> K;
    YoSeq yoseq(N, K);
    vector<int> yoseq_seq;
    while (!yoseq.empty())
        yoseq_seq.push_back(yoseq.PopAt(K));
    PrintYoSeq(yoseq_seq);
    // [1, K, N, 1000]

    /*
    N = 7, K = 3
    (1), 2, [3], 4, 5, 6, 7
    = 3
    1, 2, (4), 5, [6], 7
    = 6
    1, [2], 4, 5, (7)
    = 2
    1, (4), 5, [7]
    = 7
    (1), 4, [5]
    = 5
    [(1)], 4
    = 1
    [(4)]
    = 4
    */
    return 0;
}