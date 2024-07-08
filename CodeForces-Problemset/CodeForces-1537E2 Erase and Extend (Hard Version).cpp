#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,k;cin>>n>>k;
    string s,s2;cin>>s;
    auto prefix_t=[&](int x){
        return s2[x%s2.size()];
    };
    int lspos=1;s2.push_back(s[0]);
    cir(i,1,n){
        if(s[i]>prefix_t(i)) break;
        if(s[i]<prefix_t(i)){
            cir(j,lspos,i+1) s2.push_back(s[j]);
            lspos=i+1;
        }
    }
    cir(i,0,k) cout<<prefix_t(i);
    cout<<'\n';
    return 0;
}
