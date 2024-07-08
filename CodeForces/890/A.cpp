#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
const int _inf=1e9+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;cin>>n;vector<int> v(n);
        for(auto&i:v) cin>>i;
        reverse(v.begin(),v.end());
        cout<<[&](){
            int res=0,w=_inf;
            for(auto&i:v){
                if(i>w) res=max(res,i);
                w=min(w,i);
            }
            return res;
        }()<<'\n';
    }
    return 0;
}
