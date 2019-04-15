#include<iostream>
#include<string>
#include<cstring>
#include<fstream>
#include<vector>
#include"imfo.h"
using namespace std;
imfo::imfo(float p, int d_time, int a_time, string num,int type)
{
	departure[0] = '\0';
	arrival[0] = '\0';
	price = p;
	departure_time = d_time;
	arrival_time = a_time;
	number = num;
	//cout << "构造" << endl;
}
imfo::imfo(const imfo &imfo_copied)
{
	strcpy_s(departure, imfo_copied.departure);
	strcpy_s(arrival, imfo_copied.arrival);
	price = imfo_copied.price;
	departure_time = imfo_copied.departure_time;
	arrival_time = imfo_copied.arrival_time;
	number = imfo_copied.number;
	type = imfo_copied.type;
}
imfo::~imfo()
{

}
void imfo::print()
{
	cout << departure << " " << arrival << " " << price << endl;
	cout << departure_time << endl;
	cout << arrival_time << endl;
	cout << number << endl;
}
void imfo::Set_price(float money)
{
	price = money;
}
void imfo::Set_departure_time(int time)
{
	departure_time = time;
}
void imfo::Set_arrival_time(int time)
{
	arrival_time = time;
}
void imfo::Set_number(string num)
{
	number = num;
}
void imfo::Set_departure(char *copied)
{
	strcpy_s(departure, copied);
}
void imfo::Set_arrvial(char *copied)
{
	strcpy_s(arrival, copied);
}
void imfo::nametonum(int &x, int &y)
{
	if (strcmp(departure,"长沙")==0)
	{
		x = 0;
	}
	if (strcmp(departure,"沈阳")==0)
	{
		x = 1;
	}
	if (strcmp(departure,"北京")==0)
	{
		x = 2;
	}
	if (strcmp(departure,"石家庄")==0)
	{
		x = 3;
	}
	if (strcmp(departure,"济南")==0)
	{
		x = 4;
	}
	if (strcmp(departure,"西安") == 0)
	{
		x = 5;
	}
	if (strcmp(departure,"杭州") == 0)
	{
		x = 6;
	}
	if (strcmp(departure,"南昌") == 0)
	{
		x = 7;
	}
	if (strcmp(departure,"武汉") == 0)
	{
		x = 8;
	}
	if (strcmp(departure,"重庆") == 0)
	{
		x = 9;
	}
	if (strcmp(departure,"广州") == 0)
	{
		x = 10;
	}
	if (strcmp(departure,"南宁") == 0)
	{
		x = 11;
	}
	if (strcmp(arrival, "长沙") == 0)
	{
		y = 0;
	}
	if (strcmp(arrival, "沈阳") == 0)
	{
		y = 1;
	}
	if (strcmp(arrival, "北京") == 0)
	{
		y = 2;
	}
	if (strcmp(arrival, "石家庄") == 0)
	{
		y = 3;
	}
	if (strcmp(arrival, "济南") == 0)
	{
		y = 4;
	}
	if (strcmp(arrival, "西安") == 0)
	{
		y = 5;
	}
	if (strcmp(arrival, "杭州") == 0)
	{
		y = 6;
	}
	if (strcmp(arrival, "南昌") == 0)
	{
		y = 7;
	}
	if (strcmp(arrival, "武汉") == 0)
	{
		y = 8;
	}
	if (strcmp(arrival, "重庆") == 0)
	{
		y = 9;
	}
	if (strcmp(arrival, "广州") == 0)
	{
		y = 10;
	}
	if (strcmp(arrival, "南宁") == 0)
	{
		y = 11;
	}
}
void imfo::Set_type(int travel_type)
{
	type = travel_type;
}
void imfo::printout()
{
	switch (type)
	{
	case 1:cout << "乘坐巴士";
		break;
	case 2:cout << "乘坐飞机";
		break;
	case 3:cout << "乘坐列车";
	default:
		break;
	}
	cout << number <<"\t";
	cout << "于" << departure_time << "点从" << departure << "出发 ";
	cout << arrival_time << "点到达" << arrival << endl;
}
float imfo::Get_price(){
	return price;
}
int imfo::Get_departure_time(){
	return departure_time;
}
int imfo::Get_arrival_time() {
	return arrival_time;
}
string imfo::Get_number() {
	return number;
}
