#include <cstdio>
#include <cstring>

const int MAX = 60001;
bool dp[MAX];
int mars[1000];

int main(){
    int mar[6], cnt = 0;
    while(true){
        int sum = 0;
        for(int i = 0; i < 6; ++i){
            scanf("%d", &mar[i]);
            sum += mar[i] * (i + 1);
        }
        if(sum == 0) break;
        
        ++cnt;
        printf("Collection #%d:\n", cnt);

        if(sum % 2 == 1){
            printf("Can't be divided.\n\n");
        }else{
            sum /= 2;
            
            int mLen = 0;
            for(int i = 1; i <= 6; ++i){
                if(mar[i - 1] == 0) continue;
                for(int j = 1; j < mar[i - 1]; j *= 2){
                    mars[mLen++] = i * j;
                    mar[i - 1] -= j;
                }
                mars[mLen++] = i * mar[i - 1];
            }

            memset(dp, 0, sizeof(dp));
            dp[0] = true;
            for(int i = 0; i < mLen; ++i){
                for(int j = sum; j >= mars[i]; --j){
                    if(dp[j] || !dp[j - mars[i]]) continue;
                    dp[j] = true;
                }
            }
            if(dp[sum]){
                printf("Can be divided.\n\n");
            }else{
                printf("Can't be divided.\n\n");
            }
        }
    }
    return 0;
}
