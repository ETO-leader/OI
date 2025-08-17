#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n,k;cin>>n>>k;
        const auto tk=k;
        if(n==1&&k==1){
            cout<<"Yes"<<'\n';
            cout<<1<<'\n';
            return;
        }
        if((int64_t)(n)*(n+1)/2%n*k%n) return cout<<"No"<<'\n',void();
        if(k<2) return cout<<"No"<<'\n',void();
        set<vector<int>> vis;
        if(k&1){
            k-=3;
            vector<int> pa,pb,pc;
            cir(i,1,n+1) pa.emplace_back(i);
            cir(i,(n+1)/2,n+1) pb.emplace_back(i);
            cir(i,1,(n+1)/2) pb.emplace_back(i); 
            const auto s=(int64_t)(n)*(n+1)/2*3/n;
            cir(i,0,n) pc.emplace_back(s-pa[i]-pb[i]);
            vis.emplace(pa);
            vis.emplace(pb);
            vis.emplace(pc);
        }
        vector<int> p(n);
        ranges::iota(p,1);
        do{
            if((int)(vis.size())==tk) break;
            auto np=vector<int>(n);
            cir(i,0,n) np[i]=n+1-p[i];
            if(vis.contains(p)||vis.contains(np)) continue;
            vis.emplace(p);
            vis.emplace(np);
        }while(ranges::next_permutation(p).found);
        if((int)(vis.size())==tk){
            cout<<"Yes"<<'\n';
            for(auto&x:vis){
                for(auto&i:x) cout<<i<<' ';
                cout<<'\n';
            }
            vector<int64_t> s(n);
            for(auto&x:vis){
                auto aw=vector(x.begin(),x.end());
                cir(i,0,n) s[i]+=aw[i];
            }
            assert(set(s.begin(),s.end()).size()==1);
        }else{
            cout<<"No"<<'\n';
        }
    }();
    return 0;
}
