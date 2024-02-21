#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Cow {
public:
    struct Check {
    public:
        int length;
        int start;
        int end;
    };
    int t_arrive;
    struct Check t_check;

    void print (void) {
        cout << "(" << this->t_arrive;
        cout << "[" << this->t_check.start;
        cout << ", " << this->t_check.end;
        cout << ", " << this->t_check.length;
        cout << "])" << endl;
    }
    static bool sortByArrive (struct Cow const &c1, struct Cow const &c2) {
        /* Predicate function for sort by arrive time */
        return c1.t_arrive < c2.t_arrive;
    }
    void init (void) {
        this->t_check.end = this->t_check.start + this->t_check.length;
        return;
    }
    void setCheckStart (int t) {
        this->t_check.start = t;
        this->init();
        return;
    }
};

void arrangeCowTime (vector<Cow> &cow_vec) {
    for (int i = 0; i < cow_vec.size() - 1; i++) {
        if (cow_vec[i].t_check.end > cow_vec[i + 1].t_check.start) {
             cow_vec[i + 1].setCheckStart(cow_vec[i].t_check.end);
        }
    }
    return;
}
    


int main (void) {

    int N;
    cin >> N;
    vector<Cow> cow_vec;

    /* Input each cow's arrive time and end time */
    for (int i = 0; i < N; i++) {
        struct Cow cow_temp;
        cin >> cow_temp.t_arrive >> cow_temp.t_check.length;
        cow_temp.setCheckStart(cow_temp.t_arrive);
        cow_vec.push_back(cow_temp);
    }

    sort(cow_vec.begin(), cow_vec.end(), &Cow::sortByArrive);
    /* After this, cows are sorted by arrive time via ascending order */

    /*
    cout << "Before" << endl;
    for (Cow c: cow_vec) {
        c.print();
    }
    arrangeCowTime(cow_vec);

    cout << "After" << endl;
    for (Cow c: cow_vec) {
        c.print();
    }
    */

    arrangeCowTime(cow_vec);
    cout << prev(cow_vec.end())->t_check.end << endl;

    return 0;
}
