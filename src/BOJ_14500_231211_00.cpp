/*!
 * @section ���� 14500 ��Ʈ�γ�̳�
 * 2��, 512MB
*/
/*!
 * @subsection ����
 * ������̿��� ũ�Ⱑ 1 x 1 �� ���簢���� ���� �� �̾ ���� �����̴�.
 * ������ ���� ������ �����ؾ� �Ѵ�.
 * - ���簢���� ���� ��ġ�� �ȵȴ�.
 * - ������ ��� ����Ǿ� �־�� �Ѵ�.
 * - ���簢���� ������ ����Ǿ� �־�� �Ѵ�. ��, �������� �������� �´�� ������ �ȵȴ�.
 * ���簢�� 4���� �̾� ���� �������̳�� ��Ʈ�ι̳��� �θ���, 5������ �ִ�.
 * N x M ũ���� ���� ���� ��Ʈ�ι̳븦 �ϳ� �������� �Ѵ�.
 * ���̴� 1 x 1 ũ���� ĭ���� �������� ������, �� ĭ���� ������ �ϳ� ���� �ִ�.
 * ��Ʈ�ι̳� �ϳ��� ������ ���Ƽ� ��Ʈ�ι̳밡 ���� ĭ�� ���� �ִ� ������ ���� �ִ�� �ϴ� ���α׷��� �ۼ��Ѵ�.
 * ��Ʈ�ι̳�� �ݵ�� �� ���簢���� ��Ȯ�� �ϳ��� ĭ�� �����ϵ��� ���ƾ� �Ѵ�.
 * ȸ���̳� ��Ī�� ���ѵ� �������.
*/

/*!
 * 2023-12-11 13:37 ~ 15:40
*/

#define PS_DEBUG
#define COUT_TO_FILE
#undef PS_DEBUG
#undef COUT_TO_FILE

#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#ifdef COUT_TO_FILE
#include <fstream>
#include <string>
#endif 
#include <map>

using namespace std;
map<int, int> sin_map = { {0, 0}, {90, 1}, {180, 0}, {270, -1} };
map<int, int> cos_map = { {0, 1}, {90, 0}, {180, -1}, {270, 0} };

struct Pos { int v, h; };

class Tetro
{
    enum ETetroBox { T_0=0, T_1, T_2, T_3, T_MAX };
public:
    /// p0 ~ p3 �� Offset p0�� �»�ܿ� �ִ� ��, �׸��� �̰� ����
    void Init(const Pos& p0, const Pos& p1, const Pos& p2, const Pos& p3)
    {
        this->box_poss[T_0] = p0;
        this->box_poss[T_1] = p1;
        this->box_poss[T_2] = p2;
        this->box_poss[T_3] = p3;
    }
    // 90�� ����� ������.
    void Rotate(int degree)
    {
        for (int i = T_1; i < T_MAX; ++i)
        {
            Pos& curpos = this->box_poss[i];
            Pos prev_curpos = curpos;
            #ifdef PS_DEBUG
            cout << "Before Rotating" << degree << ": (" << curpos.v << ", " << curpos.h << ")\n";
            #endif

            curpos.h = cos_map[degree] * prev_curpos.h - sin_map[degree] * prev_curpos.v; // cos90 -sin90
            curpos.v = sin_map[degree] * prev_curpos.h + cos_map[degree] * prev_curpos.v; // sin90  cos90

            #ifdef PS_DEBUG
            cout << "After Rotating" << degree << ": (" << curpos.v << ", " << curpos.h << ")\n";
            #endif
        }
    }
    inline array<Pos, 4> GetOffsets() { return this->box_poss; };
public:
    array<Pos, 4> box_poss;
};

class Paper
{
public:
    Paper(int v_size, int h_size): 
        paper(v_size, vector<int>(h_size))
    {
        for (int v = 0; v < this->paper.size(); ++v)
            for (int h = 0; h < this->paper.front().size(); ++h)
                cin >> paper[v][h];
    }
    inline int GetScoreAt(const Pos& position) const { return this->paper[position.v][position.h];};
    inline int GetVSize() const { return this->paper.size();};
    inline int GetHSize() const { return this->paper.front().size();};
    vector<vector<int>> paper;
};


int main()
{
    int N; cin >> N;
    int M; cin >> M;

    #ifdef COUT_TO_FILE
        ofstream out("out.txt");
        auto* coutbuff = cout.rdbuf();
        cout.rdbuf(out.rdbuf());
    #endif
    

    Paper paper(N, M);

    array<Tetro, 5> tetros;
    {
        tetros[0].Init(Pos{0, 0}, Pos{0, 1}, Pos{0, 2}, Pos{0, 3});
        tetros[1].Init(Pos{0, 0}, Pos{0, 1}, Pos{1, 0}, Pos{1, 1});
        tetros[2].Init(Pos{0, 0}, Pos{1, 0}, Pos{2, 0}, Pos{2, 1});
        tetros[3].Init(Pos{0, 0}, Pos{1, 0}, Pos{1, 1}, Pos{2, 1});
        tetros[4].Init(Pos{0, 0}, Pos{0, 1}, Pos{0, 2}, Pos{1, 1});
    }
    int Max_Score = 0;

    for (Tetro& tetro: tetros)
    {
        for (int degree = 0; degree < 360; degree += 90)
        {
            tetro.Rotate(degree);
            #ifdef PS_DEBUG
            cout << "Current Tetro Offsets, Degree is:" << degree << '\n';
            for (const auto& t: tetro.GetOffsets())
                cout << "(" << t.v << ',' << t.h << ")" << " ";
            cout << '\n';
            #endif
            /// ���� �̰� ���̿� �ø��� ... �ε��� �˻縦 �ؾ���
            array<Pos, 4> offsets = tetro.GetOffsets();

            // offsets -> poss
            for (int v_pivot_pos = 0; v_pivot_pos < paper.GetVSize(); ++v_pivot_pos)
            {
                for (int h_pivot_pos = 0; h_pivot_pos < paper.GetHSize(); ++h_pivot_pos)
                {

                    array<Pos, 4> poss;
                    int cur_score = 0;

                    if (offsets[0].v + v_pivot_pos >= 0 && offsets[0].v + v_pivot_pos < paper.GetVSize())
                        poss[0].v = offsets[0].v + v_pivot_pos;
                    else continue;
                    if (offsets[0].h + h_pivot_pos >= 0 && offsets[0].h + h_pivot_pos < paper.GetHSize())
                        poss[0].h = offsets[0].h + h_pivot_pos;
                    else continue;

                    if (offsets[1].v + v_pivot_pos >= 0 && offsets[1].v + v_pivot_pos < paper.GetVSize())
                        poss[1].v = offsets[1].v + v_pivot_pos;
                    else continue;
                    if (offsets[1].h + h_pivot_pos >= 0 && offsets[1].h + h_pivot_pos < paper.GetHSize())
                        poss[1].h = offsets[1].h + h_pivot_pos;
                    else continue;

                    if (offsets[2].v + v_pivot_pos >= 0 && offsets[2].v + v_pivot_pos < paper.GetVSize())
                        poss[2].v = offsets[2].v + v_pivot_pos;
                    else continue;
                    if (offsets[2].h + h_pivot_pos >= 0 && offsets[2].h + h_pivot_pos < paper.GetHSize())
                        poss[2].h = offsets[2].h + h_pivot_pos;
                    else continue;

                    if (offsets[3].v + v_pivot_pos >= 0 && offsets[3].v + v_pivot_pos < paper.GetVSize())
                        poss[3].v = offsets[3].v + v_pivot_pos;
                    else continue;
                    if (offsets[3].h + h_pivot_pos >= 0 && offsets[3].h + h_pivot_pos < paper.GetHSize())
                        poss[3].h = offsets[3].h + h_pivot_pos;
                    else continue;

                    // ������� �����ϸ� ��ġ�� ��ȯ �Ϸ� �ȵ����ϸ� �ε��� �Ѿ�ܶ�

                    for (const auto& pos: poss)
                        cur_score += paper.GetScoreAt(pos);

                    #ifdef PS_DEBUG
                    for (int v = 0; v < paper.GetVSize(); ++v)
                    {
                        for (int h = 0; h < paper.GetHSize(); ++h)
                        {
                            bool is_tetro_here = false;
                            for (const auto& pos: poss)
                            {
                                if (pos.v == v && pos.h == h)
                                {
                                    is_tetro_here = true;
                                    break;
                                }
                            }
                            char del_s = ' ';
                            char del_e = ' ';

                            if (is_tetro_here)
                            {
                                del_s = '[';
                                del_e = ']';
                            }

                            cout << del_s << paper.GetScoreAt(Pos{v, h}) << del_e << " ";
                        }
                        cout << '\n';
                    }
                    cout << '\n';
                    #endif //PS_DEBUG
                    if (cur_score > Max_Score) Max_Score = cur_score;
                }
            }
        }
    }

    cout << Max_Score << '\n';


    return 0;
}