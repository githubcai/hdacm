#include <cstdio>
#include <cstring>

const int MAX = 300, NMAX = 101;
int w[MAX], p[MAX], dp[NMAX];

int max(int a, int b){
    return a > b ? a : b;
}

int main(){
    int C;
    scanf("%d", &C);
    while(C-- > 0){
        int n, m;
        scanf("%d%d", &n, &m);
        int tp[m], tw[m], tc[m];
        for(int i = 0; i < m; ++i){
            scanf("%d%d%d", &tp[i], &tw[i], &tc[i]);
        }

        int mLen = 0;
        for(int i = 0; i < m; ++i){
            for(int j = 1; j < tc[i]; j *= 2){
                w[mLen] = j * tw[i];
                p[mLen++] = j * tp[i];
                tc[i] -= j;
            }
            w[mLen] = tc[i] * tw[i];
            p[mLen++] = tc[i] * tp[i];
        }
        
        memset(dp, 0, sizeof(dp));
        for(int i = 0; i < mLen; ++i){
            for(int j = n; j >= p[i]; --j){
                dp[j] = max(dp[j], dp[j - p[i]] + w[i]);
            }
        }
        printf("%d\n", dp[n]);
    }
    return 0;
}
