#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;

extern auto count(int x){
    println(cout,"A {}",x);
    cout.flush();
    int c;cin>>c;
    return c;
}

extern auto remove(int x){
    println(cout,"B {}",x);
    cout.flush();
    int c;cin>>c;
    return c;
}

extern auto answer(int x){
    println(cout,"C {}",x);
    cout.flush();
}

extern void interactor(const int);

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    interactor(n);
    return 0;
}

class mathbase{
public:
    auto primes(const int n){
        vector isp(n+1,true);
        vector<int> res;
        cir(i,2,n+1){
            if(!isp[i]) continue;
            res.push_back(i);
            for(auto x=i*2;x<n+1;x+=i) isp[x]=false;
        }
        return res;
    }
} math;

extern void interactor(const int n){
    const auto sqr=(int)(sqrt(n)+1);
    auto ans=1;
    const auto pr=math.primes(n);
    const auto blocksiz=95;
    map<int,vector<int>> pos;
    auto bkc=0;
    for(auto&i:pr){
        if(i<sqr){
            pos[0].push_back(i);
        }else{
            if((int)(pos[bkc].size())>blocksiz) ++bkc;
            pos[bkc].push_back(i);
        }
    }
    auto lascnt=n;
    cir(i,1,n+1) if(pos.contains(i)){
        const auto px=pos[i];
        auto delcnt=0;
        for(auto&p:px) delcnt+=remove(p);
        const auto curcnt=count(1);
        if(lascnt-curcnt!=delcnt) for(auto&p:px) if(count(p)) ans*=p;
        lascnt=curcnt;
    }
    if(pos.count(0)) for(auto&p:pos[0]){
        remove(p);
        for(auto x=p;x<n+1&&count(x);x*=p) ans*=p;
    }
    answer(ans);
}
