#include <iostream>
#include <list>
#include <set>
#include <algorithm>

using namespace std;

struct node {
	list<node*> links, links2, links3;
	size_t* k = new size_t(0);
	size_t* l = new size_t(0);
};

list<node*> order;

void Predict(node*& p) {
	order.push_back(p);
	*p->k = order.size();
	*p->l = order.size();
	for (node*& pp : p->links)
		if (!*pp->k) {
			Predict(pp);
			p->links2.push_back(pp);
		}
		else
			p->links3.push_back(pp);
}

void Correct() {

	auto nodes(order);

	while (!nodes.empty())
	{
		node* p = nodes.front();
		nodes.pop_front();

		for (node* pp : p->links2)
			if (*p->l > * pp->l) {
				p->l = pp->l;
				//nodes.emplace_back(p->links);
				nodes.insert(nodes.begin(), p->links.begin(), p->links.end());
				//nodes.push_back(p);
				//nodes.push_back(pp);
			}

		for (node* pp : p->links3)
			if (*pp->l > * p->k) {
				pp->l = p->k;
				nodes.insert(nodes.begin(), pp->links.begin(), pp->links.end())
				//nodes.push_back(p);
				//nodes.push_back(pp);
			}
	}
}

//void Correct() {
//	for (node*& p : order)
//		Correct_p(p);
//}

//bool Correct() {
//	bool sw(false);
//	for (node*& p : order) {
//		for (node*& pp : p->links2)
//			if (*p->l > *pp->l) {
//				p->l = pp->l;
//				sw = true;
//			}
//		for (node*& pp : p->links3)
//			if (*pp->l > *p->k) {
//				pp->l = p->k;
//				sw = true;
//			}
//
//	}
//	return sw;
//}

void GetSolution(node* buffer) {
	if (order.front()->links2.size() > 1)
		cout << order.front() - buffer << ' ';
	order.pop_front();
	for (node*& p : order)
		for (node*& pp : p->links2)
			if (*pp->l >= *p->k) {
				cout << p - buffer << ' ';
				break;
			}
}

int main() {

	size_t v1(0), v2(0), vmin(200000);
	node* buffer(new node[200000]);
	node* p1(nullptr);
	node* p2(nullptr);

	while (cin >> v1 >> v2) {
		p1 = buffer + v1;
		p2 = buffer + v2;
		p1->links.push_back(p2);
		p2->links.push_back(p1);
	}

	Predict(buffer);
	for (int i(0); i < 900; ++i)
		Correct();
	GetSolution(buffer);

	//for (node*& p : order)
	//	cout << p->k - 1 << ' ' << p->l << endl;
}