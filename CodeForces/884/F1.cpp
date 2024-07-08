#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n,c;cin>>n>>c;
        if(c<0){
            map<int,int,greater<int>> s;
            cir(i,0,n){
                int k;cin>>k;s[k]++;
            }
            while(!s.empty()){
                auto [mx,cmx]=*s.begin();--s[mx];
                cout<<mx<<' ';
                if(!s[mx]) s.erase(s.begin());
                if(s.empty()) break;
                auto [mx2,cmx2]=*s.begin();
                if(mx2<mx+c) continue;
                auto [gt,gtx]=(*--s.upper_bound(mx+c));
                if(gt==mx2) continue;
                cout<<gt<<' ';--s[gt];
                vector<pair<int,int>> ins;
                if(!s[gt]) s.erase(gt);
                else ins.push_back({gt,s[gt]}),s.erase(gt);
                while((--s.upper_bound(mx2+c))->first!=mx2){
                    auto [mi,ci]=*(--s.upper_bound(mx2+c));
                    cout<<mi<<' ';--ci;
                    if(ci) ins.push_back({mi,ci});
                    s.erase(mi);
                }
                for(auto&i:ins) s.insert(i);
            }
            cout<<'\n';
        }else{
            map<int,int,less<int>> s;
            cir(i,0,n){
                int k;cin>>k;s[k]++;
            }
            while(!s.empty()){
                auto [mx,cmx]=*s.begin();--s[mx];
                cout<<mx<<' ';
                if(!s[mx]) s.erase(s.begin());
                if(s.empty()) break;
                auto [mx2,cmx2]=*s.begin();
                if(mx2>mx+c) continue;
                auto [gt,gtx]=(*--s.upper_bound(mx+c));
                if(gt==mx2) continue;
                cout<<gt<<' ';--s[gt];
                vector<pair<int,int>> ins;
                if(!s[gt]) s.erase(gt);
                else ins.push_back({gt,s[gt]}),s.erase(gt);
                while((--s.upper_bound(mx2+c))->first!=mx2){
                    auto [mi,ci]=*(--s.upper_bound(mx2+c));
                    cout<<mi<<' ';--ci;
                    if(ci) ins.push_back({mi,ci});
                    s.erase(mi);
                }
                for(auto&i:ins) s.insert(i);
            }
            cout<<'\n';
        }
    }
    return 0;
}
