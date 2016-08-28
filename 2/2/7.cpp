#include <cstdio>
#include <cstring>

const unsigned mod[20] = {1, 1, 2, 6, 4, 2, 2, 4, 2, 8, 4, 4, 8, 4, 6, 8, 8, 6, 8, 2};
const int MAX = 100000;

int lastDigit(char *buf){
    int len = strlen(buf), a[MAX];
    if(len == 1){
        return mod[buf[0] - '0'];
    }
    for(int i = 0; i < len; ++i){
        a[i] = buf[len - 1 - i] - '0';
    }

    int ret = 1;
    for(; len; len -= !a[len - 1]){
        ret = ret * mod[a[1] % 2 * 10 + a[0]] % 10;
        for(int c = 0, i = len - 1; i >= 0; --i){
            c = c * 10 + a[i];
            a[i] = c / 5;
            c %= 5;
        }
    }
    return ret;
}

int main(){
    char num[MAX];
    while(scanf("%s", num) != EOF){
        printf("%d\n", lastDigit(num));
    }
    return 0;
}
