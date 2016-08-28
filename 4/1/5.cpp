#include <cstdio>
#include <cmath>

const double PI = acos(-1.0);

double cal(double x, double l, double d, double t){
    return l * cos(t) - x / tan(t) + d / sin(t);
}

int main(){
    double x, y, l, d;
    while(scanf("%lf%lf%lf%lf", &x, &y, &l, &d) == 4){
        if(d > x || d > y){
            printf("no\n");
            continue;
        }
        double left = 0, right = PI / 2;
        while(right - left > 1e-7){
            double mid1 = (left + right) / 2;
            double mid2 = (left + mid1) / 2;
            double temp1 = cal(x, l, d, mid1), temp2 = cal(x, l, d, mid2);
            if(temp1 > temp2){
                left = mid2;
            }else{
                right = mid1;
            }
        }
        double temp = cal(x, l, d, left);
        if(temp > y){
            printf("no\n");
        }else{
            printf("yes\n");
        }
    }
    return 0;
}
