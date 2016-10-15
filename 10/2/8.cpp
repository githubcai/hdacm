#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int MAX = 1000, INF = 0x7fffff;
struct Edge{
    int to, w, next;
};

Edge edge[MAX * MAX / 2];
int time[MAX], head[MAX], edgeNum, dist[MAX], cnt[MAX];
bool vis[MAX];

void init(){
    memset(head, -1, sizeof(head));
    edgeNum = 0;
}

void addEdge(int u, int v, int w){
    Edge e = {v, w, head[u]};
    edge[edgeNum] = e;
    head[u] = edgeNum++;
}

bool spfa(int s, int verNum){
    queue<int> que;
    memset(vis, 0, sizeof(vis));
    memset(cnt, 0, sizeof(cnt));
    for(int i = 0;  i <= verNum; ++i) dist[i] = -INF;
    que.push(s);
    dist[s] = 0;
    ++cnt[s];
    while(!que.empty()){
        int u = que.front();
        que.pop();
        vis[u] = false;
        for(int i = head[u]; i != -1; i = edge[i].next){
            int v = edge[i].to;
            if(dist[v] < dist[u] + edge[i].w){
                dist[v] = dist[u] + edge[i].w;
                if(!vis[v]){
                    ++cnt[v];
                    if(cnt[v] > verNum) return false;
                    vis[v] = true;
                    que.push(v);
                }            
            }
        }
    }
    return true;
}

int main(){
    int N, cnt = 1;
    while(scanf("%d", &N) == 1 && N != 0){
        for(int i = 1; i <= N; ++i){
            scanf("%d", &time[i]);
        }
        char comm[4];
        init();
        while(true){
            scanf("%s", comm);
            if(comm[0] == '#') break;
            int a, b; scanf("%d%d", &a, &b);
            if(comm[0] == 'F'){
                if(comm[2] == 'F'){
                    addEdge(b, a, time[b] - time[a]);
                }else{
                    addEdge(b, a, -time[a]);
                }
            }else{
                if(comm[2] == 'F'){
                    addEdge(b, a, time[b]);
                }else{
                    addEdge(b, a, 0);
                }
            }
        }
        printf("Case %d:\n", cnt++);
        for(int i = 1; i <= N; ++i){
            addEdge(0, i, 0);
        }
        if(spfa(0, N)){
            for(int i = 1; i <= N; ++i){
                printf("%d %d\n", i, dist[i]);
            }
        }else{
            printf("impossible\n");
        }
        printf("\n");
    }
    return 0;
}
