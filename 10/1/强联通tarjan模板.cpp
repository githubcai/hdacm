#define N 30100
//N为最大点数
#define M 150100
//M为最大边数
int n, m;//n m 为点数和边数

struct Edge{
	int from, to, nex;
	bool sign;//是否为桥
}edge[M<<1];
int head[N], edgenum;
void add(int u, int v){//边的起点和终点
	Edge E={u, v, head[u], false};
	edge[edgenum] = E;
	head[u] = edgenum++;
}

int DFN[N], Low[N], Stack[N], top, Time; //Low[u]是点集{u点及以u点为根的子树} 中(所有反向弧)能指向的(离根最近的祖先v) 的DFN[v]值(即v点时间戳)
int taj;//连通分支标号，从1开始
int Belong[N];//Belong[i] 表示i点属于的连通分支
bool Instack[N];
vector<int> bcc[N]; //标号从1开始

void tarjan(int u ,int fa){  
	DFN[u] = Low[u] = ++ Time ;  
	Stack[top ++ ] = u ;  
	Instack[u] = 1 ;  

	for (int i = head[u] ; ~i ; i = edge[i].nex ){  
		int v = edge[i].to ;  
		if(DFN[v] == -1)
		{  
			tarjan(v , u) ;  
			Low[u] = min(Low[u] ,Low[v]) ;
			if(DFN[u] < Low[v])
			{
				edge[i].sign = 1;//为割桥
			}
		}  
		else if(Instack[v]) Low[u] = min(Low[u] ,DFN[v]) ; 		
	}  
	if(Low[u] == DFN[u]){  
		int now;
		taj ++ ; bcc[taj].clear();
		do{
			now = Stack[-- top] ;  
			Instack[now] = 0 ; 
			Belong [now] = taj ;
			bcc[taj].push_back(now);
		}while(now != u) ;
	}
}

void tarjan_init(int all){
	memset(DFN, -1, sizeof(DFN));
	memset(Instack, 0, sizeof(Instack));
	top = Time = taj = 0;
	for(int i=1;i<=all;i++)if(DFN[i]==-1 )tarjan(i, i); //注意开始点标！！！
}
vector<int>G[N];
int du[N];
void suodian(){
	memset(du, 0, sizeof(du));
	for(int i = 1; i <= taj; i++)G[i].clear();
	for(int i = 0; i < edgenum; i++){
		int u = Belong[edge[i].from], v = Belong[edge[i].to];
		if(u!=v)G[u].push_back(v), du[v]++;
	}
}
void init(){memset(head, -1, sizeof(head)); edgenum=0;}
