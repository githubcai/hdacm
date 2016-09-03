#include <iostream>
#include <queue>
#include <stack>
#include <string>
using namespace std;

int main(){
    int n;
    string f, s;
    while(cin >> n >> f >> s){
        int a = 0, b = 0;
        bool flag = true;
        stack<char> st;
        queue<string> que;
        while(b != n){
            if(!st.empty()){
                char temp = st.top();
                if(temp == s[b]){
                    que.push("out");
                    st.pop();
                    ++b;
                    continue;
                }
            }
            if(a != n){
                que.push("in");
                if(f[a] == s[b]){
                    que.push("out");
                    ++b;
                }else{
                    st.push(f[a]);
                }
                ++a;
            }else{
                flag = false;
                break;
            }
        }
        if(flag){
            cout << "Yes." << endl;;
            while(!que.empty()){
                cout << que.front() << endl;;
                que.pop();
            }
        }else{
            cout << "No." << endl;;
        }
        cout << "FINISH" << endl;
    }
    return 0;
}
