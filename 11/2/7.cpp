#include <cstdio>
#include <map>
#include <algorithm>
#include <cstring>
using namespace std;

#define LSON l, m, rt << 1
#define RSON m + 1, r, rt << 1 | 1
const int MAX = 2060;

struct Seg{
    double l, r, h;
    int flag;
};

struct Node{
    int cnt;
    double len1, len2;
};

Seg segs[MAX];
double xseg[MAX];
map<double, int> xstore;
Node nodes[MAX << 2];

bool comp(const Seg &a, const Seg &b){
    return a.h < b.h;
}

void pushUp(int l, int r, int rt){
    int ls = rt << 1, rs = rt << 1 | 1;
    if(nodes[rt].cnt > 0){
        nodes[rt].len1 = xseg[r] - xseg[l - 1];
    }else{
        if(l == r){
            nodes[rt].len1 = 0;
        }else{
            nodes[rt].len1 = nodes[ls].len1 + nodes[rs].len1;
        }
    }

    if(nodes[rt].cnt > 1){
        nodes[rt].len2 = xseg[r] - xseg[l - 1];
    }else if(nodes[rt].cnt == 1){
        if(l == r){
            nodes[rt].len2 = 0;
        }else{
            nodes[rt].len2 = nodes[ls].len1 + nodes[rs].len1;
        }
    }else{
        nodes[rt].len2 = nodes[ls].len2 + nodes[rs].len2;
    }
}

void update(int L, int R, int c, int l, int r, int rt){
    if(L <= l && r <= R){
        nodes[rt].cnt += c;
        pushUp(l, r, rt);
        return;
    }
    int m = (l + r) >> 1;
    if(L <= m) update(L, R, c, LSON);
    if(m < R) update(L, R, c, RSON);
    pushUp(l, r, rt);
}

int main(){
    int T; scanf("%d", &T);
    while(T--){
        int N, cnt = 0; scanf("%d", &N);
        for(int i = 0; i < N; ++i){
            double lx, ly, rx, ry;
            scanf("%lf%lf%lf%lf", &lx, &ly, &rx, &ry);
            xseg[cnt] = lx;
            segs[cnt].l = lx, segs[cnt].r = rx, segs[cnt].h = ly, segs[cnt++].flag = 1;
            xseg[cnt] = rx;
            segs[cnt].l = lx, segs[cnt].r = rx, segs[cnt].h = ry, segs[cnt++].flag = -1;
        }
        sort(xseg, xseg + cnt);
        sort(segs, segs + cnt, comp);
        int xcnt = 0; xstore.clear(); xstore[xseg[0]] = 0;
        for(int i = 1; i < cnt; ++i){
            if(xseg[xcnt] != xseg[i]){
                xseg[++xcnt] = xseg[i];
                xstore[xseg[i]] = xcnt;
            }
        }

        memset(nodes, 0, sizeof(nodes));
        double area = 0;
        for(int i = 0; i < cnt - 1; ++i){
            int t1 = xstore[segs[i].l], t2 = xstore[segs[i].r];
            update(t1 + 1, t2, segs[i].flag, 1, xcnt, 1);
            area += (segs[i + 1].h - segs[i].h) * nodes[1].len2;
        }
        printf("%.2lf\n", area);
    }
    return 0;
}
