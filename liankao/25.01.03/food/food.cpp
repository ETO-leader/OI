#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("food.in");
ofstream fcout("food.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
using lint=long long;
class dsu{
private:
    vector<int> siz,f;
    vector<lint> val;
    pair<lint,int> mx;
public:
    auto findset(int u)->int{
        return f[u]==u?u:f[u]=findset(f[u]);
    }
    auto active(int u){
        mx=max(mx,make_pair(val[u],u));
    }
    auto merge(int u,int v){
        u=findset(u);v=findset(v);
        if(siz[u]>siz[v]) swap(u,v);
        siz[v]+=siz[u];mx=max(mx,make_pair((val[v]+=val[u]),v));
        f[u]=v;
    }
    auto init(vector<lint>&_val){
        copy(_val.begin(),_val.end(),val.begin());
        iota(f.begin(),f.end(),0);
        fill(siz.begin(),siz.end(),1);
        mx=make_pair(0,0);
    }
    auto max_element(){return mx;}
    dsu(int _n):siz(_n),f(_n),val(_n),mx({-1,-1}){}
};
class bruteforce{
private:
    auto readarr(auto&x) const{
        for(auto&i:x) fcin>>i;
    }
    auto readarr(auto&x,auto&...args) const{
        readarr(x);readarr(args...);
    }
public:
    bruteforce(int n,int m){
        vector<int> a(n),b(m);
        vector<lint> x(n),y(m);
        vector<int> al(m),ar(m);
        readarr(a,x,b,y);
        dsu ds(m);
        vector<int> ina(n+m+7),idb(n+m+7,-1);
        for(auto&i:a) ina[i]=true;
        for(auto cnt=-1;auto&i:b) idb[i]=++cnt;
        vector<int> vaild(m);
        const auto suma=accumulate(x.begin(),x.end(),0ll);
        const auto sumb=accumulate(y.begin(),y.end(),0ll);
        auto ans=max(suma,sumb);
        auto alx=0,arx=0,plx=0,prx=0;
        cir(l,0,n){
            ds.init(y);
            iota(al.begin(),al.end(),0);
            iota(ar.begin(),ar.end(),0);
            fill(vaild.begin(),vaild.end(),false);
            auto ins=[&](int p){
                ds.active(p);
                if(p&&vaild[p-1]){
                    const auto pl=al[ds.findset(p-1)];
                    ds.merge(p-1,p);
                    al[ds.findset(p)]=pl;
                    ar[ds.findset(p)]=p;
                }
                if(p+1<m&&vaild[p+1]){
                    const auto pl=al[ds.findset(p)],pr=ar[ds.findset(p+1)];
                    ds.merge(p,p+1);
                    al[ds.findset(p)]=pl;
                    ar[ds.findset(p)]=pr;
                }
                vaild[p]=true;
            };
            cir(i,0,m) if(!ina[b[i]]) ins(i);
            cir(p,0,l) if(idb[a[p]]>-1) ins(idb[a[p]]);
            auto sum=0ll;
            cir(p,l,n) sum+=x[p];
            for(auto r=n-1;r>l-1;--r){
                if(r+1<n) sum-=x[r+1];
                if(r+1<n&&idb[a[r+1]]>-1) ins(idb[a[r+1]]);
                const auto[ansi,bp]=ds.max_element();
                if(ansi+sum>ans){
                    ans=ansi+sum;
                    alx=l;arx=r;plx=al[bp];prx=ar[bp];
                }
            }
        }
        fcout<<ans<<'\n';
        if(ans==suma) fcout<<1<<' '<<n<<'\n'<<0<<' '<<0<<'\n';
        else if(ans==sumb) fcout<<0<<' '<<0<<'\n'<<1<<' '<<m<<'\n';
        else fcout<<alx+1<<' '<<arx+1<<'\n'<<plx+1<<' '<<prx+1<<'\n';
    }
};
int main(){
    ios::sync_with_stdio(false),fcin.tie(nullptr);
    int n,m;fcin>>n>>m;
    if(n<10007&&m<10007) bruteforce(n,m);
    return 0;
}
