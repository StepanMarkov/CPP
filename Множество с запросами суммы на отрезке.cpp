#include <iostream>
#include <string>

using namespace std;

struct node {

	node(node* _p, size_t _k) :
		p(_p),
		k(_k),
		r(nullptr),
		l(nullptr),
		ss(_k) {}

	size_t k, ss;
	node* l;
	node* r;
	node* p;
};

struct mythree {

	bool Search(size_t k, node*& p) {
		if (!p) return false;
		while (p->k != k)
			if (p->k < k) {
				if (p->r) p = p->r;
				else { return false; }
			}
			else {
				if (p->l) p = p->l;
				else { return false; }
			}
		return true;
	}

	bool Search(size_t k) {
		auto p(root);
        bool res = Search(k, p);
        Splay(p);
		return res;
	}

	void Insert(size_t k) {
		if (!root)
			root = new node(nullptr, k);
		else {
			auto p(root);
			if (!Search(k, p)) {
                auto np = new node(p, k);
				((p->k < k) ? p->r : p->l) = np;
				np->ss = 0;
                Splay(np);
                np->ss += k;
                //while (p) {
				//	p->ss += k;
				//	p = p->p;
				//}
			}
		}
	}

	void Show(node* p) {
		if (p) {
			cout << p << ' ' << p->k << ' ' << p->ss << ' '
				<< p->l << ' ' << p->r << ' ' << p->p << endl;
			Show(p->l);
			Show(p->r);
		}
	}

	void Erase(size_t k) {
		auto v(root);
		if (!Search(k, v))
			return;
		auto vv(v);
		
		if (v->l && v->r) {
			auto vl(v->l);
			while (vl->r)
				vl = vl->r;
			v->k = vl->k;
			v = vl;
		}

		auto pv(v);
		while (pv != vv) {
			pv->ss -= v->k;
			pv = pv->p;

		} do {
			pv->ss -= k;
			pv = pv->p;
		} while (pv);

		auto& vx(v->l ? v->l : v->r);
		auto& u(v->p);
		if (u) ((u->l == v) ? u->l : u->r) = vx;
		else root = vx;
		if (vx) vx->p = u;
		delete v;
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
							a->ss = a->k + B->ss + b->ss;
							u->ss += (a->ss - B->ss);
						}
						else {
							a->ss = a->k + b->ss;
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
							a->ss = a->k + B->ss + b->ss;
							u->ss += (a->ss - B->ss);
						}
						else {
							a->ss = a->k + b->ss;
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

	size_t k1 = 0;
	size_t k2 = 0;
	size_t sum = 0;

	size_t SumThree() {
		sum = 0;
		if (k1 > k2) return 0;
		if (!root) return 0;
		auto pl(root);
		Search(k1, pl);
		Splay(pl);
		sum = (pl->k >= k1) * pl->k;
		if (pl->r) sum += pl->r->ss;
		auto pr(root);
		Search(k2, pr);
		Splay(pr);
		sum -= (pr->k > k2)* pr->k;
		if (pr->r) sum -= pr->r->ss;
		return sum;
	}

	mythree() : root(nullptr) {}
	~mythree() {}
	node* root;

};

int main() {

	mythree three;
	size_t num, n;
	char c;

	cin >> num;

	for (size_t i(0); i < num; ++i) {
		cin >> c;

		switch (c)
		{

		case '+':
			cin >> n;
			n = (n + three.sum) % 1000000001;
			three.Insert(n);
			break;

		case '-':
			cin >> n;
			n = (n + three.sum) % 1000000001;
			three.Erase(n);
			break;

		case '?':
			cin >> n;
			n = (n + three.sum) % 1000000001;
			if (three.Search(n))
				cout << "Found" << endl;
			else cout << "Not found" << endl;
			break;

		case 's':
			cin >> three.k1 >> three.k2;
			three.k1 = (three.k1 + three.sum) % 1000000001;
			three.k2 = (three.k2 + three.sum) % 1000000001;
			cout << three.SumThree() << endl;
			break;

		//case 'q':
		//	cin >> three.k1 >> three.k2;
		//	cout << three.SumThree() << endl;
		//	three.sum = 0;
		//	break;
		//
		//case 'z':
		//	three.Show(three.root);
		//	break;

		default:
			break;
		}
	}
}