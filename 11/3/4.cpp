#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAX = 1000001;
char A[MAX];
int Next[MAX];

void getNext(char *str, int len){
    Next[0] = 0;
    for(int i = 1, j = 0; i < len; ++i){
        while(j > 0 && str[i] != str[j]) j = Next[j - 1];
        if(str[i] == str[j]) ++j;
        Next[i] = j;
    }
}

int minMaxExpress(char *str, int len, bool flag){
    int i = 0, j = 1, k = 0;
    while(i < len && j < len && k < len){
        int ti = (i + k) % len, tj = (j + k) % len;
        if(str[ti] < str[tj]){
            flag ? j += k + 1 : i += k + 1;
            if(i == j) flag ? ++j : ++i;
            k = 0;
        }else if(str[ti] == str[tj]){
            ++k;
        }else{
            flag ? i += k + 1 : j += k + 1;
            if(i == j) flag ? ++i : ++j;
            k = 0;
        }
    }
    return min(i, j);
}

int main(){
    while(scanf("%s", A) != EOF){
        int lenA = strlen(A);
        getNext(A, lenA);
        int times = 1;
        if(lenA % (lenA - Next[lenA - 1]) == 0){
            times = lenA / (lenA - Next[lenA - 1]);
        }
        int mn = minMaxExpress(A, lenA, true), mx = minMaxExpress(A, lenA, false);
        printf("%d %d %d %d\n", mn + 1, times, mx + 1, times);
    }
    return 0;
}
