#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define LSON l, m, rt << 1
#define RSON m + 1, r, rt << 1 | 1
typedef long long LL;

const int MAX = 50010;
struct Node{
    int l, r, h, flag;
    void push(int l, int r, int h, int flag){
        this->l = l;
        this->r = r;
        this->h = h;
        this->flag = flag;
    }
};

LL  counts[MAX * 3], lens[MAX * 3];
Node nodes[MAX * 8];

bool comp(const Node &a, const Node &b){
    return a.h < b.h;
}

void pushUp(int l, int r, int rt){
    if(counts[rt] > 0){
        lens[rt] = r - l + 1;
    }else if(l == r){
        lens[rt] = 0;
    }else{
        lens[rt] = lens[rt << 1] + lens[rt << 1 | 1];
    }
}

void update(int L, int R, int c, int l, int r, int rt){
    int m = (l + r) >> 1;
    if(L <= l && r <= R){
        counts[rt] += c;
        pushUp(l, r, rt);
        return;
    }
    if(L <= m) update(L, R, c, LSON);
    if(m < R) update(L, R, c, RSON);
    pushUp(l, r, rt);
}

int main(){
    int N;
    while(scanf("%d", &N) == 1 && N){
        int cnt = 0;
        for(int i = 0; i < N; ++i){
            int x1, y1, x2, y2, x3, y3, x4, y4;
            scanf("%d%d%d%d%d%d%d%d", &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4);
            nodes[cnt++].push(x1, x3, y1, 1);
            nodes[cnt++].push(x1, x3, y4, -1);
            
            nodes[cnt++].push(x3, x2, y1, 1);
            nodes[cnt++].push(x3, x2, y3, -1);
            
            nodes[cnt++].push(x1, x4, y4, 1);
            nodes[cnt++].push(x1, x4, y2, -1);
            
            nodes[cnt++].push(x4, x2, y3, 1);
            nodes[cnt++].push(x4, x2, y2, -1);
        }
        sort(nodes, nodes + cnt, comp);
        memset(counts, 0, sizeof(counts));
        memset(lens, 0, sizeof(lens));
        LL area = 0;
        for(int i = 0; i < cnt - 1; ++i){
            if(nodes[i].l < nodes[i].r){
                update(nodes[i].l + 1, nodes[i].r, nodes[i].flag, 0, 50000, 1);
            }
            area += (nodes[i + 1].h - nodes[i].h) * lens[1];
        }
        printf("%lld\n", area);
    }
    return 0;
}
