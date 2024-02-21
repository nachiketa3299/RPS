/*
https://www.acmicpc.net/problem/25304
준원이는 저번 주에 살면서 처음으로 코스트코를 가 봤다. 정말 멋졌다. 그런데, 몇 개 담지도 않았는데 수상하게 높은 금액이 나오는 것이다! 준원이는 영수증을 보면서 정확하게 계산된 것이 맞는지 확인해보려 한다.

영수증에 적힌,

- 구매한 각 물건의 가격과 개수
- 구매한 물건들의 총 금액

을 보고, *구매한 물건의 가격*과 *개수로 계산한 총 금액*이 영수증에 적힌 총 금액과 일치하는지 검사해보자.

- 첫째 줄에는 영수증에 적힌 총 금액 $X$가 주어진다.
- 둘째 줄에는 영수증에 적힌 구매한 물건의 종류의 수 $N$이 주어진다.
- 이후 $N$개의 줄에는 각 물건의 가격 $a$와 개수 $b$가 공백을 사이에 두고 주어진다.

구매한 물건의 가격과 개수로 계산한 총 금액이 영수증에 적힌 총 금액과 일치하면 Yes를 출력한다. 일치하지 않는다면 No를 출력한다.

 $1 ≤ X ≤ 1\,000\,000\,000$ 
 $1 ≤ N ≤ 100$ 
 $1 ≤ a ≤ 1\,000\,000$ 
 $1 ≤ b ≤ 10$ 

260000
4
20000 5
30000 2
10000 6
5000 8

>>

Yes
*/

#include <iostream>

using namespace std;

class Receipt {

private:
    int _total_price;
    int _total_type_num_item; 

    typedef struct _item_and_num {
        int price;
        int num;
    } ItemPriceAndNum;

    ItemPriceAndNum * _item_arr;

    void _getInput (void) {
        this->_item_arr = new ItemPriceAndNum[this->_total_type_num_item];
        for (int i = 0; i < this->_total_type_num_item; i++) {
            cin >> this->_item_arr[i].price >> this->_item_arr[i].num;
        }
        /*
        cout << "---" << endl;
        cout << this->_total_price << endl;
        cout << this->_total_type_num_item << endl;
        for (int i = 0; i < this->_total_type_num_item; i++) {
            cout << this->_item_arr[i].price << this->_item_arr[i].num << endl;
        }
        */
    }
    bool _verify (void) {
        int real_sum = 0;
        for (int i = 0; i < this->_total_type_num_item; i++) {
            real_sum += this->_item_arr[i].price * this->_item_arr[i].num;
        }
        if (real_sum == this->_total_price) {
            return true;
        }
        else {
            return false;
        }
    }

public:
    Receipt (int tp, int ttnoi) 
    : _total_price(tp), _total_type_num_item(ttnoi) {
        this->_getInput();
    }
    void  Verify (void) {
        if (this->_verify()) {
            cout << "Yes" << '\n';
        } else {
            cout  << "No" << '\n';
        }
    }
};


int main (void) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int total_price;
    int total_type_num_of_item;

    cin >> total_price;
    cin >> total_type_num_of_item;

    Receipt R = Receipt(total_price, total_type_num_of_item);
    R.Verify();

    return 0;
}