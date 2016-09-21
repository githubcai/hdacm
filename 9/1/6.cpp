#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

struct Node{
    double l, r;
    int ref;
};

const int MAX = 50000;
Node input[MAX];
int C[MAX + 1];

int lowbit(int x){
    return x & (-x);
}

void update(int x, int add){
    while(x <= MAX){
        C[x] += add;
        x += lowbit(x);
    }
}

int getSum(int x){
    int ret = 0;
    while(x > 0){
        ret += C[x];
        x -= lowbit(x);
    }
    return ret;
}

bool cmpR(const Node &a, const Node &b){
    if(a.r == b.r) return a.l > b.l;
    return a.r > b.r;
}

bool cmpL(const Node &a, const Node &b){
    if(a.l == b.l) return a.r < b.r;
    return a.l < b.l;
}

int main(){
    int N;
    while(scanf("%d", &N) == 1){
        double L, R; scanf("%lf%lf", &L, &R);
        int count = 0, leng = 0;
        for(int i = 0; i < N; ++i){
            double x1, x2, y1, y2;
            scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
            if(x1 == x2){
                if(x1 > L && x1 < R) ++count;
                continue;
            }
            double k = (y2 - y1) / (x2 - x1);
            input[leng].l = k * (L - x1) + y1;
            input[leng].r = k * (R - x1) + y1;
            ++leng;
        }
        sort(input, input + leng, cmpR);
        for(int i = 0; i < leng; ++i){
            input[i].ref = i + 1;
        }
        sort(input, input + leng, cmpL);
        int ans = 0;
        memset(C, 0, sizeof(C));
        for(int i = 0; i < leng; ++i){
            ans += getSum(input[i].ref - 1);
            update(input[i].ref, 1);
        }
        printf("%d\n", ans + count * leng);
    }
    return 0;
}
