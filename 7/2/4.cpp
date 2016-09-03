#include <cstdio>

typedef long long LL;

LL M[55], A[55];

void exgcd(LL a, LL b, LL &d, LL &x, LL &y){
    if(!b){
        d = a;
        x = 1;
        y = 0;
    }else{
        exgcd(b, a % b, d, y, x);
        y -= x * (a / b);
    }
}

LL gcd(LL a, LL b){
    if(!b) return a;
    gcd(b, a % b);
}

LL China(int r){
    LL a, b, dm, x, y, d;
    LL c, c1, c2;
    a = M[0], c1 = A[0];
    for(int i = 1; i < r; ++i){
        b = M[i];
        c2 = A[i];
        exgcd(a, b, d, x, y);
        c = c2 - c1;
        if(c % d) return -1;
        dm = b / d;
        x = ((x * (c / d)) % dm + dm) % dm;
        c1 = a * x + c1;
        a = a * dm;
    }
    if(c1 == 0){
        c1 = 1;
        for(int i = 0; i < r; ++i){
            c1 = c1 * M[i] / gcd(c1, M[i]);
        }
    }
    return c1;
}

int main(){
    int T, t = 0;
    scanf("%d", &T);
    while(T-- > 0){
        int n;
        scanf("%d", &n);
        for(int i = 0; i < n; ++i){
            scanf("%lld", &M[i]);
        }
        for(int i = 0; i < n; ++i){
            scanf("%lld", &A[i]);
        }
        LL ans = China(n);
        printf("Case %d: %lld\n", ++t, ans);
    }
    return 0;
}
