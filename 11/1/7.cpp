#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;

#define LSON l, m, rt << 1
#define RSON m + 1, r, rt << 1 | 1

const int MAX = 200;
struct Node{
    int l, r, h, flag;
};

int xseg[MAX], counts[MAX << 2], lens[MAX << 2], dep[MAX << 2], ml[MAX << 2];
Node nodes[MAX];

bool comp(const Node &a, const Node &b){
    return a.h < b.h;
}

void build(int l, int r, int rt){
    int mid = (l + r) >> 1;
    counts[rt] = dep[rt] = lens[rt] = 0, ml[rt] = xseg[r] - xseg[l - 1];
    if(l == r) return;
    build(l, mid, rt << 1);
    build(mid + 1, r, rt << 1 | 1);
}

void pushUp(int l, int r, int rt){
    int ls = rt << 1, rs = rt << 1 | 1;
    if(dep[ls] > dep[rs]){
        dep[rt] = dep[ls];
        ml[rt] = ml[ls];
    }else if(dep[rs] > dep[ls]){
        dep[rt] = dep[rs];
        ml[rt] = ml[rs];
    }else{
        dep[rt] = dep[ls];
        ml[rt] = ml[ls] + ml[rs];
    }
    dep[rt] += counts[rt];
    if(counts[rt] > 0){
        lens[rt] = xseg[r] - xseg[l - 1];
    }else{
        lens[rt] = lens[ls] + lens[rs];
    }
}

void update(int L, int R, int c, int l, int r, int rt){
    int m = (l + r) >> 1, ls = rt << 1, rs = rt << 1 | 1;
    if(L <= l && r <= R){
        counts[rt] += c;
        if(c > 0){
            ++dep[rt];
            lens[rt] = xseg[r] - xseg[l - 1];
        }else{
            --dep[rt];
            if(counts[rt] > 0){
                lens[rt] = xseg[r] - xseg[l - 1];
            }else{
                if(l == r){
                    lens[rt] = 0;
                }else{
                    lens[rt] = lens[ls] + lens[rs];
                }
            }
        }
        return;
    }
    if(L <= m) update(L, R, c, LSON);
    if(m < R) update(L, R, c, RSON);
    pushUp(l, r, rt);
}

int main(){
    int n, w, h;
    while(scanf("%d", &n) == 1 && n){
        scanf("%d%d", &w, &h);
        int cnt = 0;
        for(int i = 0; i < n; ++i){
            int lx, ly, rx, ry;
            scanf("%d%d%d%d", &lx, &ly, &rx, &ry);
            xseg[cnt] = lx;
            nodes[cnt].l = lx, nodes[cnt].r = rx, nodes[cnt].h = ly, nodes[cnt++].flag = 1;
            xseg[cnt] = rx;
            nodes[cnt].l = lx, nodes[cnt].r = rx, nodes[cnt].h = ry, nodes[cnt++].flag = -1;
        }
        sort(xseg, xseg + cnt);
        sort(nodes, nodes + cnt, comp);
        map<int, int> xstore;
        xstore[xseg[0]] = 0;
        int xcnt = 0;
        for(int i = 1; i < cnt; ++i){
            if(xseg[xcnt] != xseg[i]){
                xseg[++xcnt] = xseg[i];
                xstore[xseg[i]] = xcnt;
            }
        }
    
        build(1, xcnt, 1);
        int area = 0, deep = 0, ans = 0;
        for(int i = 0; i < cnt - 1; ++i){
            update(xstore[nodes[i].l] + 1, xstore[nodes[i].r], nodes[i].flag, 1, xcnt, 1);
            area += (nodes[i + 1].h - nodes[i].h) * lens[1];
            if(deep < dep[1]){
                deep = dep[1];
                ans = ml[1] * (nodes[i + 1].h - nodes[i].h);
            }else if(dep[1] == deep){
                ans += ml[1] * (nodes[i + 1].h - nodes[i].h);
            }
        }
        printf("%d %d %d\n", w * h - area, deep, ans);
    }
    return 0;
}
