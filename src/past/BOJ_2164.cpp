// [2023-10-11T15:34. 2023-10-11T15:51] (17)

#include <iostream>
#include <deque>

class Deck
{
public:
	Deck(std::size_t const& NOfCards) 
	{
		for (std::size_t i = 0; i < NOfCards; ++i)
		{
			this->Cards.push_back(i + 1);
		}
		return;
	}
public:
	std::size_t GetLastRemainingCardDigit()
	{
		std::deque<std::size_t> CopiedDeque(this->Cards);
		this->exe_recur(CopiedDeque);
		return CopiedDeque.front();
	}
private:
	void exe_recur(std::deque<std::size_t>& Deque)
	{
		if (Deque.size() == 1) return;

		Deque.pop_front();
		std::size_t ToPush = Deque.front();
		Deque.pop_front();
		Deque.push_back(ToPush);

		this->exe_recur(Deque);
	}
private:
	std::deque<std::size_t> Cards;
};

int main(void)
{
	std::size_t NOfCards; std::cin >> NOfCards;
	Deck MyDeck = Deck(NOfCards);
	std::size_t LastCardDigit = MyDeck.GetLastRemainingCardDigit();
	std::cout << LastCardDigit << std::endl;
	return 0;
}