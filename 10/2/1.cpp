#include <cstdio>
#include <cstring>

const int NMAX = 8000 * 2, MMAX = 20000 * 2;
struct Edge{
    int to, next;
};

Edge edge[MMAX];
int head[NMAX], edgeNum, Stack[NMAX], top;
bool mark[NMAX];

void init(){
    memset(head, -1, sizeof(head));
    edgeNum = 0;
    memset(mark, 0, sizeof(mark));
}

void addEdge(int u, int v){
    Edge E = {v, head[u]};
    edge[edgeNum] = E;
    head[u] = edgeNum++;
}

bool dfs(int x){
    if(mark[x ^ 1]) return false;
    if(mark[x]) return true;
    mark[x] = true;
    Stack[top++] = x;
    for(int i = head[x]; i != -1; i = edge[i].next){
        if(!dfs(edge[i].to)) return false;
    }
    return true;
}

bool solve(int n){
    for(int i = 0; i < n; i += 2){
        if(!mark[i] && !mark[i ^ 1]){
            top = 0;
            if(!dfs(i)){
                while(top) mark[Stack[--top]] = false;
                if(!dfs(i ^ 1)) return false;
            }
        }
    }
    return true;
}

int main(){
    int m, n;
    while(scanf("%d%d", &n, &m) == 2){
        int a, b;
        init();
        n *= 2;
        for(int i = 0; i < m; ++i){
            scanf("%d%d", &a, &b);
            --a, --b;
            addEdge(a, b ^ 1);
            addEdge(b, a ^ 1);
        }
        if(solve(n)){
            for(int i = 0; i < n; ++i){
                if(mark[i]){
                    printf("%d\n", i + 1);
                }
            }
        }else{
            printf("NIE\n");
        }
    }
    return 0;
}
