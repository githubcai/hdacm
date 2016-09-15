#include <cstdio>
#include <cstring>

typedef long long LL;
const int MAX = 51;

struct Mat{
    LL a[MAX][MAX], size;
    Mat(){
        memset(a, 0, sizeof(a));
        size = 0;
    }
};

int f1, f2, a, b, n, k, m, s1, s2;
LL c[MAX][MAX], pa[MAX], pb[MAX], pf1[MAX], pf2[MAX];

void init(){
    c[0][0] = c[1][0] = c[1][1] = 1;
    for(int i = 2; i < 50; ++i){
        c[i][0] = c[i][i] = 1;
        for(int j = 1; j < i; ++j){
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % m;
        }
    }
    pa[0] = pb[0] = pf1[0] = pf2[0] = 1;
    for(int i = 1; i <= k; ++i){
        pa[i] = (pa[i - 1] * a) % m;
        pb[i] = (pb[i - 1] * b) % m;
        pf1[i] = (pf1[i - 1] * f1) % m;
        pf2[i] = (pf2[i - 1] * f2) % m;
    }
    s1 = pf1[k] % m;
    s2 = (pf1[k] + pf2[k]) % m;
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

Mat quickMulti(Mat m1, int n1, int mod){
    Mat ans = Mat();
    ans.size = m1.size;
    for(int i = 0; i < ans.size; ++i) ans.a[i][i] = 1;
    while(n1){
        if(n1 & 1) ans = multi(m1, ans, mod);
        m1 = multi(m1, m1, mod);
        n1 >>= 1;
    }
    return ans;
}

int main(){
    int T; scanf("%d", &T);
    while(T-- > 0){
        scanf("%d%d%d%d%d%d%d", &f1, &f2, &a, &b, &k, &n, &m);
        init();
        if(n == 1){
            printf("%d\n", s1);
            continue;
        }
        if(n == 2){
            printf("%d\n", s2);
            continue;
        }
        Mat input = Mat();
        input.a[0][0] = 1, input.size = k + 2;
        for(int i = 1; i < k + 2; ++i){
            int temp = k - i + 1;
            for(int j = 0; j <= temp; ++j){
                input.a[i][j + 1] = (c[temp][j] * pa[temp - j] % m * pb[j]) % m;
            }
        }
        for(int i = 1; i < k + 2; ++i){
            input.a[0][i] = input.a[1][i];
        }

        input = quickMulti(input, n - 2, m);
        LL result = s2 * input.a[0][0] % m;
        for(int i = 1; i < k + 2; ++i){
            result = (result + (input.a[0][i] * pf2[k - i + 1]) % m * pf1[i - 1] % m) % m;
        }
        printf("%lld\n", result);
    }
    return 0;
}
