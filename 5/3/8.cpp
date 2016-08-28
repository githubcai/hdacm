#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int MOD = 1000000007, MAX = 100000;
int n, C[MAX + 1], S[MAX], ref[MAX];

int lowbit(int x){
    return x & (-x);
}

void update(int x, int add){
    while(x <= n){
        C[x] = (C[x] + add) % MOD;
        x += lowbit(x);
    }
}

int getSum(int x){
    int ret = 0;
    while(x > 0){
        ret = (ret + C[x]) % MOD;
        x -= lowbit(x);
    }
    return ret;
}

int main(){
    while(scanf("%d", &n) == 1){
        for(int i = 0; i < n; ++i){
            scanf("%d", &S[i]);
            ref[i] = S[i];
        }
        sort(ref, ref + n);
        int leng = unique(ref, ref + n) - ref;
        memset(C, 0, sizeof(C));
        int ans = 0;
        for(int i = 0; i < n; ++i){
            int index = lower_bound(ref, ref + leng, S[i]) - ref + 1;
            int sum = getSum(index) + 1;
            ans = (ans + sum) % MOD;
            update(index, sum);
        }
        printf("%d\n", ans);
    }
    return 0;
}
