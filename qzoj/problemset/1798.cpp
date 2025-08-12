#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class dsu{
private:
    vector<int> f;
public:
    auto findset(int u)->int{
        return f[u]==u?u:f[u]=findset(f[u]);
    }
    auto merge(int u,int v){
        f[findset(u)]=findset(v);
    }
    dsu(int _n):f(_n){iota(f.begin(),f.end(),0);}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    dsu qwq(n*n);
    vector<vector<int>> a(n,vector<int>(n));
    for(auto&x:a) for(auto&i:x) cin>>i;
    static const auto mx=array<int,8>{1,-1,0,0,1,-1,1,-1};
    static const auto my=array<int,8>{0,0,1,-1,1,-1,-1,1};
    cir(i,0,n) cir(j,0,n){
        cir(d,0,8){
            const auto x=i+mx[d],y=j+my[d];
            if(x>-1&&x<n&&y>-1&&y<n&&a[x][y]==a[i][j]) qwq.merge(i*n+j,x*n+y);
        }
    }
    vector<int> umn(n*n,numeric_limits<int>::max()),umx(n*n,numeric_limits<int>::min());
    cir(i,0,n) cir(j,0,n){
        cir(d,0,8){
            const auto x=i+mx[d],y=j+my[d];
            const auto u=qwq.findset(i*n+j);
            if(x>-1&&x<n&&y>-1&&y<n) umn[u]=min(umn[u],a[x][y]),umx[u]=max(umx[u],a[x][y]);
        }
    }
    auto ansx=0,ansy=0;
    cir(i,0,n) cir(j,0,n) if(qwq.findset(i*n+j)==i*n+j){
        ansx+=(umx[i*n+j]<a[i][j]+1);
        ansy+=(umn[i*n+j]>a[i][j]-1);
    }
    cout<<ansx<<' '<<ansy<<'\n';
    return 0;
}
