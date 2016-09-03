#include <cstdio>
#include <cstring>

const int MAX = 1001;
int fac[MAX], sum[MAX], cnt;

void fen(int x){
    for(int i = 3; i * i <= x; ++i){
        if(x % i == 0){
            fac[cnt] = i;
            while(x % i == 0){
                x /= i;
                ++sum[cnt];
            }
            ++cnt;
        }
    }
    if(x > 1) fac[cnt] = x, ++sum[cnt++];
}

long long quick_mod(int a, int b, int p){
    long long ans = 1;
    while(b){
        if(b & 1) ans = ans * a % p;
        b >>= 1;
        a = a * a % p;
    }
    return ans;
}

int main(){
    int a, n;
    while(scanf("%d%d", &a, &n) == 2){
        memset(sum, 0, sizeof(sum));
        cnt = 0;
        fen(n);
        int ans = 1;
        for(int i = 0; i < cnt; ++i){
            long long tmp = quick_mod(a, (fac[i] - 1) / 2, fac[i]);
            if(tmp > 1) tmp = -1;
            if(tmp == -1 && sum[i] % 2 == 0) tmp = 1;
            ans *= tmp;
        }
        printf("%d\n", ans);
    }
    return 0;
}
