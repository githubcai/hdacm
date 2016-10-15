/*
注意下面模版是求最小字典序解
 对于一个变量 xi 的真假，我们可以认为是存在2个物体，一个物体为 xi=0 ，一个物体为 xi=1，（显然 若我们两个物体只能取其中一个，若都不取表示xi还是个未知变量，若都取是不科学的=>无解）

我们用 mark[ i *2 ] = true or false 表示 xi = 0 这个物品取或不取如我们取了 xi=0 这个物品则 mark[i*2] = 1
用 mark[ i*2+1 ] = true or false 表示 xi = 1 这个物品取或不取，如我们取了 xi=1 这个物品则mark[i*2+1] = 1
if(mark[i*2] == 0 && mark[i*2+1] == 0){ （说明没有设置xi这个变量，则我们任意假设xi的值）
if(mark[i*2] && mark[i*2+1]) ｛说明无解｝
*/

#define N 1005*2
#define M 40000+5
//注意n是拆点后的大小 即 n <<= 1 N为点数(注意要翻倍) M为边数 i&1=0为i真 i&1=1为i假
struct Edge{
	int to, nex;
}edge[M];
//注意 N M 要修改
int head[N], edgenum;
void addedge(int u, int v){
	Edge E = {v, head[u]};
	edge[edgenum] = E;
	head[u] = edgenum ++;
}

bool mark[N];
int Stack[N], top;
void init(){
	memset(head, -1, sizeof(head)); edgenum = 0;
	memset(mark, 0, sizeof(mark));
}

bool dfs(int x){
	if(mark[x^1])return false;//一定是拆点的点先判断
	if(mark[x])return true;

	mark[x] = true;
	Stack[top++] = x;

	for(int i = head[x]; i != -1; i = edge[i].nex)
		if(!dfs(edge[i].to)) return false;

	return true;
}

bool solve(int n){
	for(int i = 0; i < n; i+=2)
		if(!mark[i] && !mark[i^1])
		{ top = 0;
			if(!dfs(i))
			{ 
				while( top ) mark[ Stack[--top] ] = false;
				if(!dfs(i^1)) return false;
			}
		}
	return true;
}

