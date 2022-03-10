#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {

	size_t n, m; cin >> n >> m;
	int dest, source, rmax(-1);
	vector<int> r(n+1);
	auto begin(r.begin()), end(r.end());
	auto r1(begin), r2(begin);
	vector<decltype(begin)> way;

	for (auto iter(begin + 1); iter != end; ++iter) {
		cin >> *iter;
		rmax = max(rmax, *iter);
	}

	for (size_t i(0); i != m; ++i) {
		cin >> dest >> source;
		r1 = begin + dest;
		r2 = begin + source;
		way.clear();

		while (*r1 < 0) {
			way.push_back(r1);
			r1 = begin + abs(*r1);
		}
		while (*r2 < 0) {
			way.push_back(r2);
			r2 = begin + abs(*r2);
		}
		
		if (r1 != r2) {
			*r1 += *r2;
			*r2 = begin - r1;
			rmax = max(rmax, *r1);

			for (auto& r3 : way)
				*r3 = *r2;
		}

		cout << rmax << endl;
	}
}