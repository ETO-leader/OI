#include<bits/stdc++.h>
using namespace std;
using lint=long long;
template<typename T,typename Ty>
struct upset{
    map<T,Ty> mp;
    void insert(T v,Ty w){
        if(mp.empty()) goto ad;
        if(v<=mp.begin()->first) mp[v]=w;
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
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<int> v(n);
    for(auto&i:v) cin>>i;
    upset<int,lint> D;
    for(auto&i:v) D.insert(i,D.geting(i)+1);
    cout<<D.back()<<'\n';
    return 0;
}