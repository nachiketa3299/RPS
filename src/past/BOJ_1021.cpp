#include <iostream>

using namespace std;

struct Node {
    int pos;
    Node * next;
};

class Queue {
private:
    Node * head;
    int pos_offset;
public:
    Queue (void) {
        this->head = nullptr;
        this->pos_offset = 0;
    }
    Queue (int N, int * pos) {
        Queue();
        for (int i = 0; i < N; i++) {
            this->push_back(i + 1);
        }
    }

    void push_back (struct Node * new_node) {

        if (this->head == nullptr) {
            this->head = new_node;
        } else {
            struct Node * end_node = this->traverse();
            end_node->next = new_node;
            new_node->next = this->head;
        }
        return;
    }
    void push_back (int v) {
        struct Node * t_node = new Node;
        t_node->pos = v;
        this->push_back(t_node);
        return;
    }
    void makeLink (struct Node * o, struct Node * n) {
        o->next = n;
        return;
    }
    struct Node * traverse (void) {
        struct Node * start_pos = this->head;
        if (start_pos->next == nullptr) {
            return start_pos;
        } else {
            do {
                start_pos = start_pos->next;
            } while (start_pos->next != this->head);
            return start_pos;
        }
    }
    struct Node * traverse (int pos) {
        struct Node * start_pos = this->head;
        for (int i = 1; i < pos; i++) {
            start_pos = start_pos->next;
        }
        return start_pos;
    }

    int distance (int pos) {
        int distance;

        return distance;
        
    }

    void discard (void) {
        struct Node * head_next = this->head->next;
        struct Node * end_node = this->traverse();

        this->head->next = nullptr;

        this->head = head_next;
        end_node->next = head_next;

        return;
    }

    void moveLeft (void) {
        this->head = this->head->next;
        this->pos_offset++;
        return;
    }

    void moveRight (void) {
        this->head = this->traverse();
        this->pos_offset--;
        return;
    }

};

int main (void) {
    int N, M;
    cin >> N >> M;
    int * pos_arr = new int [M];
    for (int i = 0; i < M; i++) {
        cin >> pos_arr[i];
    }

    delete [] pos_arr;
    return 0;
}
