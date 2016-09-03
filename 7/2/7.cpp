#include <cstdio>

typedef long long LL;
const int MAX = 10;
LL M[MAX], A[MAX];
LL dg;

void exgcd(LL a, LL b, LL &d, LL &x, LL &y){
    if(!b){
        d = a, x = 1, y = 0;
    }else{
        exgcd(b, a % b, d, y, x);
        y -= x * (a / b);
    }        
}

LL gcd(LL a, LL b){
    if(!b) return a;
    return gcd(b, a % b);
}

LL China(int r){
    LL a, b, dm, x, y, d;
    LL c, c1, c2;
    dg = a = M[0], c1 = A[0];
    for(int i = 1; i < r; ++i){
        b = M[i];
        c2 = A[i];
        exgcd(a, b, d, x, y);
        c = c2 - c1;
        if(c % d) return -1;
        dm = b / d;
        dg = dg / d * b;
        x = (x * (c / d) % dm + dm) % dm;
        c1 = a * x + c1;
        a = a * dm;
    }
    if(c1 == 0){
        c1 = dg;
    }
    return c1;
}

int main(){
    int T;
    scanf("%d", &T);
    while(T-- > 0){
        int N, m;
        scanf("%d%d", &N, &m);
        for(int i = 0; i < m; ++i){
            scanf("%lld", &M[i]);
        }
        for(int i = 0; i < m; ++i){
            scanf("%lld", &A[i]);
        }
        LL ret = China(m);
        if(ret == -1 || ret > N){
            printf("0\n");
        }else{
            LL result = (N - ret) / dg + 1;
            printf("%lld\n", result);
        }
    }
    return 0;
}
