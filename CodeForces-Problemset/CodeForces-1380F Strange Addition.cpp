#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
const int MOD=998244353;
template<int mod>
class matrix{
private:
    array<array<lint,2>,2> mat;
public:
    auto&operator[](int x){
        return mat[x];
    }
    auto operator*(matrix m) const{
        matrix<mod> res;
        cir(k,0,2) cir(i,0,2){
            cir(j,0,2){
                (res[i][j]+=mat[i][k]*
                    m[k][j]%mod)%=mod;
            }
        }
        return res;
    }
    void clear(){
        cir(x,0,2) cir(y,0,2) mat[x][y]=0;
    }
    matrix(){clear();}
};
class segment{
private:
    struct node{
        matrix<MOD> d;
    };
    vector<node> tr;VI c;
    int ls(int u){return u*2;}
    int rs(int u){return u*2+1;}
    void maintain(int u){
        tr[u].d=tr[rs(u)].d*tr[ls(u)].d;
    }
    void setnode(int u,int p){
        tr[u].d[1][0]=1;tr[u].d[0][0]=c[p]+1;
        tr[u].d[0][1]=(c[p-1]==1)*(9-c[p]);
    }
    void build(int u,int l,int r){
        if(l==r) return setnode(u,l);
        const int mid=(l+r)/2;
        build(ls(u),l,mid);
        build(rs(u),mid+1,r);
        maintain(u);
    }
    void update(int u,int l,int r,int p){
        if(l==r) return setnode(u,p);
        const int mid=(l+r)/2;
        p<mid+1?update(ls(u),l,mid,p):
            update(rs(u),mid+1,r,p);
        maintain(u);
    }
    int n;
public:
    void update(int p,lint w){
        c[p]=w;update(1,1,n,p);
        if(p<n) update(1,1,n,p+1);
    }
    auto export_result(){
        return tr[1].d[0][0];
    }
    segment(VI cx):c(cx),tr(cx.size()<<2){
        build(1,1,(n=cx.size()-1));
    }
};
auto init(){
    string s;cin>>s;
    VI c(1);
    for(auto&i:s) c.push_back(i-'0');
    return c;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;cin>>n>>q;
    auto c=init();
    segment seg(c);
    cir(i,0,q){
        int p;lint w;cin>>p>>w;
        seg.update(p,w);
        cout<<seg.export_result()<<'\n';
    }
    return 0;
}
