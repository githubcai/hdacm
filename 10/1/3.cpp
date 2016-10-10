#include <iostream>
#include <cstring>
#include <map>
using namespace std;

const int MAX = 27;
int brank[MAX][MAX], grank[MAX][MAX], bres[MAX], gres[MAX], rankl[MAX], n;
char boys[MAX], girls[MAX];

void GaleShapley(){
    memset(bres, -1, sizeof(bres));
    memset(gres, -1, sizeof(gres));
    for(int i = 0; i < n; ++i) rankl[i] = 0;
    while(true){
        bool flag = false;
        for(int i = 0; i < n; ++i){
            if(bres[i] == -1){
                flag = true;
                int girl = brank[i][rankl[i]++];
                if(gres[girl] == -1){
                    bres[i] = girl;
                    gres[girl] = i;
                }else{
                    if(grank[girl][i] < grank[girl][gres[girl]]){
                        bres[gres[girl]] = -1;
                        gres[girl] = i;
                        bres[i] = girl;
                    }
                }
            }
        }
        if(!flag) break;
    }
} 

int main(){
    int T; cin >> T;;
    for(int t = 0; t < T; ++t){
        cin >> n;
        string name;
        map<char, int> mpBoys, mpGirls;
        for(int i = 0; i < n; ++i){
            cin >> name;
            mpBoys[name[0]] = 1;
        }
        int pos = 0;
        for(auto iter = mpBoys.begin(); iter != mpBoys.end(); ++iter){
            iter->second = pos;
            boys[pos++] = iter->first;
        }
        for(int i = 0; i < n; ++i){
            cin >> name;
            mpGirls[name[0]] = 1;
        }
        pos = 0;
        for(auto iter = mpGirls.begin(); iter != mpGirls.end(); ++iter){
            iter->second = pos;
            girls[pos++] = iter->first;
        }
        for(int i = 0; i < n; ++i){
            cin >> name;
            int bpos = mpBoys[name[0]];
            for(int j = 0; j < n; ++j){
                brank[bpos][j] = mpGirls[name[j + 2]];
            }
        }
        for(int i = 0; i < n; ++i){
            cin >> name;
            int gpos = mpGirls[name[0]];
            for(int j = 0; j < n; ++j){
                grank[gpos][mpBoys[name[j + 2]]] = j;
            }
        }
        GaleShapley();
        if(t > 0) cout << endl;
        for(int i = 0; i < n; ++i){
            cout << boys[i] << " " << girls[bres[i]] << endl;
        }
    }
    return 0;
}
