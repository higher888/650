#include "stdio.h"
#include "stdlib.h"
#include "math.h"

#define TRUE 1
#define FALSE 0

#define MAXSIZE 100    /* initial allocate memory space */
#define MAXEDGE 100
#define MAXVEX 100


typedef int Status;	/* Status is a function type */
typedef int Boolean; /* Boolean type, the value includes TRUE or FALSE */

typedef int VertexType; /* vertex type "int" */
typedef int EdgeType; /* edge type */

/* Adjvex List Type */
typedef struct
{
	VertexType vexs[MAXVEX]; /* Vertex List */
	EdgeType arc[MAXVEX][MAXVEX];/* 邻接矩阵,可看作边表 */
	int numVertexes, numEdges; /* 图中当前的顶点数和边数 */
}MGraph;

/* Edge Lists structure****************** */
typedef struct EdgeNode /* 边表结点 */
{
	int adjvex;    /* 邻接点域,存储该顶点对应的下标 */
	struct EdgeNode *next; /* 链域,指向下一个邻接点 */
}EdgeNode;

typedef struct VertexNode
{
	int in;	
	int data; 
	int record[MAXVEX];  
	EdgeNode *firstedge;   
}VertexNode, AdjList[MAXVEX];

typedef struct
{
	AdjList adjList;
	int numVertexes,numEdges; /* 图中当前顶点数和边数 */
}graphAdjList,*GraphAdjList;
/* **************************** */



/* 用到的队列结构与函数********************************** */
/* 循环队列的顺序存储结构 */
typedef struct
{
	int data[MAXSIZE];
	int front;    	/* 头指针 */
	int rear;		/* 尾指针,若队列不空,指向队列尾元素的下一个位置 */
}Queue;

/* 初始化一个空队列Q */
Status InitQueue(Queue *Q)
{
	Q->front=0;
	Q->rear=0;
	return  1;
}

/* 若队列Q为空队列,则返回TRUE,否则返回FALSE */
Status QueueEmpty(Queue Q)
{
	if(Q.front==Q.rear) /* 队列空的标志 */
		return TRUE;
	else
		return FALSE;
}

/* 若队列未满,则插入元素e为Q新的队尾元素 */
Status EnQueue(Queue *Q,int e)
{
	if ((Q->rear+1)%MAXSIZE == Q->front)	/* 队列满的判断 */
		return 0;
	Q->data[Q->rear]=e;			/* 将元素e赋值给队尾 */
	Q->rear=(Q->rear+1)%MAXSIZE;/* rear指针向后移一位置, */
								/* 若到最后则转到数组头部 */
	return  1;
}

/* 若队列不空,则删除Q中队头元素,用e返回其值 */
Status DeQueue(Queue *Q)
{
	int temp;
	if (Q->front == Q->rear)			/* 队列空的判断 */
		return 0;
	temp=Q->data[Q->front];				/* 将队头元素赋值给e */
	Q->front=(Q->front+1)%MAXSIZE;	/* front指针向后移一位置, */
									/* 若到最后则转到数组头部 */
	return  temp;
}
/* ****************************************************** */

//compute the vertexNumber

int VStr(char str[100])
{
    int str_size1;
    int str_size;
    int V_flag;

    for (str_size = 0;str[str_size]!='\0';str_size++)
            {
                str_size1 = str_size;
            }


    int VertexNumber = 0;

    for (V_flag = 2; V_flag < str_size1;V_flag++)
    {
        VertexNumber = VertexNumber + (str[V_flag]-'0') * pow(10,str_size1-V_flag-1);
    }


    return VertexNumber;
}

int ENum(char str[100])
{
    int str_size;
    int edgeNum = 0;


    for (str_size = 0;str[str_size]!='\0';str_size++)
            {
                if(str[str_size] == '<')
                    edgeNum++;
            }

    return edgeNum;
}


void CreateMGraph(MGraph *G, int Edge_num, int VertexNum, char str[100]) //str[100] is E ****
{
	int i, j,k;
	G->numEdges=Edge_num;
	G->numVertexes=VertexNum;

//	printf("%d %d\n",Edge_num,VertexNum);

	/* 读入顶点信息,建立顶点表 */
	for(i = 0;i<VertexNum;i++)
    {
        G->vexs[i]= i;
//        printf("%d\n",G->vexs[i]);
    }


	for (i = 0; i < G->numVertexes; i++)/* 初始化图 */
	{
		for ( j = 0; j < G->numVertexes; j++)
		{
			G->arc[i][j]=0;
		}
	}

	//obtain the edge info.
    int str_s1;
    int str_s;
    int E_flag;

    for (str_s = 0;str[str_s]!='\0';str_s++)
            {
                str_s1 = str_s + 1;
            }

    //establish the edges

    E_flag = 2;


    for (k = 0; k < Edge_num; k++)
    {
        int flag1 = 1;
        int flag2 = 1;
        while(str[E_flag]!= '<')
        {
            E_flag++;
        }

        while(str[E_flag+flag1]!=',')
        {
            flag1++;
        }

        while(str[E_flag+flag1+flag2]!= '>')
        {
            flag2++;
        }

        int E1,E2;
        int edge_left = 0;
        int edge_right = 0;
        for (E1 = E_flag + 1; E1 < E_flag + flag1;E1++)
        {
            edge_left = edge_left + (str[E1]-'0') * pow(10,E_flag + flag1-1-E1);
        }

        for (E2 = E_flag + flag1 + 1; E2 < E_flag + flag1 + flag2;E2++)
        {
            edge_right = edge_right + (str[E2]-'0') * pow(10,E_flag + flag1 + flag2-1-E2);
        }

        int error_flag = 0;
        if(edge_left>=VertexNum || edge_right>=VertexNum)
            {
                printf("Error: one or more vertexes do not exist");
                error_flag = 1;
                break;
            }
        if(error_flag ==1)
        {
            continue;
        }

        G->arc[edge_left][edge_right]=1;
        E_flag = E_flag+flag1+flag2;
//        printf("%d %d\n",edge_left,edge_right);
    }

    for(i = 0; i < G->numVertexes; i++)
	{
		for(j = i; j < G->numVertexes; j++)
		{
			G->arc[j][i] = G->arc[i][j];
//			printf("%d %d %d\n",i,j,G->arc[i][j]);
		}
	}
}

/* 利用邻接矩阵构建邻接表 */
void CreateALGraph(MGraph G,GraphAdjList *GL)
{
	int i,j;
	EdgeNode *e;

	*GL = (GraphAdjList)malloc(sizeof(graphAdjList));

	(*GL)->numVertexes=G.numVertexes;
	(*GL)->numEdges=G.numEdges;
	for(i= 0;i <G.numVertexes;i++) /* 读入顶点信息,建立顶点表 */
	{
		(*GL)->adjList[i].in=0;
		(*GL)->adjList[i].data=G.vexs[i];
		(*GL)->adjList[i].firstedge=NULL; 	/* 将边表置为空表 */
		for(j=0;j<MAXVEX;j++)
        {
            (*GL)->adjList[i].record[j] = -1;
        }

	}

	for(i=0;i<G.numVertexes;i++) /* 建立边表 */
	{
		for(j=0;j<G.numVertexes;j++)
		{
			if (G.arc[i][j]==1)
			{
				e=(EdgeNode *)malloc(sizeof(EdgeNode));
				e->adjvex=j;					/* 邻接序号为j */
				e->next=(*GL)->adjList[i].firstedge;	/* 将当前顶点上的指向的结点指针赋值给e */
				(*GL)->adjList[i].firstedge=e;		/* 将当前顶点的指针指向e */
				(*GL)->adjList[j].in++;
			}
		}
	}

}

Boolean visited[MAXSIZE]; /* 访问标志的数组 */

/* 邻接表的广度遍历算法 */
void BFSTraverse(GraphAdjList GL,int firstNode,int lastNode)
{
	int i,current;
//	printf("%d %d\n",firstNode,lastNode);
    EdgeNode *p;
    int error_flag1 = 0;

	Queue Q;
	for(i = 0; i < GL->numVertexes; i++)
       	visited[i] = FALSE;
    InitQueue(&Q);

    visited[firstNode]=TRUE;
//    printf("%d",GL->adjList[firstNode].data);/* 打印顶点,也可以其它操作 */



    EnQueue(&Q,firstNode);

    while(!QueueEmpty(Q))
        {
            current = DeQueue(&Q);
//            printf("%d-",current);
            p = GL->adjList[current].firstedge;	/* 找到当前顶点的边表链表头指针 */



            while(p)
            {
                   if(!visited[p->adjvex])	/* 若此顶点未被访问 */
                {
                    visited[p->adjvex]=TRUE;
//                    printf("-%d",GL->adjList[p->adjvex].data);
                    EnQueue(&Q,p->adjvex);	/* 将此顶点入队列 */

                    for(i=0;i<MAXVEX;i++)
                    {
                        if(GL->adjList[current].record[i] != -1)
                            GL->adjList[p->adjvex].record[i] = GL->adjList[current].record[i];
                        else
                        {
                            GL->adjList[p->adjvex].record[i] = current;
                            break;
                        }
                    }



                    if(GL->adjList[p->adjvex].data == lastNode)
                    {
                        printf("%d",GL->adjList[p->adjvex].record[0]);
                        for(i=1;GL->adjList[p->adjvex].record[i]!=-1;i++)
                        {
                            printf("-%d",GL->adjList[p->adjvex].record[i]);
                        }
                        printf("-%d",lastNode);

                        error_flag1 = 1;

                        break;
                    }
                }
                p = p->next;	/* 指针指向下一个邻接点 */
            }
        }
        if(error_flag1 == 0)
            {
                printf("Error: There is no path between the two nodes as given!");
            }
}


int main(int argc, char** argv)
{
	MGraph G;
	GraphAdjList GL;
	int i,j;
	int VertexNum;
	int Edge_num;

	char str[100];

    while (fgets(str,100,stdin))
    {
//        printf("%c\n",str[0]);
        if (str[0]=='V')
        {
//            printf("%c\n",str[0]);
            VertexNum = VStr(str);
        }
        else if (str[0]=='E')
        {
            Edge_num = ENum(str);
            CreateMGraph(&G, Edge_num, VertexNum, str);
        }

        else if (str[0]=='s')
        {
            int str_size1;
            int str_size;
            int s_flag;

            for (str_size = 0;str[str_size]!='\0';str_size++)
                {
                    str_size1 = str_size;
                }

            s_flag = 0;

            int flag1 = 1;

            while(str[s_flag]!= ' ')
            {
                s_flag++;
            }

            while(str[s_flag+flag1]!=' ')
            {
                flag1++;
            }

            int s1,s2;
            int firstNode = 0;
            int lastNode = 0;
            for (s1 = s_flag+1; s1 < s_flag + flag1; s1++)
            {
                firstNode = firstNode + (str[s1]-'0') * pow(10,s_flag + flag1-1-s1);
            }

            for (s2 = s_flag + flag1 + 1; s2 < str_size1;s2++)
            {
                lastNode = lastNode + (str[s2]-'0') * pow(10,str_size1-1-s2);
//                printf("%d %d %d\n",s2,str[s2]-'0',str_size1-1-s2);
            }
//            printf("%d %d\n",firstNode,lastNode);

            if(firstNode>=VertexNum || lastNode>=VertexNum)
            {
                printf("Error: one or more vertexes do not exist");
                continue;
            }


            CreateALGraph(G,&GL);
            BFSTraverse(GL,firstNode,lastNode);
        }


    }

	return 0;
}
