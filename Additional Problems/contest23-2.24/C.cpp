#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int x,n;cin>>x>>n;unordered_set<int> a;
    cir(i,0,n){
        int w;cin>>w;a.insert(w);
    }
    vector<int> ax;int p=x;
    for(;a.count(p);--p);
    ax.push_back(p);p=x;
    for(;a.count(p);++p);
    ax.push_back(p);
    if(x-ax[0]==ax[1]-x){
        cout<<ax[0]<<'\n';
    }else{
        cout<<(x-ax[0]<ax[1]-x?ax[0]:ax[1])<<'\n';
    }
    return 0;
}
