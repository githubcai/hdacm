#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

const int INF = 0x7fffffff, NMAX = 2510, MMAX = 3 * NMAX;
struct Edge{
    int to, cap, next;
};

Edge edge[MMAX * 2];
int head[NMAX], dist[NMAX], edgeNum;
bool vis[NMAX];
int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

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
    memset(vis, 0, sizeof(vis));
    memset(dist, -1, sizeof(dist));
    que.push(st); dist[st] = 0; vis[st] = true;
    while(!que.empty()){
        int u = que.front(); que.pop();
        for(int i = head[u]; i != -1; i = edge[i].next){
            Edge E = edge[i];
            if(!vis[E.to] && E.cap > 0){
                vis[E.to] = true;
                dist[E.to] = dist[u] + 1;
                if(E.to == ed) return true;
                que.push(E.to);
            }
        }
    }
    return false;
}

int dfs(int x, int a, int ed){
    if(a == 0 || x == ed) return a;
    int flow = 0, f;
    for(int i = head[x]; i != -1; i = edge[i].next){
        Edge &E = edge[i];
        if(dist[x] + 1 == dist[E.to] && (f = dfs(E.to, min(a, E.cap), ed)) > 0){
            E.cap -= f;
            edge[i ^ 1].cap += f;
            flow += f;
            a -= f;
            if(a == 0) break;
        }
    }
    return flow;
}

int Dinic(int st, int ed){
    int flow = 0;
    while(bfs(st, ed)){
        flow += dfs(st, INF, ed);
    }
    return flow;
}

int main(){
    int m, n;
    while(scanf("%d%d", &m, &n) == 2){
        init();
        int src = m * n, des = m * n + 1, sum = 0;
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                int val; scanf("%d", &val);
                sum += val;
                if((i + j) % 2 == 0){
                    addEdge(src, i * n + j, val);
                    for(int k = 0; k < 4; ++k){
                        int x = i + dir[k][0], y = j + dir[k][1];
                        if(x >= 0 && x < m && y >= 0 && y < n){
                            addEdge(i * n + j, x * n + y, INF);
                        }
                    }
                }else{
                    addEdge(i * n + j, des, val);
                }
            }
        }
        int result = Dinic(src, des);
        printf("%d\n", sum - result);
    }
    return 0;
}
