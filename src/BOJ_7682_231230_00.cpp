// title: 백준 7682 틱택토 G5
// date: 2023-12-30 23:20 02:04
#define PS_DEBUG
//#undef PS_DEBUG

/*
*/

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <array>
#include <algorithm>
#include <numeric>

#define SIZE_V 3
#define SIZE_H 3
#define VALID_STR "valid"
#define INVALID_STR "invalid"
#define END_STR "end"
#define SIZE_WIN 3
#define X 'X'
#define O 'O'
#define EMPTY '.'

#ifdef PS_DEBUG
#define REASON(str) cout << "> R: " << str << "\n"
#else
#define REASON(str)
#endif //PS_DEBUG 

using namespace std;

auto get_pos(const string& str, const size_t& v, const size_t& h) {
    assert(0 <= v < SIZE_V && 0 <= h < SIZE_H);
    return str[v * SIZE_V + h];
}

#ifdef PS_DEBUG
void print_board(const string& str) {
    for (size_t v = 0; v < SIZE_V; ++v) {
        for (size_t h = 0; h < SIZE_H; ++h) {
            cout << get_pos(str, v, h);
        }
        cout << "\n";
    }
}
#endif //PS_DEBUG 

bool is_valid(const string& board) {
    #ifdef PS_DEBUG
    static int tc = 0; 
    cout << "\n====>> Board tc(" << tc << ")\n";
    print_board(board);
    tc++;
    #endif //PS_DEBUG 

    size_t o_count = 0, x_count = 0;
    for (size_t v = 0; v < SIZE_V; ++v) {
        for (size_t h = 0; h < SIZE_H; ++h) {
            switch(get_pos(board, v, h)) {
                case X: ++x_count; break;
                case O: ++o_count; break;
                case EMPTY: continue;
            }
        }
    }
    size_t e_count = SIZE_V * SIZE_H - (o_count + x_count);
    
    #ifdef PS_DEBUG
    cout << "> x_count: " << x_count << "\n";
    cout << "> o_count: " << o_count << "\n";
    cout << "> e_count: " << e_count << "\n";
    #endif //PS_DEBUG 

    // 비어있는 경우 무조건 유효하지 않음
    if (e_count == SIZE_V * SIZE_H) {
        REASON("비어있는 경우 유효하지 않음");
        return false;
    }
    // 놓은 말의 수가 각각 0, 1, 2 중 하나면 크기 비교 할 것도 없이 아무도 이기지 않았고, 판도 다 차지 않았으므로 유효하지 않음
    if (x_count < SIZE_WIN && o_count < SIZE_WIN) {
        REASON("놓은 말의 수가 0, 1, 2 중 하나라, 아무도 이기지 못했고 판도 다 차지 않았으므로 유효하지 않음.");
        return false;
    }

    // 나중에 두는 O의 수가 X 보다 많은 경우는 없으므로 유효하지 않음. O는 항상 X 이하임.
    if (o_count > x_count) {
        REASON("나중에 두는 O가 X보다 많은 경우는 없으므로 유효하지 않음.");
        return false;
    }

    // 비어있지 않다
    // 놓은 말의 수가 2보다 크다
    // O가 항상 X 이하이다.

    typedef array<size_t, 8> WinShapes; // acts like bool array
    WinShapes x_win_shape; x_win_shape.fill(0); WinShapes o_win_shape; o_win_shape.fill(0);
    struct Pos { size_t v_, h_; }; typedef array<Pos, 3> WinSeq; WinSeq seq;
    auto test = [&board](const char& symbol, size_t& count, const WinSeq& poss) {
            for (const auto& pos: poss) {
                if (get_pos(board, pos.v_, pos.h_) != symbol)
                    return;
            }
            ++count;
    };
    { // 가로 x3 세로 x3 대각선 x2 총 8가지 경우에 대해서 모두 판정
    // #0 h0
    #define H_0 0
    seq[0] = Pos{0, 0}; seq[1] = Pos{0, 1}; seq[2] = Pos{0, 2};
    test(X, x_win_shape[H_0], seq);
    test(O, o_win_shape[H_0], seq);
    // #1 h1
    #define H_1 1
    seq[0] = Pos{1, 0}; seq[1] = Pos{1, 1}; seq[2] = Pos{1, 2};
    test(X, x_win_shape[H_1], seq);
    test(O, o_win_shape[H_1], seq);
    // #2 h2
    #define H_2 2
    seq[0] = Pos{2, 0}; seq[1] = Pos{2, 1}; seq[2] = Pos{2, 2};
    test(X, x_win_shape[H_2], seq);
    test(O, o_win_shape[H_2], seq);
    // #3 v0
    #define V_0 3
    seq[0] = Pos{0, 0}; seq[1] = Pos{1, 0}; seq[2] = Pos{2, 0};
    test(X, x_win_shape[V_0], seq);
    test(O, o_win_shape[V_0], seq);
    // #4 v1
    #define V_1 4
    seq[0] = Pos{0, 1}; seq[1] = Pos{1, 1}; seq[2] = Pos{2, 1};
    test(X, x_win_shape[V_1], seq);
    test(O, o_win_shape[V_1], seq);
    // #5 v2
    #define V_2 5
    seq[0] = Pos{0, 2}; seq[1] = Pos{1, 2}; seq[2] = Pos{2, 2};
    test(X, x_win_shape[V_2], seq);
    test(O, o_win_shape[V_2], seq);
    // #6 dlu
    #define DLU 6 // Diagonal Left Up
    seq[0] = Pos{0, 0}; seq[1] = Pos{1, 1}; seq[2] = Pos{2, 2};
    test(X, x_win_shape[DLU], seq);
    test(O, o_win_shape[DLU], seq);
    // #7 dld
    #define DLD 7 // Diagonal Left Down
    seq[0] = Pos{2, 0}; seq[1] = Pos{1, 1}; seq[2] = Pos{0, 2};
    test(X, x_win_shape[DLD], seq);
    test(O, o_win_shape[DLD], seq);
    }
    const auto x_win_count = accumulate(x_win_shape.cbegin(), x_win_shape.cend(), 0);
    const auto o_win_count = accumulate(o_win_shape.cbegin(), o_win_shape.cend(), 0);
    #ifdef PS_DEBUG
        cout << "> x_win_shape: "; for_each(x_win_shape.cbegin(), x_win_shape.cend(), [](const auto& e){ cout << e << " ";}); cout << "\n";
        cout << "> x_win_count: " << x_win_count << "\n";
        cout << "> o_win_shape: "; for_each(o_win_shape.cbegin(), o_win_shape.cend(), [](const auto& e){ cout << e << " ";}); cout << "\n";
        cout << "> o_win_count: " << o_win_count << "\n";
    #endif //PS_DEBUG 
    // == 이긴 숫자로 판정 시작 == 
    if (x_win_count > 1 || o_win_count > 1) {
        // 투빙고인 경우는 먼저 놓는 X 가 마지막에 가운데에 놓음으로서 대각선 2개를 완성하는 경우밖에 없음
        // 근데 이런 경우 빈 공간이 없어야함
        if (x_win_count == 2 || o_win_count == 0) {
            if (x_win_shape[DLD] == 1 && x_win_shape[DLU] == 1 && accumulate(x_win_shape.cbegin(), x_win_shape.cend()-2, 0) == 0 && e_count == 0) {
                REASON("마지막 상황에서 X 가 가운데 놓아서 대각선 2 빙고로 이김. 유효함.");
                return true;
            }
        }
        // 투빙고 모양 아니거나 빈 공간이 있는 경우
        REASON("X 혹은 O가 1 빙고를 초과함. X 가 2빙고가 될 수 있는 특수 케이스에도 해당하지 않으므로 유효하지 않음.");
        return false;
    }
    // 이긴 숫자가 1 ~ 0 인 경우
    // 둘 다 이기는 경우는 말이 안되므로 유효하지 않음
    if (x_win_count == 1 && o_win_count == 1) {
        REASON("둘 다 이기는 경우는 없음. 유효하지 않음.");
        return false;
    }
    // x 가 이기는 경우 항상 x 의 개수가 더 많아야 유효함
    if (x_win_count == 1 && o_win_count == 0) {
        if (x_count = o_count + 1)  {
            REASON("X 가 1 빙고이고, X의 개수가 O의 개수보다 하나 많으므로 유효함.");
            return true;
        }
        else {
            REASON("X 가 1 빙고인데, X의 개수가 O의 개수보다 하나 많지 않으므로 유효하지 않음.");
            return false;
        }
    }
    // o 가 이기는 경우 항상 o의 개수가 더 많아거나 같아야 유효함
    if (x_win_count == 0 && o_win_count == 1) {
        if (o_count == x_count) {
            REASON("O가 1빙고이고, O의 개수가 X의 개수와 같으므로 유효함.");
            return true;
        }
        else  {
            REASON("O가 1빙고이고, O의 개수가 X의 개수 와 같지 않으므로 유효하지 않음. O는 나중에 두므로 항상 개수가 같아야함.");
            return false;
        }
    }
    // 둘 다 이기지 못한 경우
    if (x_win_count == 0 && o_win_count == 0) {
        // 꽉 차있으면 유효함
        if (e_count == 0) {
            REASON("둘 다 빙고가 없으면서 판이 가득 찼으므로 유효함.");
            return true;
        }
        // 아니면 아직 더 둘수 있으니까 안 유효함
        else  {
            REASON("둘 다 빙고가 없는데, 아직 더 둘수 있으므로 유효하지 않음.");
            return false;
        }
    }
    // 여기까지 도달하면 먼가 잘못된거임
    REASON("분기를 이탈한 종료이므로 이게 출력된다면 오류임.");
    return false;
}

auto main() -> int
{
    {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr); cout.tie(nullptr);
    }

    /*TESTCASE START*/ while(true) { 

    string board; cin >> board;

    if (board == END_STR) 
        break;

    if (is_valid(board))
        cout << VALID_STR << "\n";
    else
        cout << INVALID_STR << "\n";

    /*TESTCASE END*/ }

    return 0;
}