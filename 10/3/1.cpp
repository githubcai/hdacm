#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

const int INF = 0x7ffffff, MMAX = 205, NMAX = 205;
struct Edge{
    int to, cap, next;
};

Edge edge[MMAX * 2];
int head[NMAX], cur[NMAX], dist[NMAX], edgeNum;

void init(){
    memset(head, -1, sizeof(head));
    edgeNum = 0;
}

void addEdge(int u, int v, int cap, int rw = 0){
    Edge E1 = {v, cap, head[u]};
    edge[edgeNum] = E1;
    head[u] = edgeNum++;
    Edge E2 = {u, rw, head[v]};
    edge[edgeNum] = E2;
    head[v] = edgeNum++;
}

bool bfs(int st, int ed){
    queue<int> que;
    memset(dist, -1, sizeof(dist));
    que.push(st); dist[st] = 0;
    while(!que.empty()){
        int u = que.front(); que.pop();
        for(int i = head[u]; i != -1; i = edge[i].next){
            Edge E = edge[i];
            if(dist[E.to] < 0 && E.cap){
                dist[E.to] = dist[u] + 1;
                if(E.to == ed) return true;
                que.push(E.to);
            }
        }
    }
    return false;
}

int dfs(int x, int a, int ed){
    if(x == ed) return a;
    int f;
    for(int &i = cur[x]; i != -1; i = edge[i].next){
        Edge &E = edge[i];
        if(E.cap > 0 && dist[x] + 1 == dist[E.to] && (f = dfs(E.to, min(a, E.cap), ed)) > 0){
            E.cap -= f;
            edge[i ^ 1].cap += f;
            return f;
        }
    }
    return 0;
}

int Dinic(int st, int ed){
    int flow = 0;
    while(bfs(st, ed)){
        memcpy(cur, head, sizeof(head));
        int temp;
        while(temp = dfs(st, INF, ed)) flow += temp;
    }
    return flow;
}

int main(){
    int M, N;
    while(scanf("%d%d", &M, &N) == 2){
        int s, e, c;
        init();
        for(int i = 0; i < M; ++i){
            scanf("%d%d%d", &s, &e, &c);
            addEdge(s, e, c);
        }
        printf("%d\n", Dinic(1, N));
    }
    return 0;
}
