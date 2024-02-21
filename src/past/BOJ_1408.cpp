#include <iostream>
#include <string>

struct Time {
public:
    int h, m, s;
public:
    Time(const std::string str): 
    h(Time::toIntTime(0, str)),
    m(Time::toIntTime(1, str)),
    s(Time::toIntTime(2, str))
    {}
    Time(int h, int m, int s) : h(h), m(m), s(s) {}
private:
    static int strToInt(const std::string& str) {
        const int t = str[0] - '0';
        const int o = str[1] - '0';
        return t * 10 + o;
    }
    static std::string intToStr(int n) {
        std::string prefix = (n < 10) ? "0" : "";
        return prefix + std::to_string(n);
    }
    static int toIntTime(int mode, const std::string& str) {
        switch(mode) {
            case 0:
                return Time::strToInt(str.substr(0, 2));
            case 1:
                return Time::strToInt(str.substr(3, 2));
            case 2:
                return Time::strToInt(str.substr(6, 2));
            defaut:
                break;
        }
        return -1;
    }
public:
    int totalSecond(void) const {
        return this->h * 3600 + this->m * 60 + this->s;
    }
    std::string toString(void) {
        std::string hstr = Time::intToStr(this->h);
        std::string mstr = Time::intToStr(this->m);
        std::string sstr = Time::intToStr(this->s);
        return hstr + ":" + mstr + ":" + sstr;
    }
    friend bool operator < (const Time& c1, const Time& c2) {
        return c1.totalSecond() < c2.totalSecond();
    }
    friend bool operator > (const Time& c1, const Time& c2) {
        return c1.totalSecond() > c2.totalSecond();
    }
    friend bool operator == (const Time& c1, const Time& c2) {
        return c1.totalSecond() == c2.totalSecond();
    }
    Time operator + (const Time& to_add) {
        int nh, nm, ns;
        nh = this->h + to_add.h;
        nm = this->m + to_add.m;
        ns = this->s + to_add.s;
        while(ns >= 60) {
            ns -= 60;
            nm++;
        }
        while(nm >= 60) {
            nm -= 60;
            nh++;
        }
        return Time(nh, nm, ns);
    }
    Time operator - (const Time& to_sub) {
        int nh, nm, ns;
        if ((*this) > to_sub) {
            nh = this->h - to_sub.h;
            nm = this->m - to_sub.m;
            ns = this->s - to_sub.s;
        } else {
            nh = to_sub.h - this->h;
            nm = to_sub.m - this->m;
            ns = to_sub.s - this->s;
        }
        while(ns < 0) {
            nm--;
            ns += 60;
        }
        while(nm < 0) {
            nh--;
            nm += 60;
        }

    }
};
class Handler {
private:
    Time ctime;
    Time stime;
public:
    Handler(std::string ct, std::string st) : ctime(ct), stime(st) {}
    std::string remainTime(void) {
        if (ctime < stime) {

        } else if (ctime > stime) {

        } else {

        }
    }
};

int main(void) {
    std::string input_current_time;
    std::string input_start_time;
    std::cin >> input_current_time;
    std::cin >> input_start_time;
    Handler h(input_current_time, input_start_time);
    std::cout << h.remainTime() std::endl;
    return 0;
}
