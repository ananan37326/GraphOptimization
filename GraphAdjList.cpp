#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3

using namespace std;

class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
	if (length == queueMaxSize)
	{
		int * tempData ;
		//allocate new memory space for tempList
		queueMaxSize = 2 * queueMaxSize ;
		tempData = new int[queueMaxSize] ;
		int i, j;
		j = 0;
		for( i = rear; i < length ; i++ )
		{
			tempData[j++] = data[i] ; //copy items from rear
		}
		for( i = 0; i < rear ; i++ )
		{
			tempData[j++] = data[i] ; //copy items before rear
		}
		rear = 0 ;
		front = length ;
		delete[] data ; //free the memory allocated before
		data = tempData ; //make list to point to new memory
	}

	data[front] = item ; //store new item
	front = (front + 1) % queueMaxSize ;
	length++ ;
}


bool Queue::empty()
{
	if(length == 0) return true ;
	else return false ;
}


int Queue::dequeue()
{
	if(length == 0) return NULL_VALUE ;
	int item = data[rear] ;
	rear = (rear + 1) % queueMaxSize ;   // circular queue implementation
	length-- ;
	return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************

//****************Dynamic ArrayList class based************************
class ArrayList
{
	int * list;
	int length ;
	int listMaxSize ;
	int listInitSize ;
public:
	ArrayList() ;
	~ArrayList() ;
	int searchItem(int item) ;
    void insertItem(int item) ;
	void removeItem(int item) ;
	void removeItemAt(int item);
	int getItem(int position) ;
	int getLength();
	bool empty();
	void printList();
} ;


ArrayList::ArrayList()
{
	listInitSize = 2 ;
	listMaxSize = listInitSize ;
	list = new int[listMaxSize] ;
	length = 0 ;
}

void ArrayList::insertItem(int newitem)
{
	int * tempList ;
	if (length == listMaxSize)
	{
		//allocate new memory space for tempList
		listMaxSize = 2 * listMaxSize ;  // doubling memory when array is full
		tempList = new int[listMaxSize] ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
	};

	list[length] = newitem ; //store new item
	length++ ;
}

int ArrayList::searchItem(int item)
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if( list[i] == item ) return i;
	}
	return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
	if ( position < 0 || position >= length ) return ; //nothing to remove
	list[position] = list[length-1] ;
	length-- ;
}


void ArrayList::removeItem(int item)
{
	int position;
	position = searchItem(item) ;
	if ( position == NULL_VALUE ) return ; //nothing to remove
	removeItemAt(position) ;
}


int ArrayList::getItem(int position)
{
	if(position < 0 || position >= length) return NULL_VALUE ;
	return list[position] ;
}

int ArrayList::getLength()
{
	return length ;
}

bool ArrayList::empty()
{
    if(length==0)return true;
    else return false;
}

void ArrayList::printList()
{
    int i;
    for(i=0;i<length;i++)
        printf("%d ", list[i]);
  //  printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList()
{
    if(list) delete [] list;
    list = 0 ;
}

//******************ArrayList class ends here*************************

//******************Graph class starts here**************************
class Graph
{
	int nVertices, nEdges ;
	bool directed ;
	ArrayList  * adjList ;
	int *color,*parent,*dist;
	//define other variables required for bfs such as color, parent, and dist
	//you must use pointers and dynamic allocation

public:
	Graph(bool dir = false);
	~Graph();
	void setnVertices(int n);
	void addEdge(int u, int v);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getDegree(int u,bool out);
    void printAdjVertices(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
	void bfs(int source); //will run bfs in the graph

};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	adjList = 0 ;
	directed = dir ; //set direction of the graph
	//define other variables to be initialized

}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;
	if(adjList!=0) delete[] adjList ; //delete previous list
	adjList = new ArrayList[nVertices] ;
	color = new int[nVertices];
	parent = new int[nVertices];
	dist = new int[nVertices];
}

void Graph::addEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range
    this->nEdges++ ;
	adjList[u].insertItem(v) ;
	if(!directed) adjList[v].insertItem(u) ;
}

void Graph::removeEdge(int u, int v)
{
    //write this function
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range
    adjList[u].removeItem(v);
    if(!directed) adjList[v].removeItem(u);
    this->nEdges--;

}

bool Graph::isEdge(int u, int v)
{
    //returns true if (u,v) is an edge, otherwise should return false
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return false; //vertex out of range

    if(adjList[u].searchItem(v)!=NULL_VALUE)
        return true;
    else
        return false;
}

int Graph::getDegree(int u,bool out = true)
{
    //returns the degree of vertex u
    if(!directed)
        return adjList[u].getLength();
    int len = 0;
    if(out)
    {
        len += adjList[u].getLength();
    }
    else
    {
        for(int i =0;i<nVertices;i++)
        {
            if(isEdge(i,u))
                len++;
        }
    }

    return len;
}

void Graph::printAdjVertices(int u)
{
    //prints all adjacent vertices of a vertex u
    if(!directed)
        adjList[u].printList();
    else
    {
        adjList[u].printList();
        for(int i=0;i<nVertices;i++)
        {
            if(isEdge(i,u))
                printf("%d ",i);
        }
    }
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    //returns true if vertices u and v have common adjacent vertices
    for(int i=0;i<adjList[u].getLength();i++)
    {
        for(int j = 0;j<adjList[v].getLength();j++)
        {
            if(adjList[u].getItem(i)==adjList[v].getItem(j))
                return true;
        }
    }
    return false;

}

void Graph::bfs(int source)
{
    //complete this function
    //initialize BFS variables for all n vertices first
    for(int i=0;i<nVertices;i++)
    {
        color[i] = WHITE;
        parent[i] = -1;
        dist[i] = INT_MIN;
    }
    Queue b;
    b.enqueue(source);
    color[source] = GREY;
    dist[source] = 0;
    while(!b.empty())
    {
        int u = b.dequeue();
        cout << u << " - ";
        for(int i = 0;i<nVertices;i++)
        {
            int x = adjList[u].getItem(i);
            if(color[x] == WHITE)
            {
                color[x] = GREY;
                b.enqueue(x);
                parent[x] = u;
                dist[x] = dist[u] + 1;
            }
        }
        color[u] = BLACK;
    }

}

int Graph::getDist(int u, int v)
{
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
        //vertex out of range
        return INFINITY ;
    bfs(u);
    return dist[v];
}

void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<adjList[i].getLength();j++)
        {
            printf(" %d", adjList[i].getItem(j));
        }
        printf("\n");
    }
}

Graph::~Graph()
{
    //write your destructor here
    delete[] adjList;
    delete[] color;
    delete[] parent;
    delete[] dist;
}


//**********************Graph class ends here******************************


//******main function to test your code*************************
int main(void)
{
    int n;
    int choice;
    bool dir;
    printf("Enter your choice:\n");
    printf("1. directed graph   2. undirected graph\n");
    cout << "Enter your choice : ";
    scanf("%d",&choice);
    if(choice == 1)dir = true;
    else if(choice == 2)dir = false;

    Graph g(dir);
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    g.setnVertices(n);

    while(1)
    {
        printf("1. Add edge\n2. Remove edge\n3. Check if there is an edge between two vertices\n4. Check the degree of a vertex\n");
        printf("5. Print the adjacent vertices of a vertex\n6. Print Graph\n7. Check if two vertex have common adjacent vertices\n");
        printf("8. Run bfs of a vertex\n9. Get the distance between two vertices\n10. Exit\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int u, v;
            printf("Enter u and v : ");
            scanf("%d %d", &u, &v);
            g.addEdge(u, v);
            cout << endl;
            //break;
        }
        else if(ch==2)
        {
            int u, v;
            printf("Enter u and v : ");
            scanf("%d %d", &u, &v);
            g.removeEdge(u,v);
            cout << endl;
           // break;

        }
        else if(ch==3)
        {
            int u, v;
            printf("Enter u and v : ");
            scanf("%d %d", &u, &v);
            if(g.isEdge(u,v))
                cout << "There is an edge" << endl;
            else
                cout << "There is no edge" << endl;
         }
        else if(ch==4)
        {
            int u,val;
            cout << "Enter the vertex to print its degree : ";
            cin >> u;
            if(choice==1)
            {
                int o;
                cout << "Press 1 to get out degree and 2 to get in degree : ";
                cin >> o;
                if(o==1)
                    val = g.getDegree(u,true);
                else
                    val = g.getDegree(u,false);
            }
            else
                val = g.getDegree(u);
            cout << "Degree : " << val;
            cout << endl;
           // break;
        }
        else if(ch==5)
        {
            int u;
            cout << "Enter the vertex to print its adjacent vertices : ";
            cin >> u;
            cout << "Adjacent vertices - ";
            g.printAdjVertices(u);
            cout << endl;
            //break;
        }

        else if(ch==6)
        {
            g.printGraph();
            cout << endl;
            //break;
        }

        else if(ch==7)
        {
            int u,v;
            cout << "Enter the vertices : ";
            scanf("%d %d",&u,&v);
            if(g.hasCommonAdjacent(u,v))
                cout << "They have common adjacent vertices";
            else
                cout << "They do not have common adjacent vertices";
            cout << endl;
            //break;
        }

        else if(ch==8)
        {
            int u;
            cout << "Enter the source vertex : ";
            cin >> u;
            g.bfs(u);
            cout << endl;
            //break;
        }

        else if(ch==9)
        {
            int u,v;
            cout <<"Enter the two vertices : ";
            cin >> u >> v;
            cout << "Distance between them = " << g.getDist(u,v);
            cout << endl;
            //break;
        }

        else if(ch==10)
        {
           // g.~Graph();
            cout << endl;
            break;
        }
    }
    return 0;

}
