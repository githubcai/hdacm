#include <cstdio>
#include <cstring>

const int MAX = 10;
typedef long long LL;

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
        if(n & 1) ans = multi(m, ans, mod);
        m = multi(m, m, mod);
        n >>= 1;
    }
    return ans;
}

int main(){
    LL k, m;
    while(scanf("%lld%lld", &k, &m) == 2){
        Mat input;
        for(int i = 0; i < MAX; ++i){
            scanf("%lld", &input.a[0][i]);
        }
        for(int i = 1; i < MAX; ++i){
            input.a[i][i - 1] = 1;
        }
        input.size = 10;
        if(k < 10){
            printf("%lld\n", k);
            continue;
        }
        input = quickMulti(input, k - 9, m);
        LL result = 0;
        for(int i = 0; i < MAX; ++i){
            result += input.a[0][i] * (9 - i);
        }
        printf("%lld\n", result % m);
    }
    return 0;
}
