#include <cstdio>
#include <cstring>

const int MAX = 100001;
char A[MAX], B[MAX];
int next[MAX];

void getNext(char *str, int slen){
    for(int i = 1, j = 0; i < slen; ++i){
        while(j > 0 && str[i] != str[j]) j = next[j - 1];
        if(str[i] == str[j]) ++j;
        next[i] = j;
    }
}

int kmp(char *str, char *pstr, int slen, int plen){
    int i, j;
    getNext(pstr, slen);
    i = slen > plen ? slen - plen : 0;
    for(j = 0; i < slen; ++i){
        while(j > 0 && pstr[j] != str[i]) j = next[j - 1];
        if(str[i] == pstr[j]) ++j;
    }
    return j;
}

int main(){
    while(scanf("%s%s", A, B) != EOF){
        int lenA = strlen(A), lenB = strlen(B), retA, retB;
        retA = kmp(A, B, lenA, lenB);
        retB = kmp(B, A, lenB, lenA);
        if(retA > retB){
            printf("%s%s\n", A, B + retA);
        }else if(retA == retB){
            if(strcmp(A, B) < 0){
                printf("%s%s\n", A, B + retA);
            }else{
                printf("%s%s\n", B, A + retB);
            }
        }else{
            printf("%s%s\n", B, A + retB);
        }
    }
    return 0;
}
