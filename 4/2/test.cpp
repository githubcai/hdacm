#include<stdio.h>
#include<iostream>
#include<memory>
#include<queue>
#include<string.h>
using namespace std;

char map[105][105];
int dir[4][2] = {0,-1,0,1,-1,0,1,0},n,m,tag[105][105][27];

struct node 
{
	int step,rest,x,y;
};

bool check(node temp)
{
	return (temp.x < n && temp.y < m && temp.x >= 0 && temp.y >= 0 && map[temp.x][temp.y] != '*' && map[temp.x][temp.y] != '#');
}

int bfs(int x,int y)
{
	queue<node>q;
	int rest,ans = 0x7fffffff,t = 0;
	if(map[x][y] == '#')
		rest = 0;
	else
		rest = map[x][y] - 'A' + 1;
	node now = {0,rest,x,y};
	tag[x][y][rest] = 0;
	q.push(now);
	while(!q.empty())
	{
		now = q.front();
		q.pop();
		if(map[now.x][now.y] == '$' && now.step < ans)
		{
			ans = now.step;
			continue;
		}
		for(int i = 0;i < 4;++i)
		{
			node temp = now;
			temp.x += dir[i][0];
			temp.y += dir[i][1];
			if(check(temp) && (map[temp.x][temp.y] > 'Z' || map[temp.x][temp.y] < 'A') && (temp.step < tag[temp.x][temp.y][temp.rest]) && temp.step < ans)
			{
				tag[temp.x][temp.y][temp.rest] = temp.step;
				if(map[temp.x][temp.y] <= '9' && map[temp.x][temp.y] >= '0')
				{
					if(temp.rest)
					{
						temp.rest--;
						q.push(temp);
						temp.rest++;
					}
					temp.step += map[temp.x][temp.y] - '0';	
				}
				q.push(temp);
			}
		}
	}
	return ans;
}

int main()
{
	while(1)
	{
		for(n = 0;;++n)
		{
			scanf("%c",&map[n][0]);
			if(map[n][0] == '\n')
				break;
			int j;
            for(j = 1;;++j)
			{
				scanf("%c",&map[n][j]);
				if(map[n][j] == '\n')
				{
					map[n][j] = 0;
					break;
				}
			}
			m = j;
			if(strcmp(map[n],"--") == 0)
				return 0;
		}
		for(int i = 0;i < n;++i)
			for(int j = 0;j < m;++j)
				for(int k = 0;k < 27;++k)
					tag[i][j][k] = 0x7fffffff;
		int ans = 0x7fffffff;
		for(int i = 0;i < n;++i)			
		{
			for(int j = 0;j < m;++j)
			{
				if(map[i][j] == '#' || (map[i][j] >= 'A' && map[i][j] <= 'Z'))
				{
					int temp = bfs(i,j);
					if(temp < ans)
						ans = temp;
				}
			}
		}
		if(ans == 0x7fffffff)
			printf("IMPOSSIBLE\n");
		else
			printf("%d\n",ans);
	}
	return 0;
}
