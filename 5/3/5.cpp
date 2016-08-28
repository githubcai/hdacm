#include <cstdio>
#include <cstring>

const int MAX = 100000;
long long C[2][MAX + 1]; 

int lowbit(int x){
    return x & (-x);
}

void update(int i, int x, int add){
    while(x <= MAX){
        C[i][x] += add;
        x += lowbit(x);
    }
}

long long getSum(int i, int x){
    long long ret = 0;
    while(x > 0){
        ret += C[i][x];
        x -= lowbit(x);
    }
    return ret;
}

int main(){
    int n;
    long long ans;
    while(scanf("%d", &n) == 1){
        ans = 0;
        memset(C, 0, sizeof(C));
        for(int i = 0; i < n; ++i){
            int x;
            scanf("%d", &x);
            long long temp1 = getSum(0, MAX) - getSum(0, x);
            long long temp2 = getSum(1, MAX) - getSum(1, x);
            ans += temp1 * x + temp2;
            update(0, x, 1);
            update(1, x, x);
        }
        printf("%lld\n", ans);
    }
    return 0;
}
