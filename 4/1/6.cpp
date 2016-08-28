#include <cstdio>
#include <cmath>

class Point{
public:
    double x, y;
};

Point A, B, C, D;
double P, Q, R;

double dist(const Point &a, const Point &b){
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

double calTime(const Point &a, const Point &b){
    return dist(A, a) / P + dist(D, b) / Q + dist(a, b) / R;
}

Point middle(const Point &a, const Point &b){
    Point temp;
    temp.x = (a.x + b.x) / 2;
    temp.y = (a.y + b.y) / 2;
    return temp;
}

double calAB(const Point &a, Point &b){
    Point left = A, right = B;
    double t1, t2;
    do{
        Point mid1 = middle(left, right);
        Point mid2 = middle(mid1, right);

        t1 = calTime(mid1, a);
        t2 = calTime(mid2, a);
        
        if(t1 > t2){
            left = mid1;
        }else{
            right = mid2;
        }
    }while(fabs(t1 - t2) > 1e-6);
    b = left;
    return t1;
}

double calCD(const Point &a, Point &b){
    Point left = C, right = D;
    double t1, t2;
    do{
        Point mid1 = middle(left, right);
        Point mid2 = middle(mid1, right);

        t1 = calTime(a, mid1);
        t2 = calTime(a, mid2);
        
        if(t1 > t2){
            left = mid1;
        }else{
            right = mid2;
        }
    }while(fabs(t1 - t2) > 1e-6);
    b = left;
    return t1;
}

int main(){
    int T;
    scanf("%d", &T);
    while(T-- > 0){
        scanf("%lf%lf%lf%lf", &A.x, &A.y, &B.x, &B.y);
        scanf("%lf%lf%lf%lf", &C.x, &C.y, &D.x, &D.y);
        scanf("%lf%lf%lf", &P, &Q, &R);
        
        double t1 = 0, t2 = 1.0;
        Point temp = D, ret;
        while(fabs(t1 - t2) > 1e-4){
            t1 = calAB(temp, ret);
            t2 = calCD(ret, temp);
        }
        printf("%.02lf\n", t1);
    }
    return 0;
}
