#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Person {
private:
    int age;
    string name;
    int index;
public:
    Person (void) {}
    void init (int n_age, string n_name, int n_index) {
        this->age = n_age;
        this->name = n_name;
        this->index = n_index;
        return;
    }

    void print (void) {
        cout << this->age << " " << this->name << endl;
    }

    static bool compare (const Person& p1, const Person& p2) {
        if (p1.age != p2.age) {
            return p1.age < p2.age;
        } else {
            return p1.index < p2.index;
        }
    }
};

int main (void) {
    int N;
    cin >> N;

    Person* p_arr = new Person [N];

    for (int i = 0; i < N; i++) {
        int age;
        string name;
        int index = i;
        cin >> age >> name;
        p_arr[i].init(age, name, index);
    }

    sort(p_arr, p_arr + N, Person::compare);

    for (int i = 0; i < N; i++) {
        p_arr[i].print();
    }

    return 0;
}
