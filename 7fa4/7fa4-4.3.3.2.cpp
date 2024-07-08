#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using ull=unsigned long long;
template<int siz>
class base{
private:
    vector<ull> p,sum;
public:
    void insert(ull x){
        for(int i=siz-1;~i;--i) if(!sum[i]){
            if(!(x&(1ull<<i))) continue;
            if(!p[i]) return p[i]=x,void();
            x^=p[i];
        }
        for(int i=siz-1;~i;--i) if(sum[i]){
            if(!(x&(1ull<<i))) continue;
            if(!p[i]) return p[i]=x,void();
            x^=p[i];
        }
    }
    void sum_ins_x(ull x){
        cir(i,0,siz) if(x&(1ull<<i)) sum[i]^=1;
    }
    ull operator()(ull x){
        ull res=0;
        for(int i=siz-1;~i;--i){
            if((!(res&(1ull<<i)))&&(!(x&(1ull<<i))))
                res^=p[i];
        }
        for(int i=siz-1;~i;--i){
            if((!(res&(1ull<<i)))&&(x&(1ull<<i)))
                res^=p[i];
        }
        return res;
    }
    base():p(siz),sum(siz){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<ull> a(n);
    base<64> b;
    for(auto&i:a){
        cin>>i,b.sum_ins_x(i);
    }
    for(auto&i:a) b.insert(i);
    const ull xorsum=accumulate(a.begin(),
        a.end(),0ull,[](ull a,ull b){return a^b;});
    cout<<(xorsum^b(xorsum))<<'\n';
    return 0;
}
