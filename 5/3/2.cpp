#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

const int NMAX = 10005, QMAX = 1000005;

struct Node{
    int v, o, next;
};

Node vect[NMAX * 2], query[QMAX * 2];
int vcnt, qcnt, dis[NMAX], ans[QMAX], father[NMAX], n, m, q, vis[NMAX], vhead[NMAX], qhead[NMAX];

void init(){
    memset(vis, 0, sizeof(vis));
    memset(dis, 0, sizeof(dis));
    memset(ans, 0, sizeof(ans));
    memset(vhead, -1, sizeof(vhead));
    memset(qhead, -1, sizeof(qhead));
    for(int i = 1; i <= n; ++i){
        father[i] = i;
    }
    vcnt = qcnt = 0;
}

void addEdge(int a, int b, int w){
    vect[vcnt].v = b;
    vect[vcnt].o = w;
    vect[vcnt].next = vhead[a];
    vhead[a] = vcnt++;
}

void addQuery(int a, int b, int id){
    query[qcnt].v = b;
    query[qcnt].o = id;
    query[qcnt].next = qhead[a];
    qhead[a] = qcnt++;
}

int find(int x){
    if(x == father[x]) return x;
    int temp = father[x];
    father[x] = find(father[x]);
    return father[x];
}

void tarjan(int u, int root){
    int temp = vhead[u];
    vis[u] = root;
    while(temp != -1){
        if(!vis[vect[temp].v]){
            dis[vect[temp].v] = dis[u] + vect[temp].o;
            tarjan(vect[temp].v, root);
            father[vect[temp].v] = u;
        }
        temp = vect[temp].next;
    }
    temp = qhead[u];
    while(temp != -1){
        if(vis[query[temp].v]){
            if(vis[query[temp].v] != root){
                ans[query[temp].o] = -1;
            }else{
                ans[query[temp].o] = dis[query[temp].v] + dis[u] - 2 * dis[find(query[temp].v)];
            }
        }
        temp = query[temp].next;
    }
}

int main(){
    while(scanf("%d %d %d", &n, &m, &q) == 3){
        init();
        for(int i = 0; i < m; ++i){
            int a, b, w;
            scanf("%d %d %d", &a, &b, &w);
            addEdge(a, b, w);
            addEdge(b, a, w);
        }
        for(int i = 0; i < q; ++i){
            int a, b;
            scanf("%d %d", &a, &b);
            addQuery(a, b, i);
            addQuery(b, a, i);
        }
        for(int i = 1; i <= n; ++i){
            if(!vis[i]){
                tarjan(i, i);
            }
        }
        for(int i = 0; i < q; ++i){
            if(ans[i] != -1){
                printf("%d\n", ans[i]);
            }else{
                printf("Not connected\n");
            }
        }
    }
    return 0;
}
