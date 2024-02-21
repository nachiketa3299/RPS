/// 백준 팩토리얼2 B5
/// @date 2023-12-15 T 21:51 10min
#define PS_DEBUG

#include <iostream>

using namespace std;

template<size_t N>
struct Factorial 
{
    static const size_t result = N * Factorial<N - 1>::result;
};

template<>
struct Factorial<1>
{
    static const size_t result = 1;
};

template<>
struct Factorial<0>
{
    static const size_t result = 1;
};


int main()
{
    int N; cin >> N;
    switch(N)
    {
        case 0: cout << Factorial<0>::result; break;
        case 1: cout << Factorial<1>::result; break;
        case 2: cout << Factorial<2>::result; break;
        case 3: cout << Factorial<3>::result; break;
        case 4: cout << Factorial<4>::result; break;
        case 5: cout << Factorial<5>::result; break;
        case 6: cout << Factorial<6>::result; break;
        case 7: cout << Factorial<7>::result; break;
        case 8: cout << Factorial<8>::result; break;
        case 9: cout << Factorial<9>::result; break;
        case 10: cout << Factorial<10>::result; break;
        case 11: cout << Factorial<11>::result; break;
        case 12: cout << Factorial<12>::result; break;
        case 13: cout << Factorial<13>::result; break;
        case 14: cout << Factorial<14>::result; break;
        case 15: cout << Factorial<15>::result; break;
        case 16: cout << Factorial<16>::result; break;
        case 17: cout << Factorial<17>::result; break;
        case 18: cout << Factorial<18>::result; break;
        case 19: cout << Factorial<19>::result; break;
        case 20: cout << Factorial<20>::result; break;
    } 
    return 0;
}