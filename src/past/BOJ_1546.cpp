/*
https://www.acmicpc.net/problem/1546

세준이는 기말고사를 망쳤다. 세준이는 점수를 조작해서 집에 가져가기로 했다. 일단 세준이는 자기 점수 중에 최댓값을 골랐다. 이 값을 M이라고 한다. 그리고 나서 모든 점수를 점수/M*100으로 고쳤다.

예를 들어, 세준이의 최고점이 70이고, 수학점수가 50이었으면 수학점수는 50/70*100이 되어 71.43점이 된다.

세준이의 성적을 위의 방법대로 새로 계산했을 때, 새로운 평균을 구하는 프로그램을 작성하시오.

첫째 줄에 시험 본 과목의 개수 N이 주어진다. 이 값은 1000보다 작거나 같다. 둘째 줄에 세준이의 현재 성적이 주어진다. 이 값은 100보다 작거나 같은 음이 아닌 정수이고, 적어도 하나의 값은 0보다 크다.

첫째 줄에 새로운 평균을 출력한다. 실제 정답과 출력값의 절대오차 또는 상대오차가 10-2 이하이면 정답이다.

3
40 80 60
>>
75.0

3
10 20 30
>>
66.666667

4
1 100 100 100
>>
75.25

5
1 2 4 8 16
>>
38.75
*/

#include <iostream>

using  namespace std;

void inputScore (double * arr, int N) {
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    return;
}
double findMaxScore (double * origin, int N) {
    double max_score = origin[0]; 
    for (int i = 0; i < N; i++) {
        if (origin[i] > max_score) {
            max_score = origin[i];
        }
    }
    return max_score;
}

void calNewScore (double max, double * origin, double * nnew, int N) {
    for (int i = 0; i < N; i++) {
        nnew[i] = (origin[i] / max) * 100;
    }
}
double calNewAverage(double * nnew, int  N) {
    double sum = 0.0;
    for (int i = 0; i < N; i++) {
        sum += nnew[i];
    }
    return sum / N;
}

int main (void) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    // number of subjects N
    int N;
    cin  >> N;

    // input scores
    double * original_scores = new double [N];
    inputScore(original_scores, N);

    // find max scores
    double max_original_score = findMaxScore(original_scores, N);

    // calculate new scores
    double * new_scores = new double [N];
    calNewScore(max_original_score, original_scores, new_scores, N);

    double new_average = calNewAverage(new_scores, N);
    cout.precision(14);
    cout << new_average << '\n';

    return 0;
}