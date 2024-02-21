/*!
 * @section 백준 14500 테트로노미노
 * 2초, 512MB
*/
/*!
 * @subsection 문제
 * 폴리노미오란 크기가 1 x 1 인 정사각형을 여러 개 이어서 붙인 도형이다.
 * 다음과 같은 조건을 만족해야 한다.
 * - 정사각형은 서로 겹치면 안된다.
 * - 도형은 모두 연결되어 있어야 한다.
 * - 정사각형의 변끼리 연결되어 있어야 한다. 즉, 꼭짓점과 꼭짓점만 맞닿아 있으면 안된다.
 * 정사각형 4개를 이어 붙인 폴리오미노는 테트로미노라고 부르며, 5가지가 있다.
 * N x M 크기의 종이 위에 테트로미노를 하나 놓으려고 한다.
 * 종이는 1 x 1 크기의 칸으로 나누어져 있으며, 각 칸에는 정수가 하나 쓰여 있다.
 * 테트로미노 하나를 적절히 놓아서 테트로미노가 놓인 칸에 쓰여 있는 수들의 합을 최대로 하는 프로그램을 작성한다.
 * 테트로미노는 반드시 한 정사각형이 정확히 하나의 칸을 포함하도록 놓아야 한다.
 * 회전이나 대칭을 시켜도 상관없다.
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
    /// p0 ~ p3 은 Offset p0은 좌상단에 있는 것, 그리고 이게 기준
    void Init(const Pos& p0, const Pos& p1, const Pos& p2, const Pos& p3)
    {
        this->box_poss[T_0] = p0;
        this->box_poss[T_1] = p1;
        this->box_poss[T_2] = p2;
        this->box_poss[T_3] = p3;
    }
    // 90의 배수만 넣으쇼.
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
            /// 이제 이걸 종이에 올리고 ... 인덱스 검사를 해야함
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

                    // 여기까지 도달하면 위치로 변환 완료 안도달하면 인덱스 넘어갔단뜻

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