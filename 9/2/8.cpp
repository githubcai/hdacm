#include <cstdio>
#include <cstring>

typedef long long LL;
const int MAX = 52;

struct Mat{
    LL a[MAX][MAX], size;
    Mat(){
        memset(a, 0, sizeof(a));
        size = 0;
    }
};

Mat multi(const Mat &m1, const Mat &m2, int mod){
    Mat ans = Mat();
    ans.size = m1.size;
    for(int i = 0; i < m1.size; ++i){
        for(int j = 0; j < m2.size; ++j){
            if(m1.a[i][j]){
                for(int k = 0; k < m1.size; ++k){
                    ans.a[i][k] = (ans.a[i][k] + m1.a[i][j] * m2.a[j][k]) % mod;
                }
            }
        }
    }
    return ans;
}

Mat quickMulti(Mat m, LL n, LL mod){
    Mat ans = Mat();
    for(int i = 0; i < m.size; ++i) ans.a[i][i] = 1;
    ans.size = m.size;
    while(n){
        if(n & 1) ans = multi(ans, m, mod);
        m = multi(m, m, mod);
        n >>= 1;
    }
    return ans;
}

LL C(LL a, LL b, LL mod){
    LL ans = 1;
    for(int i = 1; i <= b; ++i){
        ans = ans * (a - i + 1) / i;
    }
    return ans % mod;
}

int main(){
    LL N, x, M;
    while(scanf("%lld%lld%lld", &N, &x, &M) == 3){
        if(N == -1 && x == -1 && M == -1) break;
        Mat input = Mat();
        for(int i = 0; i <= x; ++i){
            for(int j = 0; j <= i; ++j){
                input.a[i + 1][j + 1] = x * C(i, j, M) % M;
            }
        }
        for(int i = 1; i <= x + 1; ++i){
            input.a[0][i] = input.a[x + 1][i];
        }
        input.a[0][0] = 1;
        input.size = x + 2;
        input = quickMulti(input, N, M);
        printf("%lld\n", input.a[0][1]);
    }
    return 0;
}
