#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    vector<vector<pair<int,int>>> p(n);
    auto transform=[&](int t){
        return (
            t/10000*60*60+
            (t%10000)/100*60+
            t%100
        );
    };
    auto numstr=[&](int t){
        if(t<10) return '0'+to_string(t);
        return to_string(t);
    };
    auto retransform=[&](int t){
        return (
            numstr(t/3600)+
            numstr(t%3600/60)+
            numstr(t%60)
        );
    };
    cir(i,0,m){
        int x,t,u;cin>>x>>t>>u;
        p[x-1].emplace_back(transform(t),transform(t)+u);
    }
    for(auto&x:p) sort(x.begin(),x.end());
    static constexpr auto maxt=24*60*60;
    vector<int> f(maxt,_inf),g(maxt,_inf);
    f[transform(60000)]=0;
    cir(i,0,n-1){
        swap(f,g);
        const auto tl=transform(60000)+i*300,tr=transform(60000)+i*600;
        auto ul=0,ur=-1;
        cir(ut,tl,tr+1){
            while(ul<(int)(p[i].size())&&p[i][ul].first<ut-307) ++ul;
            while(ur+1<(int)(p[i].size())&&p[i][ur+1].first<ut+307) ++ur;
            cir(dlt,300,601){
                auto cnt=0;
                cir(ux,ul,ur+1){
                    const auto[l,r]=p[i][ux];
                    cnt+=((ut==l&&ut+dlt==r)||(ut<l&&ut+dlt>r-1)||(ut>l&&ut+dlt<r+1));
                }
                f[ut+dlt]=min(f[ut+dlt],g[ut]+cnt);
            }
        }
        fill(g.begin()+tl,g.begin()+tr+1,_inf);
    }
    const auto ans=*min_element(f.begin(),f.end());
    cout<<ans<<'\n';
    cir(i,0,maxt) if(f[i]==ans){
        cout<<retransform(i)<<'\n';
        break;
    }
    return 0;
}
