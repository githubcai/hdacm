#include <cstdio>
#include <cstring>

const int CMAX = 1100, MMAX = 100001;
int coins[CMAX], dp[MMAX];

int main(){
    int n, m;
    while(scanf("%d%d", &n, &m) == 2 && (n != 0 || m != 0)){
        int A[n], C[n];
        for(int i = 0; i < n; ++i){
            scanf("%d", &A[i]);
        }
        for(int i = 0; i < n; ++i){
            scanf("%d", &C[i]);
        }
        int clen = 0;
        for(int i = 0; i < n; ++i){
            for(int k = 1; k < C[i]; k *= 2){
                coins[clen++] = A[i] * k;
                C[i] -= k;
            }
            coins[clen++] = A[i] * C[i];
        }
        
        memset(dp, 0, sizeof(dp));
        dp[0] = 1;
        for(int i = 0; i < clen; ++i){
            for(int j = m; j >= coins[i]; --j){
                if(dp[j] == 1 || dp[j - coins[i]] != 1) continue;
                dp[j] = 1;
            }
        }
        int max = 0;
        for(int i = 1; i <= m; ++i){
            if(dp[i] == 1) ++max;
        }
        printf("%d\n", max);
    }
    return 0;
}
