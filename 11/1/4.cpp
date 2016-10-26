#include <cstdio>

#define LSON l, m, rt << 1
#define RSON m + 1, r, rt << 1 | 1
typedef long long LL;

const int MAX = 100001;
int lazy[MAX << 2], sum[MAX << 2];

void pushUp(int rt){
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}

void pushDown(int rt, int m){
    if(lazy[rt]){
        lazy[rt << 1] = lazy[rt << 1 | 1] = lazy[rt];
        sum[rt << 1] = (m - (m >> 1)) * lazy[rt];
        sum[rt << 1 | 1] = (m >> 1) * lazy[rt];
        lazy[rt] = 0;
    }
}

void build(int l, int r, int rt){
    int m = (l + r) >> 1;
    lazy[rt] = 0;
    if(l == r){
        sum[rt] = 1;
        return;
    }
    build(LSON);
    build(RSON);
    pushUp(rt);
}

void update(int L, int R, int c, int l, int r, int rt){
    int m = (r + l) >> 1;
    if(L <= l && r <= R){
        lazy[rt] = c;
        sum[rt] = c * (r - l + 1);
        return;
    }
    pushDown(rt, r - l + 1);
    if(L <= m) update(L, R, c, LSON);
    if(R > m) update(L, R, c, RSON);
    pushUp(rt);
}

LL query(int L, int R, int l, int r, int rt){
    int m = (l + r) >> 1;
    LL ret = 0;
    if(L <= l && r <= R){
        return sum[rt];
    }
    pushDown(rt, r - l + 1);
    if(L <= m) ret += query(L, R, LSON);
    if(m < R) ret += query(L, R, RSON);
    return ret;
}

int main(){
    int T, N, Q, Case = 1;
    scanf("%d", &T);
    while(T-- > 0){
        scanf("%d", &N);
        build(1, N, 1);
        scanf("%d", &Q);
        int X, Y, Z;
        for(int i = 0; i < Q; ++i){
            scanf("%d%d%d", &X, &Y, &Z);
            update(X, Y, Z, 1, N, 1);
        }
        printf("Case %d: The total value of the hook is %lld.\n", Case++, query(1, N, 1, N, 1));
    }
    return 0;
}
