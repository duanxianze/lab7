// lab7.cpp : 定义控制台应用程序的入口点。
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

