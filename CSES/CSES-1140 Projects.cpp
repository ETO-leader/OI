#include<bits/stdc++.h>
using namespace std;
using lint=long long;
template<typename T,typename Ty>
struct upset{
    map<T,Ty> mp;
    void insert(T v,Ty w){
        if(mp.empty()) goto ad;
        if(v<mp.begin()->first) mp[v]=w;
        else if((--mp.upper_bound(v))->second>=w) return;
        ad:mp[v]=max(mp[v],w);
        stack<T> era;
        auto s=mp.upper_bound(v);
        for(;s!=mp.end()&&s->second<=w;++s) era.push(s->first);
        while(!era.empty()) mp.erase(mp.lower_bound(era.top())),era.pop(); 
    }
    Ty geting(T v){
        if(mp.empty()) return 0;
        if(v<=mp.begin()->first) return 0;
        return (--mp.lower_bound(v))->second;
    }
    Ty back(){
        return (--mp.end())->second;
    }
};
struct act{int s,e,w;};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<act> va(n);
    for(auto&i:va) cin>>i.s>>i.e>>i.w;
    sort(va.begin(),va.end(),[](act&a,act&b){
        return a.s<b.s;});
    upset<int,lint> D;
    for(auto&i:va) D.insert(i.e,D.geting(i.s)+i.w);
    cout<<D.back()<<'\n';
    return 0;
}