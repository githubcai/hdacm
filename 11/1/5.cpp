#include <cstdio>

#define LSON l, m, rt << 1
#define RSON m + 1, r, rt << 1 | 1
const int MAX = 200001;

int mx[MAX << 2];

int max(int a, int b){
    return a > b ? a : b;
}

void pushUp(int rt){
    mx[rt] = max(mx[rt << 1], mx[rt << 1 | 1]);
}

void build(int l, int r, int rt){
    int m = (l + r) >> 1;
    if(l == r){
        scanf("%d", &mx[rt]);
        return;
    }
    build(LSON);
    build(RSON);
    pushUp(rt);
}

void update(int p, int tihuan, int l, int r, int rt){
    int m = (l + r) >> 1;
    if(l == r){
        mx[rt] = tihuan;
        return;
    }
    if(p <= m){
        update(p, tihuan, LSON);
    }else{
        update(p, tihuan, RSON);
    }
    pushUp(rt);
}

int query(int L, int R, int l, int r, int rt){
    int ret = -1, m = (l + r) >> 1;
    if(L <= l && r <= R){
        return mx[rt];
    }
    if(L <= m) ret = max(ret, query(L, R, LSON));
    if(R > m) ret = max(ret, query(L, R, RSON));
    return ret;
}

int main(){
    int N, M;
    while(scanf("%d%d", &N, &M) == 2){
        build(1, N, 1);
        char comm[2];
        int A, B;
        for(int i = 0; i < M; ++i){
            scanf("%s%d%d", comm, &A, &B);
            if(comm[0] == 'Q'){
                printf("%d\n", query(A, B, 1, N, 1));
            }else{
                update(A, B, 1, N, 1);
            }
        }
    }
    return 0;
}
