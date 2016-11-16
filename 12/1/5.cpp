#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

struct Node{
    char result[501];
    int len, num;
    bool flag;
};

int N, C, M;
char nums[16];
Node res;
bool vis[5001];

int trans(char c){
    if(c >= '0' && c <= '9'){
        return c - '0';
    }else{
        return c - 'A' + 10;
    }
}

bool bfs(){
    queue<Node> que;
    Node now, next;
    now.len = now.num = 0;
    now.flag = false;
    que.push(now);
    memset(vis, 0, sizeof(vis));
    while(!que.empty()){
        now = que.front();
        que.pop();
        if(now.len > 500) return false;
        if(now.flag && now.num % N == 0){
            res = now;
            return true;
        }
        next = now;
        next.len += 1;
        for(int i = 0; i < M; ++i){
            next.result[now.len] = nums[i];
            next.num = now.num * C + trans(nums[i]);
            next.flag = next.num > 0 ? true : false;
            next.num %= N;
            if(next.num == 0 || !vis[next.num]){
                vis[next.num] = true;
                que.push(next);
            }
        }
    }
    return false;
}

int main(){
    int T; scanf("%d", &T);
    while(T-- > 0){
        scanf("%d%d%d\n", &N, &C, &M);
        scanf("%c", &nums[0]);
        for(int i = 1; i < M; ++i){
            scanf(" %c", &nums[i]);
        }
        sort(nums, nums + M);
        if(N > 0){
            if(bfs()){
                for(int i = 0; i < res.len; ++i){
                    printf("%c", res.result[i]);
                }
                printf("\n");
            }else{
                printf("give me the bomb please\n");
            }
        }else{
            if(nums[0] == '0'){
                printf("0\n");
            }else{
                printf("give me the bomb please\n");
            }
        }
    }
    return 0;
}
