#include <cstdio>
#include <cstring>
#include <cmath>

int main(){
    char N[10];
    while(scanf("%s", N) != EOF){
        int leng = strlen(N);
        long long ans = 0;
        for(int i = 0; i < leng; ++i){
            if(i + 1 == leng){
                if(N[i] > '2'){
                    ans += 3;
                }else{
                    ans += N[i] - '0';
                }
            }else{
                if(N[i] > '3'){
                    ans += (int)pow(4.0, leng - i - 1) * 3;
                    break;
                }else{
                    ans += (int)pow(4.0, leng - i - 2) * 3 * (N[i] - '0');
                }
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
