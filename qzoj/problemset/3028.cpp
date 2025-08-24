#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e9+7);
template<const int n>
class matrix:public array<array<lint,n>,n>{
public:
    auto operator*(const matrix x) const{
        auto res=matrix();
        cir(k,0,n) cir(i,0,n) cir(j,0,n) (res[i][j]+=(*this)[i][k]*x[k][j])%=MOD; 
        return res;
    }
    matrix(){for(auto&x:*this) for(auto&i:x) i=0;}
};
template<class node>
class segment{
private:
    vector<node> tr;
    constexpr auto ls(int u) const{return u*2;}
    constexpr auto rs(int u) const{return u*2+1;}
    auto maintain(int u){
        tr[u]=tr[ls(u)]*tr[rs(u)];
    }
    auto update(int u,int l,int r,int p,node w){
        if(l==r) return tr[u]=w,void();
        const auto mid=(l+r)/2;
        p-1<mid?update(ls(u),l,mid,p,w):update(rs(u),mid+1,r,p,w);
        maintain(u);
    }
    const int n;
public:
    auto update(int p,node w){
        update(1,0,n-1,p,w);
    }
    auto value(){
        return tr[1];
    }
    segment(int _n):tr(_n<<2),n(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    vector<lint> v(n);
    for(auto&i:v) cin>>i;
    segment<matrix<6>> sg(n);
    cir(i,0,n){
        int l;cin>>l;
        matrix<6> upd;
        cir(c,0,4) upd[c][c+1]=1;
        cir(c,0,l){
            lint w;cin>>w;
            upd[c][0]=w;
            upd[5][0]=v[i];
            upd[5][5]=1;
        }
        sg.update(i,upd);
    }
    int q;cin>>q;
    auto ml=matrix<6>();
    ml[0][5]=1;
    cir(i,0,q){
        int p,l;cin>>p>>v[p-1]>>l;--p;
        matrix<6> upd;
        cir(c,0,4) upd[c][c+1]=1;
        cir(c,0,l){
            lint w;cin>>w;
            upd[c][0]=w;
            upd[5][0]=v[p];
            upd[5][5]=1;
        }
        sg.update(p,upd);
        cout<<(ml*sg.value())[0][0]<<'\n';
    }
    return 0;
}
