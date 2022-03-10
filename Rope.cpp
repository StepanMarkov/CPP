#include <iostream>
#include <string>

using namespace std;

struct node {

	node(node* _p) :
		p(_p),
		r(nullptr),
		l(nullptr),
		ss(0),
		k(0) {}

	size_t ss;
	node* l;
	node* r;
	node* p;
	char k;
};

struct mythree {


	void request(size_t i, size_t j, size_t k) {
		
		auto left(operator[](i));
		auto right(operator[](j));
        
        if (!left) return;
        if (!right) return;
		
		Splay(left);
		left = left->l;
		if (left) {
			root->ss -= left->ss;
			left->p = nullptr;
			root->l = nullptr;
		}

		Splay(right);
		right = right->r;
		if (right) {
			root->ss -= right->ss;
			right->p = nullptr;
			root->r = nullptr;
		}

		auto median(root);

		root = left ? left : right;
        
        if (!root) {
            root = median;
            return;
        }

		if (right && left) {
			left->ss += right->ss;
			while (left->r) {
				left = left->r;
				left->ss += right->ss;
			}
			left->r = right;
			right->p = left;
		}

		if (root->ss != k) {
            Splay(operator[](k));
			left = root->l;
            if (left) left->ss += median->ss;
        }
		else left = root;
		root->ss += median->ss;
		if (left) {
			while (left->r) {
                left = left->r;
				left->ss += median->ss;
			}
			left->r = median;
			median->p = left;
		}
		else {
			root->l = median;
			median->p = root;
		}
	}

	void InOrder(node*& p) {
		if (!p) return;
		InOrder(p->l);
		cout << p->k;
		InOrder(p->r);
	}

	void Order(node*& p, string& s, size_t p1, size_t p2) {
		size_t pos = (p2 + p1) / 2;

		if (p1 + 1 <= pos) {
			p->l = new node(p);
			Order(p->l, s, p1, pos - 1);
		}

		p->k = s[pos];
		p->ss = p2 - p1 + 1;

		if (p2 >= pos + 1) {
			p->r = new node(p);
			Order(p->r, s, pos + 1, p2);
		}
	}

	node* operator [] (size_t n) {
		node* p(root);
		size_t index(p->ss);

		while (p) {
			if (p->ss == 1)
				return p;
			index = (p->r) ? p->ss - p->r->ss - 1 : p->ss - 1;
			if (index == n)
				return p;
			if (index < n) {
				n -= index + 1;
				p = p->r;
			}
			else p = p->l;
		}
		return p;
	}

	void Show(node* p) {
		if (p) {
			cout << p << ' ' << p->k << ' ' << p->ss << ' '
				<< p->l << ' ' << p->r << ' ' << p->p << endl;
			Show(p->l);
			Show(p->r);
		}
	}

	void Splay(node* u) {
		if (u) {
	
			node* a;
			node* b;
			bool sw1, sw2;
	
			while (u != root) {
	
				a = u->p;
				b = a->p;
				sw1 = (u == a->l);
	
				if (b) {
	
					sw2 = (a == b->l);
	
					if (sw1 && sw2) {
						auto C(a->r), B(u->r), E(b->p);
						u->p = E; u->r = a;
						a->p = u; a->l = B; a->r = b;
						b->p = a; b->l = C;
	
						if (C) {
							C->p = b;
							b->ss += C->ss - a->ss;
						}
						else b->ss -= a->ss;
	
						if (B) {
							B->p = a;
							a->ss = 1 + B->ss + b->ss;
							u->ss += (a->ss - B->ss);
						}
						else {
							a->ss = 1 + b->ss;
							u->ss += a->ss;
						}
	
						if (E) ((E->l == b) ? E->l : E->r) = u;
						else root = u;
					}
					else if (!sw1 && !sw2) {
						auto C(a->l), B(u->l), E(b->p);
						u->p = E; u->l = a;
						a->p = u; a->r = B; a->l = b;
						b->p = a; b->r = C;
						
						if (C) {
							C->p = b;
							b->ss += C->ss - a->ss;
						}
						else b->ss -= a->ss;
	
						if (B) {
							B->p = a;
							a->ss = 1 + B->ss + b->ss;
							u->ss += (a->ss - B->ss);
						}
						else {
							a->ss = 1 + b->ss;
							u->ss += a->ss;
						}
	
						if (E) ((E->r == b) ? E->r : E->l) = u;
						else root = u;
					}
					else if (sw1 && !sw2) {
						auto C(u->r), B(u->l), E(b->p);
						u->p = E; u->l = b; u->r = a;
						b->p = u; b->r = B;
						a->p = u; a->l = C;
						
						if (B) {
							B->p = b;
							b->ss += (B->ss - a->ss);
						}
						else b->ss -= a->ss;
						
						if (C) {
							C->p = a;
							a->ss += (C->ss - u->ss);
							u->ss += (a->ss - C->ss);
						}
						else {
							a->ss -= u->ss;
							u->ss += a->ss;
						}
	
						if (B) u->ss += (b->ss - B->ss);
						else u->ss += b->ss;
	
						if (E) ((E->l == b) ? E->l : E->r) = u;
						else root = u;
					}
					else if (!sw1 && sw2) {
						auto C(u->l), B(u->r), E(b->p);
						u->p = E; u->r = b; u->l = a;
						b->p = u; b->l = B;
						a->p = u; a->r = C;
	
						if (B) {
							B->p = b;
							b->ss += (B->ss - a->ss);
						}
						else b->ss -= a->ss;
	
						if (C) {
							C->p = a;
							a->ss += (C->ss - u->ss);
							u->ss += (a->ss - C->ss);
						}
						else {
							a->ss -= u->ss;
							u->ss += a->ss;
						}
	
						if (B) u->ss += (b->ss - B->ss);
						else u->ss += b->ss;
	
						if (E) ((E->r == b) ? E->r : E->l) = u;
						else root = u;
					}
				}
				else {
					if (sw1) {
						auto B(u->r);
						u->p = nullptr; u->r = a;
						a->p = u; a->l = B;
						
						if (B) {
							B->p = a;
							a->ss += (B->ss - u->ss);
							u->ss += (a->ss - B->ss);
						}
						else {
							a->ss -= u->ss;
							u->ss += a->ss;
						}
						
						root = u;
					}
					else
					{
						auto B(u->l);
						u->p = nullptr; u->l = a; 
						a->p = u; a->r = B;
						
						if (B) {
							B->p = a;
							a->ss += (B->ss - u->ss);
							u->ss += (a->ss - B->ss);
						}
						else {
							a->ss -= u->ss;
							u->ss += a->ss;
						}
	
						root = u;
					}
				}
			}
		}
	}
	mythree() : root(nullptr) {}
	~mythree() {}
	node* root;

};

int main() {

	mythree three;
	string s;
	cin >> s;
	size_t num, i, j, k;
	three.root = new node(nullptr);
	three.Order(three.root, s, 0, s.size()-1);
	cin >> num;

	for (size_t n(0); n < num; ++n) {
		cin >> i >> j >> k;
		three.request(i, j, k);
	}
	three.InOrder(three.root);

}