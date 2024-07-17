#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;cin>>n;
        vector<lint> a(n);
        for(auto&i:a) cin>>i;
        a.insert(a.begin(),0);
        a.push_back(0);
        vector<int> lf(n+2),rg(n+2),elf(n+2),erg(n+2);
        [&](){
            stack<int> pos;
            for(auto c=-1;auto&i:a) [&](){
                ++c;
                if(pos.empty()) return pos.push(c);
                while(a[pos.top()]>i) pos.pop();
                lf[c]=pos.top();pos.push(c);
            }();
        }();
        [&](){
            stack<int> pos;
            ranges::reverse(a);
            for(auto c=-1;auto&i:a) [&](){
                ++c;
                if(pos.empty()) return pos.push(c);
                while(a[pos.top()]>i) pos.pop();
                rg[n+1-c]=n+1-pos.top();pos.push(c);
            }();
            ranges::reverse(a);
        }();
        [&](){
            cir(i,1,n+1){
                auto u=i-1,v=i+1;
                while((u&&a[u]>a[i])||(v<n+1&&a[v]>a[i])){
                    if(u&&(v>n||a[v]<a[u])) erg[u]=v,u=lf[u];
                    else elf[v]=u,v=rg[v];
                }
            }
        }();
        vector<lint> ans(n+7);
        auto upd=[&](int l,int r,lint w){
            ans[l]+=w;ans[r+1]-=w;
        };
        cir(i,1,n+1){
            upd(lf[i]+1,i-1,a[i]*(i-lf[i]-1)*(rg[i]-i));
            upd(i+1,rg[i]-1,a[i]*(i-lf[i])*(rg[i]-i-1));
            upd(1,lf[i]-1,a[i]*(i-lf[i])*(rg[i]-i));
            upd(rg[i]+1,n,a[i]*(i-lf[i])*(rg[i]-i));
            upd(lf[i],lf[i],a[i]*(i-elf[i]-1)*(rg[i]-i));
            upd(rg[i],rg[i],a[i]*(i-lf[i])*(erg[i]-i-1));
        }
        cir(i,1,n+1) ans[i]+=ans[i-1];
        ans.erase(ans.begin());
        ans.resize(n);
        for(auto&i:ans) cout<<i<<' ';
        cout<<'\n';
    }
    return 0;
}
