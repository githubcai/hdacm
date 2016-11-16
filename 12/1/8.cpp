#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>
using namespace std;

const int TMAX = 26, NMAX = 2000;
struct Node{
    int ac, next[TMAX];
};

struct Edge{
    int v, next;
};

int T, Na, Nb;
Node na[NMAX], nb[NMAX];
bool can[NMAX], vis[NMAX][NMAX];
Edge edge[NMAX * TMAX];
int head[NMAX];

void cut(Node *node, int *n){
    queue<int> que;
    memset(head, -1, sizeof(head));
    memset(can, 0, sizeof(can));
    int cnt = 0;
    for(int i = 0; i < *n; ++i){
        if(node[i].ac == 1) que.push(i), can[i] = true;
        for(int j = 0; j < T; ++j){
            if(node[i].next[j] == -1) continue;
            edge[cnt].v = i, edge[cnt].next = head[node[i].next[j]];
            head[node[i].next[j]] = cnt++;
        }
    }
    while(!que.empty()){
        int now = que.front();
        que.pop();
        for(int i = head[now]; i != -1; i = edge[i].next){
            if(!can[edge[i].v]){
                can[edge[i].v] = true;
                que.push(edge[i].v);
            }
        }
    }
    for(int i = 0; i < *n; ++i){
        for(int j = 0; j < T; ++j){
            if(node[i].next[j] != -1 && !can[node[i].next[j]]){
                node[i].next[j] = -1;
            }
        }
    }
}

bool bfs(){
    queue<pair<int, int>> que;
    memset(vis, 0, sizeof(vis));
    que.push(make_pair(0, 0));
    vis[0][0] = true;
    while(!que.empty()){
        pair<int, int> now = que.front();
        que.pop();
        if(na[now.first].ac != nb[now.second].ac) return false;
        for(int i = 0; i < T; ++i){
            int nx1 = na[now.first].next[i], nx2 = nb[now.second].next[i];
            if(!(nx1 + 1) != !(nx2 + 1)) return false;
            if(nx1 == -1) continue;
            if(!vis[nx1][nx2]){
                vis[nx1][nx2] = true;
                que.push(make_pair(nx1, nx2));
            }
        }
    }
    return true;
}

void readData(Node *node, int *n){
    scanf("%d", n);
    for(int i = 0; i < *n; ++i){
        scanf("%d", &node[i].ac);
        for(int j = 0; j < T; ++j){
            scanf("%d", &node[i].next[j]);
        }
    }
    cut(node, n);
}

int main(){
    int Case = 1;
    while(scanf("%d", &T) != EOF && T){
        readData(na, &Na);
        readData(nb, &Nb);
        printf("Case #%d: %s\n", Case++, bfs() ? "Yes" : "No");
    }
    return 0;
}
