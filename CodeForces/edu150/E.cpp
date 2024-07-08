#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;cin>>n;VI v(n);
        for(auto&i:v) cin>>i,i=n-i;
        lint m;cin>>m;
        VI ord(n),cnx(n+1),pr(n),ne(n);
        iota(pr.begin(),pr.end(),-1);
        iota(ne.begin(),ne.end(),1);
        iota(ord.begin(),ord.end(),0);
        sort(ord.begin(),ord.end(),
            [&](int a,int b){return v[a]>v[b];});
        for(auto&i:ord){
            const int len=ne[i]-pr[i]-1;
            cnx[len]+=v[i]-max((pr[i]>=0?v[pr[i]]:0),
                (ne[i]<n?v[ne[i]]:0));
            if(pr[i]>=0) ne[pr[i]]=ne[i];
            if(ne[i]<n) pr[ne[i]]=pr[i];
        }
        lint ans=0;
        for(int i=n;i;--i){
            const auto all=min(m/i,cnx[i]);
            ans+=all*(i-1);m-=all*i;
            if(m<i&&cnx[i]>all){
                assert(m<i);
                ans+=max<lint>(m-1,0LL);break;
            }
        }
        cout<<ans<<'\n';
    }
    return 0;
}
