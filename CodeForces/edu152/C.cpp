#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
const int _inf=1e9+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n,m;cin>>n>>m;
        string s;cin>>s;
        for(auto&i:s) i-='0';
        vector<int> nx1(n),fr0(n);
        [&](){
            int __fr0=-1;
            cir(i,0,n){
                if(!s[i]) __fr0=i;
                fr0[i]=__fr0;
            }
            int __nx1=_inf;
            for(int i=n-1;~i;--i){
                if(s[i]) __nx1=i;
                nx1[i]=__nx1;
            }
        }();
        set<pair<int,int>> q;
        cir(i,0,m){
            int l,r;cin>>l>>r;--l,--r;
            l=nx1[l],r=fr0[r];
            if(l>r) l=-1,r=-1;
            q.insert({l,r});
        }
        cout<<q.size()<<'\n';
    }
    return 0;
}
