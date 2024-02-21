// [2023-10-10T16:33, 2023-10-10T17:21] 27+21 = 48

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>

class Graph
{
public:
	Graph(std::size_t const& InNOfVertices) : AdjList(InNOfVertices) { }
public:
	void AddEdge(std::size_t const& Start, std::size_t const& End)
	{
		// (Start: End) 를 추가함
		std::vector<std::size_t>& CurAdjList = this->AdjList[Start];
		if (std::find(CurAdjList.begin(), CurAdjList.end(), End) == CurAdjList.end())
		{
			CurAdjList.push_back(End);
		}
		// (End: Start) 를 추가함
		std::vector<std::size_t>& OtherAdjList = this->AdjList[End];
		if (std::find(OtherAdjList.begin(), OtherAdjList.end(), End) == OtherAdjList.end())
		{
			OtherAdjList.push_back(Start);
		}
		return;
	}
	void SortEdges(void)
	{
		for (std::vector<std::size_t>& CurAdjList : this->AdjList)
		{
			std::sort(CurAdjList.begin(), CurAdjList.end());
		}
		return;
	}
#pragma region DFS
public:
	void DFS(void(*Func)(std::size_t const&), std::size_t const& StartIndex) 
	{
		std::vector<bool> IsVisited(this->AdjList.size(), false);
		std::stack<std::size_t> IndexToVisit;

		// 시작 설정
		IndexToVisit.push(StartIndex);
		Func(StartIndex);
		IsVisited[StartIndex] = true;

		DFS_recur(Func, IsVisited, IndexToVisit);
		return;
	}
private:
	void DFS_recur(void(*Func)(std::size_t const&), std::vector<bool>& IsVisited, std::stack<std::size_t> IndexToVisit) 
	{
		std::size_t const& CurIndex = IndexToVisit.top();

		std::vector<std::size_t> const& CurAdjList = this->AdjList[CurIndex];
		for (std::size_t const& AdjIndex : CurAdjList)
		{
			if (!IsVisited[AdjIndex])
			{
				IndexToVisit.push(AdjIndex);
				std::size_t const& NextAdjIndex = IndexToVisit.top();

				Func(NextAdjIndex);
				IsVisited[NextAdjIndex] = true;

				this->DFS_recur(Func, IsVisited, IndexToVisit);
			}
		}
		IndexToVisit.pop();
		return;
	}
#pragma endregion
#pragma region BFS
public:
	void BFS(void(*Func)(std::size_t const&), std::size_t const& StartIndex) 
	{
		std::vector<bool> IsVisited(this->AdjList.size(), false);
		std::queue<std::size_t> IndexToVisit;

		// 시작 설정
		IndexToVisit.push(StartIndex);
		IsVisited[StartIndex] = true;
		Func(StartIndex);

		this->BFS_recur(Func, IsVisited, IndexToVisit);
		return;
	}
private:
	void BFS_recur(void(*Func)(std::size_t const&), std::vector<bool>& IsVisited, std::queue<std::size_t> IndexToVisit) 
	{
		std::size_t const& CurIndex = IndexToVisit.front();

		std::vector<std::size_t> const& CurAdjList = this->AdjList[CurIndex];
		for (std::size_t const& AdjIndex : CurAdjList)
		{
			if (!IsVisited[AdjIndex])
			{
				IndexToVisit.push(AdjIndex);
				std::size_t const& NextAdjIndex = IndexToVisit.back();

				Func(NextAdjIndex);
				IsVisited[NextAdjIndex] = true;
			}
		}
		IndexToVisit.pop();
		if (!IndexToVisit.empty()) this->BFS_recur(Func, IsVisited, IndexToVisit);
		return;
	}
#pragma endregion
public:
	static void Print(std::size_t const& Index)
	{
		std::cout << Index + 1 << " ";
		return;
	}
private:
	std::vector <std::vector<std::size_t>> AdjList;
};

int main(void)
{
	std::size_t NOfVertices; std::cin >> NOfVertices; // [1, 1e3]
	std::size_t NOfEdges; std::cin >> NOfEdges; // [1, 1e4]
	std::size_t TraverseStartIndex; std::cin >> TraverseStartIndex;

	Graph graph = Graph(NOfVertices);

	for (std::size_t i = 0; i < NOfEdges; ++i)
	{
		std::size_t Start, End; std::cin >> Start >> End;
		graph.AddEdge(Start - 1, End - 1);
	}

	graph.SortEdges();

	graph.DFS(Graph::Print, TraverseStartIndex - 1);
	std::cout << '\n';
	graph.BFS(Graph::Print, TraverseStartIndex - 1);

}
