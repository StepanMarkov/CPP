#include <iostream>
#include <vector>

using namespace std;

struct line;

struct node {
	vector<line*> lines;
	bool select = false;
};

struct line {

	line(pair<node*, node*> _nodes) : nodes(_nodes) {
		nodes.first->lines.push_back(this);
		nodes.second->lines.push_back(this);
	}

	pair<node*, node*> nodes;
	bool select = false;
};

struct graph {
	node* nodes;

	void link(const size_t& n1, const size_t& n2) {
		new line({ nodes+n1, nodes+n2 });
	}
};

struct circle {
	circle(node* _current) :
		current(_current),
		link(nullptr) {}
	node* current;
	circle* link;
};

circle* GetWay(node* pp) {
	
	auto mainway(new circle(pp));
	vector<circle*> ways({ mainway });
	bool sw(true);

	while (!ways.empty()) {
		auto way(ways.back());
		auto p(way->current);
		ways.pop_back();
		while (!p->lines.empty()) {
			auto pl(p->lines.back());
			p->lines.pop_back();
			if (!pl->select) {
				if (!p->lines.empty())
					ways.push_back(way);
				pl->select = true;
				p = (pl->nodes.first == p)
					? p = pl->nodes.second :
					pl->nodes.first;
				if (way->link)
					mainway = way->link;
				way->link = new circle(p);
				p->select = true;
				way = way->link;
			}
		}

		if (!way->link) {
			if (sw) {
				way->link = mainway->link;
				sw = false;
			}
			else way->link = mainway;
			mainway = way;
		}
	}

	return mainway;
}


int main() {


	size_t v, e, v1, v2;
	cin >> v >> e;

	if (e == 0) {
		cout << "NONE";
		return 0;
	}
	
	graph mygraph;
	mygraph.nodes = new node[v + 1];
		
	for (size_t i(1); i <= e; ++i) {
		cin >> v1 >> v2;
		mygraph.link(v1, v2);
	}

	for (size_t i(1); i <= v; ++i) {
		if (mygraph.nodes[i].lines.size() % 2) {
			cout << "NONE";
			return 0;
		}
	}

	auto way(GetWay(mygraph.nodes+1));

	for (size_t i(1); i <= v; ++i) {
		if (!mygraph.nodes[i].select) {
			cout << "NONE";
			return 0;
		}
	}

	if (way) {
		auto itway(way);
		do {
			cout << itway->current - mygraph.nodes << ' ';
			itway = itway->link;
		} while ((itway != way) && itway);
	}
	else {
		cout << "NONE";
	}
}