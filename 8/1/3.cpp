#include <cstdio>

double sum[200];
int pos;

int main(){
    int n;
    while(scanf("%d", &n) == 1){
        char c = getchar();
        if(n == 0 && c == '\n') break;
        pos = 0; sum[pos] = n;
        char op;
        while(true){
            scanf("%c %d", &op, &n);
            switch(op){
                case '+': sum[++pos] = n; break;
                case '-': sum[++pos] = -n;break;
                case '*': sum[pos] *= n; break;
                case '/': sum[pos] /= n; break;
            }
            c = getchar();
            if(c == '\n') break;
        }
        double result = 0;
        for(int i = 0; i <= pos; ++i){
            result += sum[i];
        }
        printf("%.2lf\n", result);
    }
    return 0;
}
