#include <cstdio>
#include <cstring>

char pattern[10001], str[1000001];
int next[10001] = {0};

void getNext(){
    for(int i = 1, j = 0; i < strlen(pattern); ++i){
        while(j > 0 && pattern[i] != pattern[j]) j = next[j - 1];
        if(pattern[i] == pattern[j]) ++j;
        next[i] = j;
    }
}

int kmp(){
    int count = 0, nstr = strlen(str), npat = strlen(pattern);
    getNext();
    for(int i = 0, j = 0; i < nstr; ++i){
        while(j > 0 && pattern[j] != str[i]) j = next[j - 1];
        if(str[i] == pattern[j]) ++j;
        if(j == npat){
            ++count;
            j = next[j - 1];
        }
    }
    return count;
}

int main(){
    int N; scanf("%d", &N);
    while(N-- > 0){
        scanf("%s%s", pattern, str);
        printf("%d\n", kmp());
    }
    return 0;
}
