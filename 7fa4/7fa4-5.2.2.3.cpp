#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
const lint MOD=INT_MAX+(lint)(1);
template<typename T>
class bit{
private:
    vector<T> v;
    int lowbit(int x){return x&(-x);}
public:
    void update(int x,T w){
        for(;x<v.size();x+=lowbit(x)) v[x]+=w;
    }
    T operator()(int x){
        T res=0;
        for(;x;x-=lowbit(x)) res+=v[x];
        return res;
    }
    void resize(int _x){
        (*this)=bit<T>(_x);
    }
    bit(int _x=0):v(_x){}
};
namespace math{
    vector<VI> C;
    void init_c(int n,int k){
        C.assign(n+1,VI(k+1));
        C[0][0]=1;
        cir(i,1,n+1) cir(x,0,k+1){
            if(x) C[i][x]=C[i-1][x-1];
            C[i][x]+=C[i-1][x];
        }
    }
}
struct qry{int x,y;};
vector<qry> qx;
unordered_map<int,int> id;
bit<lint> bx;
VI cnx_y,all_y;
lint solve_l(int l,int r,int k){
    lint res=0,cnxl=0,cnxr=(r-l+1);
    cir(i,l,r){
        ++cnxl;--cnxr;
        res+=(bx(id[qx[i+1].y]-1)-
            bx(id[qx[i].y]))*
            math::C[cnxl][k]*
            math::C[cnxr][k];
    }
    cir(i,l,r+1){
        const int yi=id[qx[i].y];
        int ci=cnx_y[yi],lci=all_y[yi]-ci;
        bx.update(yi,-math::C[ci][k]*
            math::C[lci][k]);
        bx.update(yi,math::C[ci+1][k]*
            math::C[lci-1][k]);
        ++cnx_y[yi];
    }
    return res;
}
lint solve(int n,int k){
    math::init_c(n,k);
    lint cnx=0;
    cir(i,0,n){
        const int l=i;
        auto&r=i;
        while(r<n-1&&qx[r+1].x==qx[l].x) ++r;
        cnx+=solve_l(l,r,k);
    }
    return cnx;
}
void init(){
    int cnx=0;
    unordered_map<int,int> all;
    map<int,int> idx;
    for(auto&[x,y]:qx)
        idx.insert({y,0}),++all[y];
    all_y.resize(1);
    for(auto&[a,b]:idx){
        id[a]=++cnx;
        all_y.push_back(all[a]);
    }
    bx.resize(cnx+1);
    cnx_y.resize(cnx+1);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int h,w,n;cin>>h>>w>>n;
    qx.resize(n);
    for(auto&[x,y]:qx) cin>>x>>y;
    sort(qx.begin(),qx.end(),[](qry&a,qry&b){
        return a.x==b.x?a.y<b.y:a.x<b.x;
    });
    init();
    int k;cin>>k;
    cout<<(solve(n,k)%MOD+MOD)%MOD<<'\n';
    return 0;
}
