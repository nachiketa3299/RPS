/// @date 2023-12-19 T 17:40 18:40
/// ���� 12865 ����� �賶 G5

// �׸����� �� ������?

/*! ���� �Է�
6 13 -> 1.xx
4 8 -> 2
3 6 -> 2
5 12 -> 2.4
*/

#define PS_DEBUG

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Item
{
    int weight_{};
    int price_{};
    double ppw() const { return (double)price_ / (double)weight_; };
};

int main()
{
    int N; cin >> N; // [1, 1e2]
    int K; cin >> K; // [1, 1e5] // �ִ� ����
    vector<Item> items(N);
    for (auto& item: items)
    {
        cin >> item.weight_; // [1, 1e5]
        cin >> item.price_; // [0, 1e3]
    }
    auto pred = [](const Item& i1, const Item& i2) 
    { 
        // ���Դ�� ȿ��� ū ���� �տ� ������ �ϵ�, 
        // ���Դ�� ȿ��� ���ٸ� ������ ���� �տ� ������ ����
        const auto i1_ppw = i1.ppw();
        const auto i2_ppw = i2.ppw();
        if (i1_ppw == i2_ppw) return i1.weight_ <= i2.weight_;
        else                  return i1_ppw > i2_ppw; 
    };
    sort(items.begin(), items.end(), pred);

    // ���⼭���� �� ������ ���
    auto sit = items.cbegin();
    auto eit = items.cbegin();

    auto cur_price = (*sit).price_;
    auto cur_weight = (*sit).weight_;
    auto max_price = cur_price;
    const auto& max_weight = K;

    while(sit != items.cend())
    {
        // ���� ���� ���� ���������� eit �� �����̷��� �õ���(�ٵ� ������ �� ������ ����)
        if (cur_weight < max_weight)
        {
            // ������ �迭�� �������ΰ�?
            if (eit + 1 == items.cend())
            {
                eit = items.cbegin();
                const auto& next_toadd_item = *(eit);
                cur_weight += next_toadd_item.weight_;
                cur_price += next_toadd_item.price_;
            }
            else
            {
                const auto& next_toadd_item = *(++eit);
                cur_weight += next_toadd_item.weight_;
                cur_price += next_toadd_item.price_;
            }

            if (cur_weight <= max_weight)
            {
                max_price = (cur_price > max_price ? cur_price : max_price);
            }
        }
        // ���� ������ ���ٸ� sit�� ������(�ٵ� ������ �� ������ ����)
        else //(cur_weight >= max_weight)
        {
            if (sit + 1 == items.cend())
                break;

            const auto& next_tosub_item = *(sit);
            cur_weight -= next_tosub_item.weight_;
            cur_price -= next_tosub_item.price_;
            if (cur_weight <= max_weight)
            {
                max_price = (cur_price > max_price ? cur_price : max_price);
            }
            ++sit;
        }
    }
    cout << max_price << '\n';
}
