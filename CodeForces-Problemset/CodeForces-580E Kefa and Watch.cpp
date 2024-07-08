#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
const int nx=1e5+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,a,b;cin>>n>>a>>b;
    array<char,nx> s;
    cir(i,0,n) cin>>s[i];
    cir(i,0,a+b){
        int op,l,r,k;cin>>op>>l>>r>>k;
        if(op==1) memset(s.begin()+l-1
            ,k+'0',r-l+1);
        else cout<<(memcmp(s.begin()+l-1,s.begin()
            +l+k-1,r-l-k+1)?"NO":"YES")<<'\n';
    }
    return 0;
}
