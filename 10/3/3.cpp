#include <cstdio>
#include <cstring>

const int MAX = 720005, INF = 0x7fffffff;
struct Edge{
    int to, vol, cost, next;
};
Edge edge[MAX << 2];
int head[MAX], edgeNum, dist[MAX], pre[MAX], pos[MAX], verNum, que[MAX];
bool vis[MAX];
int mat[600][600];

void init(){
    memset(head, -1, sizeof(head));
    edgeNum = 0;
}

void addEdge(int u, int v, int vol, int cost){
    edge[edgeNum].to = v; edge[edgeNum].vol = vol;
    edge[edgeNum].cost = cost; edge[edgeNum].next = head[u];
    head[u] = edgeNum++;
    edge[edgeNum].to = u; edge[edgeNum].vol = 0;
    edge[edgeNum].cost = -cost; edge[edgeNum].next = head[v];
    head[v] = edgeNum++;
}

bool spfa(int st, int ed){
    memset(pre, -1, sizeof(pre));
    memset(vis, 0, sizeof(vis));
    for(int i = 0; i <= verNum; ++i) dist[i]= INF;
    int front = 0, rear = 0;
    que[rear++] = st; pre[st] = st; dist[st] = 0;
    while(front != rear){
        int now = que[front];
        front = (front + 1) % MAX;
        vis[now] = false;
        for(int i = head[now]; i != -1; i = edge[i].next){
            int v = edge[i].to;
            if(edge[i].vol > 0 && dist[v] > dist[now] + edge[i].cost){
                dist[v] = dist[now] + edge[i].cost;
                pre[v] = now; pos[v] = i;
                if(!vis[v]){
                    vis[v] = true;
                    que[rear] = v;
                    rear = (rear + 1) % MAX;
                }
            }
        }
    }
    return pre[ed] != -1;
}

int minCostFlow(int st, int ed, int &flow){
    int cost = 0; flow = 0;
    while(spfa(st, ed)){
        int f = INF;
        for(int i = ed; i != st; i = pre[i]){
            if(edge[pos[i]].vol < f) f = edge[pos[i]].vol;
        }
        flow += f; cost += dist[ed] * f;
        for(int i = ed; i != st; i = pre[i]){
            edge[pos[i]].vol -= f;
            edge[pos[i] ^ 1].vol += f;
        }
    }
    return cost;
}

int main(){
    int n;
    while(scanf("%d", &n) == 1){
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j){
                scanf("%d", &mat[i][j]);
            }
        }
        init();
        int cnt = 1, total = n * n;
        for(int i = 0, cnt = 1; i < n; ++i){
            for(int j = 0; j < n; ++j){
                if((i == 0 && j == 0) || (i == n - 1 && j == n - 1)){
                    addEdge(cnt, cnt + total, 2, -mat[i][j]);
                }else{
                    addEdge(cnt, cnt + total, 1, -mat[i][j]);
                }
                if(j + 1 < n){
                    addEdge(cnt + total, cnt + 1, 1, 0);
                }
                if(i + 1 < n){
                    addEdge(cnt + total, cnt + n, 1, 0);
                }
                ++cnt;
            }
        }
        addEdge(0, 1, 2, 0);
        addEdge(2 * total, 2 * total + 1, 2, 0);
        int flow;
        verNum = 2 * total + 1;
        int result = -minCostFlow(0, 2 * total + 1, flow) - mat[0][0] - mat[n - 1][n - 1];
        printf("%d\n", result);
    }
    return 0;
}
