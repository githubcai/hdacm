/* zkw单点替换,区间最值 */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAX = 130000;
int mx[MAX << 2], M;

void build(int n){
    for(M = 1; M <= n + 1; M <<= 1);
    for(int i = M + 1; i <= M + n; ++i) scanf("%d", &mx[i]);
    for(int i = M - 1; i; --i) mx[i] = max(mx[i << 1], mx[i << 1 | 1]);
}

void update(int p, int v){
    for(mx[p += M] = v, p >>= 1; p; p >>= 1){
        mx[p] = max(mx[p << 1], mx[p << 1 | 1]);
    }
}

int query(int l, int r, int ans = 0){
    for(l += M - 1, r += M + 1; l ^ r ^ 1; l >>= 1, r >>= 1){
        if(~l & 1) ans = max(ans, mx[l ^ 1]);
        if(r & 1) ans = max(ans, mx[r ^ 1]);
    }
    return ans;
}

int main(){
    int n, m;
    char comm[2];
    while(scanf("%d%d", &n, &m) == 2){
        memset(mx, 0, sizeof(mx));
        build(n);
        int a, b;
        for(int i = 0; i < m; ++i){
            scanf("%s", comm);
            if(comm[0] == 'Q'){
                scanf("%d%d", &a, &b);
                printf("%d\n", query(a, b));
            }else{
                scanf("%d%d", &a, &b);
                update(a, b);
            }
        }
    }
    return 0;
}
