#include <cstdio>

typedef long long LL;

LL quickMul(LL a, LL n, LL mod){
    LL ret = 1;
    while(n > 0){
        if(n & 1) ret = ret * a % mod;
        a = (a * a) % mod;
        n >>= 1;
    }
    return ret;
}

int main(){
    int T; scanf("%d", &T);
    int cnt = 0;
    while(T-- > 0){
        LL n; scanf("%lld", &n);
        LL temp = (n - 1) / 2 + 1;
        LL ans = quickMul(4, temp - 1, 30021);
        if(n % 2 != 0){
            ans = (ans + 5) / 3;
        }else{
            ans = (ans + 4) / 3 * 2;
        }
        printf("Case #%d: %lld\n", ++cnt, ans % 10007);
    }
    return 0;
}
