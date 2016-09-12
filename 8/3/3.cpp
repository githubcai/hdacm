#include <cstdio>
#include <cstring>

const int MAX = 31;
typedef long long LL;

struct Mat{
    LL a[MAX][MAX], size;
    Mat(){
        memset(a, 0, sizeof(a));
        size = 0;
    }
};

Mat multi(const Mat &m1, const Mat &m2, LL mod){
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
    int T, N, K;
    scanf("%d", &T);
    while(T-- > 0){
        scanf("%d%d", &N, &K);
        Mat input;
        input.size = K + 1;
        input.a[0][0] = input.a[0][K] = input.a[1][1] = 1;
        for(int i = 2; i <= K; ++i){
            input.a[i][i - 1] = K - i + 1;
            input.a[i][i] = i;
        }
        input = quickMulti(input, N - 1, 1234567891);
        LL result = 0;
        result += input.a[0][1] * K + input.a[K][1] * K;
        printf("%lld\n", result % 1234567891);
    }
    return 0;
}
