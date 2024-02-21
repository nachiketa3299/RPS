#include <iostream>
#include <string>

class Time {
public: 
    const int s;
    const std::string t;
public:
    Time(std::string tstr) : s(Time::toSecond(tstr)), t(tstr) {}
    Time(int s) : s(s), t(Time::toTimeStr(s)) {}
    Time(void) : s(0), t("00:00:00") {}
    Time(const Time& t) : s(t.s), t(std::string(t.t)) {}

    static int toSecond(std::string tstr) {
        int h = std::stoi(tstr.substr(0, 2));
        int m = std::stoi(tstr.substr(3, 2));
        int s = std::stoi(tstr.substr(6, 2));
        return h * 3600 + m * 60 + s;
    }

    static std::string toTimeStr(int s) {
        std::string hs = std::to_string(s / 3600);
        std::string ms = std::to_string((s % 3600) / 60);
        std::string ss = std::to_string((s % 3600) % 60);
        if (hs.size() < 2) hs = "0" + hs;
        if (ms.size() < 2) ms = "0" + ms;
        if (ss.size() < 2) ss = "0" + ss;
        return hs + ":" + ms + ":" + ss;
    }

    bool operator> (const Time &t) const {
        return this->s > t.s;
    }

    bool operator< (const Time &t) const {
        return this->s < t.s;
    }
    bool operator== (const Time &t) const {
        return this->s == t.s;
    }

    Time operator- (const Time &ref) const {
        return Time(this->s - ref.s);
    }

};

Time calRemainTime(const Time& c, const Time& s) {
    if (c < s) return Time(s) - Time(c);
    else if (c > s) return Time("24:00:00") - (Time(c) - Time(s));
    else return Time("24:00:00");
}


int main(void) {
    std::string ctime, stime;
    std::cin >> ctime >> stime;
    Time c(ctime);
    Time s(stime);
    Time r = calRemainTime(c, s);
    std::cout << r.t << std::endl;
    
    return 0;
}
