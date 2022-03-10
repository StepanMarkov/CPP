#include <iostream>
#include <vector>

using namespace std;

struct node {
	vector<node*> links;
	size_t field = 0;
};

vector<node> all;

void func(node*& p) {
	for (node*& pp : p->links)
		if (!pp->field) {
			pp->field = p->field;
			func(pp);
		}
}

int main() {
	size_t v, e, v1, v2, num = 0;
	cin >> v >> e;
	all.resize(v + 1);
	node* p1; node* p2;


	for (size_t i(1); i <= e; ++i) {
		cin >> v1 >> v2;
		p1 = &all[v1]; p2 = &all[v2];
		(*p1).links.push_back(p2);
		(*p2).links.push_back(p1);
	}

	for (size_t i(1); i <= v; ++i) {
		p1 = &all[i];
		if (!p1->field) {
			p1->field = ++num;
			func(p1);
		}
	}

	cout << num;
}