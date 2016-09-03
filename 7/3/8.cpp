#include <cstdio>
#include <cstring>

const int MMAX = 2001, NMAX = 2001;
int dp[NMAX][MMAX];

void table(){
    memset(dp, 0, sizeof(dp));
    for(int i = 0; i < NMAX; ++i){
        dp[i][0] = 1;
    }
    for(int i = 1; i < NMAX; ++i){
        for(int j = 1; j < MMAX; ++j){
            dp[i][j] = (dp[i - 1][j] + dp[i - 1][j - 1]) % 1007;
        }
    }
}

int main(){
    int T;
    table();
    scanf("%d", &T);
    while(T-- > 0){
    int m, n;
        while(scanf("%d%d", &m, &n) == 2){
            printf("%d\n", dp[n][m]);
        }
    }
    return 0;
}
