#include <iostream>

using namespace std;

struct node {
	int key;
	node** left;
	node** right;
};

struct mythree {

	void InOrder(node* v) {
		if (v != nullptr) {
			InOrder(*v->left);
			cout << v->key << ' ';
			InOrder(*v->right);
		}
		else return;
	}

	void PreOrder(node* v) {
		if (v != nullptr) {
			cout << v->key << ' ';
			PreOrder(*v->left);
			PreOrder(*v->right);
		}
		else return;
	}

	void PostOrder(node* v) {
		if (v != nullptr) {
			PostOrder(*v->left);
			PostOrder(*v->right);
			cout << v->key << ' ';
		}
		else return;
	}

	mythree() {
		size_t size; cin >> size;
		int num1, num2;
		nodes = new node * [size + 1];
		*nodes++ = nullptr;
		end = nodes + size;

		for (auto p(nodes); p != end; ++p) {
			*p = new node;
			cin >> (*p)->key >> num1 >> num2;
			(*p)->left  = nodes + num1;
			(*p)->right = nodes + num2;
		}
	}

	~mythree() {
		for (auto p(nodes); p != end; ++p)
			delete* p;
		delete[] --nodes;
	}

	node** nodes;
	node** end;

};

int main() {

	mythree three;
	three.InOrder(three.nodes[0]); cout << endl;
	three.PreOrder(three.nodes[0]); cout << endl;
	three.PostOrder(three.nodes[0]);

}