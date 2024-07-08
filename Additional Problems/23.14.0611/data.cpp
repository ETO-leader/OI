#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
mt19937 rnd(time(NULL));
int main(){
    cout<<5<<'\n';
    cir(i,0,5){
        const long long n=rnd()%100000+1;
        cout<<n<<' '<<rnd()%n+1<<'\n';
    }
    return 0;
}
