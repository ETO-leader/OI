#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
const int mxm=12,ixs=600000;
vector<int> p3(1,1);
array<int,(1<<mxm)> ic;
void init(){
    cir(i,0,19) p3.push_back(p3.back()*3);
}
class ternary{
private:
    int p;
    int upx() const{return p>>mxm;};
    int px() const{return (p-((p>>mxm)<<mxm));}
public:
    int idx(){return ic[px()]+p3[6]*ic[upx()];}
    ternary&operator<<=(const int x){
        p<<=(x<<1);return *this;}
    ternary operator<<(const int x) const{
        auto px=*this;return px<<=x;}
    int operator[](const int x) const{
        return (p>>(x<<1))&3;}
    ternary&operator++(){
        int pos=0;++p;
        while((this->operator[](pos))==3)
            p+=(1<<(pos<<1)),++pos;
        return *this;
    }
    ternary&operator-=(const ternary&x){
        p-=x.p;return *this;}
    ternary operator-(const ternary x) const{
        auto px=*this;return px-=x;}
    bool operator<(const ternary&x) const{
        return p<x.p;}
    void chg(const int px,const int v){
        p-=(this->operator[](px)<<(px<<1));
        p+=(v<<(px<<1));
    }
    operator int() const{return p;}
    operator size_t() const{return p;}
    ternary(int x=0):p(x){}
};
array<ternary,ixs> idx;
const auto null=ternary(1);
const auto null_t=ternary(0);
using VI=vector<int>;
const vector<char> ix{'B','R','G'};
const int MOD=998244353;
bool sim(int a,int b){
    return (((!a)&&(!b))||(a&&b&&(a!=b)));
}
int inid(int m){
    const auto _sz=(null<<m);
    init();
    cir(i,0,(1<<mxm)){
        ternary tx(i);
        cir(j,0,mxm/2){
            ic[i]+=(tx[j]*p3[j]);
        }
    }
    int cnt=0;
    cir(i,null_t,_sz) idx[cnt]=i,++cnt;
    return cnt;
}
array<array<array<int,ixs>,mxm>,2> D;
const int mxn=2007;
array<array<char,mxn>,mxn> sx;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;
    auto sz=inid(m);
    cir(i,0,mxn) cir(j,0,mxn) cin>>sx[i][j];
    auto canput=[&](char a,int b){
        return a=='.'||(ix[b]==a);};
    int step=0;
    auto update_newline=[&](int l,int p,ternary st){
        cir(j,0,3) if(!sim(j,st[p])
            &&canput(sx[l][p],j)){
            auto cx=st;cx.chg(p,j);
            (D[step^1][p][cx.idx()]+=
                D[step][m-1][st.idx()])%=MOD;
        }
    };
    cir(pos,0,sz){
        auto&i=idx[pos];int ip=i.idx();
        if([&](){
            cir(j,0,m) if(!canput(sx[0][j],i[j]))
                return false;
            cir(j,1,m) if(sim(i[j],i[j-1]))
                return false;
            return true;
        }()){
            D[step][m-1][ip]=1;
            if(n>1) update_newline(1,0,i);
        }
    }
    cir(i,1,n){
        step^=1;
        cir(j,0,m) fill(D[step^1][j].begin(),
            D[step^1][j].end(),0);
        cir(j,0,m) cir(pos,0,sz){
            auto s=idx[pos];int sp=s.idx();
            if(j==m-1){
                if(i<n-1) update_newline(i,0,s);
                continue;
            }
            cir(w,0,3){
                if(canput(sx[i][j+1],w)&&
                    !sim(w,s[j])&&!sim(w,s[j+1])){
                    auto cx=s;cx.chg(j+1,w);
                    (D[step][j+1][cx.idx()]+=D[step][j][sp])%=MOD;
                }
            }
        }
    }
    cout<<[&](){
        int res=0;
        cir(i,0,ixs) (res+=D[step][m-1][i])%=MOD;
        return res;
    }()<<'\n';
    return 0;
}
