#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
class ternary{
private:
    int p;vector<int> p3;
    void init(){
        p3.push_back(1);
        cir(i,0,19) p3.push_back(p3.back()*3);
    }
public:
    int pow3(const int x) const{return p3[x];}
    ternary&operator<<=(const int x){
        p*=pow3(x);return *this;}
    ternary operator<<(const int x) const{
        auto w=*this;return w<<=x;}
    ternary&operator++(){
        ++p;return *this;}
    ternary&operator-=(const ternary&x){
        p-=x.p;return *this;}
    ternary operator-(const ternary&x) const{
        auto xp=*this;return xp-=x;}
    int operator[](const int x) const{
        return p/pow3(x)%3;}
    bool operator<(const ternary&x) const{
        return p<x.p;}
    operator int() const{return p;}
    operator size_t() const{return p;}
    ternary(int _p):p(_p){init();}
};
using lint=long;
struct edge{int v,w;};
int match(string&s1,string&s2){
    for(int i=s1.size()-1;i;--i){
        if(i+s2.size()>s1.size()){
            cir(p,i,s1.size()) if(s1[p]!=s2[p-i])
                goto brk;
            return s2.size()-(s1.size()-i);
        }
        brk:;
    }
    return 0;
}
const auto null=ternary(1);
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<string> cx(n);
    vector<int> v(n);
    for(auto&i:v) cin>>i;
    for(auto&i:cx) cin>>i;
    string sx;cin>>sx;
    vector<vector<edge>> G(n);
    vector<vector<lint>> D(n,vector<lint>(null<<n));
    lint ans=0;const auto _sz=(null<<n);
    cir(i,0,n) if(cx[i][0]==sx[0])
        D[i][null<<i]=cx[i].size(),
            ans=max<lint>(ans,cx[i].size());
    cir(i,0,n) cir(j,0,n) if(i!=j){
        auto vx=match(cx[i],cx[j]);
        if(vx) G[j].push_back({i,vx});
    }
    cir(s,null,_sz) cir(i,0,n){
        if((!s[i])||(s[i]>v[i])) continue;
        auto&d=D[i][s];
        const auto lx=s-(null<<i);
        for(auto&[j,w]:G[i]) if([&](){
            return s[j]&&s[j]<=v[j]&&D[j][lx];
        }()){
            d=max(d,D[j][lx]+w);
        }
        ans=max(ans,d);
    }
    cout<<ans<<'\n';
    return 0;
}
