#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto b=20;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    static constexpr auto maxw=(int)(5e5);
    vector<vector<int>> fx(maxw);
    cir(i,1,maxw){
        for(auto j=i;j<maxw;j+=i) fx[j].emplace_back(i);
    }
    while(T--) [&]{
        int n,x;cin>>n>>x;vector<int> a(n);
        auto extand=(1<<b)-1;
        for(auto&i:a) cin>>i,(extand&=i);
        set<int> s;
        cir(x,0,b){
            vector<int> nc;
            cir(i,0,n) if(!(a[i]&(1<<x))) nc.emplace_back(i);
            if(nc.size()<3) for(auto&w:nc) s.emplace(w);
        }
        vector<int> ax;
        cir(i,0,n) if(!s.count(i)) ax.emplace_back(a[i]);
        auto pax=ax,sax=ax;
        cir(i,1,(int)(ax.size())) pax[i]&=pax[i-1];
        for(auto i=max((int)(ax.size())-2,-1);~i;--i) sax[i]&=sax[i+1];
        auto c=vector(s.begin(),s.end());
        cir(i,0,(int)(c.size())){
            // Type 0: both from set S
            const auto aal=(pax.empty()?((1<<b)-1):pax.back());
            cir(j,i+1,(int)(c.size())){
                auto w=aal;
                cir(k,0,(int)(c.size())) if(k!=i&&k!=j) w&=a[c[k]];
                if(w+x<gcd(a[c[i]],a[c[j]])){
                    println("Yes");
                    println("2 {} {}",a[c[i]],a[c[j]]);
                    print("{} ",n-2);
                    cir(p,0,n) if(p!=c[i]&&p!=c[j]) print("{} ",a[p]);
                    return println();
                }
            }
            // Type 1: Only one from set S
            auto w=(1<<b)-1;
            cir(p,0,(int)(c.size())) if(i!=p) w&=a[c[p]]; 
            cir(j,0,(int)(ax.size())){
                const auto uw=w&(j?pax[j-1]:((1<<b)-1))&(j+1<(int)(ax.size())?sax[j+1]:((1<<b)-1));
                if(uw+x<gcd(a[c[i]],ax[j])){
                    println("Yes");
                    println("2 {} {}",a[c[i]],ax[j]);
                    print("{} ",n-2);
                    cir(p,0,(int)(c.size())) if(p!=i) print("{} ",a[c[p]]); 
                    cir(p,0,(int)(ax.size())) if(p!=j) print("{} ",ax[p]);
                    return println();
                }
            }
        }
        // Type 2: None from set S
        map<int,int> cnt,acnt;
        for(auto&w:ax) ++cnt[w];
        auto mx=0;
        for(auto&[w,c]:cnt) for(auto&i:fx[w]) acnt[i]+=c;
        for(auto&[w,c]:acnt) if(c>1) mx=max(mx,w);
        if(mx<extand+x+1){
            println("No");
        }else{
            vector<int> nx,cx;
            for(auto&x:c) nx.emplace_back(a[x]);
            for(auto&x:ax) (x%mx?nx:cx).emplace_back(x);
            while(cx.size()>2) nx.emplace_back(cx.back()),cx.pop_back();
            println("Yes");
            println("2 {} {}",cx[0],cx[1]);
            print("{} ",n-2);
            for(auto&w:nx) print("{} ",w);
            println();
        }
    }();
    return 0;
}
