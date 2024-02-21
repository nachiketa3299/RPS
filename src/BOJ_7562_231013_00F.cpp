// [2023-10-13T13:44, 2023-10-13T16:44]
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

struct Pos2
{
	Pos2() {}
	Pos2(std::size_t const& ix, std::size_t const& iy): x(ix), y(iy) {}
	void SetOffset(Pos2 const& OffPos) { this->SetOffset(OffPos.x, OffPos.y); return; }
	void SetOffset(std::size_t const& OffX, std::size_t const& OffY) { this->x += OffX; this->y += OffY; return; }
	bool IsInBound(std::size_t MinBoundValue, std::size_t MaxBoundValue)
	{
		bool IsXInBound = this->x < MaxBoundValue && this->x >= 0;
		bool IsYInBound = this->y < MaxBoundValue && this->y >= 0;
		return IsXInBound && IsYInBound;
	}
	std::size_t x{ 0 }, y{ 0 };
	friend bool operator==(Pos2 const& Ref1, Pos2 const& Ref2) { return Ref1.x == Ref2.x && Ref1.y == Ref2.y; }
};
class Knight
{
public:
	Knight() {}
	Knight(Pos2 const& InPos): Pos(InPos) {}
	std::vector<Pos2> GetPossiblePoss(std::size_t const& Boundsize)
	{
		std::vector<Pos2> PossiblePoss;
		for (Pos2 const& PossibleOffset : this->PossibleOffsets)
		{
			Pos2 StartPos = this->Pos;
			StartPos.SetOffset(PossibleOffset);
			if (!StartPos.IsInBound(0, Boundsize)) continue;
			PossiblePoss.push_back(StartPos);
		}
		return PossiblePoss;
	}
private:
	Pos2 Pos;
	std::vector<Pos2> const PossibleOffsets { Pos2(2, 1), Pos2(2, -1), Pos2(-2, 1), Pos2(-2, -1), Pos2(1, 2), Pos2(1, -2), Pos2(-1, 2), Pos2(-1, -2) };
};

class KnightGraph
{
public:
	KnightGraph(std::size_t const& InBoardSize, Pos2 const& InStartPos):
		BoardSize(InBoardSize), 
		AdjList(InBoardSize * InBoardSize, std::vector<std::size_t>())
	{
		this->Vertices.reserve(InBoardSize * InBoardSize);
		this->PopulateGraph(InStartPos);
		/*
		for (auto const& av : this->AdjList)
		{
			std::size_t CurVerIdx = &av - &this->AdjList.front();
			Pos2 CurVerPos = this->Vertices[CurVerIdx];
			std::cout << CurVerIdx << "(" << CurVerPos.x << ", " << CurVerPos.y << ") | ";
			for (auto const& a : av)
			{
				Pos2 CurVerPos = this->Vertices[a];
				std::cout << a << "(" << CurVerPos.x << ", " << CurVerPos.y << "), ";
			}
			std::cout << '\n';
		}
		*/
		return;
	}
	std::size_t GetMinimumMovingCount(Pos2 const& Destination, bool IsDraw=false)
	{
		if (IsDraw) this->Draw();

		std::size_t CurMovingCount = 0;

		this->BFS(CurMovingCount, Destination);

		return CurMovingCount;
	}
	void BFS(std::size_t& MovingCount, Pos2 const& Destination)
	{
		Pos2 const StartPos = this->Vertices.front();
		Pos2 const Endpos = Destination;
		std::size_t const StartPosIdx = 0;
		std::size_t const EndPosIdx = std::find(this->Vertices.cbegin(), this->Vertices.cend(), Destination) - this->Vertices.begin();

		std::vector<bool> Visited(this->Vertices.size(), false);
		std::queue<std::size_t> ToVisitQueue;
		std::vector<std::size_t> Distance(this->BoardSize * this->BoardSize, 0);

		ToVisitQueue.push(StartPosIdx);

		this->BFS_Recur(Distance, EndPosIdx, Visited, ToVisitQueue);
		MovingCount = Distance[EndPosIdx];
		return;
	}
	void BFS_Recur(std::vector<std::size_t>& Distance, std::size_t const& EndPosIdx, std::vector<bool>& Visited, std::queue<std::size_t>& ToVisitQueue)
	{
		while (!ToVisitQueue.empty())
		{
			std::size_t& CurVerIdx = ToVisitQueue.front();
			Visited[CurVerIdx] = true;
			std::vector<std::size_t> const& CurAdjList = this->AdjList[CurVerIdx];

			for (std::size_t AdjVerIdx : CurAdjList)
			{
				if (!Visited[AdjVerIdx])
				{
					ToVisitQueue.push(AdjVerIdx);
					Distance[AdjVerIdx] = Distance[CurVerIdx] + 1;
					Visited[AdjVerIdx] = true;
					if (AdjVerIdx == EndPosIdx) return;
				}
			} 
			ToVisitQueue.pop();
		}
		return;
	}
private:
	void Draw() const
	{
		std::vector<std::vector<char>> Pixels(BoardSize, std::vector<char>(BoardSize, '.'));
		for (auto const& Vertex : this->Vertices)
		{
			std::size_t const Idx = &Vertex - &this->Vertices.front();
			Pixels[Vertex.x][Vertex.y] = static_cast<char>(Idx + 48);
		}
		for (std::size_t i = 0; i < this->BoardSize; ++i)
		{ 
			for(std::size_t j = 0; j < this->BoardSize; ++j)
			{ 
				std::cout << Pixels[i][j];
			}
			std::cout << '\n';
		}
		std::cout << std::endl;
	}
	void PopulateGraph(Pos2 const& InStartPos)
	{
		this->Vertices.push_back(InStartPos);

		std::vector<Pos2> PossibleVertices;
		auto sit = this->Vertices.begin();
		for(;;++sit)
		{
			auto eit = this->Vertices.end() - 1;

			Pos2 const& CurVertex = *(sit);
			std::size_t const CurVertexIdx = &CurVertex - &this->Vertices.front();
			Knight CurKnight = Knight(CurVertex);
			std::vector<Pos2> CurPossiblePoss = CurKnight.GetPossiblePoss(this->BoardSize);
			for (Pos2 const& CurPossiblePos : CurPossiblePoss)
			{
				// 이미 있는지 확인
				bool IsAlreadyIn = (std::find(this->Vertices.cbegin(), this->Vertices.cend(), CurPossiblePos) != this->Vertices.cend());
				if (IsAlreadyIn) continue;
				// 없었으면 추가함
				this->Vertices.push_back(CurPossiblePos);
				eit = this->Vertices.end() - 1;
				std::size_t const PushedVertexIdx = this->Vertices.size() - 1;
				// 연결 리스트 연결함
				this->AdjList[CurVertexIdx].push_back(PushedVertexIdx);
				this->AdjList[PushedVertexIdx].push_back(CurVertexIdx);
			}
			if (sit == eit) break;
		}
	}
private:
	std::size_t const BoardSize;

	std::vector<Pos2> Vertices;
	std::vector<std::vector<std::size_t>> AdjList;
};

int main(void)
{
	// ===INPUT===
	std::size_t TestCaseCount; std::cin >> TestCaseCount;
	for (std::size_t i = 0; i < TestCaseCount; ++i)
	{
		std::size_t BoardSize; std::cin >> BoardSize; // [4, 3e2]
		std::size_t CurPosX, CurPosY; std::cin >> CurPosX >> CurPosY;
		Pos2 const CurPos = Pos2(CurPosX, CurPosY);
		std::size_t ToPosX, ToPosY; std::cin >> ToPosX >> ToPosY;
		Pos2 const ToPos = Pos2(ToPosX, ToPosY);
		// ===PROCESS===
		KnightGraph kgraph = KnightGraph(BoardSize, CurPos);
		std::size_t MinimumMovingCount = kgraph.GetMinimumMovingCount(ToPos, false);
		// ===OUTPUT===
		std::cout << MinimumMovingCount << std::endl;
	}
	return 0;
}