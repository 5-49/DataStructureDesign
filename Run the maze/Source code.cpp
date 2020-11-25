#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;
const int kMax1 = 100 * 100; //加入墙
const int kMax2 = 102;
bool visit[kMax2][kMax2]; //记录是否被访问过
int maze[kMax2][kMax2];  //迷宫的大小

int n, m;//迷宫的长和宽

struct Point //栈中的数据
{
	int x;
	int y;
};

struct Stack
{
	int top;
	Point path[kMax1];//存坐标点的数组栈
	Stack() { top = -1; }
	bool IsEmpty() { return top == -1;}
	void Clear() { top = -1; }//清除栈中的元素
	void Push(Point p) { path[++top] = p; }//进栈
	Point GetTop() { return path[top]; } //返回栈顶元素
	void DeleteTop() { top--; }//删除栈顶元素

	int PointAnalysis()//对栈顶元素进行处理分析
	{
		int x = path[top].x;
		int y = path[top].y;
		if (x<1 || y<1 || x>n || y>m || !visit[x][y] || maze[x][y]) 
			//在迷宫外，不符合要求
		{
			visit[x][y] = false;
			//标记这个点被访问过，并且不能任意做标记
			return 1;
		}
		else if ((x == n) && (y == m)) return 2;
		//已经找到出口，不要标记，后面直接跳出
		else
		{
			visit[x][y] = false; //标记这个点被访问过
			return 3;  //可以进栈
		}
	}

	void Output()//输出栈中的路径
	{
		int i;
		for (i = 0; i < top; i++)
		{
			cout << "(" << path[i].x << "," << path[i].y << ")" << "--->";
		}
		cout << "(" << path[i].x << "," << path[i].y << ")" << endl;
	};
};

Stack stack;

int main()
{	
	bool TestVisit();
	int Judge();
	void Search();

	int i, j;
	cout << "请输入要生成的迷宫的长和宽:"; 
	cin >> n >> m;
	for (i = 0; i <= (m + 1); i++)
		maze[0][i] = maze[n + 1][i] = 1;
	for (i = 1; i <= (n + 1); i++)
		maze[i][0] = maze[i][m + 1] = 1;
	cout << "随机生成的迷宫如下，1为墙，0为可通路(规定左上角为入口，右下角为出口):" 
		<< endl;

	//随机生成迷宫
	srand(unsigned(time(NULL)));
	for (i = 1; i <= n; i++)
		for (j = 1; j <= m; j++)
			maze[i][j] = (rand() % 2);

	//设置入口和出口
	maze[1][1] = maze[n][m] = 0;

	//输出迷宫
	cout << "生成的迷宫(带有墙)是:" << endl;
	for (i = 0; i <= (n + 1); i++)
	{
		for (j = 0; j <= (m + 1); j++)
			cout << maze[i][j] << " ";
		cout << endl;
	}
	for (i = 1; i <= n; i++)   //记录从Visit[0][0]开始
		for (j = 1; j <= m; j++)
			visit[i][j] = true;
	Search();

	system("pause");
	return 0;
}

bool TestVisit()
//检验每个节点是否都被访问过，全访问过了则为true，false为没有全部访问过
{
	int i, j;
	bool t = true;
	for (i = 1; i <= n; i++)
		for (j = 1; j <= m; j++)
			if (visit[i][j] != false)
			{
				t = false;
				break;
			}
	return t;
}

int Judge()
{
	Point t;
	int flag = 0; //先规定先向右
	while (flag == 0)
	{
		t = stack.GetTop(); //取栈顶元素
		t.y = t.y + 1; //向右  
		stack.Push(t);//将右边的点进栈
		if (stack.PointAnalysis() == 1) //新进栈的点不符合要求
		{
			stack.DeleteTop();//出栈
			t = stack.GetTop();
			t.x = t.x + 1; //向下
			stack.Push(t);//将下边的点进栈
			if (stack.PointAnalysis() == 1)//新进栈的点不符合要求
			{
				stack.DeleteTop();//出栈
				t = stack.GetTop();
				t.y = t.y - 1; //向左
				stack.Push(t);
				if (stack.PointAnalysis() == 1)
				{
					stack.DeleteTop();
					t = stack.GetTop();
					t.x = t.x - 1;	//向上
					stack.Push(t);
					if (stack.PointAnalysis() == 1)
					{
						stack.DeleteTop();
						flag = 4; //这个点4个方向都不成立
					}
				}
			}
		}
		if (stack.PointAnalysis() == 2)//到了mn的位置
		{
			flag = 5; //找到了出口并跳出
			break;
		}
	}
	return flag;
}

void Search()
{
	stack.Clear();
	Point start;
	start.x = 1;
	start.y = 1;
	stack.Push(start);
	visit[1][1] = false;

	while (true)
	{
		int t = Judge();
		if (t == 5)  //找到了路
		{
			cout << "找到了能通的路，路径为(用那个点的坐标表示):" << endl;
			stack.Output();
			break;
		}
		else if (t == 4) stack.DeleteTop();  //退回一个点继续找

		if ((TestVisit() == true) || (stack.top == -1))
		{
			cout << "没有通路!" << endl;
			break;
		}
	}
}
