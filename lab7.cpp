// lab7.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Graphlnk.h"
#include<fstream>

int main()
{
	Graphlnk<char,int> graph(20);
	ifstream file("data.txt");
	file >> graph;
	cout << graph;
    return 0;
}

