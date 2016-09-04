#include <cstdio>
#include <cstring>

const int MAX = 5001;
bool soldier[MAX];

int main(){
    int T;
    scanf("%d", &T);
    while(T-- > 0){
        int n; scanf("%d", &n);
        memset(soldier, 0, sizeof(soldier));
        int count = n;
        bool flag = true;
        while(count > 3){
            if(flag){
                int temp = 0;
                for(int i = 1; i <= n; ++i){
                    if(!soldier[i]){
                        ++temp;
                        if(temp == 2){
                            soldier[i] = true;
                            temp = 0;
                            --count;
                        }
                    }
                }
                flag = false;
            }else{
                int temp = 0;
                for(int i = 1; i <= n; ++i){
                    if(!soldier[i]){
                        ++temp;
                        if(temp == 3){
                            soldier[i] = true;
                            temp = 0;
                            --count;
                        }
                    }
                }
                flag = true;
            }
        }
        int i;
        for(i = 1; i <= n; ++i){
            if(!soldier[i]){
                printf("%d", i);
                break;
            }
        }
        for(++i; i <= n; ++i){
            if(!soldier[i]){
                printf(" %d", i);
            }
        }
        printf("\n");
    }
    return 0;
}
