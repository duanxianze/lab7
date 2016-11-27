#ifndef GRAPH_H
#define GRAPH_H
#include "SeqQueue.h"
#include <fstream>
const int maxWeight = 100000;
// 图的抽象基类定义#有权无向图
// T为顶点的类型；E为边权值的类型，一般应为某一整数类型。
template <class T, class E>
class Graph{
public:
	Graph(int sz){
		maxVertices = sz;
		numVertices = 0;
		numEdges = 0;
	}
	virtual ~Graph(){};
	bool GraphEmpty() const{				//判图空否	
		return (numEdges == 0);
	}
	bool GraphFull() const{					//判图满否 	
		return (numVertices == maxVertices || 
			numEdges == maxVertices*(maxVertices-1)/2);//无向图，有向图不除以2
	}
	int NumberOfVertices(){				//返回当前顶点数	
		return numVertices;
	}
	int NumberOfEdges(){					//返回当前边数	
		return numEdges;
	}
	void DFS();						    //深度优先遍历图，输出所有的连通分量
	void BFS();						    //广度优先遍历图，输出所有的连通分量
	void Components();					//利用深度优先搜索求非连通图的连通分量的算法
		
	friend istream& operator>> (istream &in, Graph<T,E> &G){
		int i, j, k, n, m;
		T e1, e2;
		E weight;
		in >> n >> m;				//输入顶点数与边数
		for (i = 0; i < n; i++){	//依次输入顶点值
			in >> e1;
			G.insertVertex(e1);
		}
		i = 0;
		while (i < m){
			assert(in >> e1 >> e2 >> weight);	//依次输入边的两顶点值及其权值
			j = G.getVertexPos(e1);				//取对应顶点下标
			k = G.getVertexPos(e2);
			if (j == -1 || k == -1){			//取对应顶点不存在
				cout << "Input error!\n";
			}
			else{
				G.insertEdge(j, k, weight);		//由顶点下标和权值插入边
				i++;
			}
		}
		return in;
	}friend ifstream& operator >> (ifstream &in, Graph<T, E> &G) {
		int i, j, k, n, m;
		T e1, e2;
		E weight;
		in >> n >> m;				//输入顶点数与边数
		for (i = 0; i < n; i++) {	//依次输入顶点值
			in >> e1;
			G.insertVertex(e1);
		}
		i = 0;
		while (i < m) {
			assert(in >> e1 >> e2 >> weight);	//依次输入边的两顶点值及其权值
			j = G.getVertexPos(e1);				//取对应顶点下标
			k = G.getVertexPos(e2);
			if (j == -1 || k == -1) {			//取对应顶点不存在
				cout << "Input error!\n";
			}
			else {
				G.insertEdge(j, k, weight);		//由顶点下标和权值插入边
				i++;
			}
		}
		return in;
	}
	friend ostream& operator<< (ostream &out, Graph<T,E> &G){
		int i, j, n, m;
		T e1, e2;
		E weight;
		n = G.NumberOfVertices();		//顶点数与边数
		m = G.NumberOfEdges();
		out << "Number of Vertices: " << n << endl;
		out << "Number of Edges: " << m << endl;
		out << "The edges in the graph are:\n";
		for (i = 0; i < n; i++){
			for (j = i + 1; j < n; j++){
				weight = G.getWeight(i, j);
				if (weight > 0 && weight < maxWeight){
					e1 = G.getValue(i);	//由下标取得顶点值
					e2 = G.getValue(j);
					out << "(" << e1 << "," << e2 << "," << weight << ")" << endl;
				}
			}
		}
		return out;
	}

	// 图的子类必须实现的一些接口
	virtual T getValue(int i) = 0;							//取位置为i的顶点中的值
	virtual E getWeight(int v1, int v2) = 0;				//返回边(v1,v2)上的权值
	virtual bool insertVertex(const T &vertex) = 0;			//在图中插入一个顶点vertex
	virtual bool removeVertex(int v) = 0;					//在图中删除一个顶点v
	virtual bool insertEdge(int v1, int v2, E weight) = 0;	//插入权值为weight的边(v1,v2)
	virtual bool removeEdge(int v1, int v2) = 0;			//删除边(v1,v2)
	virtual int getFirstNeighbor(int v) = 0;				//取顶点v的第一个邻接顶点
	virtual int getNextNeighbor(int v, int w) = 0;			//取v的邻接顶点w的下一邻接顶点
	virtual int getVertexPos(const T &vertex) = 0;			//给出顶点vertex在图中的位置
protected:
	int maxVertices;			//图中最大顶点数
	int numEdges;				//当前边数
	int numVertices;			//当前顶点数
	void DFS(int v, bool visited[]);					   //深度优先遍历图，子过程
	void BFS(int v, bool visited[]);
};


//深度优先遍历图,非连通图输出所有节点
template<class T, class E> 
void Graph<T,E>::DFS(){
	int i, n = NumberOfVertices();		//取图中顶点个数
	bool *visited = new bool[n]; 		//创建辅助数组
	for (i = 0; i < n; i++){			//辅助数组visited初始化	
		visited[i] = false;
	}
	//DFS(0,visited);					//连通图
	for(i=0;i<n;i++){					//#非连通图，从每个顶点开始，各做一次遍历。
		if(!visited[i]){				//#借助辅助数组，上一趟遍历已访问过的各顶点不会作为新起点。所以输出了所有连通分量，不会重复。
			DFS(i, visited); 			//从顶点0开始深度优先搜索
			cout<<endl;
		}
	}
	delete [] visited;					//释放visited
}

//从顶点位置v出发, 以深度优先的次序访问所有可读入的尚未访问过的顶点。
//算法中用到一个辅助数组visited, 对已访问过的顶点作访问标记。
template<class T, class E>
void Graph<T,E>::DFS(int v, bool visited[]){
	/*代码写在这里*/

		

}

//广度优先遍历图，输出所有的连通分量
template <class T, class E>void Graph<T,E>::BFS(){
	int i, n = NumberOfVertices();		//图中顶点个数
	bool *visited = new bool[n];	
	for (i = 0; i < n; i++){
		visited[i] = false;
	}

	for (i = 0; i < n; i++){	//#从每个顶点开始，各做一次遍历。
		//if (visited[i] == true){//#借助辅助数组，上一趟遍历已访问过的各顶点不会作为新起点。所以输出了所有连通分量，不会重复。
		//	continue;
		//}
		if(!visited[i])
			{
			 BFS(i,visited);
			}
	}
	delete [] visited;
}
template <class T, class E>
void Graph<T,E>::BFS(int i, bool visited[]){/*代码写在这里*/




}

//利用深度优先搜索求非连通图的连通分量的算法
template<class T, class E> void Graph<T,E>::Components(){
	int i, n = NumberOfVertices();		//取图中顶点个数
	bool *visited = new bool[n]; 		//创建辅助数组
	for (i = 0; i < n; i++){				//辅助数组visited初始化	
		visited[i] = false;
	}
	int j=1;
	for(i=0;i<n;i++){
		if(!visited[i]){
			cout << "Component " << j << ":" << endl;
			DFS(i, visited); 			//从顶点0开始深度优先搜索
			j++;
			cout << endl;
		}
	}
	delete [] visited;					//释放visited
}


//////////////////////////////////////////////////////////////////
//无权图的最短路径
template <class T, class E>
void BFS_shortestpath(Graph<T,E> &G, T vertex, E dist[], int path[])
{
	SeqQueue<int> Q;
	int n=G.NumberOfVertices();
	 T w;
	 int v=G.getVertexPos(vertex);
	 for(int i=0;i<n;i++)
		 dist[i]=maxValue;
	   dist[v]=0;
	//	 cout << getValue(i) << ' ';				//访问顶点v
		// visited[v] = true;						//做已访问标记
		  Q.EnQueue(v);
			//顶点进队列, 实现分层访问
			while (!Q.IsEmpty()){		//循环, 访问所有结点
				Q.DeQueue(v);					//不能随意改变控制变量i
				w =G.getFirstNeighbor(v);			//第一个邻接顶点
				while (w != -1){						//若邻接顶点w存在
					if (dist[w]==maxValue){				//若未访问过
						dist[w]=dist[v]+1;
						path[w]=v;
						Q.EnQueue(w);				//顶点w进队列
					    }
					w = G.getNextNeighbor(v, w);		//找顶点v的下一个邻接顶点
				}
			}//外层循环，判队列空否
			cout << endl;

	    //delete [] visited;

}

//  输出path
template <class T,class E>
void printpath(Graph<T,E> &g, int v, int path[])
{//int i=g.getvertexPos();
if(path[v]!=-1)
 printpath(g,path[v],path);

cout<<g.getValue(v)<< " ";
}

//Dijkstra
//Graph是一个带权有向图。
//dist[j], 0≤j<n, 是当前求到的从顶点v到顶点j的最短路径长度,
//path[j], 0≤j<n, 存放求到的最短路径。
template <class T, class E>
void ShortestPath(Graph<T,E> &G, T v, E dist[], int path[]){
    int n = G.NumberOfVertices();
    bool *S = new bool[n]; 	   //最短路径顶点集
    int i, j, k;  E w, min;
    for (i = 0; i < n; i++)	{
	    dist[i] = G.getWeight(v, i);
        S[i] = false;
        if (i != v && dist[i] < maxValue) path[i] = v;
        else path[i] = -1;
    }
    S[v] = true;  dist[v] = 0;     	//顶点v加入顶点集合
   /*补充完整代码*/
}


//a[i][j]是顶点i和j之间的最短路径长度。
//path[i][j]是相应路径上顶点j的前一顶点的顶点号。
template <class T, class E>
void Floyd(Graph<T,E> &G, E **a, int **path){
	int i, j, k, n = G.NumberOfVertices();
    for (i = 0; i < n; i++){    	//矩阵a与path初始化	
        for (j = 0; j < n; j++){
            a[i][j] = G.getWeight (i,j);
			if (i != j && a[i][j] < maxValue){
				path[i][j] = i;
			}
			else{
				path[i][j] = 0;
			}
        }
	}
    for (k = 0; k < n; k++){   //针对每一个k, 产生a(k)及path(k)			
        for (i = 0; i < n; i++){
            for (j = 0; j < n; j++){
				if (a[i][k] + a[k][j] < a[i][j]){
                    a[i][j] = a[i][k] + a[k][j];
                    path[i][j] = path[k][j]; 
                    //缩短路径长度, 绕过 k 到 j
                }
			}
		}
	}
}

// 通过path数组求最短路径的函数
#endif
