#include <stdlib.h>
#include <iostream>
#include <iomanip>

using namespace std;

// 测试数据
//int const n=5; // 进程数
//int const m=3; // 资源种类数
//int Available[m]={3,3,2};     // 可用资源
//int Max[n][m]={7,5,3,3,2,2,9,0,2,2,2,2,4,3,3};        // 最大需求
//int Allocation[n][m]={0,1,0,2,0,0,3,0,2,2,1,1,0,0,2}; // 已分得资源
//int Need[n][m]={7,4,3,1,2,2,6,0,0,0,1,1,4,3,1};       // 需求矩阵
//int Work[m]={3,3,2};          // 工作向量
//bool Finish[n]={false,false,false,false,false};       // 是否满足
//int Request[m]={1,0,2};       // 请求资源
//int P=1;                // 请求资源的进程

	int n = 100; // 进程数
	int m = 100; // 资源种类数
	int Available[100] = { 0 };     // 可用资源
	int Max[100][100] = { 0 };        // 最大需求
	int Allocation[100][100] = { 0 }; // 已分得资源
	int Need[100][100] = { 0 };       // 需求矩阵
	int Work[100] = { 0 };          // 工作向量
	bool Finish[100] = { 0 };       // 是否满足
	int Request[100] = { 0 };       // 请求资源
	char Name[100] = { 0 };     // 资源名称 eg:A B C ...
	int P = 0;                // 请求资源的进程

void init();  //  初始化函数的声明
bool safeCheck(bool flag);  //定义bool型数 flag
void printTable();  //打印函数声明
void recoverSafe(); //程序安全，恢复Work与Available值，等待请求
void bankerMethod(); //银行家算法


// 初始化进程和资源
void init()
{
	cout << "请输入参与的进程数量：";
	cin >> n;
	cout << "请输入参与的资源数量：";
	cin >> m;
	for (int i = 0; i<26; i++) //给资源取名字，例A,B,C... 
	{
		Name[i] = i + 65;
	}
	for (int i = 0; i<m; i++) //输入每一种资源的Available 例A B C 分别为 10 5 7
	{
		cout << "请输入系统中" << Name[i] << "资源的数量：";
		cin >> Available[i];
	}
	cout << "请输入各进程对各资源的最大需求量：" << endl;//Max矩阵
	for (int i = 0; i<n; i++)
		for (int j = 0; j<m; j++)
			cin >> Max[i][j];
	cout << "请输入各进程当前已分得各资源的数量：" << endl;//Allocation矩阵
	for (int i = 0; i<n; i++)
		for (int j = 0; j<m; j++)
			cin >> Allocation[i][j];
	//Need矩阵 Max=Need+Allocation
	for (int i = 0; i<n; i++)
		for (int j = 0; j<m; j++)
			Need[i][j] = Max[i][j] - Allocation[i][j];
	// 初始化Available
	for (int i = 0; i<n; i++)
		for (int j = 0; j<m; j++)
			Available[j] = Available[j] - Allocation[i][j];
	// 初始化Work
	recoverSafe();//恢复模块调用
}

// 安全性检查
bool safeCheck(bool flag)
{

	cout << "---DATA---|" << setfill(' ') << setw(3 * m + 2) << "Work" << "|" << setw(3 * m + 2) <<
		"Need" << "|" << setw(3 * m + 2) << "Allocation" << "|" << setw(3 * m + 2) << "Work+Allo" << "|" << "Finish|" << endl;

	cout << "-RESOURCE-|";
	//第二行的Work的 A B C
	for (int i = 0; i<m; i++)
		cout << "--" << Name[i];
	cout << "--|";
	//第二行的Need的 A B C
	for (int i = 0; i<m; i++)
		cout << "--" << Name[i];
	cout << "--|";
	//第二行的Allocation的 A B C
	for (int i = 0; i<m; i++)
		cout << "--" << Name[i];
	cout << "--|";
	//第二行的Work+Allocation的 A B C
	for (int i = 0; i<m; i++)
		cout << "--" << Name[i];
	cout << "--|" << endl;

number0:
	for (int i = 0; i<n; i++) //每次都从P0开始找起
	{
		int count = 0;
		for (int j = 0; j<m; j++)
		{
			if (!Finish[i] && Need[i][j] <= Work[j])//比较Need[j]与Work[j]的大小
			{
				count++;//满足执行下一个
			}
			if (count == m)//当count 为3时再执行
			{
				cout << "----P" << i << "----|";
				for (int k = 0; k<m; k++)
					cout << "-" << setw(2) << Work[k];
				cout << "--|";
				for (int k = 0; k<m; k++)
					cout << "-" << setw(2) << Need[i][k];
				cout << "--|";
				for (int k = 0; k<m; k++)
					cout << "-" << setw(2) << Allocation[i][k];
				cout << "--|";

				for (int k = 0; k<m; k++)
				{
					Work[k] = Work[k] + Allocation[i][k];
				}
				Finish[i] = true;

				for (int k = 0; k<m; k++)
					cout << "-" << setw(2) << Work[k];
				cout << "--|";
				cout << "--" << Finish[i] << "--|";
				cout << endl;
				goto number0;//循环number0
			}
		}
	}
	for (int i = 0; i<n; i++)
	{
		if (!Finish[i])
		{
			flag = false;
			break;
		}
	}
	if (flag)
	{
		cout << "********************************系统处于安全状态********************************" << endl;
		return true;
	}
	else
	{
		cout << "*******************************系统处于不安全状态*******************************" << endl;
		return false;
	}
}

// 打印试分配后的资源分配表
void printTable()
{
	//打印第一行
	cout << "---DATA---|" << setw(4 * m) << "Max" << "|" << setw(4 * m) << "Allocation"
		<< "|" << setw(4 * m) << "Need" << "|" << setw(4 * m) << "Available" << "|" << endl;
	//打印第二行
	cout << "-RESOURCE-|";
	//第二行的Max的 A B C
	for (int i = 0; i<m; i++)
		cout << "-" << Name[i] << "--";
	cout << "|";
	//第二行的Allocation的 A B C
	for (int i = 0; i<m; i++)
		cout << "-" << Name[i] << "--";
	cout << "|";
	//第二行的Need的 A B C
	for (int i = 0; i<m; i++)
		cout << "-" << Name[i] << "--";
	cout << "|";
	//第二行的Available的 A B C
	for (int i = 0; i<m; i++)
		cout << "-" << Name[i] << "--";
	cout << "|" << endl;
	//用二维数组打印数据
	for (int i = 0; i<n; i++)
	{
		cout << "---P" << i << "-----|";
		//Max矩阵
		for (int j = 0; j<m; j++)
		{
			cout << "-" << setfill('0') << setw(2) << Max[i][j] << "-";
		}
		cout << "|";
		//Allocation矩阵
		for (int j = 0; j<m; j++)
		{
			cout << "-" << setfill('0') << setw(2) << Allocation[i][j] << "-";
		}
		cout << "|";
		//Need矩阵
		for (int j = 0; j<m; j++)
		{
			cout << "-" << setfill('0') << setw(2) << Need[i][j] << "-";
		}
		cout << "|";
		//Available矩阵
		if (i == 0)
		{
			for (int j = 0; j<m; j++)
				cout << "-" << setfill('0') << setw(2) << Available[j] << "-";
			cout << "|";
		}
		cout << endl;
	}
}

// 安全性检查后，恢复Work向量和Finish向量，等待请求
void recoverSafe()
{
	// 恢复Work
	for (int i = 0; i<m; i++)
		Work[i] = Available[i];//将Available赋给Work，进行安全性序列检测
	for (int i = 0; i<n; i++)
		Finish[i] = false;
}

// 银行家算法
void bankerMethod()
{
	// 客户端提示
	cout << "请输入需要请求资源的进程编号：" << endl;
	for (int i = 0; i<n; i++)
	{
		cout << setfill(' ') << setw(3) << "P" << i << ":" << i << endl;
	}
	// 检查输入合法性
	int tmpP = -1;
	bool flagP = false;
	while (!flagP)
	{
		cout << "进程编号:";
		cin >> tmpP;
		if (tmpP<0 || tmpP >= n)
		{
			cout << "此进程不存在，请重新输入！" << endl;
			flagP = false;
		}
		else
		{
			P = tmpP;
			flagP = true;
		}
	}

	// 确认请求资源Request
	for (int i = 0; i<m; i++)
	{
		cout << "请输入进程P" << P << "请求的" << Name[i] << "资源的数量：";
		cin >> Request[i];
	}

	// 1.判断进程请求数量是否小于需求最大数量
	bool flag = true;
	int countRN = 0;
	for (int i = 0; i<m; i++)
	{
		if (Request[i] <= Need[P][i])
			countRN++;
		if (countRN == m)
			flag = true;
		else
			flag = false;
	}
	if (flag)
	{
		// 2.判断进程请求数量是否小于系统可用数量
		int countRA = 0;
		for (int i = 0; i<m; i++)
		{
			if (Request[i] <= Available[i]) //循环检测
				countRA++;
			if (countRA == m)
				flag = true;
			else
				flag = false;
		}
		if (flag)
		{
			// 3.系统试探着把资源分配给进程
			for (int i = 0; i<m; i++) {
				Available[i] = Available[i] - Request[i];
				Allocation[P][i] = Allocation[P][i] + Request[i];
				Need[P][i] = Need[P][i] - Request[i];
				Work[i] = Work[i] - Request[i];
			}
			// T0时刻的资源分配表
			cout << "-----------------------为P" << P << "分配资源后的资源分配表------------------------" << endl;
			printTable();
			// 4.安全性算法
			cout << "------------------------P" << P << "申请资源时的安全性检查-------------------------" << endl;
			flag = safeCheck(flag);

			// 如果安全性检查不通过，则回收进程请求的资源
			if (!flag)
			{
				for (int i = 0; i<m; i++) {
					Available[i] = Available[i] + Request[i];
					Allocation[P][i] = Allocation[P][i] - Request[i];
					Need[P][i] = Need[P][i] + Request[i];
					Work[i] = Work[i] + Request[i];
				}
			}
			recoverSafe();
		}
		else
			cout << "********************************系统没有足够资源可以分配，阻塞********************************" << endl;
	}
	else
		cout << "************************请求已超出进程P" << P << "需求最大值************************" << endl;
}

int main(void)
{
	// 初始化进程和资源
	cout << "********************************初始化进程和资源********************************" << endl;
	init();
	cout << "**********************************初始化已完成**********************************" << endl;

	// T0时刻的资源分配表
	cout << "---------------------------T0时刻的资源分配表----------------------------" << endl;
	printTable();

	// T0时刻的安全性检查
	cout << "---------------------------T0时刻的安全性检查----------------------------" << endl;
	bool tmp = true;
	bool flagInit = safeCheck(tmp);
	// 恢复安全性检查向量
	recoverSafe();

	// 银行家算法
	while (true)
	{
		cout << "是否要继续请求资源(y/n):" << endl;
		char yhRequest;
		cin >> yhRequest;
		if (yhRequest == 'n' || yhRequest == 'N')
			break;
		bankerMethod();
	}
	return 0;
}