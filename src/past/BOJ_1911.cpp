// [2023-10-09T13:45, 2023-10-09T14:45]
#include <iostream>
#include <vector>
#include <algorithm>

struct FHoleInfo
{
	long long StartPos;
	long long EndPos;
	static bool Compare(FHoleInfo const& Op1, FHoleInfo const& Op2)
	{
		return Op1.StartPos < Op2.StartPos;
	}
};

int main(void)
{
	std::ios_base::sync_with_stdio(false); std::cin.tie(NULL); std::cout.tie(NULL);
	// HoleCount in [1, 1e4]
	// CoverCount in [1, 1e6]
	std::size_t HoleCount, CoverLength; std::cin >> HoleCount >> CoverLength;
	std::vector<FHoleInfo> HoleInfos(HoleCount);
	for (FHoleInfo& Info : HoleInfos)
	{
		std::cin >> Info.StartPos >> Info.EndPos;
		// 범위가 서로 겹치지 않는다
	}
	std::sort(HoleInfos.begin(), HoleInfos.end(), FHoleInfo::Compare);

	// 위치별로 뚤려있냐 아니냐
	std::vector<bool> IsHoled(HoleInfos.back().EndPos + 1, false);

	for (FHoleInfo const& Info : HoleInfos)
	{
		for (long long i = Info.StartPos; i < Info.EndPos; ++i)
		{
			IsHoled.at(i) = true;
		}
	}

	long long CoverCount = 0;
	for (long long i = 0; i < IsHoled.size();)
	{
		// 구멍 아니면 걍 넘어가기
		if (!IsHoled[i])
		{
			++i;
			continue;
		}

		// 구멍이면 ... 널빤지 갯수 증가시키고, i를 널빤지 길이 바로 다음으로
		CoverCount++;
		i += CoverLength;
	}
	std::cout << CoverCount << std::endl;
	return 0;
}