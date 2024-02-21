// [2023-10-12T05:31, 2023-10-12T20:19]

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

struct Pos2
{
	Pos2() {}
	Pos2(std::size_t const& ix, std::size_t const& iy): x(ix), y(iy) {}
	void SetPos(std::size_t const& ix, std::size_t const& iy) 
	{
		this->y = iy;
		this->x = ix;
	}
	friend bool operator == (Pos2 const& Ref1, Pos2 const& Ref2) 
	{ 
		return Ref1.x == Ref2.x && Ref1.y == Ref2.y; 
	}
	Pos2& IncX() { ++this->x; return *this; }
	Pos2& IncY() { ++this->y; return *this; }
	Pos2& DecX() { --this->x; return *this; }
	Pos2& DecY() { --this->y; return *this; }
	std::size_t y{ 0 }; // 행
	std::size_t x{ 0 }; // 열
};

enum class Direction { Right=0, Down, Left, Up };

struct InputInfo
{
	std::size_t Time;
	Direction TurnDirection;
};
class Snake
{
public:
	Snake() {};
	Pos2 GetNextHeadPos() const
	{
		Pos2 PositionToReturn = this->SnakeBody.front();
		switch (this->CurDirection)
		{
		case Direction::Right:
			return PositionToReturn.IncY();
		case Direction::Down:
			return PositionToReturn.IncX();
		case Direction::Left:
			return PositionToReturn.DecY();
		default:
		case Direction::Up:
			return PositionToReturn.DecX();
		}
	}
	void TurnDirection(Direction const& ToTurn)
	{
		if (ToTurn == Direction::Right)
		{
			this->CurDirection = static_cast<Direction>((static_cast<int>(this->CurDirection) + 1) % 4);
		}
		else // ToTurn == Direction::Left
		{
			this->CurDirection = static_cast<Direction>((static_cast<int>(this->CurDirection) - 1) % 4);
		}
	}
	bool IsCollideSelf(Pos2 const& HeadPos) const
	{
		auto FindResult = std::find(this->SnakeBody.begin(), this->SnakeBody.end(), HeadPos);
		if (FindResult == this->SnakeBody.end()) return false;
		else return true;
	}
	void MoveHead(Pos2 const& NextHeadPos)
	{
		this->SnakeBody.push_front(NextHeadPos);
		return;
	}
	void CutTail()
	{
		this->SnakeBody.pop_back();
		return;
	}
private:
	Direction CurDirection{ Direction::Right };
public:
	std::deque<Pos2> SnakeBody{1, Pos2(0, 0)};
};

class SnakeGame
{
public:
	SnakeGame(std::size_t const& BoardSize, std::vector<Pos2> const& ApplePoss) :
		Size(BoardSize, BoardSize), ApplePoss(ApplePoss)
	{
	}
	std::size_t Play_UntilEnd_Return_PlayTime(std::vector<InputInfo> const& InputInfos) 
	{
		Snake snake = Snake();
		while (true)
		{
			//this->Draw(snake);
			// (0) 현재 방향 전환 정보가 있는지 확인
			auto FindResult = std::find_if(InputInfos.cbegin(), InputInfos.cend(), [this](InputInfo const& op)->bool {return op.Time == this->PlayTime; });
			if (FindResult != InputInfos.cend()) snake.TurnDirection(FindResult->TurnDirection);

			// (1) 뱀의 머리를 현재 방향으로 한칸 전진 시도함
			Pos2 const& NextHeadPos = snake.GetNextHeadPos();

			// (2) 머리가 안착한 곳이 게임 종료 조건인지 확인
			if (this->IsHeadOutBound(NextHeadPos)) break;
			/*
			bool ihb = this->IsHeadOutBound(NextHeadPos);
			bool snic = snake.IsCollideSelf(NextHeadPos);
			if (ihb) break;
			if (snic) break;
			*/


			// (3) 종료 조건 아니면 머리를 늘린다
			snake.MoveHead(NextHeadPos);

			// (4) 머리가 안착한 곳에 사과가 있는지 확인
			auto AppleFindResult = std::find(this->ApplePoss.begin(), this->ApplePoss.end(), NextHeadPos);
			bool IsThereApple = (AppleFindResult != this->ApplePoss.end());
			// (4-A) 사과가 있으면 일단 사과를 지우고, 꼬리를 수축시키지 않아도 됨
			if (IsThereApple)
			{
				this->ApplePoss.erase(AppleFindResult);
			}
			// (4-B) 사과가 없으면 꼬리를 수축시킴
			else
			{
				snake.CutTail();
			}

			if (snake.IsCollideSelf(NextHeadPos)) break;

			this->PlayTime++;
		}

		return this->PlayTime + 1;
	}
	bool IsHeadOutBound(Pos2 const& HeadPos) const
	{
		return HeadPos.x >= this->Size.x || HeadPos.y >= this->Size.y || HeadPos.x < 0 || HeadPos.y < 0;
	}
	void Draw(Snake const& snake) const
	{
		std::cout << "Current Time: " << this->PlayTime << '\n';
		std::vector<std::vector<char>> DrawBoard(this->Size.x, std::vector<char>(this->Size.y, 'O'));
		for (std::size_t i = 0; i < this->Size.x; ++i)
		{
			for (std::size_t j = 0; j < this->Size.y; ++j)
			{
				for (auto const& ApplePos : this->ApplePoss)
				{
					if (ApplePos.x != i || ApplePos.y != j) continue;
					else
					{
						DrawBoard[i][j] = 'A';
					}
				}
				for (auto const& SnakeBodyPos : snake.SnakeBody)
				{
					if (SnakeBodyPos.x != i || SnakeBodyPos.y != j) continue;
					else
					{
						if (SnakeBodyPos == snake.SnakeBody.back()) DrawBoard[i][j] = 'T';
						if (SnakeBodyPos == snake.SnakeBody.front()) DrawBoard[i][j] = 'H';
						else DrawBoard[i][j] = 'X';
					}
				}
			std::cout << DrawBoard[i][j];
			}
			std::cout << '\n';
		}
		std::cout <<  std::endl;
	}
private:
	Pos2 const Size;
	std::vector<Pos2> ApplePoss;
	std::size_t PlayTime{ 0 };
};

int main(void)
{
	// === Input ===
	std::size_t BoardSize; std::cin >> BoardSize; // [2, 1e2]
	std::size_t AppleCount; std::cin >> AppleCount; // [0, 1e2]
	std::vector<Pos2> ApplePoss(AppleCount);
	for (Pos2& ApplePos : ApplePoss)
	{
		std::cin >> ApplePos.x; // 행
		std::cin >> ApplePos.y; // 열
		--(ApplePos.x);
		--(ApplePos.y);
	}
	std::size_t InputInfoCount; std::cin >> InputInfoCount;
	std::vector<InputInfo> InputInfos(InputInfoCount);
	for (InputInfo& InputInfo : InputInfos)
	{
		std::cin >> InputInfo.Time;
		char DirChar; std::cin >> DirChar;
		InputInfo.TurnDirection = (DirChar == 'D' ? Direction::Right : Direction::Left);
	}
	// === Process ===
	SnakeGame Game(BoardSize, ApplePoss);
	std::size_t const& PlayTime = Game.Play_UntilEnd_Return_PlayTime(InputInfos);

	// === Output ===
	std::cout << PlayTime << std::endl;
	return 0;
}