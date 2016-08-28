#include <cstdio>

const int MAX = 100;
int dp[MAX], tower[MAX][MAX];;

int max(int a, int b){
    return a > b ? a : b;
}

int main(){
    int C;
    scanf("%d", &C);
    while(C-- > 0){
        int N;
        scanf("%d", &N);
        for(int i = 0; i < N; ++i){
            for(int j = 0; j <= i; ++j){
                scanf("%d", &tower[i][j]);
            }
        }
        for(int i = 0; i < N; ++i){
            dp[i] = tower[N - 1][i];
        }

        for(int i = N - 2; i >= 0; --i){
            for(int j = 0; j <= i; ++j){
                dp[j] = max(dp[j], dp[j + 1]) + tower[i][j];
            }
        }
        printf("%d\n", dp[0]);
    }
    return 0;
}
