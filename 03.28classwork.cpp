#include <iostream>
#include <vector>
#include <list>
#include <cmath>
using namespace std;

class Point {
	int x, y;
public:
	Point() {
		this->x = 0;
		this->y = 0;
	}
	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}
	Point(Point *p) {
		this->x = p->x;
		this->y = p->y;
	}
	int getX() {
		return this->x;
	}
	void setX(int x) {
		this->x = x;
	}
	int getY() {
		return this->y;
	}
	void setY(int y) {
		this->y = y;
	}
	void print() {
		cout << this->getX() << ", " << this->getY() << endl;
	}
};

class PointIterator {
	Point *val;
	PointIterator *prev;
	PointIterator *next;
public:
	PointIterator() {
		this->val = nullptr;
		this->prev = nullptr;
		this->next = nullptr;
	}

	PointIterator(Point *val) :
			PointIterator() {
		this->val = val;
	}

	PointIterator(PointIterator *pi) {
		this->val = new Point(pi->getVal());
		this->next = nullptr;
		this->prev = nullptr;
	}

	PointIterator* getPrev() {
		return this->prev;
	}
	void setPrev(PointIterator *prev) {
		this->prev = prev;
	}

	PointIterator* getNext() {
		return this->next;
	}
	void setNext(PointIterator *next) {
		this->next = next;
	}

	Point* getVal() {
		return this->val;
	}
	void setVal(Point *val) {
		this->val = val;
	}

	~PointIterator() {
		if (this->val)
			delete this->val;
	}
};

class PointList {
	PointIterator *first;
	PointIterator *last;
public:
	PointList() {
		this->first = new PointIterator();
		this->last = this->first;
	}

	PointList(Point *val) {
		this->first = new PointIterator(val);
		this->last = this->first;
	}

	PointList(PointList *list) {
		PointIterator *start1 = nullptr;
		PointIterator *start2 = list->getFirst();
		while (start2) {
			PointIterator *tmp;
			if (start1)
				PointIterator *tmp = new PointIterator(start1);
			start2 = start2->getNext();
			start1->setNext(new PointIterator(start2));
			start1 = start1->getNext();
			start1->setPrev(tmp);
		}
	}

	~PointList() {
		PointIterator *start = this->first;
		while (start->getNext()) {
			start = start->getNext();
			delete start->getPrev();
		}
		delete this->last;
	}

	PointIterator* getFirst() {
		return this->first;
	}

	PointIterator* getLast() {
		return this->first;
	}

	void push_front(Point *p) {
		PointIterator *newStart = new PointIterator(p);
		if (this->first) {
			newStart->setNext(this->first);
			this->first->setPrev(newStart);
			this->first = newStart;
		} else {
			this->first = newStart;
			this->last = newStart;
		}
	}

	void pop_front() {
		if (this->first) {
			PointIterator *tmp = this->first->getNext();
			delete this->first;
			this->first = tmp;
		}
	}

	void push_back(Point *p) {
		PointIterator *newEnd = new PointIterator(p);
		if (this->last) {
			newEnd->setPrev(this->last);
			this->last->setNext(newEnd);
			this->last = newEnd;
		} else {
			this->first = newEnd;
			this->last = newEnd;
		}
	}

	void pop_back() {
		if (this->last) {
			PointIterator *tmp = this->last->getPrev();
			delete this->last;
			this->last = tmp;
		}
	}

	int size() {
		if (!this->first)
			return 0;
		int s { 1 };
		PointIterator *ptr = this->getFirst();
		while (ptr->getNext()) {
			ptr = ptr->getNext();
			s++;
		}
		return s;
	}

	void push_index(Point *p, int idx) {
		if (this->size() <= idx) {
			push_back(p);
			return;
		}
		PointIterator *newVal = new PointIterator(p);
		PointIterator *before = this->first;
		for (int i = 0; i < idx; i++) {
			before = before->getNext();
		}
		PointIterator *after = before->getNext();
		before->setNext(newVal);
		newVal->setPrev(before);
		after->setPrev(newVal);
		newVal->setNext(after);
	}

	Point* getPoint(int idx) {
		if (this->size() <= idx) {
			return this->getLast()->getVal();
		}
		PointIterator *ptr = this->getFirst();
		for (int i = 0; i < idx; i++) {
			ptr = ptr->getNext();
		}
		return ptr->getVal();
	}

	void print() {
		PointIterator *start = this->first;
		while (start) {
			start->getVal()->print();
			start = start->getNext();
		}
	}
};

class Math {
public:
	static double d(int x1, int x2, int y1, int y2) {
		int dx = x1 - x2;
		int dy = y1 - y2;
		return pow(pow(dx, 2) + pow(dy, 2), 0.5);
	}

	static double d(Point *p1, Point *p2) {
		int x1 = p1->getX();
		int x2 = p2->getX();
		int y1 = p1->getY();
		int y2 = p2->getY();

		return d(x1, x2, y1, y2);
	}

	static double S(int x1, int x2, int y1, int y2) {
		int l = abs(x1 - x2);
		double h = (y1 + y2) / 2;
		return (double) l * h;
	}

	static double S(Point *p1, Point *p2) {
		int x1 = p1->getX();
		int x2 = p2->getX();
		int y1 = p1->getY();
		int y2 = p2->getY();

		return S(x1, x2, y1, y2);
	}

	static int maxX(PointList *l) {
		int max { l->getFirst()->getVal()->getX() };
		for (PointIterator *ptr = l->getFirst(); ptr; ptr = ptr->getNext())
			if (ptr->getVal()->getX() > max)
				max = ptr->getVal()->getX();
		return max;
	}

	static int minX(PointList *l) {
		int min { l->getFirst()->getVal()->getX() };
		for (PointIterator *ptr = l->getFirst(); ptr; ptr = ptr->getNext())
			if (ptr->getVal()->getX() < min)
				min = ptr->getVal()->getX();
		return min;
	}

	static double avgX(PointList *l){
		double a{};
		for(PointIterator *ptr = l->getFirst(); ptr; ptr = ptr->getNext()){
			a+=ptr->getVal()->getX();
		}
		a/=(double)l->size();
		return a;
	}

	static double standardDeviationX(PointList *l){
		int n=l->size();
		int x_a=avgX(l);
		double sd{};
		for(PointIterator *ptr = l->getFirst(); ptr; ptr = ptr->getNext()){
			sd+=pow(ptr->getVal()->getX()-x_a,2);
		}
		sd/=(double)(n*n-n);
		sd=pow(sd,0.5);
		return sd;
	}

};

int main() {
	PointList *list = new PointList(new Point(1, 2));
	list->push_front(new Point(2, 3));
	list->push_front(new Point(5, 13));
	list->push_back(new Point(8, 4));
	list->push_back(new Point(6, 48));
	list->push_index(new Point(111, -7), 1);
	cout << "Hello" << endl;
	list->print();
	cout << list->size() << endl;
	cout << "Distance between ";
	list->getFirst()->getVal()->print();
	cout << " and ";
	list->getPoint(3)->print();
	cout << " is ";
	cout << Math::d(list->getFirst()->getVal(), list->getPoint(3)) << endl;
	cout << "And the area under them is ";
	cout << Math::S(list->getFirst()->getVal(), list->getPoint(3)) << endl;
	cout<<"Avg x is "<<Math::avgX(list)<<endl;
	cout<<"Standard deviation is "<<Math::standardDeviationX(list)<<endl;

	PointList *list2 = new PointList;
	for (int i = 0; i < 10; i++) {
		list2->push_front(new Point(i, i));
		list2->getFirst()->getVal()->print();
		list2->pop_front();
	}
	list2->print();
	//list->getFirst()->getVal()->print();
	//list->getFirst()->getNext()->getVal()->print();
	//cout<<list->getFirst()->getNext()->getVal()->getX();

	return 0;
}
