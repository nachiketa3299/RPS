/// @date 2023-11-08T16:53 17:20
/// 백준 1138 한 줄로 서기 S2
/// 2초, 128MB, 60.7%

/*!
* N명의 사람들이 한 줄로 선다.
* 사람들은 자기보다 큰 사람이 왼쪽에 몇 명 있었는지만 기억한다.
* N명의 사람이 있고, 사람들의 키는 1부터 N까지 모두 다르다.
* 각 사람들이 기억하는 정보가 주어질 때, 줄을 어떻게 서야 하는지 출력하는 프로그램을 작성한다.
*/

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <list>
#include <iterator>

using namespace std;

typedef int         CountType;
typedef CountType   HeightType;

/// @struct Person
/// @short 사람들의 키(`height`)와 왼쪽에 나보다 큰 사람이 몇 명인지(`left`)를 저장하는 간단한 구조체.
struct Person
{
    Person(HeightType height, CountType left_greater): height(height), left(left_greater) {}
    CountType left;
    HeightType height;
};

int main()
{
    CountType N; cin >> N; ///< 사람의 수 N [1, 10] 

    /// 입력으로 들어온 사람들의 정보(@ref Person)를 저장하는 스택.
    stack<Person> person_memories; 

    for (size_t i = 0; i < N; ++i)
    {
        HeightType theight = i + 1;
        CountType tleft; cin >> tleft;
        person_memories.push(Person(theight, tleft));
    }

    /// 실제 사람들이 서 있는 순서를 저장할 리스트
    list<Person> persons;

    /// **가장 큰 놈**부터 줄을 세우면 확정적으로 세울 수 있음
    while (!person_memories.empty())
    {
        /// 리스트에 들어갈 현재 사람 `cperson`을 스택에서 뽑아온다.
        /// LIFO 구조이므로 *가장 키가 큰 사람*부터 `cperson`에 배정될 것이다.
        Person& cperson = person_memories.top(); 

        /// 여기서 `cperson`이 `persons` 리스트의 어디에 설 지 결정됨
        /// @warning `std::list` 의 반복자의 경우 **양방향 반복자(Bidirectional Iterator)**이므로, `insert_pos + cperson.left` 와 같은 형태로 사용할 수 없음
        /// @todo 근데 이거 이유는 왜 일까?
        auto insert_pos = persons.begin();
        advance(insert_pos, cperson.left);

        /// `cperson`을 지정한 자리로 삽입해 준다.
        persons.insert(insert_pos, cperson);

        person_memories.pop();
    }

    for (const Person& person : persons)
        cout << person.height << " ";

    return 0;
}