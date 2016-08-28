#include <cstdio>
#include <cstring>

const int NMAX = 30, MMAX = 3000001;
int money[NMAX], dp[MMAX];

int max(int a, int b){
    return a > b ? a : b;
}

int main(){
    float Q;
    int N;
    while(scanf("%f%d", &Q, &N) == 2 && N != 0){
        int len = 0;
        for(int i = 0; i < N; ++i){
            int m;
            scanf("%d", &m);
            bool flag = false;
            float sum = 0, temp[3] = {0};
            for(int j = 0; j < m; ++j){
                char c;
                float t;
                scanf(" %c:%f", &c, &t);
                if(!flag){
                    if((c != 'A' && c != 'B' && c != 'C') || t > 600.0) flag = true;
                    temp[c - 'A'] += t;
                    if(temp[c - 'A'] > 600.0) flag = true;
                }else{
                    continue;
                }
                sum += t;
            }
            if(sum > 1000 || flag) continue;
            money[len++] = static_cast<int>(sum * 100);
        }

        memset(dp, 0, sizeof(dp));
        int total = static_cast<int>(Q * 100);
        for(int i = 0; i < len; ++i){
            for(int j = total; j >= money[i]; --j){
                dp[j] = max(dp[j], dp[j - money[i]] + money[i]);
            }
        }
        int max = -1;
        for(int i = 1; i <= total; ++i){
            if(max < dp[i]) max = dp[i];
        }
        printf("%.2f\n", static_cast<float>(max) / 100.0);
    }
    return 0;
}
