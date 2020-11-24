#include<iostream>
#include<assert.h>
using namespace std;

class Queue {
public:
	void push(const int& x);//入队
	bool pop();//出队
	int getTop() { return people[top]; };//返回队首元素
	bool isEmpty() const { return top == rear; }
	bool isFulll() const { return rear == maxSize ; }
	Queue() { top = rear = 0; };
	Queue(int size);
	~Queue(){delete[]people;}

private:
	int* people;//存储数组
	int top;//头结点
	int rear;//尾结点
	int maxSize;//最大容量
};

//含参构造函数
Queue::Queue(int size): top(0),rear(0),maxSize(size){
	people = new int[maxSize];
	assert(people != nullptr);
}

//入队
void Queue::push(const int& x){
	assert(!isFulll());
	people[rear] = x;
	rear++;
}

//出队
bool Queue::pop(){
	if (isEmpty() == true) return false;
	top++;
	return true;
}

int main() {
	int sum;
	int id;
	cin >> sum;
	
	if (cin.fail() || sum <= 0) 
		cout << "非法输入！" << endl << "程序强制退出！" << endl;

	Queue A(sum);
	Queue B(sum);

	for (int i = 0; i < sum; i++) {
		cin >> id;
		if (cin.fail()||id<=0) {
			cout << "非法输入！" << endl << "程序强制退出！" << endl;
			system("pause");
			exit(0);
		}
		if (id % 2 == 1) {
			A.push(id);
		}
		else if (id % 2 == 0) {
			B.push(id);
		}
	}

	int flag = 1;//处理空格：判断当前是不是输出的第一个编号
	//A，B都不为空
	while (A.isEmpty() != 1 && B.isEmpty()!= 1 ) {
		//输出一个数，先看A
		if (flag == 1) {//如果是第一次输出就不输出空格
			cout << A.getTop();
			flag--;
		}
		else if (flag == 0) {//不是第一次输出就输出空格
			cout << " " << A.getTop();
		}
		A.pop();
		//如果A还有就输出A
		if (A.isEmpty() != 1) {
			cout << " " << A.getTop();
			A.pop();
		}
		//输出B
		cout << " " << B.getTop();
		B.pop();
	}

	//A为空，B不为空
	while (A.isEmpty() == 1 && B.isEmpty() != 1) {
		if (flag == 1) {//如果是第一次输出就不输出空格
			cout << B.getTop();
			flag--;
		}
		else if (flag == 0) {//不是第一次输出就输出空格
			cout << " " << B.getTop();
		}
		B.pop();
	}

	//B为空，A不为空
	while (A.isEmpty() != 1 && B.isEmpty() == 1) {
		if (flag == 1) {//如果是第一次输出就不输出空格
			cout << A.getTop();
			flag--;
		}
		else if (flag == 0) {//不是第一次输出就输出空格
			cout << " " << A.getTop();
		}
		A.pop();
	}

	system("pause");
	return 0;
}



