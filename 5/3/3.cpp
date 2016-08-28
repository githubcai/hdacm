#include <cstdio>
#include <cmath>

const int MAX = 200001;
int maxNum[MAX][20];

int max(int a, int b){
    return a > b ? a : b;
}

int RMQ(int num){
    for(int j = 1; j < 20; ++j){
        for(int i = 1; i <= num; ++i){
            if(i + (1 << j) - 1 <= num){
                maxNum[i][j] = max(maxNum[i][j - 1], maxNum[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
}

int main(){
    int n, k;
    while(scanf("%d %d", &n, &k) == 2 & !(n == -1 && k == -1)){
        int sum = 0, ma = -1;
        for(int i = 1; i <= n; ++i){
            scanf("%d", &maxNum[i][0]);
            sum += maxNum[i][0];
            if(ma < maxNum[i][0]) ma = maxNum[i][0];
        }
        if(sum <= k){
            printf("-1\n");
            continue;
        }
        if(ma > k){
            printf("1\n");
            continue;
        }

        RMQ(n);
        int left = 1, right = n;
        while(right - left > 1){
            int m = (left + right) / 2;
            int num = n / m;
            int t = (int)(log(num) / log(2.0));
            sum = 0;
            for(int i = 1, j = 1; j <= m; i += num, ++j){
                sum += max(maxNum[i][t], maxNum[i + num - (1 << t)][t]);
            }
            if(sum <= k){
                left = m;
            }else{
                right = m;
            }
        }
        printf("%d\n", right);
    }
    return 0;
}
