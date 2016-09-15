#include <cstdio>
#include <cstring>

const int MAX = 101;
int dp[MAX][MAX], a[MAX], b[MAX];

int max(const int &a, const int &b){
    return a > b ? a : b;
}

int main(){
    int n, m, k, s;
    while(scanf("%d%d%d%d", &n, &m, &k, &s) != EOF){
        memset(dp, 0, sizeof(dp));
        for(int i = 0; i < k; ++i){
            scanf("%d%d", &a[i], &b[i]);
        }
        for(int i = 0; i < k; ++i){
            for(int j = 1; j <= s; ++j){
                for(int z = b[i]; z <= m; ++z){
                    dp[j][z] = max(dp[j][z], dp[j - 1][z - b[i]] + a[i]);
                }
            }
        }
        int i;
        bool flag = false;
        for(i = 1; i <= m; ++i){
            for(int j = 1; j <= s; ++j){
                if(dp[j][i] >= n){
                    flag = true;
                    break;
                }
            }
            if(flag) break;
        }
        printf("%d\n", m - i);
    }
    return 0;
}
