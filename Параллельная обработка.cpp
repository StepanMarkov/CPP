#include <iostream>
#include <set>

using namespace std;

int main() {

	size_t n, m, dt; 
	cin >> n >> m;
	set<pair<size_t, size_t>> procs;
	pair<size_t, size_t> proc;

	for (size_t i(0); i != n; ++i)
		procs.insert({ 0, i });

	for (size_t i(0); i != m; ++i) {
		cin >> dt;
		proc = *procs.begin();
		cout << proc.second << ' ' 
			 << proc.first  << endl;
		procs.erase(proc);
		proc.first += dt;
		procs.insert(proc);
	}
}