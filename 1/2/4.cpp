#include <iostream>
#include <string>

using namespace std;

int main(){
    string line;
    while(getline(cin, line), line != "#"){
        string::size_type end = line.length();
        unsigned int result = 0;
        for(int i = 0; i < end; ++i){
            if(line[i] == ' ') continue;
            result += (line[i] - 'A' + 1) * (i + 1);
        }
        cout << result << endl;
    }
    return 0;
}
