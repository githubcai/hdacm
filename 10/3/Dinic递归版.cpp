#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<queue>
#include<cstring>
#include<vector>
#include<set>
#include<cmath>
using namespace std;
#define inf 1073741824
#define N 500 
#define M 100100
//N为点数 M为边数

struct Edge{
	int from, to, cap, nex;
}edge[M * 2];//双向边，注意RE 注意这个模版是 相同起末点的边 同时有效而不是去重
int head[N], tot;//2个要初始化-1和0

void add(int u, int v, int cap, int rw = 0){//网络流要加反向弧，即u->v 为10 则 v->u为 -10
	Edge E = { u, v, cap, head[u] };
	edge[tot] = E;
	head[u] = tot++;

	Edge E2 = { v, u, rw, head[v] }; //如果是无向边则rw的参数值和cap相同（即 add(u,v,cap,cap) ），若是有向边则rw不写（即 add(u,v,cap); ）
	edge[tot] = E2;
	head[v] = tot++;
}

int dis[N], cur[N];//dis[i]表示i点距离起点的距离 cur[i]表示i点所连接的边中 正在考虑的边 优化不再考虑已经用过的点 初始化为head
bool vis[N];
bool BFS(int Start, int End){//跑一遍最短路
	memset(vis, 0, sizeof(vis));
	memset(dis, -1, sizeof(dis));

	queue<int>Q;
	Q.push(Start);	dis[Start] = 0;	vis[Start] = 1;

	while (!Q.empty())
	{
		int u = Q.front(); Q.pop();
		for (int i = head[u]; i != -1; i = edge[i].nex){
			Edge E = edge[i];
			if (!vis[E.to] && E.cap > 0)
			{
				vis[E.to] = true;
				dis[E.to] = dis[u] + 1;
				if (E.to == End) return true;
				Q.push(E.to);
			}
		}
	}
	return false;
}
int DFS(int x, int a, int End){//当前 流入x 的流量是a   流量a 是所有流过边中 边权的最小值
	if (x == End || a == 0)return a;
	int flow = 0, f; //flow表示从x点流到下面所有点，最大的流量
	for (int& i = cur[x]; i != -1; i = edge[i].nex)
	{
		Edge& E = edge[i];
		if (dis[x] + 1 == dis[E.to] && (f = DFS(E.to, min(a, E.cap), End))>0)
		{
			E.cap -= f;
			edge[i ^ 1].cap += f;//反向边要减掉
			flow += f;
			a -= f;
			if (a == 0)break;
		}
	}
	return flow;
}
int Dinic(int Start, int End){
	int flow = 0;
	while (BFS(Start, End)){ //当存在源点到汇点的路径时
		memcpy(cur, head, sizeof(head));//把head的数组复制过去
		flow += DFS(Start, inf, End);
	}
	return flow;
}
void init(){ memset(head, -1, sizeof head); tot = 0; }

