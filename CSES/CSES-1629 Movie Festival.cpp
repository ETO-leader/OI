#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using PI=pair<int,int>;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,cnt=0;cin>>n;vector<PI> vp(n);
    for(auto&i:vp) cin>>i.first>>i.second;
    sort(vp.begin(),vp.end(),
        [](PI&a,PI&b){return a.second<b.second;});
    int le=0;
    for(auto&i:vp) if(i.first>=le) ++cnt,le=i.second;
    cout<<cnt<<'\n';
    return 0;
}