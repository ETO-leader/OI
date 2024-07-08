#include<bits/stdc++.h>
using namespace std;
using lint=long double;
using PL=pair<lint,lint>;
vector<PL> Dim,St,ms;
int N,S,M;
void dfs(int u,lint w,lint v){
    if(u==N){ms.push_back({v,w});return;}
    dfs(u+1,w,v);
    if(w+Dim[u].second<=M)
        dfs(u+1,w+Dim[u].second,v+Dim[u].first);
}
lint solve(){
    sort(ms.begin(),ms.end(),[](PL&a,PL&b){
        return a.second>b.second;});
    sort(St.begin(),St.end(),[](PL&a,PL&b){
        return a.first/a.second>b.first/b.second;});
    auto j=0;lint cnt=0,ans=0,lx=0;
    for(auto&i:ms){
        if(j==S){ans=max(ans,cnt+i.first);continue;}
        auto Nx=(M-i.second)-lx;
        if(St[j].second>Nx){
            auto Mi=(St[j].first/St[j].second)*Nx;
            St[j].first-=Mi;St[j].second-=Nx;cnt+=Mi;
            ans=max(ans,cnt+i.first);lx=M-i.second;
            continue;
        }
        cnt+=St[j].first;Nx-=St[j].second;
        St[j]={0,0};++j;
        for(;j<S&&Nx;++j){
            if(Nx>=St[j].second){
                Nx-=St[j].second,cnt+=St[j].first,St[j]={0,0};
                continue;
            }
            auto Mi=(St[j].first/St[j].second)*Nx;
            St[j].first-=Mi;St[j].second-=Nx;cnt+=Mi;
            Nx=0;break;
        }
        lx=M-i.second;
        ans=max(ans,cnt+i.first);
    }
    return ans;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    cin>>S>>N>>M;
    Dim.resize(N);St.resize(S);
    for(auto&i:St) cin>>i.second;
    for(auto&i:St) cin>>i.first;
    for(auto&i:Dim) cin>>i.second;
    for(auto&i:Dim) cin>>i.first;
    dfs(0,0,0);
    cout<<(long long)(round(solve()))<<endl;
    return 0;
}
