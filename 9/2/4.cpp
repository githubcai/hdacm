#include <cstdio>
#include <stack>
#include <cstring>
using namespace std;

struct Node{
    int num, plusNum;
};

const int MAX = 1005;
char table[5][5] = {
    '>', '>', '<', '>', '>',
    '<', 'x', '<', '>', 'x',
    '<', '<', '<', '=', 'x',
    '>', '>', 'x', '>', '>',
    '<', 'x', '<', 'x', '=',
};
char input[MAX];

char getPriority(char now, char next){
    int x, y;
    switch(now){
    case '+': x = 0; break;
    case ',': x = 1; break;
    case '(': x = 2; break;
    case ')': x = 3; break;
    case '#': x = 4; break;
    }
    switch(next){
    case '+': y = 0; break;
    case ',': y = 1; break;
    case '(': y = 2; break;
    case ')': y = 3; break;
    case '#': y = 4; break;
    }
    return table[x][y];
}

Node cal(Node a, Node b, char oper){
    Node temp;
    switch(oper){
    case '+':
        temp.num = a.num + b.num;
        temp.plusNum = a.plusNum + b.plusNum + 1;
        break;
    case ',':
        temp.num = a.num > b.num ? a.num : b.num;
        temp.plusNum = (a.num > b.num ? a.plusNum : b.plusNum) + a.plusNum + b.plusNum;
        break;
    }
    return temp;
}

int main(){
    int T; scanf("%d", &T);
    while(T-- > 0){
        scanf("%s", input);
        int leng = strlen(input);
        input[leng] = '#';
        stack<char> operS;
        stack<Node> numS;
        operS.push('#');
        for(int i = 0; i <= leng; ++i){
            if(input[i] >= '0' && input[i] <= '9'){
                int temp = input[i++] - '0';
                while(input[i] >= '0' && input[i] <= '9'){
                    temp = temp * 10 + input[i++] - '0';
                }
                --i;
                Node node = {temp, 0};
                numS.push(node);
            }else{
                if(input[i] == 'M'){
                    i += 3;
                }
                char topTemp = operS.top();
                char temp = getPriority(topTemp, input[i]);
                switch(temp){
                case '<':
                    operS.push(input[i]);
                    break;
                case '>':
                    Node a, b;
                    b = numS.top(), numS.pop();
                    a = numS.top(), numS.pop();
                    numS.push(cal(a, b, topTemp));
                    operS.pop();
                    --i;
                    break;
                case '=':
                    operS.pop();
                    break;
                }
            }
        }
        printf("%d %d\n", numS.top().num, numS.top().plusNum);
    }
    return 0;
}
