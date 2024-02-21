#include <iostream>
#include <string>

using namespace std;

namespace consts {
    const char tabchar_global = '_';
    const int fa_arr_size = 3;
    const int tab_space_size = 4;
    const int initial_depth = 0;

    namespace strings {
        const string start_line { "어느 한 컴퓨터공학과 학생이 유명한 교수님을 찾아가 물었다." };
        const string student_question { "\"재귀함수가 뭔가요?\"" };
        const string false_answer[fa_arr_size] {
            "\"잘 들어보게. 옛날옛날 한 산 꼭대기에 이세상 모든 지식을 통달한 선인이 있었어.",
            "마을 사람들은 모두 그 선인에게 수많은 질문을 했고, 모두 지혜롭게 대답해 주었지.",
            "그의 답은 대부분 옳았다고 하네. 그런데 어느 날, 그 선인에게 한 선비가 찾아와서 물었어.\""
        };
        const string real_answer { "\"재귀함수는 자기 자신을 호출하는 함수라네\"" };
        const string tail { "라고 답변하였지." };
            
    }
}


class QA {
private:
    struct Lines {
        string start;
        string question;
        struct Answers {
            string fake[3];
            string real;
        } answers;
        string tail;
    } lines;
    const string start;
    const string q;
    const string fa[consts::fa_arr_size];
    const string ra;
    const string tail;
    const char tabchar;
    int depth;

public:
    // Constructor
    QA (void)
        : start(consts::strings::start_line),
        q(consts::strings::student_question),
        ra("\"재귀함수는 자기 자신을 호출하는 함수라네\""),
        tail("라고 답변하였지."),
        tabchar(consts::tabchar_global),
        fa(&consts::strings::false_answer),
        depth(consts::initial_depth) {
        }

    
    // Managing String's Indents
    void increaseDepth (void) {
        this->depth++;
        return;
    }

    void decreaseDepth (void) {
        this->depth--;
        return;
    }

    string makeTab () const {
        string tab(this->depth * consts::tab_space_size, this->tabchar);
        return tab;
    }

    // String Access functions
    const string getStart(void) const {
        return this->start;
    }

    const string getQuestion (void) {
        return this->makeTab() + this->q;
    }

    const string getFalseAnswer (void) const {
        string nfa = "";

        for (int i = 0; i < consts::fa_arr_size; i++) {
            nfa += this->makeTab() + this->fa[i];

            if (i != 2) {
                nfa += "\n";
            }
        }

        return nfa;
    }

    string getRealAnswer (void) {
        return this->makeTab() + this->ra;
    }
    string getFQA (void) {
        return this->getQuestion() + "\n" + this->getFalseAnswer();
    }
    string getRQA (void) {
        return this->getQuestion() + "\n" + this->getRealAnswer();
    }
    string getTail (int  = 0) {
        return this->makeTab() + this->tail;
    }

    void printLine (string to_print) {
        cout << to_print << endl;
    }

    void answerRecursive (int n) {
        // Main Recursive Function
        this->increaseDepth();
        if (n == 1) {
            this->printLine(this->getRQA());
            this->printLine(this->getTail());
        } else {

            this->printLine(this->getFQA());

            this->answerRecursive(n - 1);

            this->printLine(this->getTail());
        }
        this->decreaseDepth();
    }

public:
    void answer (int n) {
        this->printLine(this->getStart());
        this->printLine(this->getFQA());
        this->answerRecursive(n);
        this->printLine(this->getTail());
        return;
    }

};


int main (void) {
    int N;
    cin >> N;
    QA qa;
    qa.answer(N);
}
