#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {

	size_t n, e , d; cin >> n >> e >> d;
	int dest, source;
	vector<int> r(n+1);
	auto begin(r.begin()), end(r.end());
	auto r1(begin), r2(begin);
	vector<decltype(begin)> way;

	for (auto iter(begin + 1); iter != end; ++iter)
		*iter = iter - begin;

	for (size_t i(0); i != e; ++i) {
		cin >> dest >> source;
		r1 = begin + dest;
		r2 = begin + source;
		way.clear();

		while (*r1 != r1-begin) {
			way.push_back(r1);
			r1 = begin + *r1;
		}
		while (*r2 != r2 - begin) {
			way.push_back(r2);
			r2 = begin + *r2;
		}
		
		if (r1 != r2) {
			*r2 = r1 - begin;
			for (auto& r3 : way)
				*r3 = *r2;
		}

		//for (auto iter(begin + 1); iter != end; ++iter)
		//	cout << *iter << ' ';
		//cout << endl;
	}

	for (size_t i(0); i != d; ++i) {
		cin >> dest >> source;
		r1 = begin + dest;
		r2 = begin + source;
		if (*r1 == *r2) {
			cout << 0;
			return 0;
		}
	}

	cout << 1;
	return 0;

}