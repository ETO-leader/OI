#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
static auto maxsiz=107;
class matrix{
private:
    vector<VI> mat;
    int nx,mx;
    static auto&gmax(auto&a,const auto b){
        return a=max(a,b);
    }
public:
    auto&operator[](size_t x){return mat[x];}
    auto operator*(matrix m) const{
        matrix res(nx,m.mx);
        cir(k,0,mx) cir(i,0,nx) cir(j,0,m.mx){
            if(mat[i][k]<0||m[k][j]<0) continue;
            gmax(res[i][j],mat[i][k]+m[k][j]);
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
    auto max_element(){
        lint res=0;
        for(auto&i:mat) for(auto&j:i) gmax(res,j);
        return res;
    }
    matrix(int _n,int _m):
        mat(_n,VI(_m,-1)),nx(_n),mx(_m){}
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
        ++cx[u];
    }
    auto init(){
        queue<int> q;q.push(rt);f=cx;
        while(!q.empty()){
            auto u=q.front();q.pop();
            f[u]+=f[fx[u]];
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
    int n;lint k;cin>>n>>k;
    ac_automaton ac(maxsiz,26);
    cir(i,0,n){
        string s;cin>>s;
        ac.insert(strvec(s));
    }
    ac.init();
    auto[tr,fx,f]=ac.getst();
    matrix g(maxsiz,maxsiz),d(maxsiz,maxsiz);
    g[0][0]=0;
    cir(i,0,ac.size()){
        cir(x,0,26){
            int v=i;
            while((v)&&(!tr[v][x])) v=fx[v];
            if(!tr[v][x]) continue;
            d[i][tr[v][x]]=f[tr[v][x]];
        }
    }
    cout<<(g*(d^k)).max_element()<<'\n';
    return 0;
}
