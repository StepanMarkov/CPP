//Найдите минимальное вершинное покрытие в двудольном графе.
//На вход подается описание двудольного графа, в котором доли уже выделены явно.
//Первая строка содержит три натуральных числа : v1 — число вершин первой доли
//v2 — число вершин второй доли, e ≤ v1∗v2 — число рёбер. 
//Подразумевается, что первая доля состоит из вершин с номерами от 0 до v1 - 1
//вторая — из вершин с номерами от v1 до v1 + v2 - 1
//Следующие e строк описывают рёбра : каждая из этих строк содержит два числа : 
//0 <= ui <= v1; v1 <= wi <= v1+v2;
// что означает, что между вершинами ui и wi есть ребро.
//Скопируйте описание графа из входа на выход и выведите 
//единственную дополнительную строку — список номеров вершин, 
//составляющих минимальное вершинное покрытие.Если таких покрытий несколько, выведите любое.
//Автор: Марков С.А.

#include <iostream>
#include <list>

using namespace std;
struct line;

struct node {				//вершина
	list<pair<node*,line*>> lines;	//вершины содержат указатель на инцедентное ребро и указатель на соседнюю вершину
	bool selected = false;		//вспомогательное поле для обхода графа
	size_t free = 0;		//поле, указывающее инцедентна ли вершина с паросочетанием
};

struct line {				//ребро
	pair<node*, node*> nodes;	//поле, указывающее из каких вершин состоит ребро
	bool selected = false;		//вспомогательное поле для обхода графа
	bool solution = false;		//поле, указывающее является относится ли ребро к паросочетанию
};

int main() {

	size_t v1, v2, e; cin >> v1 >> v2 >> e;
	size_t v(v1 + v2), index1(0), index2(0);
	auto lines(new line[e]), lend(lines + e);			//выделение памяти для ребер
	auto nodes(new node[v]), nend(nodes + v), nend1(nodes+v1);	//выделение памяти для вершин
	list<line*> wayline;						//контейнер для хранения расширяющихся путей
	list<node*> waynode;						//вспомогательный контейнер для обхода в глубину

	for (auto pline(lines); pline != lend; ++pline) {		//считываем данные
		cin >> index1 >> index2;
		auto node1(nodes + index1);
		auto node2(nodes + index2);
		pline->nodes = { node1, node2 };
		node1->lines.push_back({ node2, pline });
		node2->lines.push_back({ node1, pline });
	}

	//------------------------------------//

	do {	//итерации в алгоритме Хопкрофта-Карпа

		for (auto& x : wayline)				//цикл по расширяющимся путям
			if (x->solution) {			//если ребро пути находится в текущем паросочетании
				x->solution = false;		//исключаем ребро из паросочетания
				--x->nodes.first->free;		//помечаем в вершинах, что они инцедентное ребро
				--x->nodes.second->free;	//исключено из паросочетания
			}
			else {
				x->solution = true;		//добавляем реберо в паросочетание
				++x->nodes.first->free;		//помечаем, что вершина инцедентно с ребром
				++x->nodes.second->free;	//которое относится к паросочтатанию
			}

		wayline.clear();				//подготавливаемся к поиску расширяющихся путей

		for (auto pnode(nodes); pnode != nend; ++pnode)
			pnode->selected = false;

		for (auto p1(nodes); p1 != nend; ++p1) {	//цикл для поиска расширяющихся путей

			if (p1->free)		continue;	//первая вершина пути должна быть свободна
			if (p1->selected)	continue;	//расширяющиеся пути не должны пересекаться
			p1->selected = true;			//помечаем, что мы здесь были
			auto p2(p1);				//впомогательная локалльная переменная - конец расширающегося пути
			auto sw(false);				//впомогательная переменная, отвечающеся за переменный порядок паросочетаний в пути
			waynode.clear();

			DFS1:
			for (auto& x : p2->lines) {			//цикл по инцедентным ребрам
				if (x.first->selected) continue;	//соседную вершину уже обходили
				if (sw ^ x.second->solution) continue;	//не тот порядок паросочетания в пути
				wayline.push_back(x.second);		//добаяляем ребро в расширяющийся путь
				waynode.push_back(p2);			//добаялем вершину (для обхода в глубину)
				p2 = x.first;				//переходим к следующей вершине
				p2->selected = true;			//помечаем, что вершину уже проходили
				sw = !sw;				//меняем порядок паросочетания
				if (p2->free) goto DFS1;		//поиск в глубину, если не достигли свободной вершины
				else break;				//если наши свобоную вершину, поиск завершен
			}

			if ((!waynode.empty()) && (p2->free)) {		//не удлось найти свободную вершину
				p2 = waynode.back();			//отходим назад
				waynode.pop_back();			//исключаем последную вершину из обхода в глубину
				wayline.pop_back();			//исключаем послуюнее ребро в искомом пути
				sw = !sw;				//меняем порядок паросочетания
				goto DFS1;				//возвращаемся к поску
			}
		}
	} while (!wayline.empty());					//продолжаем итерации, пока не получится найти расширающйися путь
	
	//на этом этапе мы нашли максимальное паросочетание
	//по теореме Кенига можно найти минимальное вершиное покрытие
	//используя максимальное паросочетание

	for (auto pnode(nodes); pnode != nend; ++pnode)			//подготавливаемся к поиску минимального вершиного покрытия
		pnode->selected = false;
		
	for (auto p1(nodes); p1 != nend1; ++p1) {			//цикл по первой доле двудольного графа
									//алгоритм похож на итерацию в алгоритме Хопкрофта-Карпа
		if (p1->free)		continue;			
		if (p1->selected)	continue;
		p1->selected = true;
		auto p2(p1);
		auto sw(false);
		waynode.clear();
	
		DFS2:
		for (auto& x : p2->lines) {
			if (x.first->selected) continue;
			if (sw ^ x.second->solution) continue;
			waynode.push_back(p2);
			p2 = x.first;
			p2->selected = true;
			sw = !sw;
			goto DFS2;
		}
	
		if (!waynode.empty()) {
			p2 = waynode.back();
			waynode.pop_back();
			sw = !sw;
			goto DFS2;
		}
	}

	//--------------------------------------------------//

	cout << v1 << ' ' << v2 << ' ' << e << endl;		//выводим результат в неоходимом формате

	for (auto pline(lines); pline != lend; ++pline) {
		cout << pline->nodes.first  - nodes << ' ';
		cout << pline->nodes.second - nodes << endl;
	}

	for (auto p1(nodes); p1 != nend1; ++p1)
		if (!p1->selected)
			cout << p1 - nodes << ' ';
	for (auto p2(nend1); p2 != nend; ++p2)
		if (p2->selected)
			cout << p2 - nodes << ' ';
	
	//--------------------------------------------------//
	
	return 0;
}
