#include <cstdio>

int width, height;

void print(int x, int y){
    if(x == 0 || x == height - 1){
        if(y == 0 || y == width - 1){
            printf("+");
        }else{
            printf("-");
        }
    }else if(y == 0 || y == width - 1){
        printf("|");
    }else{
        printf(" ");
    }
}

int main(){
    int n, m;
    while(scanf("%d%d", &n, &m) == 2){
        width = n + 2, height = m + 2;
        for(int i = 0; i < height; ++i){
            for(int j = 0; j < width; ++j){
                print(i, j);
            }
            printf("\n");
        }
        printf("\n");
    }
    return 0;
}
