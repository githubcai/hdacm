#include <cstdio>
#include <cstring>

const int MAX = 4;
struct Mat{
    int a[MAX][MAX], size;
    Mat(){
        memset(a, 0, sizeof(a));
        size = 0;
    }
};

Mat multi(const Mat &m1, const Mat &m2, int mod){
    Mat ret = Mat();
    ret.size = m1.size;
    for(int i = 0; i < m1.size; ++i){
        for(int j = 0; j < m2.size; ++j){
            if(m1.a[i][j]){
                for(int k = 0; k < m1.size; ++k){
                    ret.a[i][k] = (ret.a[i][k] + m1.a[i][j] * m2.a[j][k]) % mod;
                }
            }
        }
    }
    return ret;
}

Mat quickMulti(Mat m, int n, int mod){
    Mat ret = Mat();
    ret.size = m.size;
    for(int i = 0; i < ret.size; ++i) ret.a[i][i] = 1;
    while(n){
        if(n & 1) ret = multi(ret, m, mod);
        m = multi(m, m, mod);
        n >>= 1;
    }
    return ret;
}

int main(){
    int L, M;
    Mat input = Mat();
    input.size = 4;
    input.a[0][0] = input.a[0][2] = input.a[0][3] =
    input.a[1][0] = input.a[2][1] = input.a[3][2] = 1;
    int result[5] = {0, 2, 4 , 6, 9};
    while(scanf("%d%d", &L, &M) == 2){
        if(L <= 4){
            printf("%d\n", result[L] % M);
        }else{
            Mat res = quickMulti(input, L - 4, M);
            int temp = (9 * res.a[0][0] + 6 * res.a[0][1] + 4 * res.a[0][2] + 2 * res.a[0][3]) % M;
            printf("%d\n", temp);
        }
    }
    return 0;
}
