
#include <iostream>
#include <math.h>
using namespace std;

typedef double type;
const type eps = 1E-10;

//----------------------------------//

struct vec {

	type* begin;		//первый элемент вектора
	type* end;			//значение не относится к вектору, однако память для него выделена
						//при решении слау в нем будет храниться свободный член

	vec(const size_t& M, type*& buffer) {

		//инициализироваться можно только из буфера
		//указатель на свободную память смещается
		//класс не отвечает за выделение и освобождение памяти

		begin = buffer;
		end = begin + M;
		while (buffer <= end)
			cin >> *buffer++;
	}

	size_t normalize() {

		//приведение вектора к единичной длине
		//если это невозможно метод отправляет 1
		//кроме случая когда свободный член равен 0
		//в таком случае отправляется 0

		type len(0);
		auto i(begin);
		while (i != end)
			len += *i * *i++;
		if ((len < eps) && 
			(abs(*end) > eps))
			return 1;
		len = sqrt(len);
		i = begin;
		if (len > eps)
			while (i <= end)
				*i++ /= len;
		else *begin = 0;
		return 0;
	}

	void add(const vec& v, type k) {

		//сложение с вектором
		//предварительно умноженным на k
		//реализация основной операции с вектором

		auto i(this->begin),
			j(v.begin);
		while (i <= end)
			*i++ += *j++ * k;
	}

	void show() {

		//визуализация значений
		//вспомогательый метод

		auto i(this->begin);
		while (i <= end)
			cout << *i++ << ' ';
	}

};

//----------------------------------//

struct equations {

	//класс системы уравнений
	//для перечисления уравнений используются двойные указатели
	//для свободного перемещения уравнений в системе.
	//все данные хранятся в однои непрерывном куске памяти buffer 

	vec** begin;
	vec** end;
	type* buffer;
	size_t N, M;

	equations(size_t n, size_t m) : N(n), M(m) {

		buffer = new type[n * (m + 3)];				//выделяем память под задачу
		auto buf(buffer);
		begin = new vec * [n];						//выделяем память для хранения последовательности уравненений
		end = begin + n;

		while (begin != end) {						//размещаем уравнения в памяти
			buf += 2;
			*begin++ = new (buf - 2) vec(m, buf);
		}

		begin -= n;
	}

	void show() {

		//вспомогательный метод для проверки
		//результатов

		cout << "YES" << endl;
		auto i(begin);
		while (i != end)
			(*i++)->show();
	}

	size_t normalize() {

		//метод осуществяет поиск максимального
		//диагонального элемента
		//если удалось установить, что
		//сисетема не имеет решений метод возвращает 1
		//если система имеет бесконечное число решений метод
		//отправляет 2

		type x, xmax(0);
		vec** imax(nullptr);				//указатель на уравнение с максималным диагональным элементом
		vec** iter(begin);					//итератор по уравнениям
		while (iter != end) {				//пока не прошлись по всем уравнениям
			if ((*iter)->normalize())		//Не удалось привести уравнение у единичному виду или нулю
				return 1;					//система не имеет решений
			x = abs(*(*iter)->begin);
			if (x > xmax) {					//если у уравнения диагональный элемент больше
				imax = iter;				//сохраняем указатель на уравнение
				xmax = x;
			}
			++iter;
		}

		if (imax == nullptr)				//если не нашли нужного уравнения - система имеет много решений
			return 2;						//либо имеет дно решение, но лишние уравнения

		if (begin != imax)					//если нашли, меняем местами уравнения
			swap(*begin, *imax);

		return 0;
	}

	size_t forward() {

		//метод осуществляет прямой ход метода Гаусса

		size_t state;
		size_t k(0);

		while (begin != end) {

			state = this->normalize();		//ищем уравнение с максимальным диагональным элементом
			if (state == 1) return state;	//решений нет
			if (state == 2) {				//решенией много либо лишние уравнения
				if (k == M)					//если найдено достаточное число уравений для решения, то решение одно
					break;
				else return state;			//если достаточное число уравнений нет, то решений много

			};

			vec** iter(begin + 1);			//далее идет алгоритм
			type alfa;						//приведения матрицы
			vec& first = **begin;			//к ступенчатому виду
			type koef(*first.begin);

			while (iter != end) {
				vec& second = **iter;
				alfa = *second.begin;
				second.add(first, -alfa / koef);
				++second.begin;
				++iter;
			}

			++k;
			++begin;
		}

		end = begin;
		begin -= M;
		return 0;
	}

	void reverse() {

		//обратный ход метода Гаусса

		vec** rend(begin - 1);
		vec** i(end);
		type* p;

		while (--i != rend) {
			vec& v(**i);
			type& x(*v.end);				//здесь хранится свободный член
			vec** j(i);
			p = v.begin;

			while (++p != v.end)
				x -= *p * *(**++j).end;		//подставляем неизветсные
			x /= *v.begin;					//делим на диагональный коэффициент
			v.begin = v.end;
		}
	}

};

int main() {

	size_t m, n, state;
	cin >> n >> m;

	equations x(n, m);
	state = x.forward();

	if (state == 1)
		cout << "NO";
	if (state == 2)
		cout << "INF";
	if (state == 0) {
		if (n >= m) {
			x.reverse();
			x.show();
		}
		else {
			cout << "INF";
		}
	}

}
