#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    string s;
    while(cin>>s&&s!="#"){
        string t;cin>>t;
        const auto n=(int)(s.size());
        vector<int> f(n+1);
        cir(i,1,n+1){
            f[i]=f[i-1];
            if(i>(int)(t.size())-1&&s.substr(i-(int)(t.size()),t.size())==t){
                f[i]=max(f[i-(int)(t.size())]+1,f[i]);
            }
        }
        cout<<f[n]<<'\n';
    }
    return 0;
}
