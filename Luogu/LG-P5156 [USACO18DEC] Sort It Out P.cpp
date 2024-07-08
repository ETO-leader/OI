#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
static constexpr lint maxn=1e18+7;
struct dnode{
    int d;lint c;
    dnode&operator+=(const dnode&dx){
        if(d<dx.d) (*this)=dx;
        else if(d==dx.d) c=min(maxn,c+dx.c);
        return *this;
    }
    dnode(int dx=0,lint cx=0):d(dx),c(cx){}
};
template<typename T>
class revbit{
private:
    vector<T> a;int n;
    int lowbit(int x) const{return x&(-x);}
public:
    void update(int p,T w){
        while(p) a[p]+=w,p-=lowbit(p);
    }
    T operator()(int p) const{
        T res=T(0);
        while(p<n) res+=a[p],p+=lowbit(p);
        return res;
    }
    revbit(int _n=0):n(_n+1),a(_n+1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;lint k;cin>>n>>k;VI a(n);
    for(auto&i:a) cin>>i;
    revbit<dnode> f(n+1);
    vector<dnode> D(n);
    f.update(n,dnode(0,1));
    vector<VI> G(n+1);
    vector<bool> nok(n);
    for(int i=n-1;~i;--i){
        D[i]=f(a[i]);++D[i].d;
        f.update(a[i],D[i]);
        clog<<i<<' '<<D[i].d<<' '<<D[i].c<<'\n';
    }
    cir(i,0,n) G[D[i].d].push_back(i);
    int cx=0;
    for(int i=f(1).d;i;--i){
        for(auto&v:G[i]){
            if(D[v].c<k){
                k-=D[v].c;
            }else{
                nok[a[v]-1]=true;
                while(cx<v) D[cx++]=dnode();
                break;
            }
        }
    }
    cout<<count(nok.begin(),
        nok.end(),false)<<'\n';
    cir(i,0,n) if(!nok[i]) cout<<i+1<<'\n';
    return 0;
}
