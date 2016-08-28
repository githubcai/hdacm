#include <cstdio>
#include <cstring>

const int MAX = 10001;
int Vi[MAX], Ci[MAX], dp[MAX];

int max(int a, int b){
    return a > b ? a : b;
}

int main(){
    char ch[11];
    int N, C;
    while(scanf("%d%d", &N, &C) == 2){
        int t[11][11];
        memset(t, 0, sizeof(t));
        for(int i = 0; i < N; ++i){
            int tV, tC;
            scanf("%s%d%d", ch, &tV, &tC);
            ++t[tV][tC];
        }

        int len = 0;
        for(int i = 0; i < 11; ++i){
            for(int j = 0; j < 11; ++j){
                if(t[i][j] == 0) continue;
                for(int k = 1; k < t[i][j]; k *= 2){
                    Vi[len] = k * i;
                    Ci[len++] = k * j;
                    t[i][j] -= k;
                }
                Vi[len] = t[i][j] * i;
                Ci[len++] = t[i][j] * j;
            }
        }

        memset(dp, 0, sizeof(dp));
        for(int i = 0; i < len; ++i){
            for(int j = C; j >= Ci[i]; --j){
                dp[j] = max(dp[j], dp[j - Ci[i]] + Vi[i]);
                dp[j] = max(dp[j], dp[j - 1]);
            }
        }
        printf("%d\n", dp[C]);
    }
}
