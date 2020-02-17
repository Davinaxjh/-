#include <stdlib.h>
#include <iostream>
#include <iomanip>

using namespace std;

// ��������
//int const n=5; // ������
//int const m=3; // ��Դ������
//int Available[m]={3,3,2};     // ������Դ
//int Max[n][m]={7,5,3,3,2,2,9,0,2,2,2,2,4,3,3};        // �������
//int Allocation[n][m]={0,1,0,2,0,0,3,0,2,2,1,1,0,0,2}; // �ѷֵ���Դ
//int Need[n][m]={7,4,3,1,2,2,6,0,0,0,1,1,4,3,1};       // �������
//int Work[m]={3,3,2};          // ��������
//bool Finish[n]={false,false,false,false,false};       // �Ƿ�����
//int Request[m]={1,0,2};       // ������Դ
//int P=1;                // ������Դ�Ľ���

	int n = 100; // ������
	int m = 100; // ��Դ������
	int Available[100] = { 0 };     // ������Դ
	int Max[100][100] = { 0 };        // �������
	int Allocation[100][100] = { 0 }; // �ѷֵ���Դ
	int Need[100][100] = { 0 };       // �������
	int Work[100] = { 0 };          // ��������
	bool Finish[100] = { 0 };       // �Ƿ�����
	int Request[100] = { 0 };       // ������Դ
	char Name[100] = { 0 };     // ��Դ���� eg:A B C ...
	int P = 0;                // ������Դ�Ľ���

void init();  //  ��ʼ������������
bool safeCheck(bool flag);  //����bool���� flag
void printTable();  //��ӡ��������
void recoverSafe(); //����ȫ���ָ�Work��Availableֵ���ȴ�����
void bankerMethod(); //���м��㷨


// ��ʼ�����̺���Դ
void init()
{
	cout << "���������Ľ���������";
	cin >> n;
	cout << "������������Դ������";
	cin >> m;
	for (int i = 0; i<26; i++) //����Դȡ���֣���A,B,C... 
	{
		Name[i] = i + 65;
	}
	for (int i = 0; i<m; i++) //����ÿһ����Դ��Available ��A B C �ֱ�Ϊ 10 5 7
	{
		cout << "������ϵͳ��" << Name[i] << "��Դ��������";
		cin >> Available[i];
	}
	cout << "����������̶Ը���Դ�������������" << endl;//Max����
	for (int i = 0; i<n; i++)
		for (int j = 0; j<m; j++)
			cin >> Max[i][j];
	cout << "����������̵�ǰ�ѷֵø���Դ��������" << endl;//Allocation����
	for (int i = 0; i<n; i++)
		for (int j = 0; j<m; j++)
			cin >> Allocation[i][j];
	//Need���� Max=Need+Allocation
	for (int i = 0; i<n; i++)
		for (int j = 0; j<m; j++)
			Need[i][j] = Max[i][j] - Allocation[i][j];
	// ��ʼ��Available
	for (int i = 0; i<n; i++)
		for (int j = 0; j<m; j++)
			Available[j] = Available[j] - Allocation[i][j];
	// ��ʼ��Work
	recoverSafe();//�ָ�ģ�����
}

// ��ȫ�Լ��
bool safeCheck(bool flag)
{

	cout << "---DATA---|" << setfill(' ') << setw(3 * m + 2) << "Work" << "|" << setw(3 * m + 2) <<
		"Need" << "|" << setw(3 * m + 2) << "Allocation" << "|" << setw(3 * m + 2) << "Work+Allo" << "|" << "Finish|" << endl;

	cout << "-RESOURCE-|";
	//�ڶ��е�Work�� A B C
	for (int i = 0; i<m; i++)
		cout << "--" << Name[i];
	cout << "--|";
	//�ڶ��е�Need�� A B C
	for (int i = 0; i<m; i++)
		cout << "--" << Name[i];
	cout << "--|";
	//�ڶ��е�Allocation�� A B C
	for (int i = 0; i<m; i++)
		cout << "--" << Name[i];
	cout << "--|";
	//�ڶ��е�Work+Allocation�� A B C
	for (int i = 0; i<m; i++)
		cout << "--" << Name[i];
	cout << "--|" << endl;

number0:
	for (int i = 0; i<n; i++) //ÿ�ζ���P0��ʼ����
	{
		int count = 0;
		for (int j = 0; j<m; j++)
		{
			if (!Finish[i] && Need[i][j] <= Work[j])//�Ƚ�Need[j]��Work[j]�Ĵ�С
			{
				count++;//����ִ����һ��
			}
			if (count == m)//��count Ϊ3ʱ��ִ��
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
				goto number0;//ѭ��number0
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
		cout << "********************************ϵͳ���ڰ�ȫ״̬********************************" << endl;
		return true;
	}
	else
	{
		cout << "*******************************ϵͳ���ڲ���ȫ״̬*******************************" << endl;
		return false;
	}
}

// ��ӡ�Է�������Դ�����
void printTable()
{
	//��ӡ��һ��
	cout << "---DATA---|" << setw(4 * m) << "Max" << "|" << setw(4 * m) << "Allocation"
		<< "|" << setw(4 * m) << "Need" << "|" << setw(4 * m) << "Available" << "|" << endl;
	//��ӡ�ڶ���
	cout << "-RESOURCE-|";
	//�ڶ��е�Max�� A B C
	for (int i = 0; i<m; i++)
		cout << "-" << Name[i] << "--";
	cout << "|";
	//�ڶ��е�Allocation�� A B C
	for (int i = 0; i<m; i++)
		cout << "-" << Name[i] << "--";
	cout << "|";
	//�ڶ��е�Need�� A B C
	for (int i = 0; i<m; i++)
		cout << "-" << Name[i] << "--";
	cout << "|";
	//�ڶ��е�Available�� A B C
	for (int i = 0; i<m; i++)
		cout << "-" << Name[i] << "--";
	cout << "|" << endl;
	//�ö�ά�����ӡ����
	for (int i = 0; i<n; i++)
	{
		cout << "---P" << i << "-----|";
		//Max����
		for (int j = 0; j<m; j++)
		{
			cout << "-" << setfill('0') << setw(2) << Max[i][j] << "-";
		}
		cout << "|";
		//Allocation����
		for (int j = 0; j<m; j++)
		{
			cout << "-" << setfill('0') << setw(2) << Allocation[i][j] << "-";
		}
		cout << "|";
		//Need����
		for (int j = 0; j<m; j++)
		{
			cout << "-" << setfill('0') << setw(2) << Need[i][j] << "-";
		}
		cout << "|";
		//Available����
		if (i == 0)
		{
			for (int j = 0; j<m; j++)
				cout << "-" << setfill('0') << setw(2) << Available[j] << "-";
			cout << "|";
		}
		cout << endl;
	}
}

// ��ȫ�Լ��󣬻ָ�Work������Finish�������ȴ�����
void recoverSafe()
{
	// �ָ�Work
	for (int i = 0; i<m; i++)
		Work[i] = Available[i];//��Available����Work�����а�ȫ�����м��
	for (int i = 0; i<n; i++)
		Finish[i] = false;
}

// ���м��㷨
void bankerMethod()
{
	// �ͻ�����ʾ
	cout << "��������Ҫ������Դ�Ľ��̱�ţ�" << endl;
	for (int i = 0; i<n; i++)
	{
		cout << setfill(' ') << setw(3) << "P" << i << ":" << i << endl;
	}
	// �������Ϸ���
	int tmpP = -1;
	bool flagP = false;
	while (!flagP)
	{
		cout << "���̱��:";
		cin >> tmpP;
		if (tmpP<0 || tmpP >= n)
		{
			cout << "�˽��̲����ڣ����������룡" << endl;
			flagP = false;
		}
		else
		{
			P = tmpP;
			flagP = true;
		}
	}

	// ȷ��������ԴRequest
	for (int i = 0; i<m; i++)
	{
		cout << "���������P" << P << "�����" << Name[i] << "��Դ��������";
		cin >> Request[i];
	}

	// 1.�жϽ������������Ƿ�С�������������
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
		// 2.�жϽ������������Ƿ�С��ϵͳ��������
		int countRA = 0;
		for (int i = 0; i<m; i++)
		{
			if (Request[i] <= Available[i]) //ѭ�����
				countRA++;
			if (countRA == m)
				flag = true;
			else
				flag = false;
		}
		if (flag)
		{
			// 3.ϵͳ��̽�Ű���Դ���������
			for (int i = 0; i<m; i++) {
				Available[i] = Available[i] - Request[i];
				Allocation[P][i] = Allocation[P][i] + Request[i];
				Need[P][i] = Need[P][i] - Request[i];
				Work[i] = Work[i] - Request[i];
			}
			// T0ʱ�̵���Դ�����
			cout << "-----------------------ΪP" << P << "������Դ�����Դ�����------------------------" << endl;
			printTable();
			// 4.��ȫ���㷨
			cout << "------------------------P" << P << "������Դʱ�İ�ȫ�Լ��-------------------------" << endl;
			flag = safeCheck(flag);

			// �����ȫ�Լ�鲻ͨ��������ս����������Դ
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
			cout << "********************************ϵͳû���㹻��Դ���Է��䣬����********************************" << endl;
	}
	else
		cout << "************************�����ѳ�������P" << P << "�������ֵ************************" << endl;
}

int main(void)
{
	// ��ʼ�����̺���Դ
	cout << "********************************��ʼ�����̺���Դ********************************" << endl;
	init();
	cout << "**********************************��ʼ�������**********************************" << endl;

	// T0ʱ�̵���Դ�����
	cout << "---------------------------T0ʱ�̵���Դ�����----------------------------" << endl;
	printTable();

	// T0ʱ�̵İ�ȫ�Լ��
	cout << "---------------------------T0ʱ�̵İ�ȫ�Լ��----------------------------" << endl;
	bool tmp = true;
	bool flagInit = safeCheck(tmp);
	// �ָ���ȫ�Լ������
	recoverSafe();

	// ���м��㷨
	while (true)
	{
		cout << "�Ƿ�Ҫ����������Դ(y/n):" << endl;
		char yhRequest;
		cin >> yhRequest;
		if (yhRequest == 'n' || yhRequest == 'N')
			break;
		bankerMethod();
	}
	return 0;
}