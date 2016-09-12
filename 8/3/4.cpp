#include <cstdio>
#include <cstring>
#include <map>
using namespace std;

const int MAX = 30;

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

Mat add(const Mat &m1, const Mat &m2, int mod){
    Mat ans = Mat();
    ans.size = m1.size;
    for(int i = 0; i < m1.size; ++i){
        for(int j = 0; j < m1.size; ++j){
            ans.a[i][j] = (m1.a[i][j] + m2.a[i][j]) % mod;
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

Mat cal(Mat m, int n, int mod){
    if(n == 1) return m;
    if(n % 2 == 1){
        Mat temp = cal(m, n / 2, mod), temp1 = quickMulti(m, n / 2 + 1, mod);
        Mat temp2 = multi(temp, temp1, mod);
        Mat result = add(add(temp, temp1, mod), temp2, mod);
        return result;
    }else{
        Mat temp = cal(m, n / 2, mod), temp1 = quickMulti(m, n / 2, mod);
        Mat temp2 = multi(temp, temp1, mod);
        Mat result = add(temp, temp2, mod);
        return result;
    }
}

int main(){
    int n;
    while(scanf("%d", &n) == 1){
        Mat input = Mat();
        int count = 0;
        map<long long, int> ref;
        for(int i = 0; i < n; ++i){
            long long p1, p2; scanf("%lld%lld", &p1, &p2);
            auto iter = ref.find(p1);
            if(iter == ref.end()){
                ref[p1] = count++;
            }
            iter = ref.find(p2);
            if(iter == ref.end()){
                ref[p2] = count++;
            }
            ++input.a[ref[p1]][ref[p2]];
        }
        input.size = count;
        int k; scanf("%d", &k);
        for(int i = 0; i < k; ++i){
            int v1, v2, t1, t2;
            scanf("%d%d%d%d", &v1, &v2, &t1, &t2);
            auto iter1 = ref.find(v1), iter2 = ref.find(v2);
            if(t1 == 0) t1 = 1;
            if(t1 > t2 || iter1 == ref.end() || iter2 == ref.end()){
                printf("0\n");
                continue;
            }
            Mat ans;
            if(t1 == 1){
                ans = cal(input, t2, 2008);
            }else{
                int temp = t2 - t1 + 1;
                ans = multi(quickMulti(input, t1 - 1, 2008), cal(input, temp, 2008), 2008);
            }
            printf("%d\n", ans.a[ref[v1]][ref[v2]]);
        }
    }
    return 0;
}
