#include <iostream>
#include <string>

using namespace std;

const size_t len = 10000000;

struct record {
	char word[16];
};



int main() {
	
	size_t n, m; cin >> n;
	auto data(new record[len]);
	auto end(data + len), rec(data);
	string s;
	const record empty(*(record*)"not found");

	for (auto i(data); i != end; ++i)
		*i = empty;

	for (size_t i(0); i < n; ++i) {
		
		cin >> s >> m;
		rec = data + m;
	
		if (s == "add") {
			cin >> rec->word;
			continue;
		} 

		if (s == "find") {
			cout << rec->word << endl;
			continue;
		}

		if (s == "del") {
			*rec = empty;
			continue;
		}
	
	}
	
	return 0;

}