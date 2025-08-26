#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("matrix.in");
ofstream ouf("matrix.out");
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n,m;inf>>n>>m;
    vector<int> p(n),x(n),v(n);
    cir(i,0,n){
        inf>>p[i]>>v[i];
        x[i]=i;
    }
    auto lasans=0;
    cir(i,0,m){
        int xl,yl,xr,yr,c;inf>>xl>>yl>>xr>>yr>>c;
        xl^=lasans;
        xr^=lasans;
        yl^=lasans;
        yr^=lasans;
        c^=lasans;
        --xl;--xr;
        const auto sz=(int)(p.size());
        const auto bl=lower_bound(x.begin(),x.end(),xl)-x.begin();
        const auto br=upper_bound(x.begin(),x.end(),xr)-x.begin();
        auto u=bl;
        for(;u+4<br;u+=4){
            v[u]-=(yl-1<p[u]&&p[u]<yr+1)*c;
            v[u+1]-=(yl-1<p[u+1]&&p[u+1]<yr+1)*c;
            v[u+2]-=(yl-1<p[u+2]&&p[u+2]<yr+1)*c;
            v[u+3]-=(yl-1<p[u+3]&&p[u+3]<yr+1)*c;
        }
        for(;u<br;++u) v[u]-=(yl-1<p[u]&&p[u]<yr+1)*c;
        const auto nlas=(i?lasans:n);
        lasans=nlas;
        u=bl;
        for(;u+4<br;u+=4){
            lasans-=(v[u]<0)+(v[u+1]<0)+(v[u+2]<0)+(v[u+3]<0);
        }
        for(;u<br;++u) lasans-=(v[u]<0);
        if(lasans!=nlas){
            vector<int> ban;
            cir(i,0,n) if(v[i]<0) ban.emplace_back(i);
            reverse(ban.begin(),ban.end());
            for(auto&i:ban){
                x.erase(x.begin()+i);
                v.erase(v.begin()+i);
                p.erase(p.begin()+i);
            }
        }
        ouf<<lasans<<'\n';
    }
    return 0;
}
