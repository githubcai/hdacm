#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

const int NMAX = 105, MMAX = 22000, INF = 0x7ffffff;
struct Edge{
    int to, cap, next;
};

bool relation[NMAX][NMAX];
int father[NMAX];
Edge edge[MMAX];
int head[NMAX * 2], dist[NMAX * 2], edgeNum;
bool vis[NMAX * 2];

int find(int x){
    if(x == father[x]) return x;
    father[x] = find(father[x]);
    return father[x];
}

void merge(int a, int b){
    int ar= find(a), br = find(b);
    if(ar != br){
        father[ar] = br;
    }
}

void init(){
    memset(head, -1, sizeof(head));
    edgeNum = 0;
}

void addEdge(int u , int v, int cap, int rw = 0){
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

void buildMap(int mid, int n){
    init();
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= n; ++j){
            if(relation[i][j]){
                addEdge(i, j + n, 1);
            }
        }
    }
    int temp = 2 * n + 1;
    for(int i = 1; i <= n; ++i){
        addEdge(0, i, mid);
        addEdge(i + n, temp, mid);
    }
}

int main(){
    int T; scanf("%d", &T);
    while(T-- > 0){
        int n, m, f;
        scanf("%d%d%d", &n, &m, &f);
        memset(relation, 0, sizeof(relation));
        for(int i = 0; i < m; ++i){
            int a, b; scanf("%d%d", &a, &b);
            relation[a][b] = true;
        }
        for(int i = 0; i <= n; ++i){
            father[i] = i;
        }
        for(int i = 0; i < f; ++i){
            int a, b; scanf("%d%d", &a, &b);
            merge(a, b);
        }
        for(int i = 1; i <= n; ++i){
            for(int j = i + 1; j <= n; ++j){
                if(find(i) == find(j)){
                    for(int k = 1; k <= n; ++k){
                        if(relation[i][k] ^ relation[j][k]){
                            relation[i][k] = relation[j][k] = true;
                        }
                    }
                }
            }
        }
        int left = 0, right = n;
        int ed = 2 * n + 1, ans = 0;
        while(left <= right){
            int mid = (left + right) / 2;
            buildMap(mid, n);
            if(Dinic(0, ed) == mid * n){
                ans = mid;
                left = mid + 1;
            }else{
                right = mid - 1;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
