//Найдите минимальное вершинное покрытие в двудольном графе.
//На вход подается описание двудольного графа, в котором доли уже выделены явно.
//Первая строка содержит три натуральных числа : v1 — число вершин первой доли
//v2 — число вершин второй доли, e ≤ v1∗v2 — число рёбер. 
//Подразумевается, что первая доля состоит из вершин с номерами от 0 до v1 - 1
//вторая — из вершин с номерами от v1 до v1 + v2 - 1
//Следующие e строк описывают рёбра : каждая из этих строк содержит два числа : 
//0 <= ui <= v1; v1 <= wi <= v1+v2;
// что означает, что между вершинами ui и wi есть ребро.
//Скопируйте описание графа из входа на выход и выведите 
//единственную дополнительную строку — список номеров вершин, 
//составляющих минимальное вершинное покрытие.Если таких покрытий несколько, выведите любое.
//Автор: Марков С.А.

#include <iostream>
#include <list>

using namespace std;
struct line;

struct node {
	list<pair<node*,line*>> lines;
	bool selected = false;
	size_t free = 0;
};

struct line {
	pair<node*, node*> nodes;
	bool selected = false;
	bool solution = false;
};

int main() {

	size_t v1, v2, e; cin >> v1 >> v2 >> e;
	size_t v(v1 + v2), index1(0), index2(0);
	auto lines(new line[e]), lend(lines + e);
	auto nodes(new node[v]), nend(nodes + v), nend1(nodes+v1);
	list<line*> wayline;
	list<node*> waynode;

	for (auto pline(lines); pline != lend; ++pline) {
		cin >> index1 >> index2;
		auto node1(nodes + index1);
		auto node2(nodes + index2);
		pline->nodes = { node1, node2 };
		node1->lines.push_back({ node2, pline });
		node2->lines.push_back({ node1, pline });
	}

	//------------------------------------//

	do {

		for (auto& x : wayline)
			if (x->solution) {
				x->solution = false;
				--x->nodes.first->free;
				--x->nodes.second->free;
			}
			else {
				x->solution = true;
				++x->nodes.first->free;
				++x->nodes.second->free;
			}

		wayline.clear();

		for (auto pnode(nodes); pnode != nend; ++pnode)
			pnode->selected = false;

		for (auto p1(nodes); p1 != nend; ++p1) {

			if (p1->free)		continue;
			if (p1->selected)	continue;
			p1->selected = true;
			auto p2(p1);
			auto sw(false);
			waynode.clear();

			DFS1:
			for (auto& x : p2->lines) {
				if (x.first->selected) continue;
				if (sw ^ x.second->solution) continue;
				wayline.push_back(x.second);
				waynode.push_back(p2);
				p2 = x.first;
				p2->selected = true;
				sw = !sw;
				if (p2->free) goto DFS1;
				else break;
			}

			if ((!waynode.empty()) && (p2->free)) {
				p2 = waynode.back();
				waynode.pop_back();
				wayline.pop_back();
				sw = !sw;
				goto DFS1;
			}
		}
	} while (!wayline.empty());

	for (auto pnode(nodes); pnode != nend; ++pnode)
		pnode->selected = false;
		
	for (auto p1(nodes); p1 != nend1; ++p1) {
	
		if (p1->free)		continue;
		if (p1->selected)	continue;
		p1->selected = true;
		auto p2(p1);
		auto sw(false);
		waynode.clear();
	
		DFS2:
		for (auto& x : p2->lines) {
			if (x.first->selected) continue;
			if (sw ^ x.second->solution) continue;
			waynode.push_back(p2);
			p2 = x.first;
			p2->selected = true;
			sw = !sw;
			goto DFS2;
		}
	
		if (!waynode.empty()) {
			p2 = waynode.back();
			waynode.pop_back();
			sw = !sw;
			goto DFS2;
		}
	}

	//--------------------------------------------------//

	cout << v1 << ' ' << v2 << ' ' << e << endl;

	for (auto pline(lines); pline != lend; ++pline) {
		cout << pline->nodes.first  - nodes << ' ';
		cout << pline->nodes.second - nodes << endl;
	}

	for (auto p1(nodes); p1 != nend1; ++p1)
		if (!p1->selected)
			cout << p1 - nodes << ' ';
	for (auto p2(nend1); p2 != nend; ++p2)
		if (p2->selected)
			cout << p2 - nodes << ' ';
	
	//--------------------------------------------------//
	
	return 0;
}
