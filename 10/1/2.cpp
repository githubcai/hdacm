#include <string>
#include <cstring>
#include <iostream>
#include <map>
using namespace std;

const int MAX = 501;
string boys[MAX], girls[MAX];
int n, brank[MAX][MAX], grank[MAX][MAX], bres[MAX], gres[MAX], rankl[MAX];

void GaleShapley(){
    memset(bres, 0, sizeof(bres));
    memset(gres, 0, sizeof(gres));
    for(int i = 1; i <= n; ++i) rankl[i] = 1;
    while(true){
        bool flag = false;
        for(int i = 1; i <= n; ++i){
            if(bres[i] == 0){
                flag = true;
                int girl = brank[i][rankl[i]++];
                if(gres[girl] == 0){
                    bres[i] = girl;
                    gres[girl] = i;
                }else if(grank[girl][i] < grank[girl][gres[girl]]){
                    bres[gres[girl]] = 0;
                    gres[girl] = i;
                    bres[i] = girl;
                }
            }
        }
        if(!flag) break;
    }
}

int main(){
    string name;
    while(cin >> n){
        map<string, int> mpBoys, mpGirls;
        for(int i = 0, bpos = 1; i < n; ++i, ++bpos){
            cin >> name;
            boys[bpos] = name;
            mpBoys[name] = bpos;
            for(int j = 1, gpos = 1; j <= n; ++j, ++gpos){
                cin >> name;
                if(mpGirls[name] == 0){
                    girls[gpos] = name;
                    mpGirls[name] = gpos;
                }
                brank[bpos][j] = mpGirls[name];
            }
        }
        for(int i = 0; i < n; ++i){
            cin >> name;
            int pos = mpGirls[name];
            for(int j = 1; j <= n; ++j){
                cin >> name;
                grank[pos][mpBoys[name]] = j;
            }
        }
        GaleShapley();
        for(int i = 1; i <= n; ++i){
            cout << boys[i] << " " << girls[bres[i]] << endl;
        }
        cout << endl;
    }
    return 0;
}
