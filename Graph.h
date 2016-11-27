#ifndef GRAPH_H
#define GRAPH_H
#include "SeqQueue.h"
#include <fstream>
const int maxWeight = 100000;
// ͼ�ĳ�����ඨ��#��Ȩ����ͼ
// TΪ��������ͣ�EΪ��Ȩֵ�����ͣ�һ��ӦΪĳһ�������͡�
template <class T, class E>
class Graph{
public:
	Graph(int sz){
		maxVertices = sz;
		numVertices = 0;
		numEdges = 0;
	}
	virtual ~Graph(){};
	bool GraphEmpty() const{				//��ͼ�շ�	
		return (numEdges == 0);
	}
	bool GraphFull() const{					//��ͼ���� 	
		return (numVertices == maxVertices || 
			numEdges == maxVertices*(maxVertices-1)/2);//����ͼ������ͼ������2
	}
	int NumberOfVertices(){				//���ص�ǰ������	
		return numVertices;
	}
	int NumberOfEdges(){					//���ص�ǰ����	
		return numEdges;
	}
	void DFS();						    //������ȱ���ͼ��������е���ͨ����
	void BFS();						    //������ȱ���ͼ��������е���ͨ����
	void Components();					//��������������������ͨͼ����ͨ�������㷨
		
	friend istream& operator>> (istream &in, Graph<T,E> &G){
		int i, j, k, n, m;
		T e1, e2;
		E weight;
		in >> n >> m;				//���붥���������
		for (i = 0; i < n; i++){	//�������붥��ֵ
			in >> e1;
			G.insertVertex(e1);
		}
		i = 0;
		while (i < m){
			assert(in >> e1 >> e2 >> weight);	//��������ߵ�������ֵ����Ȩֵ
			j = G.getVertexPos(e1);				//ȡ��Ӧ�����±�
			k = G.getVertexPos(e2);
			if (j == -1 || k == -1){			//ȡ��Ӧ���㲻����
				cout << "Input error!\n";
			}
			else{
				G.insertEdge(j, k, weight);		//�ɶ����±��Ȩֵ�����
				i++;
			}
		}
		return in;
	}friend ifstream& operator >> (ifstream &in, Graph<T, E> &G) {
		int i, j, k, n, m;
		T e1, e2;
		E weight;
		in >> n >> m;				//���붥���������
		for (i = 0; i < n; i++) {	//�������붥��ֵ
			in >> e1;
			G.insertVertex(e1);
		}
		i = 0;
		while (i < m) {
			assert(in >> e1 >> e2 >> weight);	//��������ߵ�������ֵ����Ȩֵ
			j = G.getVertexPos(e1);				//ȡ��Ӧ�����±�
			k = G.getVertexPos(e2);
			if (j == -1 || k == -1) {			//ȡ��Ӧ���㲻����
				cout << "Input error!\n";
			}
			else {
				G.insertEdge(j, k, weight);		//�ɶ����±��Ȩֵ�����
				i++;
			}
		}
		return in;
	}
	friend ostream& operator<< (ostream &out, Graph<T,E> &G){
		int i, j, n, m;
		T e1, e2;
		E weight;
		n = G.NumberOfVertices();		//�����������
		m = G.NumberOfEdges();
		out << "Number of Vertices: " << n << endl;
		out << "Number of Edges: " << m << endl;
		out << "The edges in the graph are:\n";
		for (i = 0; i < n; i++){
			for (j = i + 1; j < n; j++){
				weight = G.getWeight(i, j);
				if (weight > 0 && weight < maxWeight){
					e1 = G.getValue(i);	//���±�ȡ�ö���ֵ
					e2 = G.getValue(j);
					out << "(" << e1 << "," << e2 << "," << weight << ")" << endl;
				}
			}
		}
		return out;
	}

	// ͼ���������ʵ�ֵ�һЩ�ӿ�
	virtual T getValue(int i) = 0;							//ȡλ��Ϊi�Ķ����е�ֵ
	virtual E getWeight(int v1, int v2) = 0;				//���ر�(v1,v2)�ϵ�Ȩֵ
	virtual bool insertVertex(const T &vertex) = 0;			//��ͼ�в���һ������vertex
	virtual bool removeVertex(int v) = 0;					//��ͼ��ɾ��һ������v
	virtual bool insertEdge(int v1, int v2, E weight) = 0;	//����ȨֵΪweight�ı�(v1,v2)
	virtual bool removeEdge(int v1, int v2) = 0;			//ɾ����(v1,v2)
	virtual int getFirstNeighbor(int v) = 0;				//ȡ����v�ĵ�һ���ڽӶ���
	virtual int getNextNeighbor(int v, int w) = 0;			//ȡv���ڽӶ���w����һ�ڽӶ���
	virtual int getVertexPos(const T &vertex) = 0;			//��������vertex��ͼ�е�λ��
protected:
	int maxVertices;			//ͼ����󶥵���
	int numEdges;				//��ǰ����
	int numVertices;			//��ǰ������
	void DFS(int v, bool visited[]);					   //������ȱ���ͼ���ӹ���
	void BFS(int v, bool visited[]);
};


//������ȱ���ͼ,����ͨͼ������нڵ�
template<class T, class E> 
void Graph<T,E>::DFS(){
	int i, n = NumberOfVertices();		//ȡͼ�ж������
	bool *visited = new bool[n]; 		//������������
	for (i = 0; i < n; i++){			//��������visited��ʼ��	
		visited[i] = false;
	}
	//DFS(0,visited);					//��ͨͼ
	for(i=0;i<n;i++){					//#����ͨͼ����ÿ�����㿪ʼ������һ�α�����
		if(!visited[i]){				//#�����������飬��һ�˱����ѷ��ʹ��ĸ����㲻����Ϊ����㡣���������������ͨ�����������ظ���
			DFS(i, visited); 			//�Ӷ���0��ʼ�����������
			cout<<endl;
		}
	}
	delete [] visited;					//�ͷ�visited
}

//�Ӷ���λ��v����, ��������ȵĴ���������пɶ������δ���ʹ��Ķ��㡣
//�㷨���õ�һ����������visited, ���ѷ��ʹ��Ķ��������ʱ�ǡ�
template<class T, class E>
void Graph<T,E>::DFS(int v, bool visited[]){
	/*����д������*/

		

}

//������ȱ���ͼ��������е���ͨ����
template <class T, class E>void Graph<T,E>::BFS(){
	int i, n = NumberOfVertices();		//ͼ�ж������
	bool *visited = new bool[n];	
	for (i = 0; i < n; i++){
		visited[i] = false;
	}

	for (i = 0; i < n; i++){	//#��ÿ�����㿪ʼ������һ�α�����
		//if (visited[i] == true){//#�����������飬��һ�˱����ѷ��ʹ��ĸ����㲻����Ϊ����㡣���������������ͨ�����������ظ���
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
void Graph<T,E>::BFS(int i, bool visited[]){/*����д������*/




}

//��������������������ͨͼ����ͨ�������㷨
template<class T, class E> void Graph<T,E>::Components(){
	int i, n = NumberOfVertices();		//ȡͼ�ж������
	bool *visited = new bool[n]; 		//������������
	for (i = 0; i < n; i++){				//��������visited��ʼ��	
		visited[i] = false;
	}
	int j=1;
	for(i=0;i<n;i++){
		if(!visited[i]){
			cout << "Component " << j << ":" << endl;
			DFS(i, visited); 			//�Ӷ���0��ʼ�����������
			j++;
			cout << endl;
		}
	}
	delete [] visited;					//�ͷ�visited
}


//////////////////////////////////////////////////////////////////
//��Ȩͼ�����·��
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
	//	 cout << getValue(i) << ' ';				//���ʶ���v
		// visited[v] = true;						//���ѷ��ʱ��
		  Q.EnQueue(v);
			//���������, ʵ�ֲַ����
			while (!Q.IsEmpty()){		//ѭ��, �������н��
				Q.DeQueue(v);					//��������ı���Ʊ���i
				w =G.getFirstNeighbor(v);			//��һ���ڽӶ���
				while (w != -1){						//���ڽӶ���w����
					if (dist[w]==maxValue){				//��δ���ʹ�
						dist[w]=dist[v]+1;
						path[w]=v;
						Q.EnQueue(w);				//����w������
					    }
					w = G.getNextNeighbor(v, w);		//�Ҷ���v����һ���ڽӶ���
				}
			}//���ѭ�����ж��пշ�
			cout << endl;

	    //delete [] visited;

}

//  ���path
template <class T,class E>
void printpath(Graph<T,E> &g, int v, int path[])
{//int i=g.getvertexPos();
if(path[v]!=-1)
 printpath(g,path[v],path);

cout<<g.getValue(v)<< " ";
}

//Dijkstra
//Graph��һ����Ȩ����ͼ��
//dist[j], 0��j<n, �ǵ�ǰ�󵽵ĴӶ���v������j�����·������,
//path[j], 0��j<n, ����󵽵����·����
template <class T, class E>
void ShortestPath(Graph<T,E> &G, T v, E dist[], int path[]){
    int n = G.NumberOfVertices();
    bool *S = new bool[n]; 	   //���·�����㼯
    int i, j, k;  E w, min;
    for (i = 0; i < n; i++)	{
	    dist[i] = G.getWeight(v, i);
        S[i] = false;
        if (i != v && dist[i] < maxValue) path[i] = v;
        else path[i] = -1;
    }
    S[v] = true;  dist[v] = 0;     	//����v���붥�㼯��
   /*������������*/
}


//a[i][j]�Ƕ���i��j֮������·�����ȡ�
//path[i][j]����Ӧ·���϶���j��ǰһ����Ķ���š�
template <class T, class E>
void Floyd(Graph<T,E> &G, E **a, int **path){
	int i, j, k, n = G.NumberOfVertices();
    for (i = 0; i < n; i++){    	//����a��path��ʼ��	
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
    for (k = 0; k < n; k++){   //���ÿһ��k, ����a(k)��path(k)			
        for (i = 0; i < n; i++){
            for (j = 0; j < n; j++){
				if (a[i][k] + a[k][j] < a[i][j]){
                    a[i][j] = a[i][k] + a[k][j];
                    path[i][j] = path[k][j]; 
                    //����·������, �ƹ� k �� j
                }
			}
		}
	}
}

// ͨ��path���������·���ĺ���
#endif
