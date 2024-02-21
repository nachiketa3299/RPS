// [2023-10-16T00:02,]
#include <iostream>
#include <vector>

using namespace std;

class NQueen
{
	struct BoardInfo {
		bool IsQueen { false };
		bool CanBeQueen { false };
	};
public:
	std::size_t operator()(std::size_t const& N) {
		std::vector<std::vector<BoardInfo>> Board(N, std::vector<BoardInfo>(N));
		for (std::size_t i = 0; i < N; ++i) {
		}
		return 0;
	}
};


int main(void) {
	std::size_t QueenCount; std::cin >> QueenCount; // [1, 15]
	std::cout << NQueen()(QueenCount) << std::endl;
	return 0;
}

