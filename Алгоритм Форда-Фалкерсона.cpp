//Первая строка содержит два числа v и e — число вершин и число рёбер сети. 
//Следующие ee строк описывают рёбра: каждая из них содержит три целых числа через пробел:
//исходящую и входящую вершины для этого ребра, а так же его пропускную способность.
//Выведите единственное число — величину максимального потока из вершины 0 в вершину v−1.

#include <iostream>
#include <list>

using namespace std;
struct line;

struct node {
	list<line*> forward;
	list<line*> reverse;
};

struct line {
	pair<node*, node*> nodes;
	size_t capacity = 0;
	size_t stream	= 0;
	size_t selected = 0;
};

int main() {

	size_t v, e; cin >> v >> e;
	size_t index1(0), index2(0);
	size_t dx(0), dxmin(0);
	line* lines(new line[e]);
	line* lineback(lines + e - 1);
	line* linei(nullptr);
	node* nodes(new node[v]);
	node* node1(nullptr);
	node* node2(nullptr);
	list<line*> way;
	list<line*> wayfail;
	bool freeway;

	for (size_t index(0); index != e; ++index) {
		cin >> index1 >> index2;
		node1 = nodes + index1;
		node2 = nodes + index2;
		linei = lines + index;
		cin >> linei->capacity;
		linei->nodes = { node1, node2 };
		node1->forward.push_back(linei);
		node2->reverse.push_back(linei);
	}

	freeway = true;
	node1 = nodes;
	node2 = node1 + v - 1;
	
	while (freeway) {

		for (auto& liner : way) {
			if (liner->selected == 1)
				liner->stream += dxmin;
			else liner->stream -= dxmin;
			liner->selected = 0;
		} way.clear();

		for (auto& liner : wayfail)
			liner->selected = 0;
		wayfail.clear();

		node1 = nodes;
		dxmin = -1;

		while (freeway && (node1 != node2)) {

			freeway = false;

			for (auto& liner : node1->forward) {
				if (liner->selected) continue;
				dx = liner->capacity - liner->stream;
				if (!dx) continue;
				way.push_back(liner);
				liner->selected = 1;
				if (dx < dxmin) dxmin = dx;
				node1 = liner->nodes.second;
				freeway = true;
				break;
			}

			if (!freeway)
				for (auto& liner : node1->reverse) {
					if (liner->selected) continue;
					if (!liner->stream) continue;
					dx = liner->stream;
					way.push_back(liner);
					liner->selected = 2;
					if (dx < dxmin) dxmin = dx;
					node1 = liner->nodes.first;
					freeway = true;
					break;
				}

			if (!(freeway || way.empty())) {
				auto& x(way.back()->nodes);
				node1 = (node1 == x.first) ?
					x.second : x.first;
				wayfail.push_back(way.back());
				way.pop_back();
				freeway = true;
			}
		}
	}

	size_t result(0);
	for (auto& liner : node2->forward)
		result += liner->stream;
	for (auto& liner : node2->reverse)
		result += liner->stream;

	std::cout << result;
	return 0;
}
