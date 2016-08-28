#include <cstdio>
#include <cmath>

double cal(double Y, double x){
    double temp = 8 * x * x * x * x + 7 * x * x * x + 2 * x * x + 3 * x + 6 - Y;
    return temp;
}

int main(){
    int T;
    scanf("%d", &T);
    
    while(T-- > 0){
        int Y;
        scanf("%d", &Y);
        
        double left = 0, right = 100, rl = cal(Y, left), rr = cal(Y, right);
        if(rl > 0 || rr < 0){
            printf("No solution!\n");
            continue;
        }
        while(fabs(rl - rr) > 1e-6){
            double mid = (left + right) / 2;
            double rm = cal(Y, mid);
            if(rm > 0){
                right = mid;
                rr = rm;
            }else{
                left = mid;
                rl = rm;
            }
        }
        printf("%.04lf\n", left);
    }
    return 0;
}
