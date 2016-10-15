/*
分析：由于题目给定的是某一时刻的信息，但是试图描述的却是某一时间段的信息，所以处理的时候将时间点转化为时间段。对于每一个时间段x（每一小时作为一个时间段处理）定义出一个变量 need[x] 表示从1到x时间段一共雇佣了多少员工。则对于题目中所描述的数据能够较好的构图，关键还能够解决雇佣多少人的问题，而如果采用 need[x] 表示x时段工作的员工的人数，虽然能够列出方程但不利于问题的求解。

约定 need[x] 表示x时间段至少要有多少员工在，have[x] 表示x时段有多少人申请工作，lim表示欲招的员工个数。对于题目中给定的信息构图如下：
0 <= need[x] - need[x-1] <= have[x];      // 雇佣的人数少于申请者但不能为负数
need[x] - need[x-8] >= need[x]               // 当x>=8时，该方程成立，否则将出现负数显然不成立
need[x-8+24] - need[i] <= lim - need[x]   // 当x<8时，由于昨天的雇人可以通宵上班，因此这个约束通过反面处理
need[24] - need[0] >= lim                      // 最后24小时内雇佣人应该大于等于lim个人

接下来就是求解什么了，我们要得到一天最少的雇佣人数即 need[24] - need[0] >= M中的M，因为M是一个变量，所以要求解M的最大值。将式子化为 need[0] - need[24] <= -M，M去最大，-M取最小，即求24到0的最短路，再比较 need[0] 是否等于-lim。最后就是要枚举lim，因为该模型只能够判定一个lim是否能够合法，而不能够一次求出最优解，由于最多有1000人，可以采用二分查找来枚举。
*/

#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int NMAX = 26, MMAX = 1000, INF = 0x7fffff;
struct Edge{
    int to, w, next;
};

Edge edge[MMAX];
int head[NMAX], edgeNum, dist[NMAX], cnt[NMAX], verNum;
bool vis[NMAX];
int r[NMAX], t[NMAX];

void init(){
    memset(head, -1, sizeof(head));
    edgeNum = 0;
}

void addEdge(int u, int v, int w){
    Edge e = {v, w, head[u]};
    edge[edgeNum] = e;
    head[u] = edgeNum++;
}

bool spfa(int s){
    queue<int> que;
    memset(vis, 0, sizeof(vis));
    memset(cnt, 0, sizeof(cnt));
    for(int i = 0; i <= verNum; ++i) dist[i] = INF;
    que.push(s);
    dist[s] = 0;
    ++cnt[s];
    while(!que.empty()){
        int u = que.front();
        que.pop();
        vis[u] = false;
        for(int i = head[u]; i != -1; i = edge[i].next){
            int v = edge[i].to;
            if(dist[v] > dist[u] + edge[i].w){
                dist[v] = dist[u] + edge[i].w;
                if(!vis[v]){
                    ++cnt[v];
                    if(cnt[v] > verNum) return false;
                    vis[v] = true;
                    que.push(v);
                }
            }
        }
    }
    return true;
}

int main(){
    int T; scanf("%d", &T);
    while(T-- > 0){
        memset(r, 0, sizeof(r));
        memset(t, 0, sizeof(t));
        for(int i = 1; i < 25; ++i){
            scanf("%d", &t[i]);
        }
        int N; scanf("%d", &N);
        for(int i = 0; i < N; ++i){
            int a; scanf("%d", &a);
            ++r[a + 1];
        }
        int left = 0, right = N;
        int ans = INF;
        while(left <= right){
            int mid = (left + right) / 2;
            init();
            for(int i = 1; i < 25; ++i){
                addEdge(i, i - 1, 0);
                addEdge(i - 1, i, r[i]);
                if(i <= 8){
                    addEdge(i, i + 16, mid - t[i]);
                }else{
                    addEdge(i, i - 8, -t[i]);
                }
            }
            addEdge(24, 0, -mid);
            verNum = 24;
            if(spfa(0)){
                ans = mid;
                right = mid - 1;
            }else{
                left = mid + 1;
            }
        }
        if(ans == INF){
            printf("No Solution\n");
        }else{
            printf("%d\n", ans);
        }
    }
    return 0;
}
