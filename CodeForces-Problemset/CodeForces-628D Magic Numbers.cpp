#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
const int MOD=1e9+7;
using VI=vector<int>;
using VB=vector<bool>;
vector<vector<VI>> D;
vector<vector<VB>> vis;
int dp(int i,int j,int k,int st,
    bool isr,VI&x,int m,int d){
    auto cl=[&](int p){return (k*10+p)%m;};
    if(!i) return !k;
    if((st&1)&&isr&&d>x[i-1]) return 0;
    int dx=0,&di=(isr?dx:D[i][j][k]);
    if((!isr)&&vis[i][j][k]) return di;
    if(!isr) vis[i][j][k]=true;
    if(st&1){
        return di=dp(i-1,d,cl(d),st^1,
            isr&&(d==x[i-1]),x,m,d);
    }
    int upx=isr?x[i-1]+1:10;
    cir(v,0,upx){
        if(v==d) continue;
        (di+=dp(i-1,v,cl(v),st^1,
            isr&&(v==x[i-1]),x,m,d))%=MOD;
    }
    return di;
}
istream&operator>>(istream&is,VI&v){
    string sx;is>>sx;v.clear();
    for(auto&i:sx) v.push_back(i-'0');
    reverse(v.begin(),v.end());
    return is;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int m,d;VI l,r;cin>>m>>d>>l>>r;
    int len=l.size(),i=0;
    while(i<len){
        if(l[i]){l[i]--;break;}
        l[i]=9;++i;
    }
    bool tag0=false;
    if(i==len) fill(l.begin(),l.end(),0),tag0=(!d);
    auto ass=[&](){
        D.clear();
        D.assign(len,vector<VI>(10,VI(m)));
        vis.clear();
        vis.assign(len,vector<VB>(10,VB(m)));
    };
    ass();
    auto dx=dp(len,0,0,0,true,r,m,d);
    ass();
    cout<<(dx-dp(len,0,0,0,true,l,m,d)
        +MOD+tag0)%MOD<<'\n';
    return 0;
}
