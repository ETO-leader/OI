#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
auto xcnt=0;
class segment{
    vector<valarray<int>> tr;
    vector<int> cnt;
    constexpr auto ls(auto u) const{return u*2;}
    constexpr auto rs(auto u) const{return u*2+1;}
    auto rotate(int u,int c){
        cnt[u]+=c;
        const auto x=tr[u];
        cir(i,0,10) tr[u][(i+c)%10]=x[i];
        return x;
    }
    auto push_down(int u){
        for(auto v:{ls(u),rs(u)}) rotate(v,cnt[u]);
        cnt[u]=0;
    }
    auto build(int u,int l,int r,string&s){
        if(l==r) return tr[u][s[l]-'0']=1,tr[u];
        const auto mid=(l+r)/2;
        ++xcnt;
        return tr[u]=build(ls(u),l,mid,s)+build(rs(u),mid+1,r,s);
    }
    auto query(int u,int l,int r,int ql,int qr){
        if(r<ql||qr<l) return valarray<int>(10);
        if(ql-1<l&&r-1<qr) return rotate(u,1);
        push_down(u);
        const auto mid=(l+r)/2;
        const auto res=valarray<int>(query(ls(u),l,mid,ql,qr)+query(rs(u),mid+1,r,ql,qr));
        ++xcnt;
        tr[u]=tr[ls(u)]+tr[rs(u)];
        return res;
    }
    const int n;
public:
    auto init(string s){
        build(1,0,n-1,s);
    }
    auto query(int l,int r){
        const auto x=query(1,0,n-1,l,r);
        auto res=0;
        cir(i,0,10) res+=x[i]*i;
        return res;
    }
    segment(int _n):tr(_n<<2,valarray<int>(10)),cnt(_n<<2),n(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,q;cin>>n>>q;
    string s;cin>>s;
    segment sg(n);
    sg.init(s);
    cir(i,0,q){
        int l,r;cin>>l>>r;--l;--r;
        cout<<sg.query(l,r)<<'\n';
    }
    return 0;
}
