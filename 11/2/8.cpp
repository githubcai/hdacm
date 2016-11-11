#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;

#define LSON l, m, rt << 1
#define RSON m + 1, r, rt << 1 | 1
typedef long long LL;

struct Que{
    int l, r, pos;
};

const int MAX = 30001, QMAX = 100000;
LL sum[MAX << 2], ans[QMAX];
int A[MAX];
Que ques[QMAX];

bool comp(const Que &a, const Que &b){
    return a.r < b.r;
}

void pushUp(int rt){
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}

void update(int x, int add, int l, int r, int rt){
    if(l == r){
        sum[rt] += add;
        return;
    }
    int m = (l + r) >> 1;
    if(x <= m) update(x, add, LSON);
    if(x > m) update(x, add, RSON);
    pushUp(rt);
}

LL query(int L, int R, int l, int r, int rt){
    LL ret = 0;
    if(L <= l && r <= R) return sum[rt];
    int m = (l + r) >> 1;
    if(L <= m) ret += query(L, R, LSON);
    if(m < R) ret += query(L, R, RSON);
    return ret;
}

int main(){
    int T; scanf("%d", &T);
    while(T--){
        int N; scanf("%d", &N);
        for(int i = 1; i <= N; ++i){
            scanf("%d", &A[i]);
        }
        int M; scanf("%d", &M);
        for(int i = 0; i < M; ++i){
            scanf("%d%d", &ques[i].l, &ques[i].r);
            ques[i].pos = i;
        }
        sort(ques, ques + M, comp);
        memset(sum, 0, sizeof(sum));
        int index = 1;
        map<LL, int> store;
        for(int i = 0; i < M; ++i){
            for(; index <= ques[i].r; ++index){
                if(store[A[index]]){
                    update(store[A[index]], -A[index], 1, N, 1);
                }
                update(index, A[index], 1, N, 1);
                store[A[index]] = index;
            }
            ans[ques[i].pos] = query(ques[i].l, ques[i].r, 1, N, 1);
        }
        for(int i = 0; i < M; ++i){
            printf("%lld\n", ans[i]);
        }
    }
    return 0;
}
