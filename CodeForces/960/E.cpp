#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
auto checkml(int u){
    cout<<format("? {}",u)<<'\n';
    cout.flush();
    int tp;cin>>tp;
    return tp;
}
auto answer(int u){
    cout<<format("! {}",u)<<'\n';
    cout.flush();
}
class check{
private:
    vector<vector<int>> gr,hx;
    vector<int> dfn,rdfn,rid,fx,ht;
    int cnt;
    auto dfs(int u,int h=0,int f=1)->void{
        dfn[u]=++cnt;rid[dfn[u]]=u;ht[u]=h;
        hx[h].push_back(dfn[u]);fx[u]=f;
        for(auto&i:gr[u]) if(i!=f) dfs(i,h+1,u);
        rdfn[u]=cnt;
    }
    auto ask(int u,int las,int h,int delta,const int sqr,bool spc=false)->void{
        if(checkml(u)){
            auto nhx=h+(int)(sqr/1.2);
            auto lb=ranges::lower_bound(hx[nhx],dfn[u]);
            auto rb=ranges::upper_bound(hx[nhx],rdfn[u]);
            while(lb==rb){
                --nhx;spc=true;
                lb=ranges::lower_bound(hx[nhx],dfn[u]);
                rb=ranges::upper_bound(hx[nhx],rdfn[u]);
            }
            if(!spc) for(auto i=(int)(sqr/1.2+1);i<(int)(sqr*1.3);++i){
                auto nlb=ranges::lower_bound(hx[h+i],dfn[u]);
                auto nrb=ranges::upper_bound(hx[h+i],rdfn[u]);
                if(nlb==nrb) break;
                if(nrb-nlb<rb-lb) lb=nlb,rb=nrb,nhx=h+i;
            }
            if(nhx!=h){
                auto chs=false;
                const auto clb=lb;
                if(rb-lb<sqr+7) for(;lb<rb;++lb){
                    const auto ux=rid[*lb];
                    if(checkml(ux)){
                        ask(ux,u,nhx,nhx-h,sqr,spc);
                        chs=true;
                        break;
                    }
                }
                if(!chs) ask(rid[*clb],u,nhx,nhx-h,sqr,true);
            }else{
                spc=true;
            }
        }else{
            spc=true;
        }
        if(spc&&checkml(u)) throw u;
        if(!checkml(las)) return;
        checkml(u);
        auto cntx=0;
        while(checkml(las)&&cntx<delta+2) ++cntx,checkml(u);
        assert(las==1||cntx<delta+2);
        throw fx[fx[las]];
    }
public:
    auto insert(int u,int v){
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
    auto play(){
        dfs(1);
        #if not defined(ONLINE_JUDGE)
            const auto sqr=3;
        #else
            const auto sqr=50;
        #endif
        try{
            ask(1,1,0,sqr,sqr);
            assert(false);
        }catch(int ans){
            answer(ans);
        }
    }
    check(int n):gr(n+307),hx(n+307),dfn(n+307),rdfn(n+307),rid(n+307),fx(n+307),ht(n+307),cnt(0){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--) [&]{
        int n;cin>>n;check ck(n);
        cir(i,0,n-1){
            int u,v;cin>>u>>v;
            ck.insert(u,v);
        }
        ck.play();
    }();
    return 0;
}
