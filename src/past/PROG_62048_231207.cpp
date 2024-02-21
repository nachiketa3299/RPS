/*!
* @file PROG_62048_231207.cpp
* @date 2023-12-07 T 1907
* 프로그래머스 62048 멀쩡한 사각형 L2
*/

/*!
* 가로 길이가 W, 세로 길이가 H인 직사각형 종이가 있다.
* 가로, 세로 방향과 평행하게 격자 형태로 선이 그어져 있다.
* 모든 격자칸은 1 x 1 크기이다.
* 누군가 이 종이를 대각선 꼭지점 2개를 잇는 방향으로 잘라 놓아서, 크기가 같은 직각삼각형 2개로 나뉘어 버렸다.
* 새로운 종이를 구할 수가 없어서, 1 x 1 로 격자와 평행한 방향으로 잘라 사용할 수 있는 만큼만 사용한다.
* W, H 가 주어질 때, 사용할 수 있는 정사각형의 개수를 구하는 `solution` 함수를 완성한다.
* W, H는 1 0000 0000 (1억) 이하의 자연수이다.
* W:8 H:12 R:80
*/

#define PS_DEBUG
//#undef PS_DEBUG

#include <iostream>

using namespace std;
using LongInt = long long;

LongInt solution(int w, int h)
{
    LongInt answer = 0;

    double tilt = (double)h / (double)w;

    // 좌하단이 (0, 0) 우상단이 (W, H)
    for (int i = 0; i < w; ++i)
        answer += ((tilt * i) + h) * 2;
    return answer;
}
