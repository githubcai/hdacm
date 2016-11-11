/* zkw单点增减, 区间和 */
#include <cstdio>
#include <cstring>

const int MAX = 50000;
int M, sum[MAX << 2];

void build(int n){
    for(M = 1; M <= n + 1; M <<= 1);
    for(int i = M + 1; i <= M + n; ++i) scanf("%d", &sum[i]);
    for(int i = M -1; i; --i) sum[i] = sum[i << 1] + sum[i << 1 | 1];
}

void update(int p, int add){
    for(sum[p += M] += add, p >>= 1; p; p >>= 1){
        sum[p] = sum[p << 1] + sum[p << 1 | 1];
    }
}

int query(int l, int r, int ans = 0){
    for(l += M - 1, r += M + 1; l ^ r ^ 1; l >>= 1, r >>= 1){
        if(~l & 1) ans += sum[l ^ 1];
        if(r & 1) ans += sum[r ^ 1];
    }
    return ans;
}

int main(){
    char comm[6];
    int T, Case = 1; scanf("%d", &T);
    while(T-- > 0){
        int N; scanf("%d", &N);
        memset(sum, 0, sizeof(sum));
        build(N);
        printf("Case %d:\n", Case++);
        int a, b;
        while(true){
            scanf("%s", comm);
            if(comm[0] == 'Q'){
                scanf("%d%d", &a, &b);
                printf("%d\n", query(a, b));
            }else if(comm[0] =='A'){
                scanf("%d%d", &a, &b);
                update(a, b);
            }else if(comm[0] == 'S'){
                scanf("%d%d", &a, &b);
                update(a, -b);
            }else{
                break;
            }
        }
    }
    return 0;
}
