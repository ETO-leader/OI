#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,ai;cin>>n>>m;
    multiset<int> chs;
    cir(i,0,n) cin>>ai,chs.insert(ai);
    cir(i,0,m){
        int pi;cin>>pi;
        auto lb=chs.upper_bound(pi);
        if(lb==chs.begin()) cout<<-1<<'\n';
        else cout<<(*(--lb))<<'\n',chs.erase(lb);
    }
    return 0;
}