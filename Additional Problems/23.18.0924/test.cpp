#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr int MOD=998244353;
using __int=__int128;
istream&operator>>(istream&is,__int&p){
    string s;is>>s;p=0;__int v=1;
    for(auto&i:s) i=='-'?(v*=-1):(p*=10)+=(i-'0');
    return p*=v,is;
}
ostream&operator<<(ostream&os,__int p){
    if(p<0) os<<'-',p=-p;
    if(p>9) os<<(p/10);
    return os<<(int)(p%10);
}
class pairhash{
public:
    auto operator()(const pair<int,int>&p) const{
        size_t pf=p.first,ps=p.second;
        return (pf^(pf<<7))|(ps>>6)
            &(pf|ps|((pf+ps)<<5))
            ^((pf<<12)|(ps>>8));
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    freopen("fire.in","r",stdin);
    freopen("fire.ans","w",stdout);
    __int n,t;cin>>n>>t;
    if(n==1){
        //∑4k^2+4
        cout<<(t*(t+1)*(t*2+1)/6)*8%MOD<<'\n';
    }else if(t<101){
        unordered_map<pair<int,int>,int,pairhash> mp;
        int cnx=0;
        cir(i,0,n){
            int x,y;cin>>x>>y;
            mp[{x,y}]=-1;
            cir(w,1,t+1){
                cir(nx,x-w,x+w+1) cir(ny,y-w,y+w+1){
                    if(!(nx==x-w||ny==y-w||nx==x+w||ny==y+w))
                        continue;
                    ++cnx;
                    auto&x=mp[{nx,ny}];
                    if(!x) x=w;
                    else x=min(x,w);
                }
            }
        }
        __int ans=0;
        for(auto&[x,y]:mp) if(y>0) ans+=y;
        cout<<ans%MOD<<'\n';
    }else{
        int x,y,u,v;cin>>x>>y>>u>>v;
        if(x>u) swap(x,y);
        if(y>v) swap(y,v);
        __int ans=0;
        cir(w,1,t+1){
            if(x+w<u-w||y+w<v-w){
                ans+=(__int)(16)*w*w%MOD;
                continue;
            }
            int mrga=(x+w-(u-w));
            int mrgb=(y+w-(v-w));
            ans+=((__int)(16)*w-2*mrga-2*mrgb)*w%MOD;
        }
        cout<<ans%MOD<<'\n';
    }
    return 0;
}
