#include <iostream>
#include <string>

using namespace std;

class QuestionAnswer {
private:
    struct Lines {
        string start;
        string question;
        struct Answers {
            string fake;
            string real;
        } answers;
        string tail;
    } lines;

    struct Indents {
        char character;
        int depth;
        int tab_space_size;
    } indents;

private:
    string makeIndent (void) const {
        string indent(this->indents.depth * this->indents.tab_space_size, this->indents.character);
        return indent;
    }
    void print (const string& to_print) const {
        cout << to_print << endl;
        return;
    }
    string makeIndentString (string str) {
        size_t pos = 0;
        string token = "";
        while ((pos = str.find('\n')) != string::npos) {
            token += makeIndent() + str.substr(0, pos);
        }
    }
public:
    /* Constructor */
    QuestionAnswer (void) {}

    /* Other */
    void answer (int n) {
        this->print(this->lines.start);
        this->print(this->lines.question);
    }

};
