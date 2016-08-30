#include <cstdio>
#include <cstring>

const int MAX = 10;

struct Mat{
    long long a[MAX][MAX], size;
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

Mat quickMulti(Mat m, int n, int mod){
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
    long long k, m;
    while(scanf("%lld%lld", &k, &m) == 2){
        if(k < 10){
            printf("%lld\n", k);
            continue;
        }
        Mat mat = Mat();
        for(int i = 0; i < 10; ++i){
            scanf("%lld", &mat.a[0][i]);
        }
        for(int i = 1; i < 10; ++i){
            mat.a[i][i - 1] = 1;
        }
        mat.size = 10;
        Mat ans = quickMulti(mat, k - 9, m);
        long long sum = 0;
        for(int i = 0; i < 10; ++i){
            sum += ans.a[0][i] * (9 - i);
        }
        printf("%lld\n", sum % m);
    }
    return 0;
}
