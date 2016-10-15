#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
using namespace std;

const int MAX = 810, INF = 0x7fffff;
struct Edge{
    int to, next;
    double w;
};

Edge edge[2 * MAX * MAX];
int head[MAX], edgeNum, cnt[MAX], verNum;
bool vis[MAX];
double dist[MAX];

void init(){
    memset(head, -1, sizeof(head));
    edgeNum = 0;
}

void addEdge(int u, int v, double w){
    Edge e = {v, head[u], w};
    edge[edgeNum] = e;
    head[u] = edgeNum++;
}

bool spfa(int s){
    deque<int> que;
    memset(vis, 0, sizeof(vis));
    memset(cnt, 0, sizeof(cnt));
    for(int i = 0; i <= verNum; ++i) dist[i] = INF;
    que.push_back(s);
    dist[s] = 0;
    ++cnt[s];
    while(!que.empty()){
        int u = que.front();
        que.pop_front();
        vis[u] = false;
        for(int i = head[u]; i != -1; i = edge[i].next){
            int v = edge[i].to;
            if(dist[v] > dist[u] + edge[i].w){
                dist[v] = dist[u] + edge[i].w;
                if(!vis[v]){
                    ++cnt[v];
                    if(cnt[v] > verNum) return false;
                    vis[v] = true;
                    if(!que.empty()){           // SLF优化SPFA
                        if(dist[v] < dist[que.front()]){
                            que.push_front(v);
                        }else{
                            que.push_back(v);
                        }
                    }else{
                        que.push_back(v);
                    }
                }
            }
        }
    }
    return true;
}

int main(){
    int N, M, L, U;
    while(scanf("%d%d%d%d", &N, &M, &L, &U) == 4){
        init();
        for(int i = 1; i <= N; ++i){
            for(int j = 1; j <= M; ++j){
                double temp; scanf("%lf", &temp);
                addEdge(i, N + j, -log(1.0 * L / temp));
                addEdge(N + j, i, log(1.0 * U / temp));
            }
        }
        for(int i = 1; i <= N + M; ++i){
            addEdge(0, i, 0);
        }
        verNum = N + M;
        if(spfa(0)){
            printf("YES\n");
        }else{
            printf("NO\n");
        }
    }
    return 0;
}
