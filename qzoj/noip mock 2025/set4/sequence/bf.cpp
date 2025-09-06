#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n,l,k;cin>>n>>l>>k;
        vector<int> a(n);
        for(auto&i:a) cin>>i;
        sort(a.begin(),a.end());
        auto kth=[k](auto&a,int l,int r){
            auto x=vector<int>(a.begin()+l,a.begin()+r+1);
            sort(x.begin(),x.end(),greater<>());
            return x[k-1];
        };
        auto calc=[&](vector<int> b){
            auto res=0;
            cir(i,0,n-l+1) res+=kth(b,i,i+l-1);
            return res;
        };
        auto mn=a,mx=a;
        do{
            if(calc(mn)>calc(a)) mn=a;
            if(calc(mx)<calc(a)) mx=a;
        }while(next_permutation(a.begin(),a.end()));
        for(auto&i:mx) clog<<i<<' ';
        clog<<'\n';
        for(auto&i:mn) clog<<i<<' ';
        clog<<'\n';
        cout<<calc(mx)<<' '<<calc(mn)<<'\n';
    }();
    return 0;
}
