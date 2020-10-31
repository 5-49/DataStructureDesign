// Author: YangJing 
// Date: 2020/10/13.
//Using Microsoft Visual Studio
//Use Google naming rules

#include<iostream>
#include<string>
using namespace std;

//考生节点类定义
class Node
{
public:
	int id;//考生号
	string name;//姓名
	string sex;//性别
	int age;//年龄
	string exam;//报考类别
	Node* next;
	Node() { next = nullptr; }

	void Display()
	{	
		//输出考生节点信息
		cout << id<< "\t" << name << "\t" << sex 
			<< "\t" << age << "\t" << exam << endl;
		return;
	}
};

//链表类定义
class Link
{
public:
	Node* head;
	int len;
	Link()
	{	
		len = 0;
		head = new Node();
	}

	void AddNode(Node* s);
	void DeleteNode(int id);
	Node* FindNode(int id);
	void ModifyNode(int id);
	void Traverse();
};

//增加考生节点
void Link::AddNode(Node* s)
{
	Node*p = new Node();
	p = s;
	p->next = head->next;
	head->next = p;
	len++;
}

//删除考生节点
void Link::DeleteNode(int id)
{
	Node*q = head;
	Node*p = head->next;
	while (p != nullptr)
	{
		if (p->id == id)
		{
			q->next = p->next;
			cout << "你要删除的考生信息是：" << endl;
			p->Display();
			delete p;
			len--;
			break;
		}
		else
		{
			p = p->next;
			q = q->next;
		}
	}
}

//寻找考生并返回这个节点
Node* Link::FindNode(int id)
{
	Node*p = head->next;
	while (p != nullptr)
	{
		if (p->id == id)
		{
			return p;
			break;
		}
		else
		{
			p = p->next;
		}
	}
	return nullptr;
}

//修改考生信息
void Link::ModifyNode(int id)
{
	Node*p = FindNode(id);
	cout << "请重新输入该考号学生的姓名，性别，年龄以及报考类别：" << endl;
	cin >> p->name >> p->sex >> p->age >> p->exam;
	cout << "修改成功!" << endl;
}

//按考号排序并输出考生信息
void Link::Traverse()
{
	Node* p = new Node();

	//冒泡排序
	for (int i = 0; i < len; i++)
	{
		for (p = head->next; p->next != nullptr; p = p->next)
		{
			if (p->id > p->next->id)
			{	
				swap(p->id, p->next->id);
				swap(p->name, p->next->name);
				swap(p->age, p->next->age);
				swap(p->sex, p->next->sex);
				swap(p->exam, p->next->exam);
			}
		}
	}

	cout << "考号" <<"\t"<< "姓名" << "\t" << "性别" 
		<< "\t" << "年龄" << "\t" << "报考类别" << endl;

	p = head->next;
	while (p != nullptr) {
		p->Display();
		p = p->next;
	}
}

//测试循环
void TestLoop()
{
	int num;
	cout << "首先建立考生信息系统：" << endl << "请输入考生人数：";
	cin >> num;
	cout << "请依次输入考生的考号，姓名，性别，年龄和报考类型：" << endl;

	Link StudentList;
	//初始化考生信息
	for (int i = 0; i < num; i++)
	{
		Node* p=new Node();
		cin >> p->id >> p->name >> p->sex >> p->age >> p->exam;
		StudentList.AddNode(p);
	}

	cout << "请选择你要进行的操作：1，插入；2，删除；3，查找；4，修改；5，统计；0，取消操作。" << endl;

	while (1)
	{
		cout << endl << "请选择你的操作：";

		int operate;
		cin >> operate;
		int temp;
		Node* s = new Node();
		switch (operate)
		{
		case 1://插入考生
			cout << "请依次输入该考生的考号，姓名，性别，年龄和报考类型：" << endl;
			cin >> s->id >> s->name >> s->sex >> s->age >> s->exam;
			if(StudentList.FindNode(s->id)!=nullptr)
				StudentList.AddNode(s);
			else cout << "插入失败，该考号已存在学生，请检查输入考号是否正确。" << endl;
			break;
		case 2://删除一个考生
			cout << "请输入要删除的考生的考号：" << endl;
			cin >> temp;
			if (StudentList.FindNode(temp) != nullptr)
				StudentList.DeleteNode(temp);
			else cout << "删除失败，考试系统中无该考号，请检查输入考号是否正确。" << endl;
			break;
		case 3://查找一个考生
			cout << "请输入要查找的考生的考号：" << endl;
			cin >> temp;
			if (StudentList.FindNode(temp) != nullptr) 
			{
				cout << "考号" << "\t" << "姓名" << "\t" << "性别"
					<< "\t" << "年龄" << "\t" << "报考类别" << endl;
				StudentList.FindNode(temp)->Display();
			}
			else cout << "不存在该考生，请检查输入的考号是否正确。" << endl;
			break;
		case 4://修改其中一个考生信息
			cout << "请输入要修改的考生的考号：" << endl;
			cin >> temp;
			if (StudentList.FindNode(temp) != nullptr)
				StudentList.ModifyNode(temp);
			else cout << "修改失败，考试系统中无该考号，请检查输入考号是否正确。" << endl;
			break;
		case 5://按序打印当前考生列表
			cout << "当前考试系统中，考生列表如下：" << endl;
			StudentList.Traverse();
			break;
		case 0:
			return;
		}
	}
	return;
}

//主函数
int main()
{
	TestLoop();
	return 0;
}
