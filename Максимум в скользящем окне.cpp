#include <iostream>
#include <algorithm>
#include <intrin.h>
#include <deque>

using namespace std;

typedef int* ptr;

ptr MaximumSet(ptr begin, ptr end) {
	
	int maxl(*begin), maxr(*--end);
	
	while (begin != end) {
	
		if (maxl < maxr) {
			if (*++begin < maxl)
				*begin = maxl;
			else 
				maxl = *begin;
		}
		else if (*--end < maxr)
			*end = maxr;
		else
			maxr = *end;
	}
	
	return end;
}

void DequeMethod(ptr a, int n, int m) {
	deque<int> q;
	for (int i = 0; i < m; ++i) {
		while (!q.empty() && a[q.back()] <= a[i]) {
			q.pop_back();
		}
		q.push_back(i);
	}
	//res.push_back(a[q.front()]);

	for (int i = m; i < n; ++i) {

		while (!q.empty() && q.front() <= i - m) {
			q.pop_front();
		}

		while (!q.empty() && a[q.back()] <= a[i]) {
			q.pop_back();
		}
		q.push_back(i);

		//res.push_back(a[q.front()]);
	}
	//return res;
}

void MarkovMethod(ptr begin, ptr end, int m) {

	ptr iter1(begin), iter2(begin + m), iter3, imax1;
	ptr imax2(MaximumSet(iter1, iter2));
	int max1, max2(*imax2), max3;

	while (iter2 < end) {
		imax1 = imax2;
		iter3 = min(iter2 + m, end);
		imax2 = MaximumSet(iter2, iter3--);
		max1 = max2;
		max2 = *imax2;

		*iter1++ = max1;

		if (imax2 >= imax1 + m) {

			while (iter1 <= imax1) {

				if (*iter2 > max1)
					goto cycle1;

				*iter1 = max1;
				++iter1;
				++iter2;
			} goto cycle2;

			while (iter1 <= imax1) {
				cycle1:
				*iter1 = *iter2;
				++iter1;
				++iter2;
			}

			cycle2:
			while (iter2 < imax2) {

				if (*iter2 > * iter1)
					goto cycle3;

				++iter1;
				++iter2;
			} goto cycle5;

			while (iter2 < imax2) {
				cycle3:
				*iter1 = *iter2;
				++iter1;
				++iter2;
			}
		}
		else {

			max3 = max(max1, max2);

			while (iter2 < imax2) {

				if (*iter2 > max1)
					goto cycle4;

				*iter1 = max1;
				++iter1;
				++iter2;
			}

			while (iter2 < imax2) {
				cycle4:
				*iter1 = *iter2;
				++iter1;
				++iter2;
			}

			while (iter1 <= imax1) {
				*iter1 = max3;
				++iter1;
				++iter2;
			}
		}

		cycle5:
		while (iter2 < iter3) {

			if (*iter1 < max2)
				goto cycle6;

			++iter1;
			++iter2;
		} goto cycle7;

		while (iter2 < iter3) {
			cycle6:
			*iter1 = max2;
			++iter1;
			++iter2;
		}

		cycle7:
		++iter2;
	}

	if ((begin - end) % m == 0)
		*iter1 = max2;

}

int main() {

	int n = 100000;
	int m = 1000;

	ptr vbegin(new int[n]);
	ptr vend(vbegin + n);

	for (ptr v(vbegin); v < vend; ++v)
		*v = rand();

	auto clock = __rdtsc();
	MarkovMethod(vbegin, vend, m);
	clock = __rdtsc() - clock;
	cout << clock << endl;

	clock = __rdtsc();
	DequeMethod(vbegin, n, m);
	clock = __rdtsc() - clock;
	cout << clock << endl;

	system("PAUSE");

}