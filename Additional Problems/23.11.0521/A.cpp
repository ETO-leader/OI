#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
auto init(int x){
    vector<VI> res(x);
    VI isp(x,true);
    cir(i,2,x){
        if(!isp[i]) continue;
        res[i].push_back(i);
        for(int j=i*2;j<x;j+=i)
            isp[j]=false,res[j].push_back(i);
    }
    return res;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;const int maxw=1e6+7;
    auto plst=init(maxw);
    set<int,greater<int>> px;
    cir(i,0,n){
        int k;cin>>k;px.insert(k);
    }
    for(auto&i:px){
        [&](){
            for(auto&j:plst[i]){
                if(!px.count(j)) return;
            }
            cout<<i<<'\n';
            exit(0);
        }();
    }
    cout<<-1<<'\n';
    return 0;
}
