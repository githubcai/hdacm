#include <cstdio>
#include <cstring>

const int MAX = 1001;
int num[MAX], dp[MAX];

int main(){
    int N;
    while(scanf("%d", &N) == 1 && N != 0){
        memset(num, 0, sizeof(num));
        for(int i = 1; i <= N; ++i){
            scanf("%d", &num[i]);
        }
        memset(dp, 0, sizeof(dp));
        for(int i = 1; i <= N; ++i){
            for(int j = 0; j < i; ++j){
                if(num[i] > num[j]){
                    int temp = dp[j] + num[i];
                    if(dp[i] < temp) dp[i] = temp;
                }
            }
        }
        int max = 0;
        for(int i = 1; i <= N; ++i){
            if(max < dp[i]) max = dp[i];
        }
        printf("%d\n", max);
    }
    return 0;
}
