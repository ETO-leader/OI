#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n;cin>>n;vector<int> a(n),b(n);
        for(auto&i:a) cin>>i;
        for(auto&i:b) cin>>i;
        auto cntf=0,p=-1;
        auto cnt=0;
        stringstream op;
        cir(i,0,n){
            if(a[i]==b[i]) ++cntf,p=i;
        }
        if(cntf>1||(cntf&&(!(n&1)))) return cout<<"-1"<<'\n',void();
        if(cntf&&(p!=n/2)){
            swap(a[p],a[n/2]);
            swap(b[p],b[n/2]);
            op<<p+1<<' '<<n/2+1<<'\n';
            ++cnt;
        }
        map<pair<int,int>,int> pos;
        set<pair<int,int>> chked;
        cir(i,0,n) pos[{a[i],b[i]}]=i;
        for(auto&[x,p]:pos){
            if(!pos.contains({x.second,x.first})) return cout<<"-1"<<'\n',void();
        }
        cir(i,0,n) if(!chked.contains({a[i],b[i]})){
            const auto p=pos[{b[i],a[i]}];
            if(p!=n-i-1){
                ++cnt;
                op<<n-i<<' '<<p+1<<'\n';
                swap(pos[{a[n-i-1],b[n-i-1]}],pos[{b[i],a[i]}]);
                swap(a[n-i-1],a[p]);
                swap(b[n-i-1],b[p]);
            }
            chked.emplace(a[i],b[i]);
            chked.emplace(b[i],a[i]);
        }
        cout<<cnt<<'\n';
        cout<<op.str();
    }();
    return 0;
}
