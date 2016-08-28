#include <cstdio>

const int MAX = 100000;

int main(){
    int T, cnt = 0;
    scanf("%d", &T);
    while(T-- > 0){
        ++cnt;
        int N;
        scanf("%d", &N);
        
        int num[MAX];
        for(int i = 0; i < N; ++i){
            scanf("%d", &num[i]);
        }

        int sum = num[0], high = 1, low = 1, smax = num[0], mhigh = 1, mlow = 1;
        for(int i = 1; i < N; ++i){
            sum += num[i];
            if(sum >= num[i]){
                high = i + 1;   
            }else{
                sum = num[i];
                high = low = i + 1;
            }
            if(smax < sum){
                smax = sum;
                mhigh = high;
                mlow = low;
            }
        }

        if(cnt != 1) printf("\n");
        printf("Case %d:\n", cnt);
        printf("%d %d %d\n", smax, mlow, mhigh);
    }
    return 0;
}
