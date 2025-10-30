#include <bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
using lint=long long;
class mathbase{
private:
    const int p;
public:
    constexpr auto qpow(lint a,auto b) const{
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=p;
            (a*=a)%=p;b>>=1;
        }
        return res;
    }
    constexpr auto inv(auto x) const{
        return qpow(x,p-2);
    }
    mathbase(auto _p):p(_p){}
};
int main() {
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n,k;
        cin>>n>>k;
        vector<int> a(n);
        for(auto&x:a) cin>>x,--x;
        vector<int> vis(n);
        vector<vector<vector<int>>> vx(n+1);
        vector<int> cnt(n+1);
        cir(i,0,n){
            if(vis[i]) continue;
            auto j=i;
            vector<int> c;
            while(!vis[j]){
                c.emplace_back(j);
                vis[j]=true;
                j=a[j];
            }
            vx[(int)(c.size())-1].emplace_back(c);
        }
        for(auto c=0;auto&x:vx) if((!((++c)&1))&&x.size()>0){
            if(k>20||x.size()&((1<<k)-1)){
                cout<<"NO"<<'\n';
                return;
            }
        }
        cout<<"YES"<<'\n';
        for(auto i=0;auto&x:vx){
            ++i;
            while(!x.empty()){
                auto t=min<int>(__lg(x.size()),k);
                auto pw=mathbase(i).qpow(2,k-t);
                auto cs=vector(x.end()-(1<<t),x.end());
                x.erase(x.end()-(1<<t),x.end());
                for(auto&c:cs){
                    vector<int> nc(i);
                    cir(j,0,i) nc[pw*j%i]=c[j];
                    c=nc;
                }
                vector<int> nc;
                cir(j,0,i) cir(k,0,(1<<t)) nc.emplace_back(cs[k][j]);
                cir(j,0,(int)(nc.size())) a[nc[j]] = nc[(j + 1) % nc.size()];
            }
        }
        for(auto&x:a) cout<<x+1<<' ';
        cout<<'\n';
    }();
    return 0;
}
