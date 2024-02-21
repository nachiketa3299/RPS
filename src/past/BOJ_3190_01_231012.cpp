// [2023-10-12T20:00, 2023-10-12T21:30]

#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <stack>

struct Pos2
{
	std::size_t x{ 0 }, y{ 0 };
	Pos2& IncX(void) { ++this->x; return *this; }
	Pos2& IncY(void) { ++this->y; return *this; }
	Pos2& DecX(void) { --this->x; return *this; }
	Pos2& DecY(void) { --this->y; return *this; }
	friend bool operator==(Pos2 const& Ref1, Pos2 const& Ref2) { return Ref1.x == Ref2.x && Ref1.y == Ref2.y; }
};

enum class Direction { Right=0, Down, Left, Up, MAX };
struct InputInfo
{
	std::size_t Time;
	Direction TurnDirection;
};

class Snake
{
public:
	Pos2 GetNextHeadPos(void) const
	{
		Pos2 PosToReturn = this->Body.front();
		switch (this->CurDirection)
		{
		case Direction::Right:	return PosToReturn.IncY();
		case Direction::Down:	return PosToReturn.IncX();
		case Direction::Left:	return PosToReturn.DecY();
		case Direction::Up:		return PosToReturn.DecX();
		default:				return PosToReturn;
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
			this->CurDirection = static_cast<Direction>((static_cast<int>(this->CurDirection) - 1 + static_cast<int>(Direction::MAX)) % 4);
		}
		return;
	}
	bool IsHeadCollideWithSelf(void) const
	{
		auto FindResult = std::find(this->Body.begin() + 1, this->Body.end(), this->Body.front());
		if (FindResult == this->Body.end()) return false;
		else return true;
	}
	void PushHead(Pos2 const& NextHeadPos)
	{
		this->Body.push_front(NextHeadPos);
		return;
	}
	void PopTail(void)
	{
		this->Body.pop_back();
		return;
	}
	Pos2 GetHeadPos(void) const
	{
		return this->Body.front();
	}
	std::deque<Pos2> GetBody() const
	{
		return this->Body;
	}
private:
	Direction CurDirection{ Direction::Right };
	std::deque<Pos2> Body{1};
};
class Game
{
public:
	Game(std::size_t const& InBoardSize, std::vector<Pos2> const& InApplePoss): BoardSize(InBoardSize), IsAppleExists(InBoardSize, std::vector<bool>(InBoardSize, false))
	{
		for (Pos2 const& InApplePos : InApplePoss) this->IsAppleExists[InApplePos.x][InApplePos.y] = true;
		return;
	}
	Game& Play(std::deque<InputInfo>& InputInfos, bool IsDraw=false)
	{
		Snake snake;
		while (true)
		{
			if (IsDraw) this->Draw(snake, InputInfos);
			// === HEAD ===
			// (1) 방향 전환 정보가 있다면 반영
			if (!InputInfos.empty() && InputInfos.front().Time == this->PlayTime)
			{
				snake.TurnDirection(InputInfos.front().TurnDirection);
				InputInfos.pop_front();
			}
			// (2) 다음 뱀의 머리가 위치할 곳 받아옴
			Pos2 const& NextSnakeHeadPos = snake.GetNextHeadPos();

			// (3) 다음 머리 위치가 보드 사이즈 넘어가는지 확인
			if (this->IsOutBound(NextSnakeHeadPos)) break;

			// 일단 머리를 늘린다
			snake.PushHead(NextSnakeHeadPos);
			// (4) 자기 자신이랑 출돌하는지 확인
			if (snake.IsHeadCollideWithSelf()) break;

			// === TAIL ===
			// (5) 머리 있는 곳에 사과가 있는지 확인
			// (5-T) 사과가 있다면?
			if (this->IsAppleExists[snake.GetHeadPos().x][snake.GetHeadPos().y])
			{
				// 사과를 없앤다
				this->IsAppleExists[snake.GetHeadPos().x][snake.GetHeadPos().y] = false;
			}
			// (5-F) 사과가 없다면?
			else
			{
				// 꼬리를 수축한다
				snake.PopTail();
			}
			this->PlayTime++;
		}
		this->PlayTime++;
		return *this;
	}
	bool IsOutBound(Pos2 const& InHeadPos)
	{
		return InHeadPos.x >= this->BoardSize || InHeadPos.y >= this->BoardSize || InHeadPos.x < 0 || InHeadPos.y < 0;
	}
	std::size_t GetPlayTime(void) const { return this->PlayTime; }
private:
	void Draw(Snake const& snake, std::deque<InputInfo> const& InputInfos) const
	{
		std::cout << "PlayTime: " << this->GetPlayTime();
		if (InputInfos.front().Time == this->GetPlayTime())
		{
			switch (InputInfos.front().TurnDirection)
			{
			case Direction::Right: std::cout << "Turn Right"; break;
			case Direction::Left: std::cout << "Turn Left"; break;
			}
		}
		std::cout << '\n';
		for (std::size_t i = 0; i < this->BoardSize; ++i)
		{
			char Pixel;
			for (std::size_t j = 0; j < this->BoardSize; ++j)
			{
				Pixel = '.';
				if (this->IsAppleExists[i][j]) Pixel = 'A';
				for (Pos2 const& BodyBlock : snake.GetBody())
				{
					if (BodyBlock.x == i && BodyBlock.y == j)
					{
						Pixel = 'X';
					}
				}
				if (snake.GetHeadPos().x == i && snake.GetHeadPos().y == j) Pixel = 'H';
				std::cout << Pixel;
			}
			std::cout << '\n';
		}
		return;
	}
	std::size_t BoardSize;
	std::vector<std::vector<bool>> IsAppleExists;
	std::size_t PlayTime{ 0 };
};

int main(void)
{
	// === INPUT ===
	std::size_t BoardSize; std::cin >> BoardSize; // [2, 1e2]
	std::size_t AppleCount; std::cin >> AppleCount; // [0, 1e2]
	std::vector<Pos2> ApplePoss(AppleCount);
	for (Pos2& ApplePos : ApplePoss)
	{
		std::cin >> ApplePos.x; --(ApplePos.x);
		std::cin >> ApplePos.y; --(ApplePos.y);
	}
	std::size_t InputInfoCount; std::cin >> InputInfoCount;
	std::deque<InputInfo> InputInfos;
	for (std::size_t i = 0; i < InputInfoCount; ++i)
	{
		InputInfo tInputInfo;
		std::cin >> tInputInfo.Time;
		char DirChar; std::cin >> DirChar;
		tInputInfo.TurnDirection = (DirChar == 'D' ? Direction::Right : Direction::Left);
		InputInfos.push_back(tInputInfo);
	}
	// === PROCESS ===
	Game game(BoardSize, ApplePoss);
	std::size_t const& PlayTime = game.Play(InputInfos, true).GetPlayTime();

	// === OUTPUT ===
	std::cout << PlayTime << std::endl;
	return 0;
}