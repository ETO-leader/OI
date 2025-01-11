#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("doll.in");
ofstream fcout("doll.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
template<class comp>
class sparsetable{
private:
    static constexpr auto ups=21;
    vector<vector<int>> mn;
    vector<int> lgx;
    auto init(vector<int> a){
        const auto n=(int)(a.size());
        mn.resize(ups,vector<int>(n));
        mn[0]=a;
        cir(x,1,ups) cir(p,0,n-(1<<x)+1) mn[x][p]=min(mn[x-1][p],mn[x-1][p+(1<<(x-1))],comp());
        lgx.resize(n+7);
        cir(i,2,n) lgx[i]=lgx[i>>1]+1;
    }
public:
    auto query(int l,int r){
        const auto x=lgx[r-l+1];
        return min(mn[x][l],mn[x][r-(1<<x)+1],comp());
    }
    sparsetable(auto x){init(x);}
};
int main(){
    ios::sync_with_stdio(false),fcin.tie(nullptr);
    int n,q;fcin>>n>>q;vector<int> a(n);
    for(auto&i:a) fcin>>i;
    vector<int> p(n);
    iota(p.begin(),p.end(),0);
    sparsetable<less<int>> stmn(a);
    sparsetable<greater<int>> stmx(a);
    cir(i,0,n){
        auto pos=0;
        while(p[i]!=pos){
            pos=p[i];
            if(!pos) break;
            auto l=p[pos-1],r=pos-1,ans=pos;
            while(l-1<r){
                const auto mid=(l+r)/2;
                stmn.query(mid,pos-1)>stmx.query(pos,i)||stmx.query(mid,pos-1)<stmn.query(pos,i)?
                    ((r=mid-1),(ans=mid)):(l=mid+1);
            }
            p[i]=ans;
        }
    }
    static constexpr auto ups=21;
    vector up(n,vector<int>(ups));
    cir(u,0,n){
        up[u][0]=p[u]-1;
        cir(c,1,ups){
            if(up[u][c-1]>-1) up[u][c]=up[up[u][c-1]][c-1];
            else up[u][c]=-1;
        }
    }
    cir(i,0,q){
        int l,r;fcin>>l>>r;--l;--r;
        auto ans=0,u=r;
        for(auto c=ups-1;~c;--c) if(up[u][c]>l-1){
            ans+=(1<<c);u=up[u][c];
        }
        fcout<<r-l-ans<<'\n';
    }
    return 0;
}
