/// @file BOJ_2852.cpp
/// @date 2023-11-22T13:07 2023-11-12T14:24 1시간 17분
/// 백준 2852 (NBA 농구)
/// 1초 / 128MB

/*!
* 동혁이는 NBA에서 골이 들어갈 때마다
* - (1) 골이 들어간 시간
* - (2) 골을 넣은 팀
* 을 적는 이상한 취미를 가지고 있다.
* 농구 경기는 48분간 진행된다. 
* 각 팀이 몇 분동안 이기고 있었는가를 출력하는 프로그램을 작성한다.
*/

#include <iostream>
#include <string>
#include <vector>
#include <array>

using namespace std;
using CountType = size_t;
using RawStringTimeType = string;
using TeamNumberType = size_t;
using TimeType = int;

#define TEAM_NONE 0
#define TEAM_1 1
#define TEAM_2 2
#define MAX_TEAM_NUM 3

class Time
{
public:
    Time(): min(0), sec(0) {};
    Time(TimeType min, TimeType sec): min(min), sec(sec) {};
    Time(TimeType total_sec): min(total_sec / 60), sec(total_sec % 60) {};
public:
    TimeType GetTotalSec() const { return this->min * 60 + this->sec; };
    void Flush() { this->min = 0; this->sec = 0; };
public:
    Time& operator+=(const Time& oth)
    {
        TimeType total_sec = this->GetTotalSec() + oth.GetTotalSec();
        this->min = total_sec / 60;
        this->sec = total_sec % 60;
        return *this;
    }
    friend Time operator-(const Time& left, const Time& right)
    {
        return Time(left.GetTotalSec() - right.GetTotalSec());
    }
    friend Time operator+(const Time& left, const Time& right)
    {
        return Time(left.GetTotalSec() + right.GetTotalSec());
    }
    string ToString() const
    {
        return Time::PadTimeString(this->min) + ":" + Time::PadTimeString(this->sec);
    }
    static string PadTimeString(const TimeType& time)
    {
        return time < 10 ? "0" + to_string(time) : to_string(time);
    }
    static Time GetMaxTime()
    {
        return Time(48, 0);
    }
private:
    TimeType min = 0;
    TimeType sec = 0;
};


struct GoalData
{
    /// @short 입력을 받아서 팀 / 시간 형태로 저장한다.
    GoalData()
    {
        cin >> this->team_number;
        RawStringTimeType input_time_str; cin >> input_time_str;
        this->time = Time(stoi(input_time_str.substr(0, 2)), stoi(input_time_str.substr(3, 2)));
        return;
    }
    TeamNumberType team_number = 0;
    Time time;
};

void PrintWinningTimePerTeam(const vector<GoalData>& goals)
{
    /// @brief 팀별 점수를 기록
    array<CountType, MAX_TEAM_NUM> scores; scores.fill(0);
    /// @brief 팀별 이기는 시간 기록
    array<Time, MAX_TEAM_NUM> winning_time; 
    /// @brief 직전에 이긴 팀 기록. 초기엔 아무도 이기고 있지 않으므로 TEAM_NONE
    TeamNumberType last_winning_team = TEAM_NONE;
    /// @brief 직전의 득점 시간 기록 (없는 경우 초기값 00:00)
    Time last_winning_team_time;
    /// @brief 이기는 팀이 바뀌면 이 버퍼의 값을 @ref winning_time 에 비로소 합산.
    Time winning_time_buffer;

    for (const GoalData& goal : goals)
    {
        /// 득점해주고
        ++scores[goal.team_number];

        /// @brief 지금 이기고 있는 팀이 어디냐. (동점일 경우 TEAM_NON)
        TeamNumberType current_winning_team;
        if (scores[TEAM_1] > scores[TEAM_2])      current_winning_team = TEAM_1;
        else if (scores[TEAM_1] < scores[TEAM_2]) current_winning_team = TEAM_2;
        else                                      current_winning_team = TEAM_NONE;

        /// 버퍼 값 업데이트 (직전에 이긴 팀이고 현재는 이기고 있지 않더라도, **지금 이 순간 까지** 이긴 것이므로 업데이트 해주어야함)
        winning_time_buffer += goal.time - last_winning_team_time;
        /// 직전의 득점 시간 업데이트
        last_winning_team_time = goal.time;

        /// 직전에 이기던 팀과 지금 이기는 팀이 다른 경우 -> 버퍼를 비워주고 새로운 세팅작업
        if (last_winning_team != current_winning_team)
        {
            /// 직전에 이기던 팀의 총 이기는 시간에 버퍼 값을 추가해줌
            winning_time[last_winning_team] += winning_time_buffer;
            /// 버퍼를 비워줌
            winning_time_buffer.Flush();
            /// 직전에 이기던 팀을 현재 이기턴 팀으로 바꿔줌
            last_winning_team = current_winning_team;
        }
    }

    /// 마지막에 버퍼가 무조건 남아있기 때문에 비워 주어야 한다.
    winning_time_buffer += Time::GetMaxTime() - last_winning_team_time;
    winning_time[last_winning_team] += winning_time_buffer;

    cout << winning_time[TEAM_1].ToString() << '\n';
    cout << winning_time[TEAM_2].ToString() << '\n';
    return;
}

int main()
{
    {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr); std::cout.tie(nullptr);
    }

    /// @brief 골이 들어간 횟수 N [1, 100]
    CountType input_goal_count; cin >> input_goal_count;
    vector<GoalData> goals;
    for (CountType i = 0; i < input_goal_count; ++i)
        goals.push_back(GoalData());

    ::PrintWinningTimePerTeam(goals);

    return 0;
}
 
 