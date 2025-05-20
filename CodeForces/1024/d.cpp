#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class bit{
private:
    vector<int> a;
    constexpr auto lowbit(int x){return x&(-x);}
public:
    auto update(int u,int x){
        for(++u;u;u-=lowbit(u)) a[u]=max(a[u],x);
    }
    auto query(int u=0){
        auto res=0;
        for(++u;u<(int)(a.size());u+=lowbit(u)){
            res=max(res,a[u]);
        }
        return res;
    }
    bit(int _n):a(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n;cin>>n;vector<int> a(n);
        for(auto&i:a) cin>>i,--i;
        vector<int> up,dw;
        vector<int> cl(n),cr(n);
        bit dl(n);
        cir(i,0,n){
            while((!up.empty())&&up.back()>a[i]){
                dl.update(up.back(),-1);
                up.pop_back();
            }
            while((!dw.empty())&&dw.back()>a[i]){
                dl.update(dw.back(),-1);
                dw.pop_back();
            }
            up.emplace_back()
            dl.update(i,1);
        }
    }();
    return 0;
}
