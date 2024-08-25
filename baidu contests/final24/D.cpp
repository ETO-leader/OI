#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--) [&](){
        int n,q;cin>>n>>q;string s;cin>>s;
        const auto m=n*2;
        basic_string w(n,0ll);
        for(auto&i:w) cin>>i;
        s+=s;w+=w;
        for(auto&i:s) i-='A';
        vector<vector<int>> pos(26);
        cir(i,0,m){
            pos[s[i]].push_back(i);
        }
        vector<int> nxt(m+2);nxt[m]=m+1;nxt[m+1]=m+1;
        for(auto p=m-1;~p;--p){
            if(pos[s[p]].back()==p){
                nxt[p]=p+1;
            }else{
                const auto fd=*upper_bound(pos[s[p]].begin(),pos[s[p]].end(),p);
                nxt[p]=fd+1;
            }
        }
        constexpr auto ups=23;
        vector up(ups,vector<int>(m+2));
        up[0]=nxt;
        cir(i,0,ups) up[i][m+1]=m+1;
        cir(i,1,ups) cir(u,0,m+1) up[i][u]=up[i-1][up[i-1][u]];
        auto fnd=[&](int u,int r,int p){
            cir(c,0,26){
                if(u+1>p) break;
                for(auto i=ups-1;~i;--i) if(up[i][u]<p+1) u=up[i][u];
                if(nxt[u]<r+2) return u;
                if(u==p) break;
                ++u;
            }
            return u;
        };
        cir(i,0,q){
            int op;cin>>op;
            if(op==1){
                int p,wx;cin>>p>>wx;--p;
                w[p]=wx;
                w[p+n]=wx;
            }else{
                int l,r;cin>>l>>r;--l;--r;
                if(r<l) r+=n;
                auto ans=0ll;
                cir(i,0,26){
                    if(pos[i].empty()) continue;
                    auto las=upper_bound(pos[i].begin(),pos[i].end(),r);
                    if(las==pos[i].begin()) continue;
                    las=prev(las);
                    if(*las<l) continue;
                    auto px=fnd(l,r,*las);
                    ans+=(px==*las||nxt[px]>r+1)*w[*las];
                }
                cout<<ans<<'\n';
            }
        }
    }();
    return 0;
}
