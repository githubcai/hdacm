#include <cstdio>
#include <cstring>

const int MAX = 1000;
int p[MAX], dp[MAX];

int max(int a, int b){
    return a > b ? a : b;
}

int main(){
    int n, m;
    while(scanf("%d", &n) == 1 && n != 0){
        int ti = -1, tm = -1;
        for(int i = 0; i < n; ++i){
            scanf("%d", &p[i]);
            if(tm < p[i]){
                tm = p[i];
                ti = i;
            }
        }
        p[ti] = p[n - 1], p[n - 1] = tm;
        scanf("%d", &m);
        
        if(m < 5){
            printf("%d\n", m);
            continue;
        }

        memset(dp, 0, sizeof(dp));
        for(int i = 0; i < n - 1; ++i){
            for(int j = m - 5; j >= p[i]; --j){
                dp[j] = max(dp[j], dp[j - p[i]] + p[i]);
            }
        }
        printf("%d\n", m - dp[m - 5] - p[n - 1]);
    }
    return 0;
}
