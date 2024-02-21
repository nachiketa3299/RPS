// [[2023-10-19T15:58, 2023-10-19T17:24]]

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <array>

using namespace std;
using _2DBV = vector<vector<bool>>;
using _SE = pair<size_t, size_t>;

constexpr char ZERO = '0';
constexpr char ONE = '1';

class QTree
{
	struct Node;
	using _4CH = array<Node*, 4>;
	using _4CHI = array<_SE, 4>;
	struct Node
	{
		_4CH* children = nullptr;
		bool cmp_data = false;
		bool has_children() const { return this->children; };
		void make_children() 
		{ 
			this->children = new _4CH;
			for (size_t i = 0; i < 4; ++i) (*this->children)[i] = new Node;
			return; 
		}
	};
	enum TSeq { LeftUp = 0, RightUp, LeftDown, RightDown, Max };
public:
	QTree(const _2DBV& vid) : raw(vid) 
	{
		this->root = new Node;
		this->make_quadtree(this->root, { 0, 0 }, vid.size());
		return;
	};
	void print_cmp_data() const { this->print_recur(this->root); }
private:
	void print_recur(const Node* croot) const
	{
		static auto btoc = [](const bool& ib) { return (ib ? ONE : ZERO); };
		if (croot->has_children()) 
		{
			cout << "(";
			for (const auto& ch : *croot->children) print_recur(ch);
			cout << ")";
		}
		else cout << btoc(croot->cmp_data);
		return;
	}
	void make_quadtree(Node*& croot, const _SE& se, const size_t& csize) 
	{
		if (this->is_all_same(se, csize)) 
		{
			croot->cmp_data = this->raw[se.first][se.second];
			return;
		}
		// if not all same, make 4 children
		const _4CHI nses = this->get_divide_idxs(se, csize);
		croot->make_children();
		for (size_t i = 0; i < nses.size(); ++i) 
			this->make_quadtree((*croot->children)[i], nses[i], csize / 2);
		return;
	}
	bool is_all_same(const _SE& se, const size_t& csize) const
	{
		// size one block is always same
		if (csize == 1) return true;
		const bool& sval = this->raw[se.first][se.second];
		for (size_t i = se.first; i < se.first + csize; ++i) 
		{
			for (size_t j = se.second; j < se.second + csize; ++j) 
				// only 1 difference makes return
				if (this->raw[i][j] != sval) return false;
		}
		// here everythin is same as sval
		return true;
	}
	_4CHI get_divide_idxs(const _SE& se, const size_t& csize) const 
	{
		size_t hsize = csize / 2;
		_4CHI arr;
		arr[LeftUp]	   = _SE(se.first, se.second);
		arr[RightUp]   = _SE(arr[0].first	     , arr[0].second + hsize);
		arr[LeftDown]  = _SE(arr[0].first + hsize, arr[0].second	    );
		arr[RightDown] = _SE(arr[0].first + hsize, arr[0].second + hsize);
		return arr;
	}
	Node* root = nullptr;
	const _2DBV raw;
	static const int a;
};

int main(void) 
{
	/* === INPUT === */
	size_t ivid_size; cin >> ivid_size; // vid_size = 2^k, k in [0, 6]
	_2DBV vid(ivid_size, vector<bool>(ivid_size, false));
	auto ctob = [&vid](const char& ch) { return ((ch == ONE) ? true : false); };
	for (size_t i = 0; i < ivid_size; ++i) 
	{
		string istr; cin >> istr;
		for (size_t j = 0; j < istr.size(); ++j) vid[i][j] = ctob(istr[j]);
	}
	/* === PROCESS === */
	QTree qt = QTree(vid);
	/* === OUTPUT === */
	qt.print_cmp_data();

	return 0;
}
