#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class interactor{
public:
    constexpr auto ask(vector<lint> x) const{
        print(cout,"{} ",x.size());
        for(auto&i:x) print(cout,"{} ",i);
        println(cout,"");
        cout.flush();
        int res;cin>>res;
        return res;
    }
    constexpr auto accepted(int _TResult){
        return _TResult==-1;
    }
} interact;
static constexpr auto maxq=5;
static constexpr auto maxlen=(int)(1e4);
static constexpr auto lim=10004205361450474ll;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    function<lint(int,int)> dfs; 
    function<vector<lint>(int,lint)> divide;
    function<void(int,lint)> ask;
    vector<unordered_map<int,lint>> f(maxq+1);
    divide=[&](int c,lint l){
        vector<lint> res;
        const auto q=min<lint>(maxlen,l);
        auto cur=l-1;
        if(c>1) cir(i,0,q+1) res.emplace_back(cur+=dfs(c-1,min<lint>(cur+1,maxlen))+1);
        else cir(i,0,q+1) res.emplace_back(++cur);
        return res;
    };
    dfs=[&](int c,int q){
        if(c==1) return (lint)(q);
        if(f[c].count(q)) return f[c][q];
        return f[c][q]=divide(c,q).back()-q;
    };
    ask=[&](int c,lint l){
        if(c==1){
            auto qs=vector<lint>();
            cir(i,0,min<lint>(l,maxlen)) qs.emplace_back(l+i);
            while(qs.back()>lim) qs.pop_back();
            const auto p=interact.ask(qs);
            if(interact.accepted(p)) return;
            abort();
        }
        auto qs=divide(c,l);
        qs.pop_back();
        while(qs.back()>lim) qs.pop_back();
        const auto p=interact.ask(qs);
        if(interact.accepted(p)) return;
        qs.emplace(qs.begin(),l-1);
        return ask(c-1,qs[p]+1);
    };
    println(cerr,"max-range = {}",dfs(maxq,1));
    ask(maxq,1);
    return 0;
}
