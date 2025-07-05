#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;vector<lint> a(n);
    for(auto&x:a) cin>>x;
    map<lint,lint,greater<>> cnt;
    for(auto&x:a) ++cnt[x];
    auto ucnt=0ll;
    priority_queue<lint,vector<lint>,greater<>> q;
    for(auto&[x,y]:cnt){
        const auto uw=ucnt-(int)(q.size())*2;
        const auto c=min(uw,y);
        ucnt+=y;y-=c;
        vector<int> emp;
        cir(i,0,c) emp.emplace_back(x);
        for(auto i=1;(i<y+1)&&(!q.empty());i+=2){
            const auto w=q.top();q.pop();
            if(w<x){
                emp.emplace_back(x);
                if(i<y) emp.emplace_back(x);
            }else{
                emp.emplace_back(w);
                if(i<y&&x*2>w) emp.emplace_back(x*2-w);
            }
        }
        for(auto&x:emp) q.emplace(x);
    }
    auto ans=accumulate(a.begin(),a.end(),0ll);
    while(!q.empty()) ans-=q.top(),q.pop();
    cout<<ans<<'\n';
    return 0;
}
