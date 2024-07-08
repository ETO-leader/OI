#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--) [&](){
        int n;cin>>n;
        lint pre=0,cnt=0;
        cir(i,0,n){
            lint x;cin>>x;
            pre+=x;cnt+=(x&1);
            if(!i){
                cout<<pre<<' ';
            }else{
                //Mod 3=1
                if(cnt%3==1) cout<<pre-(cnt/3+1)<<' ';
                else cout<<pre-cnt/3<<' ';
                //cout<<pre-max<lint>(cnt/3,0)<<' ';
            }
        }
        cout<<'\n';
    }();
    return 0;
}