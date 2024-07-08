#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int a,b;cin>>a>>b;
        set<pair<int,int>> sp;
        if(!(a&1)) sp.insert(pair(a/2,b*2));
        if(!(b&1)) sp.insert(pair(a*2,b/2));
        bool ans=false;
        for(auto&[x,y]:sp){
            ans|=(!((a==x&&b==y)||(a==y&&b==x)));
        } 
        cout<<(ans?"Yes\n":"No\n");
    }
    return 0;
}
