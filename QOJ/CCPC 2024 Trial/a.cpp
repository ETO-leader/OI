#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n;cin>>n;
        vector<int64_t> a(n);
        for(auto&i:a) cin>>i;
        vector<int64_t> pre(n),suf(n);
        [&]{
            stack<int> p;
            vector<int64_t> val(n);
            auto cur=0ll;
            p.emplace(-1);
            cir(i,0,n){
                while(p.top()>-1&&a[p.top()]<a[i]) cur-=val[p.top()],p.pop();
                pre[i]=(cur+=(val[i]=a[i]*(i-p.top())));
                p.emplace(i);
            }
        }();
        [&]{
            stack<int> p;
            vector<int64_t> val(n);
            p.emplace(n);
            auto cur=0ll;
            for(auto i=n-1;~i;--i){
                while(p.top()<n&&a[p.top()]<a[i]) cur-=val[p.top()],p.pop();
                suf[i]=(cur+=(val[i]=(a[i]*(p.top()-i))));
                p.emplace(i);
            }
        }();
        for(auto&i:pre) clog<<i<<' ';
        clog<<'\n';
        for(auto&i:suf) clog<<i<<' ';
        clog<<'\n';
        auto ans=min(suf[0],pre[n-1]);
        cir(i,0,n-1) ans=min(ans,pre[i]+suf[i+1]);
        cout<<ans<<'\n';
    }();
    return 0;
}

