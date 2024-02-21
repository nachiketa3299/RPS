#pragma once

#include <iostream>
#include <vector>
#include <functional>

using namespace std;

#define SOL ::solution
template < typename InputType, typename AnswerType >
struct TestCase
{
    TestCase(InputType input, AnswerType answer): input(input), answer(answer) {};
    InputType input;
    AnswerType answer;
};

template < typename InputType, typename AnswerType >
struct Solver
{
    using SolutionSignature = function<AnswerType(InputType)>;
    using TestDataType = vector<TestCase<InputType, AnswerType>>;
public:
    Solver(TestDataType test_data): solution(SOL), test_data(test_data) {};
    void operator()() 
    {
        for (const auto& tc : this->test_data)
        {
            AnswerType ans = this->solution(tc.input);
            AnswerType cans = tc.answer;
            if (ans == cans) cout << "Correct: " << ans << " == " << cans << '\n';
            else cout << "Incorrect: " << ans << " != " << cans << "\n";
        }
        return;
    };
private:
    SolutionSignature solution;
    TestDataType test_data;
};

#define SOLVE(input_t, ans_t, iavi) int main(void) { Solver<input_t, ans_t> sol { (iavi) }; sol();}
