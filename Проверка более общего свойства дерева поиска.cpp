#include <iostream>

using namespace std;

struct node {

	node() : parent(nullptr),
		left(nullptr), right(nullptr), key(0) {}

	long long key;
	node* parent;
	node* left;
	node* right;
};

struct mythree {

	void InOrder(node* v) {

		if (v->left) {
			InOrder(v->left);
			if (nodes[-1]->key == v->key)
				sw = false;
		}

		if (*(nodes - 1))
			if (nodes[-1]->key > v->key)
				sw = false;

		*nodes++ = v;

		if (v->right) {
			InOrder(v->right);
			//if (nodes[-1]->key < v->key)
			//	sw = false;
		}
	}

	const char* IsBinarySearch() {

		if (size) {
			sw = true;
			InOrder(*nodes);

			if (sw)
				return "CORRECT";
			else return "INCORRECT";

		}
		return "CORRECT";
	}


	mythree() {
		cin >> size;
		long long num1, num2;
		nodes = new node * [size + 1];
		*nodes++ = nullptr;
		end = nodes + size;

		for (auto pp(nodes); pp != end; ++pp)
			*pp = new node;

		for (auto pp(nodes); pp != end; ++pp) {
			auto p(*pp);
			cin >> p->key >> num1 >> num2;
			p->left = nodes[num1];
			p->right = nodes[num2];
			if (p->left)  p->left->parent = p;
			if (p->right) p->right->parent = p;
		}
	}

	~mythree() {
		//for (auto p(nodes); p != end; ++p)
		//	delete* p;
		//delete[] --nodes;
	}

	node** nodes;
	node** end;
	size_t size;
	bool sw;

};

int main() {

	mythree three;
	cout << three.IsBinarySearch();

}