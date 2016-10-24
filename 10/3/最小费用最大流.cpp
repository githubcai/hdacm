/*
    学习最小费用最大流前，需要学习最大流算法。在最大流算法中，没有考虑边的费用问题。在MinCostMaxFlow中，引入了费用的概念：cij表示边(i,j)单位流量的费用。在满足流量=v(f)的同时，并且要求费用最少。
    最小费用最大流的迭代算法：
    1.求出从s到t的最小费用通路(spfa)和通路的最大流量f。
    2.让通路上的边(i,j)流量减去f；添加反向边(j,i)，容量为f，费用为-cost(i,j)。
    3.重复1,2，直到从s到t的流量=v(f)或者再也找不到从s到t的最小费用道路为止。
    最小费用最大流算法还可以解决二分图最优匹配。
*/
const int size = 1102;
const int INF = 0x7fffffff;
struct Edge{
	int to, vol, cost, next;
}e[size*40];
int index[size];
int edgeNum;
int pre[size], pos[size];
int dis[size], que[size*10];
bool vis[size];

void addEdge(int from, int to, int vol, int cost){
	e[edgeNum].to = to;
	e[edgeNum].vol = vol;
    e[edgeNum].cost = cost;
	e[edgeNum].next = index[from];
	index[from] = edgeNum++;
	e[edgeNum].to = from;
	e[edgeNum].vol = 0;
    e[edgeNum].cost = -cost;
	e[edgeNum].next = index[to];
	index[to] = edgeNum++;
}

bool spfa(int s, int t){
	int i;
    memset(pre, -1, sizeof(pre));
	memset(vis, 0, sizeof(vis));
    int head, tail; head = tail = 0;
    for(i = 0; i < size; i++) dis[i] = INF;
    que[tail++] = s;
	pre[s] = s;
	dis[s] = 0;
	vis[s] = 1;
    while(head != tail){
        int now = que[head++];
		vis[now] = 0;
		for(i = index[now]; i != -1; i = e[i].next){
			int adj = e[i].to;
			if(e[i].vol > 0 && dis[now] + e[i].cost < dis[adj]){
				dis[adj] = dis[now] + e[i].cost;
				pre[adj] = now;
				pos[adj] = i;
				if(!vis[adj]){
					vis[adj] = 1;
					que[tail++] = adj;
				}
			}
		}
    }
    return pre[t] != -1;
}

int MinCostFlow(int s, int t, int flow){
	int i;
    int cost = 0;
    flow = 0;
    while(spfa(s, t)){
        int f = INF;
        for(i = t; i != s; i = pre[i])
            if (e[pos[i]].vol < f) f = e[pos[i]].vol;
        flow += f; cost += dis[t] * f;
        for(i = t; i != s; i = pre[i]){
            e[pos[i]].vol -= f;
            e[pos[i] ^ 1].vol += f;
        }
    }
    return cost; // flow是最大流值
}
