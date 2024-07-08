#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
template<const bool rev>
auto dfs(int w,const int logx,vector<bool>&stx){
    if(stx[w]) return;
    stx[w]=true;
    cir(i,0,logx+1) if((!(w&(1<<i)))^rev){
        dfs<rev>(w^(1<<i),logx,stx);
    }
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n,q;cin>>n>>q;
        const int logx=sizeof(int)*8ul-__builtin_clz(n);
        int ans=0;
        vector<bool> stx(1<<(logx+1)),sub(1<<(logx+1));
        cir(qx,0,q){
            int x;cin>>x;(x+=ans)%=n;
            auto ansi=(1<<(logx+1))-1;
            for(auto i=logx;~i;--i){
                if((x&(1<<i))&&stx[ansi^(1<<i)]){
                    ansi^=(1<<i);
                }
            }
            ans=max(ans,x-(ansi&x));
            ansi=0;
            for(int i=logx;~i;--i){
                if((!(x&(1<<i)))&&sub[ansi^(1<<i)]){
                    ansi^=(1<<i);
                }
            }
            ans=max(ans,(ansi|x)-x);
            dfs<false>(x,logx,stx);
            dfs<true>(x,logx,sub);
            cout<<ans<<' ';
        }
        cout<<'\n';
    }
    return 0;
}
