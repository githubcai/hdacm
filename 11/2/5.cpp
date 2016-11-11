#include <cstdio>
#include <algorithm>
using namespace std;

#define LSON l, m, rt << 1
#define RSON m + 1, r, rt << 1 | 1
const int MAX = 50001;
struct Node{
    int start, end;
    int ls, rs, ms;
    int lazy, cnt, reset;
};

Node nodes[MAX << 2];

void pushDown(int l, int r, int mid, int rt){
    if(nodes[rt].lazy != -1){
        int ls = rt << 1, rs = rt << 1 | 1;
        nodes[ls].ms = nodes[ls].ls = nodes[ls].rs = (mid - l + 1) * nodes[rt].lazy;
        nodes[rs].ms = nodes[rs].ls = nodes[rs].rs = (r - mid) * nodes[rt].lazy;
        nodes[ls].start = nodes[rs].start = nodes[rt].start;
        nodes[ls].end = nodes[rs].end = nodes[rt].end;
        nodes[ls].lazy = nodes[rs].lazy = nodes[rt].lazy;
        nodes[rt].lazy = -1;
    }
}

void pushUp(int l, int r, int mid, int rt){
    int ls = rt << 1, rs = rt << 1 | 1;
    nodes[rt].ls = nodes[ls].ls;
    nodes[rt].rs = nodes[rs].rs;
    if(nodes[rt].ls == mid - l + 1) nodes[rt].ls += nodes[rs].ls;
    if(nodes[rt].rs == r - mid) nodes[rt].rs += nodes[ls].rs;
    nodes[rt].ms = max(max(nodes[ls].ms, nodes[rs].ms), nodes[ls].rs + nodes[rs].ls);
}

void countUp(int rt){
    nodes[rt].cnt = nodes[rt << 1].cnt + nodes[rt << 1 | 1].cnt;
}

void countDown(int rt){
    if(nodes[rt].reset){
        int ls = rt << 1, rs = rt << 1 | 1;
        nodes[ls].cnt = nodes[rs].cnt = 0;
        nodes[ls].reset = nodes[rs].reset = 1;
        nodes[rt].reset = 0;
    }
}

void Count(int x, int t, int l, int r, int rt){
    if(l == r){
        nodes[rt].cnt = t;
        return;
    }
    int m = (l + r) >> 1;
    countDown(rt);
    if(x <= m){
        Count(x, t, LSON);
    }else{
        Count(x, t, RSON);
    }
    countUp(rt);
}

void update(int L, int R, int t, int l, int r, int rt){
    if(L <= l && r <= R){
        nodes[rt].lazy = t;
        nodes[rt].ls = nodes[rt].rs = nodes[rt].ms = t * (r - l + 1);
        if(t){
            nodes[rt].start = nodes[rt].end = -1;
        }else{
            nodes[rt].start = L, nodes[rt].end = R;
        }
        return;
    }
    int m = (l + r) >> 1;
    pushDown(l, r, m, rt);
    if(L <= m) update(L, R, t, LSON);
    if(m < R) update(L, R, t, RSON);
    pushUp(l, r, m, rt);
}

int New(int x, int l, int r, int rt){
    if(l == r) return l;
    int m = (l + r) >> 1, ls = rt << 1, rs = rt << 1 | 1;
    pushDown(l, r, m, rt);
    if(nodes[ls].ms >= x){
        return New(x, LSON);
    }else if(nodes[ls].rs + nodes[rs].ls >= x){
        return m - nodes[ls].rs + 1;
    }else{
        return New(x, RSON);
    }
}

void Reset(int N){
    update(1, N, 1, 1, N, 1);
    nodes[1].reset = 1;
    nodes[1].cnt = 0;
}

int Free(int x, int l, int r, int rt){
    if(l == r) return rt;
    int m = (l + r) >> 1;
    pushDown(l, r, m, rt);
    if(x <= m){
        return Free(x, LSON);
    }else{
        return Free(x, RSON);
    }
}

int Get(int x, int l, int r, int rt){
    if(l == r) return l;
    int m = (l + r) >> 1, ls = rt << 1;
    countDown(rt);
    if(nodes[ls].cnt >= x){
        return Get(x, LSON);
    }else{
        return Get(x - nodes[ls].cnt, RSON);
    }
}

int main(){
    char comm[6]; int N, M;
    while(scanf("%d%d", &N, &M) != EOF){
        Reset(N);
        for(int i = 0; i < M; ++i){
            scanf("%s", comm);
            if(comm[0] == 'R'){
                Reset(N);
                printf("Reset Now\n");
            }else if(comm[0] == 'N'){
                int x; scanf("%d", &x);
                if(nodes[1].ms >= x){
                    int ans = New(x, 1, N, 1);
                    printf("New at %d\n", ans);
                    Count(ans, 1, 1, N, 1);
                    update(ans, ans + x - 1, 0, 1, N, 1);
                }else{
                    printf("Reject New\n");
                }
            }else if(comm[0] == 'F'){
                int x; scanf("%d", &x);
                int ans = Free(x, 1, N, 1);
                if(nodes[ans].start < 0){
                    printf("Reject Free\n");
                }else{
                    printf("Free from %d to %d\n", nodes[ans].start, nodes[ans].end);
                    Count(nodes[ans].start, 0, 1, N, 1);
                    update(nodes[ans].start, nodes[ans].end, 1, 1, N, 1);
                }
            }else{
                int x; scanf("%d", &x);
                if(x > nodes[1].cnt){
                    printf("Reject Get\n");
                }else{
                    printf("Get at %d\n", Get(x, 1, N, 1));
                }
            }
        }
        printf("\n");
    }
    return 0;
}
