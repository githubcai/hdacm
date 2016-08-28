#include <cstdio>
#include <cmath>

const int MAX = 10000;
const double PI = acos(-1.0);
double pies[MAX];

int cal(double v, int N){
    int temp = 0;
    for(int i = 0; i < N; ++i){
        temp += int(pies[i] / v);
    }
    return temp;
}

int main(){
    int T;
    scanf("%d", &T);
    while(T-- > 0){
        int N, F;
        scanf("%d%d", &N, &F);
        ++F;
        double sum = 0;
        for(int i = 0; i < N; ++i){
            int temp;
            scanf("%d", &temp);
            pies[i] = PI * temp * temp;
            sum += pies[i];
        }
        
        double left = 0, right = sum / F;
        while(fabs(left - right) > 1e-6){
            double temp = (left + right) / 2;
            int mr = cal(temp, N);
            if(mr >= F){
                left = temp;
            }else{
                right = temp;
            }
        }
        printf("%.04lf\n", left);
    }
    return 0;
}
