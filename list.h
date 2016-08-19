#include <cstdio>

const int maxNode = 10000;
template<class T>
struct list_node {
	list_node *pre, *suf;
	T data;
	list_node() {
		pre = suf = NULL;
	}
	list_node(T data):data(data) {
		pre = suf = NULL;
	}
};

template<class T>
struct list {
	typedef list_node<T> T_node;
	T_node *front,*back;
	int num;
	list() {
		num = 0;
		front = new T_node();
		back = new T_node();
		front->suf = back;
		back->pre = front;
	}
	int getNum() {
		return num;
	}
	void push_front(T data) {
		T_node *newNode = new T_node(data);
		newNode->suf = front->suf;
		front->suf->pre = newNode;

		front->suf = newNode;
		newNode->pre = front;

		++num;
	}
	void push_back(T data) {
		T_node *newNode = new T_node(data);
		newNode->pre = back->pre;
		back->pre->suf = newNode;

		back->pre = newNode;
		newNode->suf = back;

		++num;
	}
	void pop_front() {
		if (num == 0) {
			// ERROR handle
			return ;
		}
		T_node *rabbish = front->suf;
		front->suf->suf->pre = front;
		front->suf = front->suf->suf;
		delete rabbish;
		--num;
	}
	void pop_back() {
		if (num == 0) {
			// ERROR handle
			return ;
		}
		T_node *rabbish = back->pre;
		back->pre->pre->suf = back;
		back->pre = back->pre->pre;
		delete rabbish;
		--num;
	}
	bool empty() {
		return num == 0;
	}
	T get_front() {
		if (front->suf == NULL) {
			// ERROR handle
			return *(new T);
		}
		return front->suf->data;
	}
	T get_back() {
		if (back->pre == NULL) {
			// ERROR handle
			return *(new T);
		}
		return back->pre->data;
	}
};

