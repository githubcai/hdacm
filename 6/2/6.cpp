#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>
using namespace std;

struct Bus{
    char name[21];
    int x, y;
};

struct Node{
    int v, length;
};

const int MAX = 5102, INF = 0x7fffff;
int table[8] = {5120, 2560, 1280, 640, 320, 160, 80, 40};
int dist[MAX], verNum;
bool used[MAX];
vector<Node> maze[MAX];
Bus buses[MAX];

void trans(char *c, int x, int y, int *rx, int *ry){
    *rx = x, *ry = y;
    for(int i = 0; i < 8; ++i){
        switch(c[i]){
            case '0':{
                break;
            }
            case '1':{
                *ry += table[i];
                break;
            }
            case '2':{
                *rx += table[i];
                break;
            }
            case '3':{
                *rx += table[i];
                *ry += table[i];
                break;
            }
        }
    }
}

void init(){
    for(int i = 0; i < MAX; ++i){
        maze[i].clear();
    }
}

int position(char *c){
    for(int i = 0; i < verNum; ++i){
        if(strcmp(buses[i].name, c) == 0) return i + 1;
    }
    return -1;
}

double calDist(int sx, int sy, int ex, int ey){
    return sqrt((sx - ex) * (sx - ex) + (sy - ey) * (sy - ey));
}

void Dijkstra(int v){
    memset(used, 0, sizeof(used));
    for(int i = 0; i < verNum; ++i){
        dist[i] = INF;
    }
    for(auto iter = maze[v].begin(); iter != maze[v].end(); ++iter){
        dist[iter->v] = iter->length;
    }
    used[v] = true;
    for(int i = 1; i < verNum; ++i){
        int mark, tMin = INF;
        for(int j = 0; j < verNum; ++j){
            if(dist[j] < tMin && !used[j]){
                mark = j;
                tMin = dist[j];
            }
        }
        used[mark] = true;
        for(auto iter = maze[mark].begin(); iter != maze[mark].end(); ++iter){
            if(!used[iter->v] && dist[iter->v] > dist[mark] + iter->length){
                dist[iter->v] = dist[mark] + iter->length;
            }
        }
    }
}

int main(){
    int T;
    scanf("%d", &T);
    while(T-- > 0){
        char Start[9], End[9];
        int sx, sy, ex, ey, startx, starty, endx, endy;
        scanf("%s %d %d", Start, &sx, &sy);
        scanf("%s %d %d", End, &ex, &ey);
        trans(Start, sx, sy, &startx, &starty);
        trans(End, ex, ey, &endx, &endy);
    
        scanf("%d", &verNum);
        for(int i = 0; i < verNum; ++i){
            scanf("%s %d %d", buses[i].name, &buses[i].x, &buses[i].y);
        }
        
        init();
        int m; scanf("%d", &m);
        for(int i = 0; i < m; ++i){
            int line = verNum + i + 1, K;
            scanf("%d", &K);
            for(int j = 0; j < K; ++j){
                char temp[21]; scanf("%s", temp);
                int pos; pos = position(temp);
                Node node = {pos, 1};
                maze[line].push_back(node);
                node.v = line;
                maze[pos].push_back(node);
            }
        }
        if(calDist(startx, starty, endx, endy) <= 2000.0){
            printf("walk there\n");
            continue;
        }
        bool flag = false;
        for(int i = 0; i < verNum; ++i){
            double temp = calDist(startx, starty, buses[i].x, buses[i].y);
            if(temp <= 1000.0){
                Node node = {i + 1, 0};
                maze[0].push_back(node);
                node.v = 0;
                maze[i + 1].push_back(node);
                flag = true;
            }
            temp = calDist(endx, endy, buses[i].x, buses[i].y);
            if(temp <= 1000.0){
                Node node = {i + 1, 0};
                maze[verNum + m + 1].push_back(node);
                node.v = verNum + m + 1;
                maze[i + 1].push_back(node);
                flag = true;
            }
        }
        if(!flag){
            printf("take a taxi\n");
            continue;
        }
        verNum += 2 + m;
        Dijkstra(0);
        if(dist[verNum - 1] == INF){
            printf("take a taxi\n");
        }else{
            printf("%d\n", dist[verNum - 1] / 2);
        }
    }
    return 0;
}
