#include <cstdio>
#include <vector>

using namespace std;

const int MAX = 15;
int table[MAX];

int Joseph(int s, int n, int m){
    vector<int> f(n + 1, 0);
    f[1] = (s + m) % (n + 1);
    for(unsigned i = 2; i <= n; ++i){
        f[i] = (f[i - 1] + m) % (i + n);
    }
    return f[n];
}

int cal(int k){
    for(int i = 0;; ++i){
        for(int j = k + 1 + 2 * k * i; j <= 2 * k + 2 * k * i; ++j){
            int temp = Joseph(0, k, j);
            if(temp == 0){
                temp = Joseph(k - 1, k, j);
                if(temp == k - 1) return j;
            }
        }
    }
}

void init(){
    for(int i = 1; i < 14; ++i){
         table[i] = cal(i);
    }
}

int main(){
    init();
    int k;
    while(scanf("%d", &k) == 1 && k != 0){
        printf("%d\n", table[k]);
    }
}
