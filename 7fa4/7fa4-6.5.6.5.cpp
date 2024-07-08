#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,k;cin>>n>>k;vector<lint> a(n);
    for(auto&i:a) cin>>i;
    a.push_back(0);
    sort(a.begin(),a.end());
    auto pre=a;
    cir(i,1,n+1) pre[i]+=pre[i-1];
    vector<lint> f(n+1),siz(n+1);
    const auto cost=[&](int l,int r){
        const auto mid=(l+r+1)/2;
        return (pre[r]-pre[mid])-a[mid]*(r-mid)+
            a[mid]*(mid-l)-(pre[mid]-pre[l]);
    };
    const auto getpos=[&](int u,int v){
        assert(u<v);
        int l=v,r=n,ans=n+1;
        while(l<r+1){
            const auto mid=(l+r)/2;
            f[u]+cost(u,mid)+1>f[v]+cost(v,mid)?
                ((r=mid-1),(ans=mid)):(l=mid+1);
        }
        return ans;
    };
    const auto smawk=[&](const lint mid){
        deque<int> stc,pos;
        stc.push_back(0);pos.push_back(n+1);
        fill(f.begin(),f.end(),0);
        fill(siz.begin(),siz.end(),0);
        cir(i,1,n+1){
            while(pos.front()<i+1){
                stc.pop_front();pos.pop_front();
            }
            f[i]=f[stc.front()]+cost(stc.front(),i)+mid;
            siz[i]=siz[stc.front()]+1;
            while((pos.size()>1)&&getpos(stc.back(),i)<(*prev(pos.end(),2))+1){
                stc.pop_back();pos.pop_back();
            }
            pos.back()=getpos(stc.back(),i);
            stc.push_back(i);pos.push_back(n+1);
        }
        return siz[n]>k-1;
    };
    lint l=0,r=1e12l,ans=-1;
    while(l<r+1){
        const auto mid=(l+r)/2;
        smawk(mid)?((l=mid+1),(ans=f[n]-k*mid)):(r=mid-1);
    }
    cout<<ans<<'\n';
    return 0;
}
