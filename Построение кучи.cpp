#include <iostream>
#include <vector>

using namespace std;

typedef int* ptr;

int main() {


	size_t n; cin >> n;

	bool sw = (n % 2 == 0);

	ptr begin(new int[n+sw+1]), end(begin + n + 1);
	if (sw) *end = INT_MAX;

	for (ptr v(begin+1); v < end; ++v)
		cin >> *v;

	ptr  p1, p2, p3, p4;

	vector<pair<int,int>> result;

	for (ptr p(end-1); p != begin; --p ) {
		
		p4 = p;

		while (true) {

			p1 = p4;
			p2 = p1 + (p1 - begin);
			p3 = p2 + 1;
			if (p2 >= end) break;
			if (*p1 > * p2) p4 = (*p2 > * p3) 
			&& (*p1 > * p3) ? p3 : p2;
			else if (*p1 > * p3) p4 = p3;
			else break;
			result.push_back({ p1 - begin - 1, p4 - begin - 1 });
			*begin = *p1;
			*p1 = *p4;
			*p4 = *begin;
		}
	}

	cout << result.size() << endl;

	for (auto& x : result)
		cout << x.first << ' ' << x.second << endl;

	
}