#include <cstdio>
#include <cstring>

const int MAX = 100000;
char magic[MAX][21], cont[MAX][81];
int leng;

int main(){
    leng = 0;
    while(true){
        char temp[105];
        gets(temp);
        int i = 0, j;
        if(temp[i] == '@') break;
        for(j = 0, i = 1; temp[i] != ']'; ++i, ++j){
            magic[leng][j] = temp[i];
        }
        magic[leng][j] = '\0';
        for(j = 0, i += 2; temp[i] != '\0'; ++i, ++j){
            cont[leng][j] = temp[i];
        }
        cont[leng][j] = '\0';
        ++leng;
    }
    int N;
    scanf("%d\n", &N);
    while(N-- > 0){
        char temp[105];
        gets(temp);
        if(temp[0] == '['){
            int l = strlen(temp);
            temp[l - 1] = '\0';
            int i;
            for(i = 0; i < leng; ++i){
                if(strcmp(magic[i], temp + 1) == 0){
                    break;
                }
            }
            if(i == leng){
                printf("what?\n");
            }else{
                printf("%s\n", cont[i]);
            }
        }else{
            int i;
            for(i = 0; i < leng; ++i){
                if(strcmp(cont[i], temp) == 0){
                    break;
                }
            }
            if(i == leng){
                printf("what?\n");
            }else{
                printf("%s\n", magic[i]);
            }
        }
    }
    return 0;
}
