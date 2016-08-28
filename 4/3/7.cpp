#include <cstdio>
#include <stack>
#include <cctype>
#include <cstring>
using namespace std;

struct Node{
    int sum, plusNum;
};

const int MAX = 1000;
char input[MAX + 1];
int pos;

char Precede(char a, char b){
    char pre[][5] = {
        {'>', '>', '<', '>', '>'},
        {'<', '0', '<', '>', '0'},
        {'<', '<', '<', '=', '0'},
        {'>', '>', '0', '>', '>'},
        {'<', '0', '<', '0', '='}
    };
    int i, j;
    switch(a){
        case '+': i = 0; break;
        case ',': i = 1; break;
        case '(': i = 2; break;
        case ')': i = 3; break;
        case '#': i = 4; break;
    }
    switch(b){
        case '+': j = 0; break;
        case ',': j = 1; break;
        case '(': j = 2; break;
        case ')': j = 3; break;
        case '#': j = 4; break;
    }
    return pre[i][j];
}

Node Operate(const Node &a, char theta, const Node &b){
    Node result;
    switch(theta){
        case '+':{
            result.sum = a.sum + b.sum;
            result.plusNum = a.plusNum + b.plusNum + 1;
            break;
        }
        case ',':{
            result.sum = a.sum > b.sum ? a.sum : b.sum;
            result.plusNum = a.plusNum + b.plusNum + (a.sum > b.sum ? a.plusNum : b.plusNum);
        }
    }
    return result;
}

int getNext(int *n){
    if(!isdigit(input[pos])){
        if(input[pos] == 'M'){
            pos += 3;
            *n = input[pos++];
        }else if(input[pos] == '#'){
            *n = input[pos];
        }else{
            *n = input[pos++];
        }
        return 1;
    }
    *n = 0;
    while(isdigit(input[pos])){
        *n = *n * 10 + (input[pos++] - '0');
    }
    return 0;
}

Node EvaluateExpression(){
    stack<char> OPTR;
    stack<Node> OPND;
    OPTR.push('#');
    int c;
    char x = OPTR.top();
    int flag = getNext(&c);
    while(c != '#' || x != '#'){
        if(flag == 0){
            Node p = {c, 0};
            OPND.push(p);
            flag = getNext(&c);
        }else{
            x = OPTR.top();
            switch(Precede(x, c)){
                case '<':{
                    OPTR.push(c);
                    flag = getNext(&c);
                    break;
                }
                case '=':{
                    OPTR.pop();
                    flag = getNext(&c);
                    break;
                }
                case '>':{
                    char theta = OPTR.top();
                    OPTR.pop();
                    Node a, b;
                    b = OPND.top(), OPND.pop();
                    a = OPND.top(), OPND.pop();
                    OPND.push(Operate(a, theta, b));
                    break;
                }
            }
        }
        x = OPTR.top();
    }
    Node p = OPND.top();
    return p;
}

int main(){
    int T;
    scanf("%d", &T);
    while(T-- > 0){
        pos = 0;
        scanf("%s", input);
        int len = strlen(input);
        input[len] = '#';
        Node p = EvaluateExpression();
        printf("%d %d\n", p.sum, p.plusNum);
    }
    return 0;
}
