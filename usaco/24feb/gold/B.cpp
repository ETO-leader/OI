#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=__int128_t;
template<typename _Ty>
class bit{
private:
    vector<_Ty> a;
    constexpr auto lowbit(int x){return x&(-x);}
public:
    auto update(int x,_Ty w){
        for(++x;x<a.size();x+=lowbit(x)) a[x]+=w;
    }
    auto query(int x){
        _Ty res=0;
        for(++x;x;x-=lowbit(x)) res+=a[x];
        return res;
    }
    bit(int _x=0):a(_x){}
};
istream&operator>>(istream&is,lint&x){
    string s;is>>s;x=0;
    for(const auto&c:s) (x*=10)+=(c-'0');
    return is;
}
ostream&operator<<(ostream&os,lint x){
    if(x>9) os<<x/10;
    return (os<<(int)(x%10));
}
int Main(int n,basic_string<lint> a){
    a=a+a;vector<int> stc;
    vector<lint> ans(n+1);
    ans[0]=accumulate(a.begin(),a.end(),(lint)(0))/2;
    cir(i,0,n*2){
        while((!stc.empty())&&a[stc.back()]>a[i]-1)
            stc.pop_back();
        stc.push_back(i);
        if(i>n-1){
            for(int p=(int)(stc.size())-2;~p;--p){
                const auto tml=i-stc[p];
                if(tml>n) break;
                ans[tml]-=a[stc[p+1]]-a[stc[p]];
            }
        }
    }
    cir(i,1,n+1) cout<<(ans[i]+=ans[i-1])<<'\n';
    return 0;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;basic_string<lint> a(n,0);
    for(auto&i:a) cin>>i;
    if(*max_element(a.begin(),a.end())<3){
        return Main(n,a);
    }
    int cxx=0;
    while(a[0]>a[1]&&(++cxx)<20){
        auto w=a[0];
        a.erase(a.begin());
        a.push_back(w);
    }
    a=a+a+a;vector<int> stc;
    lint k=1000000000000000000ll;
    cir(i,0,n*3) (a[i]*=k)+=i;
    cir(i,n,n*2) swap(a[i],a[i+n]);
    bit<lint> ax(n*5+7);
    vector<int> lf(n*3,-1),rg(n*3,-1);
    [&](){
        stack<int> stc;
        cir(i,0,n*3){
            while((!stc.empty())&&(a[stc.top()]>a[i]))
                stc.pop();
            if(!stc.empty()) lf[i]=stc.top();
            stc.push(i);
        }
    }();
    [&](){
        stack<int> stc;
        for(int i=n*3-1;~i;--i){
            while((!stc.empty())&&(a[stc.top()]>a[i]))
                stc.pop();
            if(!stc.empty()) rg[i]=stc.top();
            stc.push(i);
        }
    }();
    lint mn=(lint)(1e36);
    cir(i,n,n*2) mn=min(mn,a[i]);
    cir(i,n,n*2){
        if(a[i]==mn){
            ax.update(0,a[i]);
            ax.update(n,-a[i]);continue;
        }
        ax.update(0,a[i]);
        ax.update(i-lf[i],-a[i]);
        ax.update(rg[i]-i,-a[i]);
        ax.update(rg[i]-i+(i-lf[i]),a[i]);
    }
    vector<lint> ans(n+1);
    cir(i,0,n+1) ans[i]=ax.query(i);
    cir(i,1,n+1) cout<<(ans[i]+=ans[i-1])/k<<'\n';
    return 0;
}
