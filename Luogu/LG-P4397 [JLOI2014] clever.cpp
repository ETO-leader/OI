#include<bits/stdc++.h>
#define cir(i,a,b) for(lint i=a;i<b;++i)
#define _cir(i,a,expr) for(lint i=a;(expr);++i)
using namespace std;
using lint=long long;
vector<int> P;
void init_pr(int x){
    vector<bool> isnp(x);P.clear();
    cir(i,2,x){
        if(isnp[i]) continue;
        for(lint j=1LL*i*i;j<x;j+=i) isnp[j]=true;
        P.push_back(i);
    }
}
set<lint> ans;
bool bfck(int x){
    if(x==1) return false;
    _cir(i,2,i*i<=x) if(!(x%i)) return false;
    return true;
}
bool dfs(lint sum,lint x,lint ns){
    if(sum==1) return ans.insert(ns),true;
    if(bfck(sum-1)&&sum>P[x]) ans.insert(ns*(sum-1));
    _cir(i,x,P[i]*P[i]<=sum){
        lint p=P[i],s=P[i]+1;
        for(;s<=sum;p*=P[i],s+=p) if(!(sum%s)) 
            dfs(sum/s,i+1,ns*p);
    }
    return true;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int s;init_pr(114514+7);
    while(cin>>s){
        ans.clear();dfs(s,0,1);
        cout<<ans.size()<<'\n';
        for(auto i:ans) cout<<i<<' ';
        if(!ans.empty()) cout<<'\n';
    }
    return 0;
}