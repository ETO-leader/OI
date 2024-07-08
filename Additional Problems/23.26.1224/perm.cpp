#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("perm.in");
ofstream fcout("perm.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
enum direct{predirect=1,sufdirect=-1};
template<typename T,direct dir>
class bit{
private:
    vector<T> a;
    static auto lowbit(int x){return x&(-x);}
public:
    auto update(int x,T w){
        ++x;
        for(;x&&x<a.size();x+=lowbit(x)*dir){
            a[x]+=w;
        }
    }
    auto query(int x){
        T res=0;++x;
        for(;x&&x<a.size();x-=lowbit(x)*dir){
            res+=a[x];
        }
        return res;
    }
    bit(int _x):a(_x+1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;fcin>>n;vector<int> a(n);
    for(auto&i:a) fcin>>i;
    auto ans=[&](){
        bit<unsigned,sufdirect> bx(n+7);
        bit<unsigned,sufdirect> bk(n+7);
        unsigned res=0;
        for(int i=n-1;~i;--i){
            res+=bk.query(a[i])*(bx.query(a[i])-2);
            bk.update(a[i],bx.query(a[i]));
            bx.update(a[i],1);
        }
        return res;
    }();
    ans-=[&](){
        bit<unsigned,sufdirect> bx(n+7);
        unsigned res=0;
        for(int i=n-1;~i;--i){
            auto ax=bx.query(a[i]);
            res+=(unsigned)(
                1ll*ax*(ax-1)*(ax-2)/6);
            bx.update(a[i],1);
        }
        return res;
    }();
    ans-=[&](){
        bit<unsigned,sufdirect> bk(n+7);
        vector<unsigned> fnd(n);
        for(int i=n-1;~i;--i){
            fnd[i]=bk.query(a[i]);
            bk.update(a[i],1);
        }
        bit<unsigned,predirect> bx(n+7);
        unsigned res=0;
        cir(i,0,n){
            res+=bx.query(a[i])*(unsigned)(
                1ll*fnd[i]*(fnd[i]-1)/2);
            bx.update(a[i],1);
        }
        return res*2;
    }();
    fcout<<ans<<'\n';
    return 0;
}
