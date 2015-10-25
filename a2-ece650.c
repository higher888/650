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
	EdgeType arc[MAXVEX][MAXVEX];/* �ڽӾ���,�ɿ����߱� */
	int numVertexes, numEdges; /* ͼ�е�ǰ�Ķ������ͱ��� */
}MGraph;

/* Edge Lists structure****************** */
typedef struct EdgeNode /* �߱��� */
{
	int adjvex;    /* �ڽӵ���,�洢�ö����Ӧ���±� */
	struct EdgeNode *next; /* ����,ָ����һ���ڽӵ� */
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
	int numVertexes,numEdges; /* ͼ�е�ǰ�������ͱ��� */
}graphAdjList,*GraphAdjList;
/* **************************** */



/* �õ��Ķ��нṹ�뺯��********************************** */
/* ѭ�����е�˳��洢�ṹ */
typedef struct
{
	int data[MAXSIZE];
	int front;    	/* ͷָ�� */
	int rear;		/* βָ��,�����в���,ָ�����βԪ�ص���һ��λ�� */
}Queue;

/* ��ʼ��һ���ն���Q */
Status InitQueue(Queue *Q)
{
	Q->front=0;
	Q->rear=0;
	return  1;
}

/* ������QΪ�ն���,�򷵻�TRUE,���򷵻�FALSE */
Status QueueEmpty(Queue Q)
{
	if(Q.front==Q.rear) /* ���пյı�־ */
		return TRUE;
	else
		return FALSE;
}

/* ������δ��,�����Ԫ��eΪQ�µĶ�βԪ�� */
Status EnQueue(Queue *Q,int e)
{
	if ((Q->rear+1)%MAXSIZE == Q->front)	/* ���������ж� */
		return 0;
	Q->data[Q->rear]=e;			/* ��Ԫ��e��ֵ����β */
	Q->rear=(Q->rear+1)%MAXSIZE;/* rearָ�������һλ��, */
								/* ���������ת������ͷ�� */
	return  1;
}

/* �����в���,��ɾ��Q�ж�ͷԪ��,��e������ֵ */
Status DeQueue(Queue *Q)
{
	int temp;
	if (Q->front == Q->rear)			/* ���пյ��ж� */
		return 0;
	temp=Q->data[Q->front];				/* ����ͷԪ�ظ�ֵ��e */
	Q->front=(Q->front+1)%MAXSIZE;	/* frontָ�������һλ��, */
									/* ���������ת������ͷ�� */
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

	/* ���붥����Ϣ,��������� */
	for(i = 0;i<VertexNum;i++)
    {
        G->vexs[i]= i;
//        printf("%d\n",G->vexs[i]);
    }


	for (i = 0; i < G->numVertexes; i++)/* ��ʼ��ͼ */
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

/* �����ڽӾ��󹹽��ڽӱ� */
void CreateALGraph(MGraph G,GraphAdjList *GL)
{
	int i,j;
	EdgeNode *e;

	*GL = (GraphAdjList)malloc(sizeof(graphAdjList));

	(*GL)->numVertexes=G.numVertexes;
	(*GL)->numEdges=G.numEdges;
	for(i= 0;i <G.numVertexes;i++) /* ���붥����Ϣ,��������� */
	{
		(*GL)->adjList[i].in=0;
		(*GL)->adjList[i].data=G.vexs[i];
		(*GL)->adjList[i].firstedge=NULL; 	/* ���߱���Ϊ�ձ� */
		for(j=0;j<MAXVEX;j++)
        {
            (*GL)->adjList[i].record[j] = -1;
        }

	}

	for(i=0;i<G.numVertexes;i++) /* �����߱� */
	{
		for(j=0;j<G.numVertexes;j++)
		{
			if (G.arc[i][j]==1)
			{
				e=(EdgeNode *)malloc(sizeof(EdgeNode));
				e->adjvex=j;					/* �ڽ����Ϊj */
				e->next=(*GL)->adjList[i].firstedge;	/* ����ǰ�����ϵ�ָ��Ľ��ָ�븳ֵ��e */
				(*GL)->adjList[i].firstedge=e;		/* ����ǰ�����ָ��ָ��e */
				(*GL)->adjList[j].in++;
			}
		}
	}

}

Boolean visited[MAXSIZE]; /* ���ʱ�־������ */

/* �ڽӱ�Ĺ�ȱ����㷨 */
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
//    printf("%d",GL->adjList[firstNode].data);/* ��ӡ����,Ҳ������������ */



    EnQueue(&Q,firstNode);

    while(!QueueEmpty(Q))
        {
            current = DeQueue(&Q);
//            printf("%d-",current);
            p = GL->adjList[current].firstedge;	/* �ҵ���ǰ����ı߱�����ͷָ�� */



            while(p)
            {
                   if(!visited[p->adjvex])	/* ���˶���δ������ */
                {
                    visited[p->adjvex]=TRUE;
//                    printf("-%d",GL->adjList[p->adjvex].data);
                    EnQueue(&Q,p->adjvex);	/* ���˶�������� */

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
                p = p->next;	/* ָ��ָ����һ���ڽӵ� */
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
