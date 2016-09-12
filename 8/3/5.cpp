#include <cstdio>
#include <cstring>

const int MAX = 2;

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
        int n; scanf("%d", &n);
        if(n == 1){
            printf("9\n");
        }else{
            Mat input = Mat();
            input.a[0][0] = input.a[1][1] = 5;
            input.a[0][1] = 12, input.a[1][0] = 2;
            input.size = 2;
            Mat ret = quickMulti(input, n - 1, 1024);

        }
    }
    return 0;
}
