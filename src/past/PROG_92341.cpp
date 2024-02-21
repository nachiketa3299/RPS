#include <string>
#include <vector>
#include <iomanip>
#include <map>
#include <sstream>
#include <chrono>
#include <cmath>
#include <stack>

using namespace std;
using CarID = string;
using FeePolicy = vector<int>;

enum class InOut { IN, OUT };
enum FP
{
    BASIC_TIME=0,
    BASIC_FEE,
    PER_MIN,
    PER_FEE
};

/// @short 시간 범위를 표현하는 구조체이다. time_t에 대한 래퍼로 작동한다.
/// @todo time_t와 chrono 사용법이 조금 복잡하고 언젠가 정리해야 겠다고 생각했는데 알아봐야 할 것 같다.
struct TimeRange
{
    /// @param[in] in_time_str 입차 시간에 대한 문자열이다.
    /// @param[in] out_time_str 출차 시간에 대한 문자열이다. 만일 출차 시간이 제공되지 않았다면, 기본적으로 23:59에 출차한 것으로 간주한다.
    TimeRange(const string& in_time_str, const string& out_time_str="23:59"): in_time(TimeRange::make_time(in_time_str)), out_time(TimeRange::make_time(out_time_str)) {};

    /// @param[in] io 입차인지 출차인지에 대한 정보이다.
    /// @param[in] time_str 시간에 대한 문자열이다.
    /// @todo 현재 io는 항상 InOut::OUT일때만 쓰인다.
    void SetTime(const InOut& io, const string& time_str)
    {
        switch (io)
        {
        case InOut::IN:
            in_time = TimeRange::make_time(time_str);
            break;
        default:
        case InOut::OUT:
            out_time = TimeRange::make_time(time_str);
            break;
        }
    }
    /// @short 현재 시간 범위의 끝 시간(out_time)에서 시작 시간(in_time)을 뺀 것을 분으로 형변환 하여 반환한다.
    /// @return 끝 시간과 시작 시간의 차 (분)
    int GetTimeDiffInMin() const
    {
        auto min_diff = chrono::minutes(static_cast<int>(difftime(this->out_time, this->in_time) / 60));
        return min_diff.count();
    }
    time_t in_time;
    time_t out_time;
private:
    /// @param[in] time_str "HH:MM" 형태로 주어지는 시간 문자열이다.
    /// @return time_t 형식의 시간 정보이다.
    /// @todo tm, time_t, 이거 다시 찾아볼 것.
    static time_t make_time(const string& time_str)
    {
        struct tm t = {};
        istringstream ss(time_str); ss >> get_time(&t, "%H:%M");
        time_t time = mktime(&t);
        return time;
    }
};

///  @short 어떤 일련번호를 가진 차량의 모든 입출차 기록을 보유하고 있는 구조체
struct ParkData
{
    /// @short 스택에 들어있는 시간 정보를 들어온 요금 정책을 토대로 최종 주차요금을 계산한다.
    /// @param[in] f 요금 정책. 고정 길이 4를 가진 배열이며, 각 인덱스의 정보는 열거형 #FP로 접근한다.
    /// @see @ref FP
    int GetParkFee(const FeePolicy& f)
    {
        int total_fee = f[BASIC_FEE];
        int total_park_time = 0;

        /// 출차 시간 정보가 없을 때까지 총 주차시간을 계산한다.
        while (!this->time_ranges.empty())
        {
            total_park_time += this->time_ranges.top().GetTimeDiffInMin();
            this->time_ranges.pop();
        }

        /// 만약 전체 주차 시간이 요금 정책의 기본 주차 시간을 초과했다면 다음을 수행해서 추가요금을 계산한다.
        if (total_park_time > f[BASIC_TIME])
        {
            int over_time = total_park_time - f[BASIC_TIME];
            int over_fee = (int)(ceil((double)over_time / f[PER_MIN])) * f[PER_FEE];
            total_fee += over_fee;
        }

        return total_fee;
    }

    /// @param[in] io InOut::IN, InOut::OUT 둘 중 하나인 입출차 정보이다.
    /// @param[in] time_str "HH:MM" 형태로 들어오는 시간 문자열이다.
    /// @details 입차인 경우 TimeRange(입차) 형태로 time_ranges 스택에 푸쉬한다. 출차의 경우 time_ranges 스택의 탑의 out_time을 수정한다. out_time은 기본적으로 23:59로 초기화 되어 있다.
    void SetTimeData(const InOut& io, const string& time_str)
    {
        switch (io)
        {
        case InOut::IN:
            this->time_ranges.push(TimeRange(time_str));
            break;
        default:
        case InOut::OUT:
            this->time_ranges.top().SetTime(io, time_str);
            break;
        }
        return;
    }

    /// @short 한 차량은 출차를 여러번 할 수 있기 때문에 시간 정보는 컨테이너에 들어가야 한다.
    /// @todo 사실 stack으로 구현한 의도는 stack이 LIFO(Last-In First-Out) 구조이기 때문이고, 데이터가 항상 입차->출차->입차->출차 로 일어나기 때문이었는데 사실 한 차량이 여러번 입출차할 수 있는지 중간에 알아서 (입차, 출차)->(입차, 출차) 형태가 되어버렸다. 이거 한번 의미에 맞게 다시 구현해보기.
    stack<TimeRange> time_ranges;
};

namespace raw_len
{
    constexpr size_t time = 5;
    constexpr size_t id = 4;
}

vector<int> solution(FeePolicy fees, vector<string> records)
{
    vector<int> answer;

    /// 차량 번호에 대해 오름차순으로 정렬되어야 하므로, 차량 번호(CarID)에 대한 맵 형식으로 데이터를 관리
    /// @todo Lexiographical Order? 언젠가 얼핏 본거 같은데 알아볼 것
    map<CarID, ParkData> park_datas; 

    /// records는 차량의 출차 정보에 대한 문자열들의 벡터이므로 순회하면서 다음을 수행함
    for (const auto& record : records)
    {
        /// 들어온 출차 정보는 "12:39 1234 In" 형식이다.
        /// records[0:5]는 출차 시간이다. 예) "12:39"
        const string raw_time_str = record.substr(0                                  , raw_len::time);
        /// records[6:10]은 차량 번호(CarID)이다. 예) "1234"
        const string raw_id_str   = record.substr(raw_len::time + 1                  , raw_len::id  );
        /// records[11:-1]은 차가 나간 것인지, 들어온 것인지에 대한 정보이다. "In"이면 IN으로, "Out"이면 OUT으로 처리한다.
        const InOut  io           = record.substr(raw_len::time + 1 + raw_len::id + 1, -1           ).front() == 'I' ? InOut::IN : InOut::OUT;

        /// 특정 차량 번호를 가진 차량의 출차시간 정보를 기입한다. 
        park_datas[raw_id_str].SetTimeData(io, raw_time_str);
    }

    /// 이 시점에서 park_datas는 차량 번호(CarID)에 대해 출차 시간 정보를 완벽하게 가지고 있게 된다.
    for (auto& park_data : park_datas)
    {
        /// 각 차량에 대해서 요금 정책 fees로 요금을 계산한다.
        answer.push_back(park_data.second.GetParkFee(fees));
    }
    return answer;
}
