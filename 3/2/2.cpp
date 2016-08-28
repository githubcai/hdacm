#include <cstdio>
#include <cstring>

const int MAX = 1000;
int dp[MAX][MAX];

int max(int x, int y){
    return x > y ? x : y;
}

int main(){
    char X[MAX], Y[MAX];
    while(scanf("%s %s", X, Y) != EOF){
        memset(dp, 0, sizeof(dp));
        int xlen, ylen;
        xlen = strlen(X);
        ylen = strlen(Y);
        for(int i = 1; i <= xlen; ++i){
            for(int j = 1; j <= ylen; ++j){
                if(X[i - 1] == Y[j - 1]){
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                }else{
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        printf("%d\n", dp[xlen][ylen]);
    }
}
