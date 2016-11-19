#include <cstdio>

const int INF = 0x7fffffff;
char cube[6][5];
char rdir[24][7] = {
    "BWRYOG", "BRYOWG", "BYOWRG", "BOWRYG",
    "WGRBOY", "WRBOGY", "WBOGRY", "WOGRBY",
    "RGYBWO", "RYBWGO", "RBWGYO", "RWGYBO",
    "YOBRGW", "YBRGOW", "YRGOBW", "YGOBRW",
    "OYBWGR", "OBWGYR", "OWGYBR", "OGYBWR",
    "GRYOWB", "GYOWRB", "GOWRYB", "GWRYOB"
};
int step;
int dir[12][12][2] = {
    {{1, 0}, {1, 1}, {1, 3}, {1, 2}, {0, 0}, {0, 2}, {4, 3}, {4, 1}, {5, 0}, {5, 2}, {2, 0}, {2, 2}},
    {{1, 1}, {1, 3}, {1, 2}, {1, 0}, {4, 3}, {4, 1}, {5, 0}, {5, 2}, {2, 0}, {2, 2}, {0, 0}, {0, 2}},
    {{3, 0}, {3, 1}, {3, 3}, {3, 2}, {0, 1}, {0, 3}, {4, 2}, {4, 0}, {5, 1}, {5, 3}, {2, 1}, {2, 3}},
    {{3, 1}, {3, 3}, {3, 2}, {3, 0}, {4, 2}, {4, 0}, {5, 1}, {5, 3}, {2, 1}, {2, 3}, {0, 1}, {0, 3}},
    {{2, 0}, {2, 1}, {2, 3}, {2, 2}, {}, {}, {}, {}, {}, {}, {}, {}},
    {{2, 1}, {2, 3}, {2, 2}, {2, 0}, {}, {}, {}, {}, {}, {}, {}, {}},
    {{4, 0}, {4, 1}, {4, 3}, {4, 2}, {}, {}, {}, {}, {}, {}, {}, {}},
    {{4, 1}, {4, 3}, {4, 2}, {4, 0}, {}, {}, {}, {}, {}, {}, {}, {}},
    {{0, 0}, {0, 1}, {0, 3}, {0, 2}, {}, {}, {}, {}, {}, {}, {}, {}},
    {{0, 1}, {0, 3}, {0, 2}, {0, 0}, {}, {}, {}, {}, {}, {}, {}, {}},
    {{5, 0}, {5, 1}, {5, 3}, {5, 2}, {}, {}, {}, {}, {}, {}, {}, {}},
    {{5, 1}, {5, 3}, {5, 2}, {5, 0}, {}, {}, {}, {}, {}, {}, {}, {}},
};

int getH(){
    int ret = INF, cnt;
    bool flag;
    for(int k = 0; k < 24; ++k){
        cnt = 0; flag = true;
        for(int i = 0; i < 6 && flag; ++i){
            for(int j = 0; j < 4 && flag; ++j){
                if(cube[i][j] != rdir[k][i]) ++cnt;
                if(cnt >= ret) flag = false;
            }
        }
        if(flag) ret = cnt;
    }
    return ret;
}

bool dfs(int cnt){

}

int main(){
    while(scanf("%s", cube[0]) != EOF){
        for(int i = 1; i < 4; ++i){
            scanf("%s", cube[0] + i);
        }
        for(int i = 1; i < 6; ++i){
            for(int j = 0; j < 4; ++j){
                scanf("%s", cube[i] + j);
            }
        }
        step = 0;
        while(!dfs(0)){
            ++step;
        }
        printf("%d\n", step);
    }
    return 0;
}
