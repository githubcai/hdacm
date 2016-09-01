#include <cstdio>

const int MAX = 301;
int c1[MAX], c2[MAX];

int main(){
    int nNum;
    while(scanf("%d", &nNum) == 1 && nNum != 0){
        for(int i = 0; i <= nNum; ++i){
            c1[i] = 1;
            c2[i] = 0;
        }
        for(int i = 2; i <= 17; ++i){
            for(int j = 0; j <= nNum; ++j){
                for(int k = 0; k + j <= nNum; k += i * i){
                    c2[k + j] += c1[j];
                }
            }
            for(int j = 0; j <= nNum; ++j){
                c1[j] = c2[j];
                c2[j] = 0;
            }
        }
        printf("%d\n", c1[nNum]);
    }
    return 0;
}
