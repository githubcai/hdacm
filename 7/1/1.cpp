#include <cstdio>
#include <cstring>

struct Node{
    int x, y;
};

Node nodes[1000];

int main(){
    int n;
    while(scanf("%d", &n) == 1 && n != 0){
        for(int i = 0; i < n; ++i){
            scanf("%d%d", &nodes[i].x, &nodes[i].y);
        }
        bool flag = true;
        for(int i = 0; i < n; ++i){
            int vx1, vx2, vy1, vy2;
            vx1 = nodes[(i + 1) % n].x - nodes[i].x, vy1 = nodes[(i + 1) % n].y - nodes[i].y;
            vx2 = nodes[(i + 2) % n].x - nodes[(i + 1) % n].x, vy2 = nodes[(i + 2) % n].y - nodes[(i + 1) % n].y;
            int temp = vx1 * vy2 - vx2 * vy1;
            if(temp < 0){
                flag = false;
                break;
            }
        }
        if(flag){
            printf("convex\n");
        }else{
            printf("concave\n");
        }
    }
    return 0;
}
