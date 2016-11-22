#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAX = 500000, INF = 0x7ffffff;
struct Edge{
    int to, w, next;
};

int head[MAX], dp[MAX], d[MAX], n, L, R, cnt;
Edge edge[MAX];

void dfs(int r, bool boy){
    if(d[r] > R){
        dp[r] = 0;
        return;
    }
    bool flag = true;
    dp[r] = (boy ? -1 : INF);
    for(int i = head[r]; i != -1; i = edge[i].next){
        flag = false;
        int v = edge[i].to;
        d[v] = d[r] + edge[i].w;
        dfs(v, !boy);
        if(dp[v] == -1 || dp[v] == INF) continue;
        int temp = d[r] + dp[v] + edge[i].w;
        if(temp >= L && temp <= R){
            if(boy){
                dp[r] = max(dp[r], dp[v] + edge[i].w);
            }else{
                dp[r] = min(dp[r], dp[v] + edge[i].w);
            }
        }
    }
    if(flag) dp[r] = 0;
}

int main(){
    while(scanf("%d%d%d", &n, &L, &R) != EOF){
        memset(head, -1, sizeof(head));
        cnt = 0;
        for(int i = 1; i < n; ++i){
            int from, to, w;
            scanf("%d%d%d", &from, &to, &w);
            edge[cnt].to = to, edge[cnt].w = w, edge[cnt].next = head[from];
            head[from] = cnt++;
        }
        d[0] = 0;
        dfs(0, true);
        if(dp[0] >= L && dp[0] <= R){
            printf("%d\n", dp[0]);
        }else{
            printf("Oh,my god!\n");
        }
    }
    return 0;
}
