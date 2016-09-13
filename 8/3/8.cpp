#include <cstdio>
#include <cstring>

typedef long long LL;
const int MAX = 51;

struct Mat{
    int a[MAX][MAX], size;
    Mat(){
        memset(a, 0, sizeof(a));
        size = 0;
    }
};

int f1, f2, a, b, n, k, m, s2;
int c[MAX][MAX], pa[MAX], pb[MAX], pf1[MAX], pf2[MAX];

void init(){
    c[0][0] = c[1][0] = c[1][1] = 1;
    for(int i = 2; i < MAX; ++i){
        c[i][0] = c[i][i] = 1;
        for(int j = 1; j < i; ++j){
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % m;
        }
    }
    pa[0] = pb[0] = pf1[0] = pf2[0] = 1;
    for(int i = 1; i < MAX; ++i){
        pa[i] = ((LL)pa[i - 1] * (LL)a) % m;
        pb[i] = ((LL)pb[i - 1] * (LL)b) % m;
        pf1[i] = ((LL)pf1[i - 1] * (LL)f1) % m;
        pf2[i] = ((LL)pf2[i - 1] * (LL)f2) % m;
    }
    s2 = (pf1[k] + pf2[k]) % m;
}

Mat multi(const Mat &m1, const Mat &m2, int mod){
    Mat ans = Mat();
    ans.size = m1.size;
    for(int i = 0; i < m1.size; ++i){
        for(int j = 0; j < m2.size; ++j){
            if(m1.a[i][j]){
                for(int k = 0; k < m1.size; ++k){
                    ans.a[i][k] = ((LL)ans.a[i][k] + (LL)m1.a[i][j] * (LL)m2.a[j][k]) % mod;
                }
            }
        }
    }
    return ans;
}

Mat quickMulti(Mat m1, int n, int mod){
    Mat ans = Mat();
    ans.size = m1.size;
    for(int i = 0; i < ans.size; ++i) ans.a[i][i] = 1;
    while(n){
        if(n & 1) ans = multi(m1, ans, mod);
        m1 = multi(m1, m1, mod);
        n >>= 1;
    }
    return ans;
}

int main(){
    int T; scanf("%d", &T);
    while(T-- > 0){
        scanf("%d%d%d%d%d%d%d", &f1, &f2, &a, &b, &k, &n, &m);
        init();
        Mat input = Mat();
        input.a[0][0] = 1, input.size = k + 2;
        for(int i = 1; i < k + 2; ++i){
            int temp = k - i + 1;
            for(int j = 0; j <= temp; ++j){
                input.a[i][j + 1] = ((LL)c[temp][j] * (LL)pa[temp - j] * (LL)pb[j]) % m;
            }
        }
        for(int i = 1; i < k + 2; ++i){
            input.a[0][i] = input.a[1][i];
        }

        input = quickMulti(input, n - 2, m);
        int result = s2;
        for(int i = 1; i < k + 2; ++i){
            result = ((LL)result + (LL)input.a[0][i] * (LL)pf2[k - i + 1] * (LL)pf1[i - 1]) % m;
        }
        printf("%d\n", result);
    }
    return 0;
}
