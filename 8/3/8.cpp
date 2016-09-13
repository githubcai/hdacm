#include <cstdio>
#include <cstring>

typedef long long LL;
const int MAX = 50;
int f1, f2, a, b, n, m, k, mod;
int c[MAX][MAX], pa[MAX], pb[MAX], pf1[MAX], pf2[MAX];

void init(){
    c[0][0] = c[1][0] = c[1][1] = 1;
    for(int i = 2; i < MAX; ++i){
        c[i][0] = c[i][i] = 1;
        for(int j = 1; j < i; ++j){
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
        }
    }
    pa[0] = pb[0] = pf1[0] = pf2[0] = 1;
    for(int i = 1; i < MAX; ++i){
        pa[i] = ((LL)pa[i - 1] * (LL)a) % mod;
        pb[i] = ((LL)pb[i - 1] * (LL)b) % mod;
        pf1[i] = ((LL)pf1[i - 1] * (LL)f1) % mod;
        pf2[i] = ((LL)pf2[i - 1] * (LL)f2) % mod;
    }
}

int main(){
    return 0;
}
