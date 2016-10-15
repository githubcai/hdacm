#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int MAX = 105, INF = 0x7fffff;
struct Edge{
    int to, w, next;
};
Edge edges[MAX * 4];
int head[MAX], dist[MAX], edgeNum, cnt[MAX], verNum;
bool vis[MAX];

void init(){
    memset(head, -1, sizeof(head));
    edgeNum = 0;
}

void addEdge(int u, int v, int w){
    Edge e = {v, w, head[u]};
    edges[edgeNum] = e;
    head[u] = edgeNum++;
}

bool spfa(int s){
    queue<int> que;
    memset(vis, 0, sizeof(vis));
    memset(cnt, 0, sizeof(cnt));
    for(int i = 0; i <= verNum; ++i){
        dist[i] = INF;
    }
    que.push(s);
    dist[s] = 0;
    ++cnt[s];
    while(!que.empty()){
        int u = que.front();
        que.pop();
        vis[u] = false;
        for(int i = head[u]; i != -1; i = edges[i].next){
            int v = edges[i].to;
            if(dist[v] > dist[u] + edges[i].w){
                dist[v] = dist[u] + edges[i].w;
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
    int m;
    while(scanf("%d%d", &verNum, &m) == 2 && verNum != 0){
        ++verNum; init();
        int si, ni, ki; char oi[3];
        for(int i = 0; i < m; ++i){
            scanf("%d%d%s%d", &si, &ni, oi, &ki);
            if(oi[0] == 'g'){
                addEdge(si + ni, si - 1, -ki - 1);
            }else{
                addEdge(si - 1, si + ni, ki - 1);
            }
        }
        for(int i = 0; i < verNum; ++i){
            addEdge(verNum, i, 0);
        }
        if(spfa(verNum)){
            printf("lamentable kingdom\n");
        }else{
            printf("successful conspiracy\n");
        }
    }
    return 0;
}
