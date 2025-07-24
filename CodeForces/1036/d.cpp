#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n,k;cin>>n>>k;
        vector<lint> a(n);
        for(auto&i:a) cin>>i;
        auto x=a;
        if(k<3) return cout<<"YES"<<'\n',void();
        ranges::sort(x);
        const auto w=x[k-2];
        deque<int> v;
        for(auto&x:a) if(x<w+1) v.emplace_back(x);
        auto ans=0;
        while(!v.empty()){
            if(v.front()==v.back()){
                ans+=min<int>(v.size(),2);
                v.pop_front();
                if(!v.empty()) v.pop_back();
            }else{
                if(v.front()==w) v.pop_front();
                else if(v.back()==w) v.pop_back();
                else return cout<<"NO"<<'\n',void();
            }
        }
        cout<<(ans>k-2?"YES":"NO")<<'\n';
    }();
    return 0;
}
