#include <cstdio>
#include <cstring>

char A[1005], B[1005];
int Ai[251], Bi[251], result[251], lenAi, lenBi, lenR;

void trans(){
    int table[4] = {1, 10, 100, 1000};
    memset(Ai, 0, sizeof(Ai));
    memset(Bi, 0, sizeof(Bi));
    int lenA = strlen(A), lenB = strlen(B);
    for(int i = lenA - 1, j = 0; i >= 0; --i, ++j){
        int r = j % 4;
        lenAi = j / 4;
        Ai[lenAi] = Ai[lenAi] + table[r] * (A[i] - '0');
    }
    for(int i = lenB - 1, j = 0; i >= 0; --i, ++j){
        int r = j % 4;
        lenBi = j / 4;
        Bi[lenBi] = Bi[lenBi] + table[r] * (B[i] - '0');
    }
}

void cal(){
    memset(result, 0, sizeof(result));
    int c = 0, i;
    for(i = 0; i <= lenAi || i <= lenBi; ++i){
        result[i] = Ai[i] + Bi[i] + c;
        c = result[i] / 10000;
        result[i] = result[i] % 10000;
    }
    if(c != 0){
        result[i] = c;
        lenR = i;
    }else{
        lenR = i - 1;
    }
}

void print(int cnt){
    printf("Case %d:\n", cnt);

    printf("%d", Ai[lenAi]);
    for(int i = lenAi - 1; i >= 0; --i){
        printf("%04d", Ai[i]);
    }
    printf(" + ");

    printf("%d", Bi[lenBi]);
    for(int i = lenBi - 1; i >= 0; --i){
        printf("%04d", Bi[i]);
    }
    printf(" = ");

    printf("%d", result[lenR]);
    for(int i = lenR - 1; i >= 0; --i){
        printf("%04d", result[i]);
    }
    printf("\n");
}

int main(){
    int T, cnt = 0;
    scanf("%d", &T);
    while(T-- > 0){
        scanf("%s%s", A, B);
        trans();
        cal();
        
        ++cnt;
        if(cnt > 1){
            printf("\n");
        }
        print(cnt);
    }
    return 0;
}
