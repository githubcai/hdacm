#include <cstdio>

char input[1001];

int main(){
    while(scanf("%s", input) != EOF){
        int count = 0;
        for(int i = 0; input[i] != 'B'; ++i){
            if(input[i] == '('){
                ++count;
            }else{
                --count;
            }
        }
        printf("%d\n", count);
    }
    return 0;
}
