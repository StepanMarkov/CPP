#include <iostream>
#include <string>


using namespace std;

size_t p(1000000007);
size_t x(3);

template <typename iter>
size_t mhash(iter begin, iter end) {
	
	size_t y(1), res(0);

	for (auto c = begin; c != end; ++c) {
		res += *c * y;
		y *= x;
		//y = y % p;
	}
	return res;
}

size_t mpow(size_t n1, size_t n2) {

	size_t res(1);
	for (auto i(0); i < n2; ++i) {
		res *= n1;
		//res = res % p;
	}
	return res;
}

template<typename iter>
bool equal(const string& s, iter it) {
	for (auto& c : s)
		if (c != *it++)
			return false;
	return true;
}

int main() {

	string pattern, text;
	cin >> pattern >> text;
	size_t m = pattern.size();
	auto c1(text.begin()), c2(c1 + m);
	size_t dh = mpow(x, m - 1);
	size_t hp = mhash(pattern.rbegin(), 
					  pattern.rend());
	size_t ht = mhash(make_reverse_iterator(c2), 
					  make_reverse_iterator(c1));

	if ((hp == ht) && (equal(pattern, c1)))
		cout << 0 << ' ';
 
	ht -= (*c1 * dh);
    
    //size_t t = 0;
    //t = t - 1;
    //cout << t << ' ' << (t *= 2) << ' ' << t/2 << " ass";

	while (c2 != text.end()) {
		ht = ((ht * x) + *c2);       
		++c1; ++c2;
		//cout << ht << ' ';
		//ht = mhash(make_reverse_iterator(c2),
		//		make_reverse_iterator(c1));
		//cout << ht << endl;       
		if ((hp == ht) && (equal(pattern,c1)))
			cout << c1 - text.begin() << ' ';
            
       //cout << *c1 << ' ' << ht << endl;
            
		ht -= (*c1 * dh);
	};

	return 0;

}