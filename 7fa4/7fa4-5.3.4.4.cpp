#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using db=long double;
using VI=vector<lint>;
using VDF=vector<db>;
static auto maxsiz=107;
class matrix{
private:
    vector<VDF> mat;
    int nx,mx;
public:
    auto&operator[](size_t x){return mat[x];}
    auto operator*(matrix m) const{
        matrix res(nx,m.mx);
        cir(k,0,mx) cir(i,0,nx) cir(j,0,m.mx){
            res[i][j]+=mat[i][k]*m[k][j];
        }
        return res;
    }
    auto operator^(lint x){
        auto res=*this,k=*this;--x;
        while(x){
            if(x&1) res=res*k;
            k=k*k;x>>=1;
        }
        return res;
    }
    matrix(int _n,int _m):
        mat(_n,VDF(_m)),nx(_n),mx(_m){}
};
class ac_automaton{
private:
    vector<VI> tr;VI fx,f,cx;
    int cnt,rt;
    auto allocm(){return ++cnt;}
public:
    auto insert(const VI a){
        int u=rt;
        for(auto&i:a){
            if(!tr[u][i]) tr[u][i]=allocm();
            u=tr[u][i];
        }
        cx[u]=true;
    }
    auto init(){
        queue<int> q;q.push(rt);f=cx;
        while(!q.empty()){
            auto u=q.front();q.pop();
            int cnt=-1;
            for(auto&i:tr[u]) if(((++cnt)+1)&&i){
                if(!u){
                    fx[i]=u;q.push(i);
                }else{
                    int v=fx[u];
                    while(v&&(!tr[v][cnt])) v=fx[v];
                    fx[i]=tr[v][cnt];q.push(i);
                }
            }
        }
    }
    auto getst(){
        return tuple(tr,fx,f);
    }
    auto size(){return cnt+1;}
    ac_automaton(int siz,int alp):rt(0),
        tr(siz,VI(alp)),fx(siz),
        f(siz),cx(siz),cnt(0){}
};
auto strvec(const string s){
    VI res;res.reserve(s.size());
    for(auto&i:s) res.push_back(i-'a');
    return res;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,alp;lint k;cin>>n>>k>>alp;
    ac_automaton ac(maxsiz,alp);
    vector<string> strs(n);
    for(auto&s:strs) cin>>s;
    VI nok(n);
    for(auto&s:strs) cir(j,0,n) if(s!=strs[j]){
        if(strs[j].find(s)!=string::npos){
            nok[j]=true;
        }
    }
    cir(i,0,n) if(!nok[i])
        ac.insert(strvec(strs[i]));
    ac.init();
    auto[tr,fx,f]=ac.getst();
    matrix g(1,maxsiz+1),
        d(maxsiz+1,maxsiz+1);
    g[0][0]=1;
    cir(u,0,maxsiz){
        if(f[u]) continue;
        const auto p=(db)(1)/alp;
        cir(i,0,alp){
            int v=u;
            while(v&&(!tr[v][i])) v=fx[v];
            if(f[tr[v][i]]){
                d[u][0]+=p;d[u][maxsiz]+=p;
            }else{
                d[u][tr[v][i]]+=p;
            }
        }
    }
    d[maxsiz][maxsiz]=1;
    cout<<fixed<<setprecision(15)<<
        (g*(d^k))[0][maxsiz]<<'\n';
    return 0;
}
