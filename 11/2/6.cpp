#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

#define LSON l, m, rt << 1
#define RSON m + 1, r, rt << 1 | 1
const int MAX = 100001;
struct Plank{
    int l, r, h, v;
    int ln, rn;
};

struct Node{
    int mark, lazy;
};

Node nodes[MAX << 2];
Plank planks[MAX];
int dp[MAX];

bool cmp(const Plank &a, const Plank &b){
    return a.h < b.h;
}

void pushDown(int rt){
    if(nodes[rt].lazy != 0){
        int ls = rt << 1, rs = rt << 1 | 1;
        nodes[ls].mark = nodes[rs].mark = nodes[ls].lazy = nodes[rs].lazy = nodes[rt].lazy;
        nodes[rt].lazy = 0;
    }
}

void pushUp(int rt){
    int ls = rt << 1, rs = rt << 1 | 1;
    if(nodes[ls].mark == nodes[rs].mark){
        nodes[rt].mark = nodes[ls].mark;
    }else{
        nodes[rt].mark = 0;
    }
}

void build(int l, int r, int rt){
    nodes[rt].mark = 0;
    nodes[rt].lazy = 0;
    if(l == r) return;
    int m = (l + r) >> 1;
    build(LSON);
    build(RSON);
}

void update(int L, int R, int t, int l, int r, int rt){
    if(L <= l && r <= R){
        nodes[rt].mark = t;
        nodes[rt].lazy = t;
        return;
    }
    pushDown(rt);
    int m = (l + r) >> 1;
    if(L <= m) update(L, R, t, LSON);
    if(m < R) update(L, R, t, RSON);
    pushUp(rt);
}

int query(int x, int l, int r, int rt){   
    if(l == r || nodes[rt].mark != 0){
        return nodes[rt].mark;
    }
    pushDown(rt);
    int m = (l + r) >> 1;
    if(x <= m) return query(x, LSON);
    if(x > m) return query(x, RSON);
}

int main(){
    int N;
    while(scanf("%d", &N) != EOF){
        for(int i = 1; i <= N; ++i){
            scanf("%d%d%d%d", &planks[i].h, &planks[i].l, &planks[i].r, &planks[i].v);
        }
        sort(planks + 1, planks + N + 1, cmp);
        build(1, MAX, 1);
        for(int i = 1; i <= N; ++i){
            planks[i].ln = query(planks[i].l, 1, MAX, 1);
            planks[i].rn = query(planks[i].r, 1, MAX, 1);
            update(planks[i].l, planks[i].r, i, 1, MAX, 1);
        }
        memset(dp, 0, sizeof(dp));
        dp[N] = planks[N].v + 100;
        for(int i = N; i > 0; --i){
            int ln = planks[i].ln, rn = planks[i].rn;
            dp[ln] = max(dp[ln], dp[i] + planks[ln].v);
            dp[rn] = max(dp[rn], dp[i] + planks[rn].v);
        }
        printf("%d\n", dp[0] > 0 ? dp[0] : -1);
    }
    return 0;
}
