#include <cstdio>
#include <cmath>

int main(){
    int T;
    scanf("%d", &T);
    while(T-- > 0){
        int n;
        scanf("%d", &n);
        printf("%d\n", int(pow(2, n) - 1));
    }
    return 0;
}
