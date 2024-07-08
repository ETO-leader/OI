#include<bits/stdc++.h>
using namespace std;
int main(int argc,char*argv[]){
    int n=atoi(argv[1]);
    cout<<n<<'\n';
    mt19937 rnd(time(nullptr));
    for(int i=0;i<n;++i) cout<<(rnd()&1)+1<<' ';
    cout<<'\n';
}
