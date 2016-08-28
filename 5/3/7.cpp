#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int MOD = 1000000007, MAX = 500000;
long long C[MAX + 1], B[MAX], A[MAX], ref[MAX];

int lowbit(int x){
    return x & (-x);
}

void update(int x, long long add){
    while(x <= MAX){
        C[x] += add;
        x += lowbit(x);
    }
}

long long getSum(int x){
    long long ret = 0;
    while(x > 0){
        ret += C[x];
        ret %= MOD;
        x -= lowbit(x);
    }
    return ret;
}

int main(){
    long long N, n, m, X, Y, Z;
    int cnt = 0;
    scanf("%lld", &N);
    while(N-- > 0){
        ++cnt;
        scanf("%lld%lld%lld%lld%lld", &n, &m, &X, &Y, &Z);
        for(int i = 0; i < m; ++i){
            scanf("%lld", &A[i]);
        }
        for(int i = 0; i < n; ++i){
            ref[i] = B[i] = A[i % m]; 
            A[i % m] = (X * A[i % m] + Y * (i + 1)) % Z;
        }
        sort(ref, ref + n);
        int leng = unique(ref, ref + n) - ref;
        memset(C, 0, sizeof(C));
        long long ans = 0;
        for(int i = 0; i < n; ++i){
            int index = lower_bound(ref, ref + leng, B[i])- ref + 2;
            long long sum = getSum(index - 1) + 1;
            ans += sum;
            update(index, sum);
        }
        printf("Case #%d: %lld\n", cnt, ans % MOD);
    }
    return 0;
}
