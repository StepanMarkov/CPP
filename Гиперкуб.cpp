//Докажите, что kk - мерный гиперкуб kk - связен с помощью теоремы Менгера.
//kk - мерным гиперкубом называется граф, в котором вершины — битовые строки длины kk,
//а рёбра проведены между теми парами вершин, которые отличаются ровно в одном бите.
//На вход подаётся две различные битовых строки AA и BB длины k \lt 100k < 100 через пробел.
//Выведите kk простых путей в kk - мерном гиперкубе из AA в BB, не пересекающихся по внутренним вершинам.Формат вывода : 
//один путь на строку; путь – последовательности битовых строк, разделённая пробелами.

#include <iostream>
#include <string>
#include <list>
#include <vector>

using namespace std;

inline void flip(char& c) {
	c = (c == '0') ? '1' : '0';
}

int main() {

	string s1, s2, s;
	cin >> s1 >> s2;
	//s1 = "0111111011011";
	//s2 = "1111011011010";
	list<size_t> index1, index2;
	const size_t size(s1.size());

	for (size_t i(0); i != size; ++i) {
		if (s1[i] == s2[i])
			index1.push_back(i);
		else index2.push_back(i);
	}

	for (size_t j(0); j != index2.size(); ++j) {
		s = s1;
		cout << s << ' ';
		for (size_t& i : index2) {
			flip(s[i]);
			cout << s << ' ';
		}
		cout << endl;
		index2.push_back(index2.front());
		index2.pop_front();
	}

	for (size_t& j : index1) {
		s = s1;
		cout << s << ' ';
		flip(s[j]);
		cout << s << ' ';
		for (size_t& i : index2) {
			flip(s[i]);
			cout << s << ' ';
		}
		cout << s2 << ' ' << endl;
	}
}