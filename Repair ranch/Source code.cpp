#include<assert.h>
#include<iostream>
#include<cstdlib>
using namespace std;


//思路：逆向思考，每次都拿最小的两个碎片相加在一起 

class PriorityQueue {
public:
	int *elements;//存放元素的数组
	int count;//统计当前有多少个元素
	int max_size;//初始化的数组容量

	bool Insert(const int x);//插入函数
	bool Remove(const int x);//删除函数
	PriorityQueue() { max_size = count = 0; elements = nullptr; }
	PriorityQueue(int i) {
		count = 0;
		max_size = i;
		elements = new int[i];
		assert(elements != nullptr);
	}

};

//该插入函数实现在优先级队列中插入数据
//并且保持优先级队列的有序性
bool PriorityQueue::Insert(const int x) {
	if (count == max_size) {
		cout << "输入超过限数" << endl;
		return false;
	}

	if (count == 0) elements[count++] = x;
	else {
		int i = 0;
		for (i = 0; i < count; i++) {
			int position;
			if (elements[i] > x) {//找到插入位置position
				position = i;
				for (int j = count; j > position; j--) {
					elements[j] = elements[j - 1];
				}//position以耙院蟮脑?睾笠盘
				elements[position] = x;//position位置赋值x
				count++;
				break;
			}
		}

		if (i == count) elements[count++] = x;
	}
	return true;
}

//该删除函数实现在优先级队列中删除数据
//并且保持优先级队列的有序性
bool PriorityQueue::Remove(const int x) {
	int position;
	for (position = 0; position < count; position++) {
		if (elements[position] == x)
			break;//找到这个元素的位置
	}
	if (position == count) {
		cout << "没有这个元素" << endl;
		return false;
	}
	else {
		for (int i = position; i < count - 1; i++) {
			elements[i] = elements[i + 1];//后面的数组前移动
		}
		count--;
	}
	return true;
}

//寻找最小花费的函数
int MinSum(PriorityQueue A) {
	//数组元素不足三个时
	if (A.count == 0 || A.count == 1) return 0;
	if (A.count == 2) return A.elements[0] + A.elements[1];

	int sum = 0, temp;
	int temp0, temp1;

	while (A.count != 2) {
		//取前两个元素（因为前两个最小）
		temp0 = A.elements[0];
		temp1 = A.elements[1];
		//求和并加入花费计算
		temp = temp0 + temp1;
		sum = sum + temp;
		//删除这两个元素，并把它们的和插入数组
		A.Remove(temp0);
		A.Remove(temp1);
		A.Insert(temp);
	}

	//当只剩下两个元素，count==2时跳出循环
	//返回值为当前花费加上最后两个碎片
	return sum + A.elements[0] + A.elements[1];
}

//主函数
int main() {
	int sum, temp;
	//输入木头碎片个数
	cout << "请输入木头的碎片数量以及每一块木头碎片的大小：" << endl;
	cin >> sum;
	PriorityQueue Hedge(sum);
	//输入每一块木头碎片的大小
	for (int i = 0; i < sum; i++) {
		cin >> temp;
		Hedge.Insert(temp);
	}
	//调用函数输出结果
	cout << MinSum(Hedge) << endl;

	system("pause");
	return 0;
}
