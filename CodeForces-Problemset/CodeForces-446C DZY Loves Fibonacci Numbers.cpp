#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
static constexpr int MOD=1e9+9;
struct seg{int l,r;};
auto prefix_fib(int n){
    VI fib(n,1),pfb;
    cir(i,2,n)
        fib[i]=(fib[i-1]+fib[i-2])%MOD;
    pfb=fib;
    cir(i,1,n) (pfb[i]+=pfb[i-1])%=MOD;
    return pair(fib,pfb);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;cin>>n>>q;
    const int sqr=sqrt(n)+1;
    auto [fib,pf]=prefix_fib(n);
    VI pre(n);vector<seg> s;
    for(auto&i:pre) cin>>i;
    cir(i,1,n) (pre[i]+=pre[i-1])%=MOD;
    auto push_tag=[&](){
        VI ins(n),prex(n);vector<VI> del(n);
        for(auto&[l,r]:s)
            ++ins[l],del[r].push_back(r-l);
        lint fn2=0,fn1=0;
        cir(i,0,n){
            swap(fn1,fn2);
            prex[i]=fn1=(fn2+fn1+ins[i])%MOD;
            for(auto&x:del[i]){
                (fn1+=MOD-fib[x])%=MOD;
                if(x) (fn2+=MOD-fib[x-1])%=MOD;
            }
        }
        cir(i,1,n) (prex[i]+=prex[i-1])%=MOD;
        cir(i,0,n) (pre[i]+=prex[i])%=MOD;
        s.clear();
    };
    auto calc_tag=[&](int l,int r){
        lint res=0;
        for(auto&[lx,rx]:s){
            if(rx<l||lx>r) continue;
            if(lx<l){
                res+=(pf[min(r,rx)-lx]-
                    pf[l-lx-1]+MOD)%MOD;
            }else{
                res+=pf[min(r,rx)-lx];
            }
            res%=MOD;
        }
        return res;
    };
    cir(i,0,q){
        int op,l,r;cin>>op>>l>>r;
        if(op==1){
            s.push_back({l-1,r-1});
            if(s.size()>sqr) push_tag();
        }else{
            --l,--r;
            cout<<(((pre[r]-(l?pre[l-1]:(lint)(0)))
                +calc_tag(l,r))%MOD+MOD)%MOD<<'\n';
        }
    }
    return 0;
}
