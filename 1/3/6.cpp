#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int n;
    while(cin >> n, n != 0){
        vector<int> a, b;
        for(int i = 0; i < n; ++i){
            int j;
            cin >> j;
            a.push_back(j);
        }
        for(int i = 0; i < n; ++i){
            int j;
            cin >> j;
            b.push_back(j);
        }
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());

        int sumA = 0, sumB = 0;
        for(int i = 0; i < n; ++i){
            if(a[i] > b[i]){
                sumA += 2;
            }else if(a[i] == b[i]){
                sumA += 1;
                sumB += 1;
            }else{
                sumB += 2;
            }
        }

        cout << sumA << " vs " << sumB << endl;
    }
    return 0;
}
