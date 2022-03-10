#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

size_t p(1000000007);
size_t x(263);
size_t n, m;

size_t mhash(const string& s) {
	
	size_t y(1), res(0);	
	
	for (const char& c : s) {
		res += c * y;
		y *= x;
		y = y % p;
	}

	return (res % p) % m;

}

int main() {

	cin >> m >> n;
	string s;
	size_t h;
	vector<list<string>> data(m);

	for (size_t i(0); i < n; ++i) {
		
		cin >> s;

		if (s == "add") {
			cin >> s;
			auto& x = data[mhash(s)];
			if (find(x.begin(), x.end(), s) == x.end())
				x.push_front(s);
			continue;
		}

		if (s == "del") {
			cin >> s;
			data[mhash(s)].remove(s);
			continue;
		}

		if (s == "find") {
			cin >> s;
			auto& x = data[mhash(s)];
			if (find(x.begin(), x.end(), s) != x.end())
				cout << "yes" << endl;
			else cout << "no" << endl;
			continue;
		}

		if (s == "check") {
			cin >> h;
			auto& x = data[h];
			for (auto& y : x)
				cout << y << ' ';
			cout << endl;
			continue;
		}

	}


	return 0;

}