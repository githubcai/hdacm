#include <cstdio>
#include <cstring>

const int MMAX = 10001, NMAX = 100;
int Mj[NMAX];
float Pj[NMAX], dp[MMAX];

float max(float a, float b){
    return a > b ? a : b;
}

int main(){
    int T;
    scanf("%d", &T);
    while(T-- > 0){
        int N;
        float P;
        scanf("%f%d", &P, &N);
        P = 1 - P;

        int total = 0;
        for(int i = 0; i < N; ++i){
            scanf("%d%f", &Mj[i], &Pj[i]);
            total += Mj[i];
            Pj[i] = 1 - Pj[i];
        }
        
        memset(dp, 0, sizeof(dp));
        dp[0] = 1;
        for(int i = 0; i < N; ++i){
            for(int j = total; j >= Mj[i]; --j){
                dp[j] = max(dp[j], dp[j - Mj[i]] * Pj[i]);
            }
        }
        for(int i = total; i >= 0; --i){
            if(dp[i] >= P){
                printf("%d\n", i);
                break;
            }
        }
    }
    return 0;
}
