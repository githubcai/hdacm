#include <cstdio>
#include <cstring>

const int NMAX = 305, MMAX = 150000, INF = 0x7fffffff;
struct Edge{
    int to, vol, cost, next;
};

Edge edge[MMAX];
int head[NMAX], edgeNum, dist[NMAX], pre[NMAX], pos[NMAX], verNum, que[NMAX];
bool vis[NMAX];

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
    for(int i = 0; i <= verNum; ++i) dist[i] = INF;
    int front = 0, rear = 0;
    que[rear++] = st; pre[st] = st; dist[st] = 0;
    while(front != rear){
        int now = que[front];
        front = (front + 1) % NMAX;
        vis[now] = false;
        for(int i = head[now]; i != -1; i = edge[i].next){
            int v = edge[i].to;
            if(edge[i].vol > 0 && dist[v] > dist[now] + edge[i].cost){
                dist[v] = dist[now] + edge[i].cost;
                pre[v] = now; pos[v] = i;
                if(!vis[v]){
                    vis[v] = true;
                    if(front != rear){
                        if(dist[v] < dist[que[front]]){
                            front = (front - 1 + NMAX) % NMAX;
                            que[front] = v;
                        }else{
                            que[rear] = v;
                            rear = (rear + 1) % NMAX;
                        }
                    }else{
                        que[rear] = v;
                        rear = (rear + 1) % NMAX;
                    }
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
    int n, m, k, p;
    while(scanf("%d%d%d%d", &n, &m, &k, &p) == 4){
        int a, b, c;
        init();
        for(int i = 1; i <= n; ++i){
            scanf("%d", &a);
            addEdge(0, a, 1, 0);
            addEdge(m + i, n + m + 1, 1, 0);
        }
        for(int i = 0; i < k; ++i){
            scanf("%d%d%d", &a, &b, &c);
            addEdge(a, b, INF, c);
            addEdge(b, a, INF, c);
        }
        for(int i = 0; i < p; ++i){
            scanf("%d%d%d", &a, &b, &c);
            addEdge(b, a + m, 1, c);
        }
        verNum = n + m + 2;
        printf("%d\n", minCostFlow(0, n + m + 1, a));
    }
    return 0;
}
