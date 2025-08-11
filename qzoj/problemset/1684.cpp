#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    vector<string> a(n);
    for(auto&i:a) cin>>i;
    vector<vector<string>> f(1<<n,vector<string>(n));
    cir(i,0,n) f[1<<i][i]=a[i];
    static constexpr auto c=251ull; 
    vector<uint64_t> pw(60,1);
    cir(i,1,60) pw[i]=pw[i-1]*c;
    cir(s,0,(1<<n)) cir(i,0,n) if((s>>i)&1){
        auto&cur=f[s][i];
        vector<uint64_t> suf(min<int>(cur.size(),60));
        auto w=(uint64_t)(0);
        cir(i,0,(int)(suf.size())) suf[i]=(w+=cur[(int)(cur.size())-1-i]*pw[i]);
        cir(j,0,n) if(!((s>>j)&1)){
            auto uc=0;
            auto w=(uint64_t)(0);
            cir(p,0,(int)(min(suf.size(),a[j].size()))){
                (w*=c)+=a[j][p];
                if(suf[p]==w) uc=p+1;
            }
            cir(i,uc,(int)(a[j].size())) cur+=a[j][i];
            if(f[s|(1<<j)][j].empty()||f[s|(1<<j)][j].size()>cur.size()||(f[s|(1<<j)][j].size()==cur.size()&&f[s|(1<<j)][j]>cur)){
                f[s|(1<<j)][j]=cur;
            }
            cir(i,uc,(int)(a[j].size())) cur.pop_back();
        }
    }
    auto ans=f[(1<<n)-1][0];
    cir(i,1,n) if(ans.size()>f[(1<<n)-1][i].size()||(ans.size()==f[(1<<n)-1][i].size()&&ans>f[(1<<n)-1][i])) ans=f[(1<<n)-1][i];
    cout<<ans<<'\n';
    return 0;
}
