#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;vector<int> a(n);
    for(auto&i:a) cin>>i;
    if(!(n%4)){
        cout<<"Yes"<<'\n';
    }else if(n%2){
        cout<<(ranges::count(a,1)?"Yes":"No")<<'\n';
    }else{
        auto x=false,y=false;
        cir(i,0,n) if(a[i]) x|=(i&1),y|=(!(i&1));
        cout<<((x&&y)?"Yes":"No")<<'\n';
    }
    return 0;
}
