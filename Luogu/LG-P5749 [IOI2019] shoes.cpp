#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
template<typename T>
class bit{
private:
    vector<T> v;
    int lowbit(int x){return x&(-x);}
    void __update(int u,T w){
        ++u;
        while(u<v.size()) v[u]+=w,u+=lowbit(u);
    }
public:
    void update(int u,T w){__update(u,w);}
    T operator()(int u){
        T res=0;++u;
        while(u) res+=v[u],u-=lowbit(u);
        return res;
    }
    void resize(int n){(*this)=bit<T>(n);}
    bit(int n=0):v(n+1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;
    unordered_map<int,vector<int>> um;
    n<<=1;vector<int> v(n);
    cir(i,0,n){
        cin>>v[i];
        um[v[i]].push_back(i);
    }
    vector<bool> del(n);
    bit<lint> bx(n);
    lint ans=0;
    cir(i,0,n) bx.update(i,1);
    for(int i=n-1;~i;--i){
        if(del[i]) continue;
        um[v[i]].pop_back();
        const auto rp=um[-v[i]].back();
        um[-v[i]].pop_back();
        del[rp]=true;
        ans+=bx(i-1)-bx(rp)+(v[i]<0);
        bx.update(i,-1);bx.update(rp,-1);
    }
    cout<<ans<<'\n';
    return 0;
}
