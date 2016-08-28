#include <cstdio>

const int MAX = 10000001, MOD = 1000000007;
int N, M, pre[MAX], total;

void init(){
    for(int i = 0; i <= N; ++i){
        pre[i] = i;
    }
    total = N;
}

int find(int x){
    if(x == pre[x]) return x;
    int temp = pre[x];
    pre[x] = find(pre[x]);
    return pre[x];
}

void merge(int a, int b){
    int ar, br;
    ar = find(a), br = find(b);
    if(ar != br){
        pre[ar] = br;
        --total;
    }
}

void power(){
    long long a = 26, result = 1;
    while(total > 0){
        if(total % 2 == 1){
            result = result * a % MOD;
        }
        a = a * a % MOD;
        total /= 2;
    }
    printf("%lld\n", result);
}

int main(){
    while(scanf("%d%d", &N, &M) == 2){
        init();
        for(int i = 0; i < M; ++i){
            int L, R, rL, rR;
            scanf("%d%d", &L, &R);
            rL = find(L - 1), rR = find(R);
            if(rL != rR){
                merge(L - 1, R);
            }
        }
        power();
    }
    return 0;
}
