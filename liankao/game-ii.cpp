#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("game.in");
ofstream ouf("game.out");
class fileio{
public:
    ~fileio(){
        inf.close();ouf.close();
    }
} use_fileio;
class dsu{
private:
    vector<int> a;
public:
    auto findset(int u)->int{
        return a[u]==u?u:a[u]=findset(a[u]);
    }
    auto merge(int u,int v){
        a[findset(u)]=findset(v);
    }
    dsu(int _n):a(_n){iota(a.begin(),a.end(),0);}
};
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n,m,q;inf>>n>>m>>q;vector<int> a(n);
    for(auto&i:a) inf>>i,--i;
    vector<int> nxt(q),cur(n,-1),qx(q);
    cir(i,0,q){
        int x,c;inf>>x>>c;--x;--c;
        qx[i]=c;
        nxt[i]=cur[x];
        cur[x]=i;
        // qx[x].emplace_front(c,i);
    }
    dsu ds(n+7);
    vector top{0,1,2},sid{0,1,2},csg{0,0,0};
    sid.resize(n+7);
    vector<int> las(m);
    auto cnt=2,lasw=0;
    vector<int> ans(q);
    cir(i,0,n){
        const auto x=sid[ds.findset(las[a[i]])];
        las[a[i]]=++cnt;
        ds.merge(top[2],top[0]);
        if(x==1){
            csg[0]=i;csg[1]=i+1;csg[2]=lasw;
            sid[top[0]]=0;sid[top[1]]=1;sid[cnt]=2;
            top[2]=cnt;
        }else{
            csg[0]=i;csg[1]=i+1;csg[2]=lasw;
            sid[top[0]]=1;sid[top[1]]=2;sid[top[2]]=0;
            const auto ctop=top;
            top[0]=cnt;top[1]=ctop[0];top[2]=ctop[1];
            lasw=i;
        }
        for(auto p=cur[i];~p;p=nxt[p]) ans[p]=csg[sid[ds.findset(las[qx[p]])]];
        // for(auto&[w,id]:qx[i]) ans[id]=csg[sid[ds.findset(las[w])]];
    }
    cir(i,1,q) ans[i]^=ans[i-1];
    for(auto&i:ans) ouf<<(bool)(i);
    ouf<<'\n';
    return 0;
}
