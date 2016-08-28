#include <iostream>
#include <string>
#include <map>
#include <array>

using namespace std;

array<unsigned int, 26> count;

int main(){
    string line;
    while(getline(cin, line)){
        count.fill(0);
        for(auto iter = line.begin(); iter != line.end(); ++iter){
            if(*iter >= 'a' && *iter <= 'z'){
                count[*iter - 'a']++;
            }
        }
        for(int i = 0; i < 26; ++i){
            cout << static_cast<char>('a' + i) << ":" << count[i] << endl;
        }
        cout << endl;
    }
    return 0;
}
