#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int NMAX = 1000100, MMAX = 3003000, INF = 0x7ffffff;
struct Edge{
    int to, w, next;
};

Edge edge[MMAX];
int head[NMAX], dist[NMAX], edgeNum, verNum;
bool vis[NMAX];

void init(){
    memset(head, -1, sizeof(head));
    edgeNum = 0;
}

void addEdge(int u, int v, int w){
    edge[edgeNum].to = v; edge[edgeNum].w = w; edge[edgeNum].next = head[u]; head[u] = edgeNum; edgeNum++;
    edge[edgeNum].to = u; edge[edgeNum].w = w; edge[edgeNum].next = head[v]; head[v] = edgeNum; edgeNum++;
}

void spfa(int s){
    deque<int> que;
    for(int i = 0; i <= verNum; ++i) dist[i] = INF;
    memset(vis, 0, sizeof(vis));
    que.push_back(s);
    dist[s] = 0;
    while(!que.empty()){
        int u = que.front();
        que.pop_front();
        vis[u] = false;
        for(int i = head[u]; i != -1; i = edge[i].next){
            int v = edge[i].to;
            if(dist[v] > dist[u] + edge[i].w){
                dist[v] = dist[u] + edge[i].w;
                if(!vis[v]){
                    vis[v] = true;
                    if(!que.empty()){
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
}

void buildMap(int N, int M){
    int temp;
    for(int i = 1; i <= M; ++i){
        scanf("%d", &temp);
        addEdge(0, i, temp);
    }
    for(int i = 1; i < N; ++i){
        for(int j = 1; j <= M; ++j){
            scanf("%d", &temp);
            addEdge((2 * i - 1) * M + j, 2 * i * M + j, temp);
        }
    }
    for(int i = 1; i <= M; ++i){
        scanf("%d", &temp);
        addEdge((2 * N - 1) * M + i, verNum, temp);
    }

    for(int i = 0; i < N; ++i){
        scanf("%d", &temp);
        addEdge(verNum, 2 * (N + i) * M + 1, temp);
        for(int j = 1; j < M; ++j){
            scanf("%d", &temp);
            addEdge(2 * (N + i) * M + 2 * j, 2 * (N + i) * M + 2 * j + 1, temp);
        }
        scanf("%d", &temp);
        addEdge(0, 2 * (N + i) * M + 2 * M, temp);
    }

    for(int i = 0; i < 2 * N; ++i){
        for(int j = 1; j <= M; ++j){
            scanf("%d", &temp);
            addEdge(i * M + j, 2 * (N + i / 2) * M + 2 * j - 1, temp);
            scanf("%d", &temp);
            addEdge(i * M + j, 2 * (N + i / 2) * M + 2 * j, temp);
        }
    }
}

int main(){
    int N, M;
    while(scanf("%d%d", &N, &M) == 2){
        init();
        verNum = 4 * N * M + 1;
        buildMap(N, M);
        spfa(0);
        printf("%d\n", dist[verNum]);
    }
    return 0;
}
