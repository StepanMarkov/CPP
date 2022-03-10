#include <iostream>
#include <vector>
#include <deque>

using namespace std;

struct node {
	vector<node*> links;
	size_t lenght = 0;
	bool field = false;
};

vector<node> all;
deque<node*> deq;

int main() {
	size_t v, e, v1, v2, num = 0;
	cin >> v >> e;
	all.resize(v);
	node* p1; node* p2;

	for (size_t i(0); i < e; ++i) {
		cin >> v1 >> v2;
		p1 = &all[v1]; p2 = &all[v2];
		(*p1).links.push_back(p2);
		(*p2).links.push_back(p1);
	}

	if (!all.empty())
		deq.push_back(&*all.begin());

	while (!deq.empty()) {
		node*& p(deq.back());
		p->field = true;
		for (node*& pp : p->links)
			if (!pp->field) {
				if (!pp->lenght)
					pp->lenght = p->lenght + 1;
				deq.push_front(pp);
			}
		deq.pop_back();
	}

	for (auto& p : all)
		cout << p.lenght << ' ';
}