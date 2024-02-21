#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <limits>

struct Pos2
{
	Pos2(void) {};
	Pos2(int const& ix, int const& iy): x(ix), y(iy) {};
	Pos2& SetOffset(Pos2 const& OffPos) { this->SetOffset(OffPos.x, OffPos.y); return *this; };
	Pos2& SetOffset(int const& OffX, int const& OffY) { this->x += OffX; this->y += OffY; return *this; };
	bool IsXYInBound(int const& InMinBound, int const& InMaxBound) const { return this->IsXInBound(InMinBound, InMaxBound) && this->IsYInBound(InMinBound, InMaxBound); };
	bool IsXInBound(int const& InMinBound, int const& InMaxBound) const { return InMinBound <= this->x && this->x < InMaxBound; };
	bool IsYInBound(int const& InMinBound, int const& InMaxBound) const { return InMinBound <= this->y && this->y < InMaxBound; };
	friend bool operator==(Pos2 const& Ref1, Pos2 const& Ref2) { return Ref1.x == Ref2.x && Ref1.y == Ref2.y; };
public:
	int x{ 0 }, y { 0 };
};
namespace Chess
{
	class Knight
	{
	public:
		Knight(int const& InStartPosX, int const& InStartPosY) : Pos(InStartPosX, InStartPosY) {};
		Knight(Pos2 const& InStartPos) : Pos(InStartPos) {};
		std::vector<Pos2> const GetPossiblePoss(int const& BoardBound) const
		{
			std::vector<Pos2> PossiblePoss;
			for (Pos2 const& PossibleOffset : Chess::Knight::PossibleOffsets)
			{
				Pos2 BasePos = this->Pos;
				Pos2 const PossiblePos = BasePos.SetOffset(PossibleOffset);
				if (PossiblePos.IsXYInBound(0, BoardBound)) PossiblePoss.push_back(PossiblePos);
			}
			return PossiblePoss;
		}
		Pos2 const& GetPos(void) const { return this->Pos; };
	protected:
		Pos2 Pos;
		static std::vector<Pos2> const PossibleOffsets;
	};

	std::vector<Pos2> const Chess::Knight::PossibleOffsets { Pos2(2, 1), Pos2(2, -1), Pos2(-2, 1), Pos2(-2, -1), Pos2(1, 2), Pos2(1, -2), Pos2(-1, 2), Pos2(-1, -2)};

	class Board
	{
	public:
		Board(int const& InBoardSize): BoardSize(InBoardSize) {};
		int GetMinMovingCount(Knight const& InKnight, Pos2 const& InEndPos)
		{
			int const MaxVerticesCount = this->BoardSize * this->BoardSize;

			struct VertexInfo
			{
				bool IsVisited{ false };
				int Distance{ std::numeric_limits<decltype(this->Distance)>::max() };
			};

			std::vector<std::vector<VertexInfo>> Vertices(this->BoardSize, std::vector<VertexInfo>(this->BoardSize));
			VertexInfo& StartVertex = Vertices[InKnight.GetPos().x][InKnight.GetPos().y];
			StartVertex.IsVisited = true; 
			StartVertex.Distance = 0;

			std::queue<Pos2> VerticesToVisit; VerticesToVisit.push(InKnight.GetPos());

			while (!VerticesToVisit.empty())
			{
				Pos2 const& CurKnightPos = VerticesToVisit.front();
				VertexInfo& CurVertexInfo = Vertices[CurKnightPos.x][CurKnightPos.y];
				if (CurKnightPos == InEndPos) return CurVertexInfo.Distance;

				for (Pos2 const& PossiblePos : Knight(CurKnightPos).GetPossiblePoss(this->BoardSize))
				{
					VertexInfo& PossibleVertex = Vertices[PossiblePos.x][PossiblePos.y];
					if (PossibleVertex.IsVisited) continue;

					PossibleVertex.IsVisited = true;
					PossibleVertex.Distance = CurVertexInfo.Distance + 1;

					VerticesToVisit.push(PossiblePos);
				}
				VerticesToVisit.pop();
			}

			return 0;
		}
	private:
		int BoardSize;
	};
}



int main(void)
{
	int TestCaseCount; std::cin >> TestCaseCount;
	for (int TestCase = 0; TestCase < TestCaseCount; ++TestCase)
	{
		/* === INPUT === */
		int BoardSize; std::cin >> BoardSize; // [4, 3e2]
		int CurPosX, CurPosY; std::cin >> CurPosX >> CurPosY;
		int EndPosX, EndPosY; std::cin >> EndPosX >> EndPosY;
		/* === PROCESS === */
		Pos2 const StartPos = Pos2(CurPosX, CurPosY);
		Pos2 const EndPos = Pos2(EndPosX, EndPosY);
		Chess::Board board = Chess::Board(BoardSize);
		int const MinMovingCount = board.GetMinMovingCount(Chess::Knight(StartPos), EndPos);
		/* ===PRINT=== */
		std::cout << MinMovingCount << '\n';
	}
	return 0;
}