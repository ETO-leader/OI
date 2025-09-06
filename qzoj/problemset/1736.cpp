#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class bit{
private:
    vector<int> a;
    constexpr auto lowbit(auto x) const{return x&(-x);}
public:
    auto update(int u,int x){
        for(++u;u<(int)(a.size());u+=lowbit(u)) a[u]+=x;
    }
    auto query(int u){
        auto res=0ll;
        for(++u;u;u-=lowbit(u)) res+=a[u];
        return res;
    }
    bit(int _n):a(_n+1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    bit bx(n+7);
    cir(i,0,m){
        int op;cin>>op;
        if(op==1){
            int l,r;cin>>l>>r;--l;--r;
            bx.update(l,1);
            bx.update(r+1,-1);
        }else{
            int p;cin>>p;--p;
            cout<<(bx.query(p)&1)<<'\n';
        }
    }
    return 0;
}
