#include <cstdio>

const int MAX = 5843;
int table[MAX];

int min(int *pos, int &m){
    int prime[] = {2, 3, 5, 7}, p = 0;
    m = table[pos[0]] * 2;
    for(int i = 1; i < 4; ++i){
        int temp = table[pos[i]] * prime[i];
        if(m > temp){
            m = temp;
            p = i;
        }
    }
    return p;
}

int init(){
    table[1] = 1;
    int pos[] = {1, 1, 1, 1}, prime[] = {2, 3, 5, 7};
    for(int i = 2; i < MAX;){
        int p, temp;
        p = min(pos, temp);
        if(temp > table[i - 1]){
            table[i++] = temp; 
        }
        ++pos[p];
    }
}

int main(){
    init();
    int n;
    char suffix[][3] = {"th", "st", "nd", "rd"};
    while(scanf("%d", &n) == 1 && n != 0){
        int i = n % 10;
        if(!((i == 1 && n % 100 != 11) || (i == 2 && n % 100!= 12) || (i == 3 && n % 100 != 13))){
            i = 0;
        }
        printf("The %d%s humble number is %d.\n", n, suffix[i], table[n]);
    }
    return 0;
}
