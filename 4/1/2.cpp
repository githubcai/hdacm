#include <cstdio>
#include <cmath>

double cal1(double x, double y){
    double temp = 42 * pow(x, 6) + 48 * pow(x, 5) +  21 * x * x + 10 * x - y;
    return temp;
}

double cal2(double x, double y){
    double temp = 6 * pow(x, 7) + 8 * pow(x, 6) +  7 * x * x * x + 5 * x * x - y * x;
    return temp;
}

int main(){
    int T;
    scanf("%d", &T);

    while(T-- > 0){
        int Y;
        scanf("%d", &Y);
        double left = 0, right = 100, lr = cal1(left, Y), rr = cal1(right, Y);
        if(lr >= 0){
            printf("%.04lf\n", cal2(left, Y));
            continue;
        }else if(rr <= 0){
            printf("%.04lf\n", cal2(right, Y));
            continue;
        }
        while(fabs(lr - rr) > 1e-6){
            double mid = (left + right) / 2;
            double rm = cal1(mid, Y);
            if(rm > 0){
                right = mid;
                rr = rm;
            }else{
                left = mid;
                lr = rm;
            }
        }
        printf("%.04lf\n", cal2(left, Y));
    }
    return 0;
}
