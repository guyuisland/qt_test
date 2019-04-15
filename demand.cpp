#include<iostream>
#include<string>
#include<cstring>
#include<algorithm>
#include"demand.h"
#include"imfo.h"
#include<queue>
#include<stack>
#include "mainwindow.h"
#include   <ui_mainwindow.h>

constexpr auto maxtime = 9999;
using namespace std;
extern vector<vector<vector<imfo> > > coach;
extern vector<vector<vector<imfo> > > air;
extern vector<vector<vector<imfo> > > train;

#define price_max 99999;
#define time_max 99999;
float matrix[100][100];  //邻接矩阵
bool visited[100];     //标记数组
float dist[100];         //源点到顶点i的最短距离
int path[100];           //记录最短路的路径
int enqueue_num[100];  //记录入队次数
int vertex_num = 12;       //顶点数
int edge_num = 50;          //边数
int path_matrix[12][12][12]; //记录从A到B经过的路径
int start_to_end[200];//记录从起点到终点的总路线
vector<vector<imfo> > p;
vector<imfo> out_order;
int tmp = 999999;

demand::demand(int dpt,int avi,int stg):departure(dpt),arrvial(avi),strategy(stg)
{
    /*bound = 0;
	char ch = '\0';
	string str;
	cout << "请输入出发城市:";
	getline(cin, str);
	departure=nametonum(str);
	cout << "请输入目的城市:";
	getline(cin, str);
	arrvial=nametonum(str);
	cout << "请输入想要途径的城市：";
	while (ch != '\n')
	{
		cin >> str;
		way_city.push_back(nametonum(str));
		ch = cin.get();
	}
	cout << "请输入出发时间范围(小时):";
	cin >> time_range[0];
	cin >> time_range[1];
	cout << "\n-----------1----------最少花费" << endl;
	cout << "-------------2----------最短时间" << endl;
	cout << "-------------3----------规定时间内花费最少" << endl;
	cout << "请输入您的旅行策略:";
	cin >> strategy;
	if (strategy == 3)
	{
		cout << "请输入规定的时间：";
		cin >> bound;
    }*/
}

demand::~demand()
{
	cout << "调用demand析构函数" << endl;
}
void demand::print()
{
	vector<int>::iterator iter;
	for (iter = way_city.begin();iter != way_city.end();iter++)
	{
		cout << *iter;
	}
}
int demand::nametonum(string &str)
{
	int x = -1;
	if (str=="长沙") 
	{
		x = 0;
	}
	if (str=="沈阳") 
	{
		x = 1;
	}
	if (str=="北京")
	{
		x = 2;
	}
	if (str=="石家庄")
	{
		x = 3;
	}
	if (str=="济南")
	{
		x = 4;
	}
	if (str=="西安")
	{
		x = 5;
	}
	if (str=="杭州")
	{
		x = 6;
	}
	if (str=="南昌")
	{
		x = 7;
	}
	if (str=="武汉")
	{
		x = 8;
	}
	if (str=="重庆")
	{
		x = 9;
	}
	if (str== "广州")
	{
		x = 10;
	}
	if (str=="南宁")
	{
		x = 11;
	}
	return x;
}
void demand::least_time()
{

	int cur_arrvial = way_city[0];
	int cur_departure = departure;
	int min_time = maxtime;
	int nowtime = 0;
	int total_time = 0;
	int temp = cur_arrvial;
	int path[12], D[12], detime[12] = { 0 };
	bool visited[12];
	int **Gra = new int*[12];
	for (int i = 0;i < 12;i++)
	{
		Gra[i] = new int[12];
	}
	vector<int> finalroad;
	vector<int> nowroad;
	vector<int> city_pass;
	vector<int>::iterator city_iter;
	vector<int>::iterator final_iter=finalroad.begin();
	vector<int>::iterator nowroad_iter = nowroad.begin();
	finalroad.push_back(departure);
	for (city_iter = way_city.begin();city_iter != way_city.end();city_iter++)
	{
		city_pass.push_back(*city_iter);
	}
	city_pass.push_back(arrvial);
	for (city_iter = city_pass.begin();city_iter != city_pass.end();city_iter++)
	{
		cur_arrvial = *city_iter;
		/*初始化图*/
		for (int i = 0; i < 12; i++)
		{
			for (int j = 0; j < 12; j++)
			{
				Gra[i][j] = maxtime;
			}
			visited[i] = false;
			path[i] = -1;
		}
		if (city_iter == city_pass.begin())
		{
			initial_Grapah(Gra, time_range, detime, cur_departure);
		}
		else {
			initial_Grapah(Gra, nowtime, detime, cur_departure);
		}
		cur_arrvial = *city_iter;
		/*迪杰斯特拉*/
		for (int i = 0;i < 12;i++)
		{
			D[i] = Gra[cur_departure][i];
			if (D[i]< maxtime)
			{
				path[i] = cur_departure;
			}
			else
			{
				path[i] = -1;
			}
		}
		visited[cur_departure] = true;
		D[cur_departure] = 0;
		int min,count=0,i=0;
		for (int k = 0;k < 12;k++)
		{
			min = maxtime;
			for (int w = 0;w < 12;w++)
			{
				if (!visited[w] && D[w] < min)
				{
					i = w;
					min = D[w];
				}
			}
			nowtime = (detime[find_detime(path,i)]+D[i])%24;
			visited[i] = true;
			renew_Grapah(Gra, nowtime);
			for (int w = 0;w < 12;w++)
			{
				if (!visited[w] && (D[i] + Gra[i][w] < D[w]))
				{
					D[w] = D[i] + Gra[i][w];
					path[w] = i;
				}
			}
		}
		temp = cur_arrvial;
		/*输出*/
		//cout << D[temp] << endl;
		total_time += D[temp];
		while (temp != -1)
		{
			//finalroad.insert(finalroad.begin(),temp);
			nowroad.push_back(temp);
			temp = path[temp];
		}
		reverse(nowroad.begin(), nowroad.end());
		for (nowroad_iter = ++nowroad.begin();nowroad_iter!=nowroad.end();nowroad_iter++)
		{
			finalroad.push_back(*nowroad_iter);
		}
		nowroad.clear();
		vector<int>::iterator path_iter;
		for (path_iter = finalroad.begin();path_iter != finalroad.end();path_iter++)
		{
			cout << *path_iter<<"\t";
		}
		cout << endl;
		cur_departure = cur_arrvial;
	}
	cout << total_time << endl;
	/*释放数组*/
	for (int i = 0;i < 12;i++)
	{
		delete[]Gra[i];
	}
	delete Gra;
	/*计算两城市之间的最短时间*/
	/*初始化图*/
	/*迪杰斯特拉*/
	//initial_Grapah(Gra, time_range,detime,departure);
	/*for (int i = 0;i < 12;i++)
	{
		D[i] = Gra[departure][i];
		if (D[i]< maxtime)
		{
			path[i] = departure;
		}
		else
		{
			path[i] = -1;
		}
	}
	visited[departure] = true;
	D[departure] = 0;
	int min,count=0,i=0;
	for (int k = 0;k < 12;k++)
	{
		min = maxtime;
		for (int w = 0;w < 12;w++)
		{
			if (!visited[w] && D[w] < min)
			{
				i = w;
				min = D[w];
			}
		}
		nowtime = (detime[find_detime(path,i)]+D[i])%24;
		visited[i] = true;
		renew_Grapah(Gra, nowtime);
		
		for (int w = 0;w < 12;w++)
		{
			if (!visited[w] && (D[i] + Gra[i][w] < D[w]))
			{
				D[w] = D[i] + Gra[i][w];
				path[w] = i;
			}
		}
	}
	cout << D[temp] << endl;
	while (temp != -1)
	{
		finalroad.insert(finalroad.begin(),temp);
		temp = path[temp];
	}
	vector<int>::iterator path_iter;
	for (path_iter = finalroad.begin();path_iter != finalroad.end();path_iter++)
	{
		cout << *path_iter<<"\t";
	}
	cout << endl;*/
	return;
}
void initial_Grapah(int **Gra,int time_range[],int detime[],int departure)
{
	int min_time, dtime, atime;
	vector<imfo>::iterator coach_iter;
	for (int k = 0; k < 12; k++)
	{
		for (int i = 0;i < 12; i++)
		{
			min_time = maxtime;
			if (i == k)
			{
				continue;
			}
			for (coach_iter = coach[k][i].begin();coach_iter != coach[k][i].end();coach_iter++)
			{
				if (coach_iter->Get_departure_time() < time_range[0])
				{
					continue;
				}
				else {
					dtime = coach_iter->Get_departure_time();
					atime = coach_iter->Get_arrival_time();
					if (atime < dtime)
					{
						atime += 24;
					}
					if (coach_iter->Get_departure_time() < time_range[1])
					{
						if (atime - dtime < min_time)
						{
							min_time = atime - dtime;
							if (k == departure)
							{
								detime[i] = dtime;
							}
							
						}
							
					}
					else
					{
						continue;
					}
				}
			}
			Gra[k][i] = min_time;
		}
	}
	
}
void initial_Grapah(int **Gra, int nowtime, int detime[], int departure)
{
	int min_time, dtime = 0, atime = 0, wait_time = 0;
	vector<imfo>::iterator coach_iter;
	for (int k = 0; k < 12; k++)
	{
		for (int i = 0;i < 12;i++)
		{
			min_time = maxtime;
			if (i == k)
			{
				continue;
			}
			for (coach_iter = coach[k][i].begin();coach_iter != coach[k][i].end();coach_iter++)
			{
				dtime = coach_iter->Get_departure_time();
				atime = coach_iter->Get_arrival_time();
				if (dtime < nowtime)
				{
					wait_time = dtime + 24 - nowtime;
				}
				else
				{
					wait_time = dtime - nowtime;
				}
				if (atime < dtime)
				{
					atime += 24;
				}
				if (atime - dtime + wait_time < min_time)
				{
					min_time = atime - dtime + wait_time;
					if (k == departure)
					{
						detime[i] = dtime;
					}
				}
			}
			Gra[k][i] = min_time;
		}
	}

}
void renew_Grapah(int **Gra,int nowtime)
{
	int min_time, dtime=0, atime=0,wait_time=0;
	vector<imfo>::iterator coach_iter;
	for (int k = 0; k < 12; k++)
	{
		for (int i = 0;i < 12;i++)
		{
			min_time = maxtime;
			if (i == k)
			{
				continue;
			}
			for (coach_iter = coach[k][i].begin();coach_iter != coach[k][i].end();coach_iter++)
			{
				dtime = coach_iter->Get_departure_time();
				atime = coach_iter->Get_arrival_time();
				if (dtime < nowtime)
				{
					wait_time = dtime + 24 - nowtime;
				}
				else
				{
					wait_time = dtime - nowtime;
				}
				if (atime < dtime)
				{
					atime += 24;
				}
				if (atime - dtime + wait_time < min_time)
				{
					min_time = atime - dtime + wait_time;
				}
			}
			Gra[k][i] = min_time;
		}
	}
}
int find_detime(int path[],int i)
{
	while (path[path[i]] != -1)
	{
		i = path[i];
	}
	return i;
}
void get_path_matrix(int source, float *min)
{
	for (int i = 0; i < vertex_num; i++)
	{
		if (i != source)
		{
			int p = i;
			stack<int> s;

			while (source != p)  //路径顺序是逆向的，所以先保存到栈
			{
				s.push(p);
				p = path[p];
			}

			path_matrix[source][i][0] = source;
			int j = 1;
			while (!s.empty())  //依次从栈中取出的才是正序路径
			{
				path_matrix[source][i][j] = s.top();
				s.pop();
				j++;
			}
		}
	}
}
int SPFA(int source, float *min)
{
	memset(visited, 0, sizeof(visited));
	memset(enqueue_num, 0, sizeof(enqueue_num));
	for (int i = 0; i < vertex_num; i++)
	{
		dist[i] = 99999;
		path[i] = source;
	}
	queue<int> Q;
	Q.push(source);
	dist[source] = 0;
	visited[source] = 1;
	enqueue_num[source]++;
	while (!Q.empty())
	{
		int u = Q.front();
		Q.pop();
		visited[u] = 0;
		for (int v = 0; v < vertex_num; v++)
		{
			if (matrix[u][v] != 99999)
			{
				if (dist[u] + matrix[u][v] < dist[v])
				{
					dist[v] = dist[u] + matrix[u][v];
					path[v] = u;
					if (!visited[v])
					{
						Q.push(v);
						enqueue_num[v]++;
						if (enqueue_num[v] >= vertex_num)
							return false;
						visited[v] = 1;
					}
				}
			}
		}
		for (int i = 0; i < 12; ++i) {
			min[i] = dist[i];
		}
	}
	return true;
}
float get_money(float **matrix_min, int start, int end, int a[], int len) {
	int i, order[12];
	float all_money = 0;
	for (i = 1; i <= len + 1; i++)
		order[i] = a[i - 1];
	order[0] = start;
	order[i] = end;

	for (i = 0; i <= len + 1; i++) {
		all_money = all_money + matrix_min[order[i]][order[i + 1]];
	}
	return all_money;
}
void full_permutation(int a[], int len, int k, int start, int end, float &least_money, int *order, float **matrix_min)
{
	if (len == k)
	{
		int i;
		float money = get_money(matrix_min, start, end, a, len);
		if (least_money > money)
		{
			least_money = money;
			for (i = 0; i <= len; ++i)
				order[i + 1] = a[i];
			order[0] = start;
			order[len + 2] = end;
		}

	}
	else
	{
		for (int idx = k; idx <= len; ++idx)
		{
			swap(a[idx], a[k]);
			full_permutation(a, len, k + 1, start, end, least_money, order, matrix_min);
			swap(a[idx], a[k]);
		}
	}
}
float** get_min_matrix(string** min_money_number) {
	int i, j;
	float min, temp;
	float **matrix_min = new float*[12];
	for (i = 0; i < 12; i++)
	{
		matrix_min[i] = new float[12];
	}
	vector<imfo>::iterator iter;
	for (i = 0; i < 12; ++i) {
		for (j = 0; j < 12; j++) {
			if (coach[i][j].empty()) {
				matrix_min[i][j] = price_max;
				min_money_number[i][j] = "0000000";
				p[i].push_back(0);
				continue;
			}
			min = coach[i][j][0].Get_price();
			min_money_number[i][j] = coach[i][j][0].Get_number();
			p[i][j] = coach[i][j][0];
			for (iter = coach[i][j].begin(); iter != coach[i][j].end(); ++iter)
			{
				temp = iter->Get_price();
				if (temp < min) {
					min = temp;
					min_money_number[i][j] = iter->Get_number();
					p[i][j] = *iter;
				}
			}
			matrix_min[i][j] = min;
		}
	}
	return matrix_min;
}
void demand::least_money()
{
	/*************************************************************************************/
	//中间是对一些重要变量的定义
    float least_money = 99999;
	int out_num = 0;

	int i=0, j=0, k;
	int len=0;//len等于数组b中元素的数量减一
	int  start = departure;//起始城市
	int  end = arrvial;//终止城市
	float** matrix_min;//存放两个城市之间的最小费用
	float min[12];//临时存放一个城市到其他几个城市的最小费用
	int b[12];
	for (i=0;i<12;i++)
	{
		b[i] = -1;
	}
	vector<int>::iterator iter;
	for(iter=way_city.begin();iter!=way_city.end();iter++)
	{
		len++;
	}
	len = len - 1;
	for (iter = way_city.begin(); iter != way_city.end(); iter++)
	{
		b[j] = *iter;
		j++;
	}

	int order[12];//存放这几个城市是怎么途径的
	//int b[3] = { 2,3,11 };//途径的城市,len=b数组的大小-1
	


	string number_matrix[12];
	string** min_money_number = new string*[12];

	/*************************************************************************************/



	/*************************************************************************************/
	//中间是对数据的初始化
	p.resize(12);//r行
	for (k = 0; k < 12; k++) {
		p[k].resize(12);//每行为c列
	}
	for (i = 0; i < 200; i++) {
		start_to_end[i] = -1;
	}
	for (i = 0; i < 12; i++)
	{
		order[i] = -1;
	}
	for (i = 0; i < 12; i++)
	{
		min_money_number[i] = new string[12];
	}
	for (i = 0; i < 12; i++)
	{
		for (j = 0; j < 12; j++)
		{
			for (k = 0; k < 12; k++)
				path_matrix[i][j][k] = -1;
		}
	}
	for (i = 0; i < 200; i++)
	{
		start_to_end[i] = -1;
	}
	for (i = 0; i < vertex_num; i++) {
		for (j = 0; j < vertex_num; j++) {
			matrix[i][j] = 88888; //Initialize the matrix array
		}
	}

	/*************************************************************************************/


	matrix_min = get_min_matrix(min_money_number);//min_money_number存放的是两个城市之间的最小费用

	for (i = 0; i < 12; ++i)
	{
		for (j = 0; j < 12; ++j)
		{
			matrix[i][j] = matrix_min[i][j];
		}
	}

	for (int source = 0; source < 12; ++source)
	{
		SPFA(source, min);
		for (i = 0; i < 12; ++i)
		{
			matrix_min[source][i] = min[i]; //matrix_min is Shortest path between two points
		}
	}

	for (i = 0; i < 12; i++)
	{
		SPFA(i, min);
		get_path_matrix(i, min);
	}


    if(len == -1)
        {
            least_money = matrix_min[start][end];
            order[0] = start;
            order[1] = end;
        }
    else
    {
        full_permutation(b, len, 0, start, end, least_money, order, matrix_min);
    }
	start_to_end[0] = start;
	k = 1;
	for (i = 0; order[i + 1] != -1; i++)
	{
		for (j = 1; path_matrix[order[i]][order[i + 1]][j] != -1; j++)
		{
			start_to_end[k] = path_matrix[order[i]][order[i + 1]][j];
			k++;
		}
	}
	for (i = 0; start_to_end[i + 1] != -1; i++)
	{
		out_order.push_back(p[start_to_end[i]][start_to_end[i + 1]]);
	}
	out_num = i;
	
    //vector<imfo>::iterator iter1;
    //i = 0;
    /*for (iter1 = out_order.begin(); iter1 != out_order.end(); iter1++)
	{
		cout << "第" << i << "步:";
		i++;
		iter1->printout();
    }*/
    tmp = least_money;
	
}

