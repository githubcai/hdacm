#include <cstdio>
#include <limits>
#include <algorithm>
using namespace std;

const int MAX = 10001, NMAX = 500, INF = (numeric_limits<int>::max)();
int dp[MAX], w[NMAX], v[NMAX];

int min(int a, int b){
    return a > b ? b : a;
}

int main(){
    int T;
    scanf("%d", &T);
    while(T-- > 0){
        int E, F;
        scanf("%d%d", &E, &F);
        int weight = F - E;
        int N;
        scanf("%d", &N);
        for(int i = 0; i < N; ++i){
            scanf("%d%d", &v[i], &w[i]);
        }
        fill(dp, dp + MAX, INF);
        dp[0] = 0;
        for(int i = 0; i < N; ++i){
            for(int j = 1; j <= weight; ++j){
                int temp = j - w[i];
                if(j - w[i] < 0 || dp[temp] == INF) continue;
                dp[j] = min(dp[j], dp[temp] + v[i]);
            }
        }
        if(dp[weight] != INF){
            printf("The minimum amount of money in the piggy-bank is %d.\n", dp[weight]);
        }else{
            printf("This is impossible.\n");
        }
    }
    return 0;
}
