#include <cstdio>
#include <cstring>

const int MAX = 10;

struct Mat{
    int a[MAX][MAX], size;
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
    int T; scanf("%d", &T);
    while(T-- > 0){
        int n, k;
        Mat input = Mat();
        scanf("%d%d", &n, &k);
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j){
                scanf("%d", &input.a[i][j]);
            }
        }
        input.size = n;
        input = quickMulti(input, k, 9973);
        int result = 0;
        for(int i = 0; i < n; ++i){
            result += input.a[i][i];
        }
        printf("%d\n", result % 9973);
    }
    return 0;
}
