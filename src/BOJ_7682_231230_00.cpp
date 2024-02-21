// title: ���� 7682 ƽ���� G5
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

    // ����ִ� ��� ������ ��ȿ���� ����
    if (e_count == SIZE_V * SIZE_H) {
        REASON("����ִ� ��� ��ȿ���� ����");
        return false;
    }
    // ���� ���� ���� ���� 0, 1, 2 �� �ϳ��� ũ�� �� �� �͵� ���� �ƹ��� �̱��� �ʾҰ�, �ǵ� �� ���� �ʾ����Ƿ� ��ȿ���� ����
    if (x_count < SIZE_WIN && o_count < SIZE_WIN) {
        REASON("���� ���� ���� 0, 1, 2 �� �ϳ���, �ƹ��� �̱��� ���߰� �ǵ� �� ���� �ʾ����Ƿ� ��ȿ���� ����.");
        return false;
    }

    // ���߿� �δ� O�� ���� X ���� ���� ���� �����Ƿ� ��ȿ���� ����. O�� �׻� X ������.
    if (o_count > x_count) {
        REASON("���߿� �δ� O�� X���� ���� ���� �����Ƿ� ��ȿ���� ����.");
        return false;
    }

    // ������� �ʴ�
    // ���� ���� ���� 2���� ũ��
    // O�� �׻� X �����̴�.

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
    { // ���� x3 ���� x3 �밢�� x2 �� 8���� ��쿡 ���ؼ� ��� ����
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
    // == �̱� ���ڷ� ���� ���� == 
    if (x_win_count > 1 || o_win_count > 1) {
        // �������� ���� ���� ���� X �� �������� ����� �������μ� �밢�� 2���� �ϼ��ϴ� ���ۿ� ����
        // �ٵ� �̷� ��� �� ������ �������
        if (x_win_count == 2 || o_win_count == 0) {
            if (x_win_shape[DLD] == 1 && x_win_shape[DLU] == 1 && accumulate(x_win_shape.cbegin(), x_win_shape.cend()-2, 0) == 0 && e_count == 0) {
                REASON("������ ��Ȳ���� X �� ��� ���Ƽ� �밢�� 2 ����� �̱�. ��ȿ��.");
                return true;
            }
        }
        // ������ ��� �ƴϰų� �� ������ �ִ� ���
        REASON("X Ȥ�� O�� 1 ���� �ʰ���. X �� 2���� �� �� �ִ� Ư�� ���̽����� �ش����� �����Ƿ� ��ȿ���� ����.");
        return false;
    }
    // �̱� ���ڰ� 1 ~ 0 �� ���
    // �� �� �̱�� ���� ���� �ȵǹǷ� ��ȿ���� ����
    if (x_win_count == 1 && o_win_count == 1) {
        REASON("�� �� �̱�� ���� ����. ��ȿ���� ����.");
        return false;
    }
    // x �� �̱�� ��� �׻� x �� ������ �� ���ƾ� ��ȿ��
    if (x_win_count == 1 && o_win_count == 0) {
        if (x_count = o_count + 1)  {
            REASON("X �� 1 �����̰�, X�� ������ O�� �������� �ϳ� �����Ƿ� ��ȿ��.");
            return true;
        }
        else {
            REASON("X �� 1 �����ε�, X�� ������ O�� �������� �ϳ� ���� �����Ƿ� ��ȿ���� ����.");
            return false;
        }
    }
    // o �� �̱�� ��� �׻� o�� ������ �� ���ưų� ���ƾ� ��ȿ��
    if (x_win_count == 0 && o_win_count == 1) {
        if (o_count == x_count) {
            REASON("O�� 1�����̰�, O�� ������ X�� ������ �����Ƿ� ��ȿ��.");
            return true;
        }
        else  {
            REASON("O�� 1�����̰�, O�� ������ X�� ���� �� ���� �����Ƿ� ��ȿ���� ����. O�� ���߿� �ιǷ� �׻� ������ ���ƾ���.");
            return false;
        }
    }
    // �� �� �̱��� ���� ���
    if (x_win_count == 0 && o_win_count == 0) {
        // �� �������� ��ȿ��
        if (e_count == 0) {
            REASON("�� �� ���� �����鼭 ���� ���� á���Ƿ� ��ȿ��.");
            return true;
        }
        // �ƴϸ� ���� �� �Ѽ� �����ϱ� �� ��ȿ��
        else  {
            REASON("�� �� ���� ���µ�, ���� �� �Ѽ� �����Ƿ� ��ȿ���� ����.");
            return false;
        }
    }
    // ������� �����ϸ� �հ� �߸��Ȱ���
    REASON("�б⸦ ��Ż�� �����̹Ƿ� �̰� ��µȴٸ� ������.");
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