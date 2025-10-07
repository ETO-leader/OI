#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class _Float{
private:
    lint _v,_p;
    static constexpr auto _b=60;
public:
    auto&operator<<=(int p){
        _p+=p;
        return*this;
    }
    auto operator<<(int p) const{
        auto res=*this;
        return res<<=p;
    }
    friend auto operator<(const _Float a,const _Float b){
        if(a._p!=b._p)return a._p<b._p;
        return a._v<b._v;
    }
    auto binary() const{
        string res;
        if(!_v) return (string)("0");
        auto p=__lg(_v);
        auto c=_p-_b;
        for(auto x=p;~x;--x){
            if((int)(res.size())==_p+1) break;
            res+=('0'+((_v>>x)&1));
        }
        cir(i,0,c) res+='0';
        return res;
    }
    _Float(lint v):_v(v),_p(0){
        while(!((_v>>_b)&1)) _v<<=1;
        while(v>1) v>>=1,++_p;
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    vector<pair<int,int>> a(n);
    for(auto&[ls,rs]:a) cin>>ls>>rs;
    auto dfs=[&](auto __self,int u){
        if(u<0) return _Float(-u);
        --u;
        const auto res=max(__self(__self,a[u].first),__self(__self,a[u].second))<<1;
        return res;
    };
    cout<<dfs(dfs,1).binary()<<'\n';
    return 0;
}
