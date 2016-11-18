#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int NMAX = 10, MMAX = 10;
int n, pos[NMAX], depth, temp[NMAX];
char str[NMAX][MMAX], dna[] = {'A', 'T', 'C', 'G'};

bool done(){
    for(int i = 0; i < n; ++i){
        if(pos[i] != temp[i]) return false;
    }
    return true;
}

int getH(){
    int res = 0;
    for(int i = 0; i < n; ++i){
        res = max(res, pos[i] - temp[i]);
    }
    return res;
}

bool dfs(int step){
    if(step == depth) return done();
    if(step + getH() > depth) return false;
    int tmp[NMAX];
    for(int i = 0; i < 4; ++i){
        bool flag = false;
        memcpy(tmp, temp, sizeof(temp));
        for(int j = 0; j < n; ++j){
            if(temp[j] == pos[j]) continue;
            if(str[j][temp[j]] == dna[i]){
                ++temp[j];
                flag = true;
            }
        }
        if(flag && dfs(step + 1)) return true;
        if(flag) memcpy(temp, tmp, sizeof(tmp));
    }
    return false;
}

int main(){
    int T; scanf("%d", &T);
    while(T-- > 0){
        scanf("%d", &n);
        depth = 0;
        for(int i = 0; i < n; ++i){
            scanf("%s", str[i]);
            pos[i] = strlen(str[i]);
            depth = max(depth, pos[i]);
        }
        memset(temp, 0, sizeof(temp));
        while(!dfs(0)){
            ++depth;
            memset(temp, 0, sizeof(temp));
        }
        printf("%d\n", depth);
    }
    return 0;
}
