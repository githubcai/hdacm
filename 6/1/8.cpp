#include <cstdio>
#include <algorithm>
using namespace std;

struct Node{
    int u, v, c;
};

const int MAX = 10000;
int pre[MAX], n;
bool flags[MAX];
long long result;

void init(){
    for(int i = 0; i < n; ++i){
        pre[i] = i;
    }
    fill(flags, flags + n, false);
    result = 0;
}

int find(int x){
    if(x == pre[x]) return x;
    pre[x] = find(pre[x]);
    return pre[x];
}

void merge(const Node &p){
    int ur, vr;
    ur = find(p.u), vr = find(p.v);
    if(ur == vr){
        if(flags[ur]) return;
        flags[ur] = true;
    }else{
        if(flags[ur] && flags[vr]) return;
        pre[ur] = vr;
        if(flags[ur] || flags[vr]) flags[vr] = true;
    }
    result += p.c;
}

bool cmp(const Node &a, const Node &b){
    return a.c > b.c;
}

int main(){
    int m;
    while(scanf("%d%d", &n, &m) == 2 && !(n == 0 && m == 0)){
        init();
        Node nodes[m];
        for(int i = 0; i < m; ++i){
            scanf("%d%d%d", &nodes[i].u, &nodes[i].v, &nodes[i].c);
        }
        sort(nodes, nodes + m, cmp);
        for(int i = 0; i < m; ++i){
            merge(nodes[i]);
        }
        printf("%lld\n", result);
    }
    return 0;
}
