#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n,k;cin>>n>>k;
        string s;cin>>s;
        vector<int> cnt('z'+1);
        for(auto&i:s){
            cnt[i]^=1;
        }
        cout<<(accumulate(cnt.begin(),cnt.end()
            ,0)-1<k+1?"YES":"NO")<<'\n';
    }
    return 0;
}
