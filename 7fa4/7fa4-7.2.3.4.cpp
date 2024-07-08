#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--) [&](){
        int n;cin>>n;
        vector<int> a(n),pos(n+1);
        for(auto&i:a) cin>>i;
        cir(i,0,n){
            if((a[i]&1)==(i&1))
                return cout<<-1<<'\n',void();
            pos[a[i]]=i;
        }
        stringstream ans;auto cnt=0;
        auto rev=[&](int p){
            ++cnt;ans<<p+1<<' ';
            reverse(a.begin(),a.begin()+p+1);
            cir(i,0,n) pos[a[i]]=i;
        };
        for(int w=n;w>1;w-=2){
            rev(pos[w]);rev(pos[w-1]-1);
            rev(pos[w-1]+1);rev(2);rev(w-1);
        }
        cout<<cnt<<'\n'<<ans.str()<<'\n';
    }();
    return 0;
}
