/*
    f[1] = 0;
    f[i] = (f[i - 1] + m) % i (i > 1);
*/
#include <vector>
#include <cstdio>

using namespace std;

int JosephusProblem_Solution(int n, int m){
    if(n < 1 || m < 1) return -1;

    vector<int> f(n + 1, 0);
    for(unsigned i = 2; i <= n; ++i){
        f[i] = (f[i - 1] + m) % i;
    }
    return f[n];
}

int main(){
    int n, m;
    while(scanf("%d%d", &n, &m) == 2 && !(n == 0 && m == 0)){
        printf("%d\n", JosephusProblem_Solution(n, m));
    }
}
