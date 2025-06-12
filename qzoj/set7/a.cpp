#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    lint n,x;cin>>n>>x;
    auto sum=0ll;
    cir(i,1,n-1) sum+=n-1-i;
    if(sum<x){
        cout<<-1<<'\n';
    }else{
        vector<bool> ban(n-1);
        cir(i,1,n-1) if(sum-(n-1-i)>x-1){
            sum-=(n-1-i);
            cout<<i<<' ';
            ban[i]=true;
        }
        cout<<n-1<<' ';
        cir(i,1,n-1) if(!ban[i]) cout<<i<<' ';
        cout<<n<<'\n';
    }
    return 0;
}
