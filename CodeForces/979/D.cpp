#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int n,q;cin>>n>>q;
        vector<int> a(n);
        for(auto&i:a) cin>>i,--i;
        string s;cin>>s;
        vector<int> nd(n);
        cir(i,0,n){
            if(a[i]>i){
                ++nd[i];
                --nd[a[i]];
            }else{
                ++nd[a[i]];
                --nd[i];
            }
        }
        cir(i,1,n) nd[i]+=nd[i-1];
        set<int> npos;
        auto check=[&](int p){
            if(npos.count(p)) npos.extract(p);
            if(nd[p]&&s[p]!='R'&&(p+1>n-1||s[p+1]!='L')) npos.insert(p);
        };
        cir(i,0,n) check(i);
        cir(i,0,q){
            int p;cin>>p;--p;
            s[p]=(s[p]=='L'?'R':'L');
            if(p) check(p-1);
            check(p);
            if(p+1<n) check(p+1);
            println("{}",npos.empty()?"YES":"NO");
        }
    }();
    return 0;
}
