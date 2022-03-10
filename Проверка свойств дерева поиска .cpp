#include <iostream>

using namespace std;

struct node {

    node() : parent(nullptr), 
        left(nullptr), right(nullptr) {}
    
	long long key;
	node* parent;
	node* left;
	node* right;
};

struct mythree {

	void InOrder(node* v) {
		if (v != nullptr) {
			InOrder(v->left);
			//cout << v->key << ' ';
			*nodes++ = v;
			InOrder(v->right);
		}
		else return;
	}

	const char* IsBinarySearch() {

		if (size) {

			InOrder(*nodes);
			nodes -= size;
			auto pp1(nodes), pp2(pp1 + 1);

			//for (auto pp(nodes); pp != end; ++pp)
			//	cout << (*pp)->parent << ' ' << endl;
			//cout << endl;
			
			while (pp2 != end) {

				auto p1(*pp1), p2(*pp2);

				if (p2->key < p1->key)
					return "INCORRECT";

				//if (p2->key == p1->key)
                //    if (p1->parent != p2->right)
				//	    return "INCORRECT";
				++pp1;
				++pp2;
			}
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
			p->left   = nodes[num1];
			p->right  = nodes[num2];
			//p->parent = nodes[-1];
			if (p->left)  p->left->parent  = p;
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

};

int main() {

	mythree three;
	cout << three.IsBinarySearch();

}