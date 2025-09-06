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
    bit pos(n+7),lpos(n+7);
    cir(i,0,m){
        int op;cin>>op;
        if(op==1){
            int l,r;cin>>l>>r;--l;--r;
            pos.update(0,1);
            pos.update(r+1,-1);
            lpos.update(0,1);
            lpos.update(l,-1);
        }else{
            int l,r;cin>>l>>r;--l;--r;
            cout<<pos.query(l)-lpos.query(r)<<'\n';
        }
    }
    return 0;
}
