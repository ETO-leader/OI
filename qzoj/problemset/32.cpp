#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    string s;cin>>s;
    const auto n=(int)(s.size());
    auto cmp=[&](int i,int j,int p,int k){
        while(i<j&&s[i]=='0') ++i;
        while(p<k&&s[p]=='0') ++p;
        if(j-i>k-p) return false;
        if(j-i<k-p) return true;
        cir(x,0,j-i+1){
            if(s[i+x]>s[p+x]) return false;
            if(s[i+x]<s[p+x]) return true;
        }
        return false;
    };
    vector<int> f(n);
    cir(i,1,n) cir(j,0,i){
        if(cmp(f[j],j,j+1,i)) f[i]=j+1;
    }
    const auto p=f[n-1];
    if(!p){
        cout<<s<<'\n';
    }else{
        vector<int> g(p);
        g[p-1]=p-1;
        for(auto i=p-1;~i;--i){
            if(cmp(i,p-1,p,n-1)) g[i]=p-1;
            else cir(j,i+1,p){
                if(!cmp(i,j-1,p,n-1)) break;
                if(cmp(i,j-1,j,g[j])) g[i]=j-1;
            }
        }
        auto x=0;
        while(x<p){
            cir(i,x,g[x]+1) cout<<s[i];
            cout<<',';
            x=g[x]+1;
        }
        cir(i,p,n) cout<<s[i];
        cout<<'\n';
    }
    return 0;
}
