#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class dsu{
private:
    vector<int> f;
public:
    auto findset(int u)->int{
        return f[u]==u?u:(f[u]=findset(f[u]));
    }
    auto merge(int u,int v){
        f[findset(u)]=findset(v);
    }
    dsu(int n):f(n){iota(f.begin(),f.end(),0);}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n,m;cin>>n>>m;
        vector<string> s(n);
        for(auto&x:s) cin>>x;
        dsu qwq(n*m+7);
        const auto otsd=n*m;
        map<char,pair<int,int>> mv;
        mv['L']={0,-1};
        mv['R']={0,1};
        mv['U']={-1,0};
        mv['D']={1,0};
        auto id=[&](int x,int y){
            return x<0||y<0||x>n-1||y>m-1?otsd:x*m+y;
        };
        cir(i,0,n) cir(j,0,m) if(s[i][j]!='?'){
            const auto[mx,my]=mv[s[i][j]];
            qwq.merge(id(i,j),id(i+mx,j+my));
        }
        auto ans=0;
        cir(i,0,n) cir(j,0,m) if(s[i][j]!='?') ans+=qwq.findset(id(i,j))!=qwq.findset(otsd);
        cir(i,0,n) cir(j,0,m) if(s[i][j]=='?'){
            for(auto chr:{'L','R','U','D'}){
                const auto[mx,my]=mv[chr];
                if(qwq.findset(id(i+mx,j+my))!=qwq.findset(otsd)){
                    ++ans;break;
                }
            }
        }
        cout<<ans<<'\n';
    }();
    return 0;
}
