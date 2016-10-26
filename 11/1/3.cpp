#include <cstdio>
#include <cstring>
#include <map>
#include <algorithm>
using namespace std;

#define LSON l, m, rt << 1
#define RSON m + 1, r, rt << 1 | 1
typedef long long LL;

const int MAX = 210;

struct Node{
    double l, r, h;
    int flag;
};

LL counts[MAX << 2];
Node nodes[MAX];
double xseg[MAX], sum[MAX << 2];
map<double, int> xstore;

bool comp(const Node &a, const Node &b){
    return a.h < b.h;
}

void pushUp(int l, int r, int rt){
    if(counts[rt] > 0){
        sum[rt] = xseg[r] - xseg[l - 1];
    }else if(l == r){
        sum[rt] = 0;
    }else{
        sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
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
    int n, Case = 1;
    while(scanf("%d", &n) == 1 && n != 0){
        int cnt = 0;
        for(int i = 0; i < n; ++i){
            double lx, ly, rx, ry;
            scanf("%lf%lf%lf%lf", &lx, &ly, &rx, &ry);
            xseg[cnt] = lx;
            nodes[cnt].l = lx, nodes[cnt].r = rx, nodes[cnt].h = ly, nodes[cnt++].flag = 1;
            xseg[cnt] = rx;
            nodes[cnt].l = lx, nodes[cnt].r = rx, nodes[cnt].h = ry, nodes[cnt++].flag = -1;
        }
        sort(xseg, xseg + cnt);
        sort(nodes, nodes + cnt, comp);
        int xcnt = 0;
        xstore.clear();
        xstore[xseg[0]] = 0;
        for(int i = 1; i < cnt; ++i){
            if(xseg[xcnt] != xseg[i]){
                xseg[++xcnt] = xseg[i];
                xstore[xseg[i]] = xcnt;
            }
        }

        memset(counts, 0, sizeof(counts));
        memset(sum, 0, sizeof(sum));
        update(xstore[nodes[0].l] + 1, xstore[nodes[0].r], nodes[0].flag, 1, xcnt, 1);
        double area = 0;
        for(int i = 1; i < cnt; ++i){
            area += (nodes[i].h - nodes[i - 1].h) * sum[1];
            update(xstore[nodes[i].l] + 1, xstore[nodes[i].r], nodes[i].flag, 1, xcnt, 1);
        }
        printf("Test case #%d\n", Case++);
        printf("Total explored area: %.2lf\n\n", area);
    }
    return 0;
}
