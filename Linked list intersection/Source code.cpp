#include<iostream>

using namespace std;

class Element {
private:
	int data;
public:
	Element* next;
	int getData() const { return data; }
	//构造函数
	Element(int a, Element* link = nullptr) {
		data = a;
		next = link;
	};
	//在该元素后插入一个元素并返回这个元素
	Element* insertAfter(int i) {
		next = new Element(i);
		return next;
	}
};

class List {
private:
	Element* head;
	//输入运算符重载
	friend istream& operator>>(istream&, List&);

public:
	//默认构造函数
	List() { head = new Element(-1); }
	Element* getHead() const { return head; }
	bool Search(int i);//搜索函数
	void Display() const;//打印函数
};

istream& operator>>(istream& in, List& x) {
	Element* rear = x.getHead();
	while (1) {
		int i;
		in >> i;
		if (i == -1) break;
		// 非降序，正，整数
		else if (in.fail()||i != (int)i || i < 0 || i < rear->getData()) {
			cout << endl << " (T︿T) 非法输入导致程序强制退出!" 
				<< endl << endl << "都和你说啦输入的序列应该是非降序正整数序列。"
				<<endl << endl;
			system("pause");
			exit(-1);
		}
		rear = rear->insertAfter(i);
	}
	return in;
}

//寻找序列中值为i的元素
bool List::Search(int i) {
	Element* p = head;
	if (i < 0) return false;
	p = p->next;
	while (p != nullptr) {
		if (p->getData() == i)
			return true;
		else p = p->next;
	}
	return false;
}

//打印函数
void List::Display() const {
	Element* p = head;
	if (p->next == nullptr) {
		cout << "NULL";
		return;
	}
	while (p->next != nullptr) {
		cout << p->next->getData() << " ";
		p = p->next;
	}
	cout << endl;
	return;
}

//两个链表求交集
List Intersection(List& A, List& B) {
	Element* a = A.getHead();
	List C; //结果存储在C中
	Element* c = C.getHead();

	while (a->next != nullptr) {
		a = a->next;
		if (B.Search(a->getData())) 
			c = c->insertAfter(a->getData());
	}
	return C;
}

void testLoop() {
	List A;
	List B;
	cout << "请输入一串非降序正整数序列 A 。" <<
		"元素之间用空格隔开，以-1作为输入结束的标志" << endl << endl;
	cout << "注意是非降序正整数序列喔！(^ω^)" << endl << endl;
	cin >> A;
	cout << endl << "请输入一串非降序正整数序列 B。" <<
		"用空格隔开，以-1作为输入结束的标志" << endl << endl;
	cout << "仍然注意是非降序正整数序列！(^ω^)" << endl << endl;
	cin >> B;

	cout << endl << "两者的交集是：" << endl;
	Intersection(A, B).Display();
}

int main() {
	testLoop();
	system("pause");
	return 0;
}
