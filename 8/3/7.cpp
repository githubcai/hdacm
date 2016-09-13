#include <cstdio>
#include <cstring>

const int MAX = 3;
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

Mat quickMulti(Mat m, int n, int mod){
    Mat ans = Mat();
    ans.size = m.size;
    for(int i = 0; i < ans.size; ++i) ans.a[i][i] = 1;
    while(n){
        if(n & 1) ans = multi(ans, m, mod);
        m = multi(m, m, mod);
        n >>= 1;
    }
    return ans;
}

int main(){
    int N;
    while(scanf("%d", &N) == 1 && N != 0){
        Mat input = Mat();
        input.size = 3;
        input.a[0][0] = input.a[0][2] = input.a[1][0] = input.a[2][2] = 1;
        input.a[0][1] = 2;
        if(N == 1){
            printf("1\n");
        }else if(N == 2){
            printf("2\n");
        }else{
            input = quickMulti(input, N - 2, 200907);
            printf("%lld\n", (input.a[0][0] * 2 + input.a[0][1] + input.a[0][2]) % 200907);
        }
    }
    return 0;
}
