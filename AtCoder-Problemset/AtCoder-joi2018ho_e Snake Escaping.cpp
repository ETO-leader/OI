#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
const auto split(const string s){
    vector<int> b,r,q;
    for(auto c=0;auto&i:s){
        if(i=='0') b.push_back(c++);
        else if(i=='1') r.push_back(c++);
        else q.push_back(c++);
    }
    return tuple(b,r,q);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int l,n;cin>>l>>n;
    vector<int> val(1<<l);
    for(char c;auto&i:val) cin>>c,i=c-'0';
    auto f=val,g=val;
    cir(i,0,l) cir(w,0,(1<<l)){
        if(w&(1<<i)){
            f[w]+=f[w^(1<<i)];
        }else{
            g[w]+=g[w^(1<<i)];
        }
    }
    cir(i,0,n){
        const auto[b,r,q](split([](){
            string s;cin>>s;
            reverse(s.begin(),s.end());
            return s;
        }()));
        auto ans=0;
        function<void(int,int)> dfsq=[&](int x,int s){
            if(x==(int)(q.size()))
                return ans+=val[s],void();
            dfsq(x+1,s);dfsq(x+1,s|(1<<q[x]));
        };
        function<void(int,int,int)> dfsb=[&](int x,int k,int s){
            if(x==(int)(b.size()))
                return ans+=k*g[s],void();
            dfsb(x+1,k,s);dfsb(x+1,-k,s|(1<<b[x]));
        };
        function<void(int,int,int)> dfsr=[&](int x,int k,int s){
            if(x==(int)(r.size()))
                return ans+=k*f[s],void();
            dfsr(x+1,-k,s);dfsr(x+1,k,s|(1<<r[x]));
        };
        auto szq=0,szr=0;
        for(const auto&x:q) szq|=(1<<x);
        for(const auto&x:r) szr|=(1<<x);
        if((int)(q.size())<l/3+1) dfsq(0,szr);
        else if((int)(b.size())<l/3+1) dfsb(0,1,szr);
        else dfsr(0,1,szq);
        cout<<ans<<'\n';
    }
    return 0;
}
