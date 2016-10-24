#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

const int NMAX = 605, MMAX = 200000, INF = 0x3fffffff;
struct Edge{
    int to, cap, next;
};

Edge edge[MMAX];
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
    int N, M, n[200], t[200], s[200], e[200], time[400];
    while(scanf("%d%d", &N, &M) == 2){
        int sum = 0, cnt = 0;
        for(int i = 0; i < N; ++i){
            scanf("%d%d%d%d", &s[i], &n[i], &e[i], &t[i]);
            sum += t[i] * n[i];
            time[cnt++] = s[i];
            time[cnt++] = e[i];
        }
        sort(time, time + cnt);
        int temp = cnt; cnt = 0;
        for(int i = 1; i < temp; ++i){
            if(time[i] != time[cnt]){
                time[++cnt] = time[i];
            }
        }
        init();
        int st = 0, ed = 1 + cnt + N + 1;
        for(int i = 1; i <= N; ++i){
            addEdge(st, i, t[i - 1] * n[i - 1]);
        }
        for(int i = 1; i <= cnt; ++i){
            for(int j = 0; j < N; ++j){
                if(s[j] < time[i] && e[j] >= time[i]){
                    addEdge(j + 1, N + i, INF);
                }
            }
            addEdge(N + i, ed, (time[i] - time[i - 1]) * M);
        }
        int ret = Dinic(st, ed);
        if(ret == sum){
            printf("Yes\n");
        }else{
            printf("No\n");
        }
    }
    return 0;
}
