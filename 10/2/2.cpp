#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int MAX = 50010, INF = 0x7ffffff;
struct Edge{
    int to, w, next;
};

Edge edges[MAX * 4];
int head[MAX], vis[MAX], dist[MAX], edgeNum;

void init(){
    memset(head, -1, sizeof(head));
    edgeNum = 0;
}

void addEdge(int i, int j, int w){
    Edge e = {j, w, head[i]};
    edges[edgeNum] = e;
    head[i] = edgeNum++;
}

void spfa(int s, int e){
    queue<int> que;
    for(int i = s; i <= e; ++i) dist[i] = -INF;
    memset(vis, 0, sizeof(vis));
    que.push(s);
    dist[s] = 0;
    while(!que.empty()){
        int u = que.front();
        que.pop();
        vis[u] = false;
        for(int i = head[u]; i != -1; i = edges[i].next){
            int v = edges[i].to;
            if(dist[v] < dist[u] + edges[i].w){
                dist[v] = dist[u] + edges[i].w;
                if(!vis[v]){
                    vis[v] = true;
                    que.push(v);
                }
            }
        }
    }
}

int main(){
    int n;
    while(scanf("%d", &n) == 1){
        init();
        int left = INF, right = -INF;
        for(int i = 0; i < n; ++i){
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            ++b;
            addEdge(a, b, c);
            if(a < left) left = a;
            if(b > right) right = b;
        }
        for(int i = left; i < right; ++i){
            addEdge(i, i + 1, 0);
            addEdge(i + 1, i, -1);
        }
        spfa(left, right);
        printf("%d\n", dist[right]);
    }
    return 0;
}
