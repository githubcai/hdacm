#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX = 60;
int g[MAX][MAX], dp[MAX], can[MAX][MAX], mx, verNum;

bool dfs(int pcnt, int dep){
    if(0 == pcnt){
        if(dep > mx) mx = dep;
        return true;
    }
    for(int i = 0; i < pcnt; ++i){
        int k = can[dep - 1][i], cnt = 0;
        if(dep + verNum - k <= mx) return false;
        if(dep + dp[k] <= mx) return false;
        for(int j = i + 1; j < pcnt; j++){
            int p = can[dep - 1][j];
            if(g[k][p] == 1) can[dep][cnt++] = p;
        }
        dfs(cnt, dep + 1);
    }
    return true;
}

int clique(){
    mx = 0;
    for(int i = verNum - 1; i >= 0; i--){
        int pcnt = 0;
        for(int j = i + 1; j < verNum; j++){
            if(g[i][j] == 1) can[0][pcnt++] = j;
        }
        dfs(pcnt, 1);
        dp[i] = mx;
    }
    return mx;
}

int main(){
    int n;
    while(scanf("%d", &verNum) == 1 && verNum != 0){
        for(int i = 0; i < verNum; ++i){
            for(int j = 0; j < verNum; ++j){
                scanf("%d", &g[i][j]);
            }
        }
        int ans = clique();
        printf("%d\n", ans);
    }
    return 0;
}
