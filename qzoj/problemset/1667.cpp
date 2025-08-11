#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n;cin>>n;
        unordered_set<uint64_t> cnt;
        unordered_set<uint64_t> val;
        cir(i,0,n){
            string s;cin>>s;
            auto w=(uint64_t)(0);
            cir(i,0,(int)(s.size())){
                (w*=11)+=(s[i]-'0'+1);
                if(i<(int)(s.size())-1) cnt.emplace(w);
                else val.emplace(w);
            }
        }
        auto ok=false;
        for(auto&x:val) ok|=cnt.count(x);
        cout<<(ok?"NO":"YES")<<'\n';
    }();
    return 0;
}
