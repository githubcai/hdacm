#include <cstdio>
#include <cstring>
#include <cmath>

const int MAX = 2;

struct Mat{
    int a[MAX][MAX], size;
    Mat(){
        memset(a, 0, sizeof(a));
        size = 0;
    }
};

int table[40];

void init(){
    memset(table, 0, sizeof(table));
    table[1] = 1;
    for(int i = 2; i < 40; ++i){
        table[i] = table[i - 1] + table[i - 2];
    }
}

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
    for(int i = 0; i < m.size; ++i) ans.a[i][i] = 1;
    while(n){
        if(n & 1) ans = multi(ans, m, mod);
        m = multi(m, m, mod);
        n >>= 1;
    }
    return ans;
}

int main(){
    init();
    int n;
    while(scanf("%d", &n) == 1){
        if(n < 40){
            printf("%d\n", table[n]);
            continue;
        }
        double front = -0.5 * log10(5.0) + n * log10(0.5 + sqrt(5.0) / 2.0);
        front = front - floor(front);
        front = floor(pow(10, front) * 1000);

        Mat input = Mat();
        input.size = 2;
        input.a[0][0] = input.a[0][1] = input.a[1][0] = 1;
        input = quickMulti(input, n - 1, 10000);
        printf("%d...%04d\n", (int)front, input.a[0][0]);
    }
    return 0;
}
