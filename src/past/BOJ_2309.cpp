// 2023-10-05T16:32
// 2023-10-05T17:12

#include <iostream>
#include <vector>
#include <algorithm>

std::size_t const P_NUM = 9;
std::size_t const A_NUM = 7;
std::size_t const H_SIZE = 100;

std::size_t Sum(std::vector<int> const &v) 
{
    std::size_t SumToReturn = 0; 
    for (auto const&e: v) 
    {
        SumToReturn += e;
    }
    return SumToReturn;
}

void Print(std::vector<int> const &v) {
    for (auto const &e: v)
    {
        std::cout << e << '\n';
    }
    return;
}

int main(void) {
    std::vector<int> InDwarfHeights(P_NUM);
    for (int& DwarfHeight: InDwarfHeights)
    {
        std::cin >> DwarfHeight;
    }

    for (std::size_t a = 0; a < P_NUM - 6; ++a) 
    {
        for (std::size_t b = a + 1; b < P_NUM - 5; ++b) 
        {
            for (std::size_t c = b + 1; c < P_NUM - 4; ++c) 
            {
                for (std::size_t d = c + 1; d < P_NUM - 3; ++d) 
                {
                    for (std::size_t e = d + 1; e < P_NUM - 2; ++e) 
                    {
                        for (std::size_t f = e + 1; f < P_NUM - 1; ++f) 
                        {
                            for (std::size_t g = f + 1; g < P_NUM; ++g) 
                            {
                                std::vector<int> CandidateDwarfHeights 
                                { 
                                    InDwarfHeights[a], 
                                    InDwarfHeights[b], 
                                    InDwarfHeights[c], 
                                    InDwarfHeights[d], 
                                    InDwarfHeights[e], 
                                    InDwarfHeights[f], 
                                    InDwarfHeights[g] 
                                };
                                if (Sum(CandidateDwarfHeights) == H_SIZE) 
                                {
                                    std::sort(CandidateDwarfHeights.begin(), CandidateDwarfHeights.end());
                                    Print(CandidateDwarfHeights);
                                    return 0;
                                }
                            }
                        }
                    }
                }
                
            }
        }
    }
    return 0;
}
