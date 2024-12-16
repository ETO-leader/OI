#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,h;cin>>n>>h;
    vector<tuple<int,int,int>> rx;
    unordered_map<int,list<int>> wx;
    vector<pair<int,int>> lst;
    cir(i,0,n){
        int w;cin>>w;wx[w].emplace_back(i);
        rx.emplace_back(w,w,n+7);
        const auto sw=w;w/=2;
        while(w) rx.emplace_back(w,sw,-i),w/=2;
        lst.emplace_back(sw,-i);
    }
    sort(rx.begin(),rx.end());
    reverse(rx.begin(),rx.end());
    vector<int> ans(n);
    for(auto&[w,sw,c]:rx){
        if(!h) break;
        while(!wx[w].empty()){
            if(!h) break;
            const auto u=wx[w].front();
            ++ans[u];
            wx[w].pop_front();
            --h;
        }
        if(c>n+3) continue;
        if(!h) break;
        ++ans[-c];
        --h;
    }
    const auto adx=h/n;
    h%=n;
    sort(lst.begin(),lst.end());
    reverse(lst.begin(),lst.end());
    for(auto&[sw,c]:lst){
        if(!h) break;
        ++ans[-c];
        --h;
    }
    for(auto&i:ans) cout<<i+adx<<' ';
    cout<<'\n';
    return 0;
}
