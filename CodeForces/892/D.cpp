#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
struct qry{int p,type,id;};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;cin>>n;vector<qry> qx;
        vector<int> ansi(n);
        cir(i,0,n){
            int l,r,a,b;cin>>l>>r>>a>>b;
            ansi[i]=b;
            qx.push_back({b,1,i});
            qx.push_back({l,-1,i});
        }
        int q;cin>>q;vector<int> ans(q);
        cir(i,0,q){
            int&p=ans[i];cin>>p;
            qx.push_back({p,0,i});
        }
        multiset<int,greater<int>> s;
        sort(qx.begin(),qx.end(),[](qry&a,qry&b){
            return a.p==b.p?a.type>b.type:a.p>b.p;
        });
        for(auto&[p,type,id]:qx){
            if(type==1){
                if(!s.empty()) ansi[id]=*s.begin();
                s.insert(ansi[id]);
            }else if(!type){
                if(!s.empty())
                    ans[id]=max(ans[id],*s.begin());
            }else{
                s.extract(ansi[id]);
            }
        }
        for(auto&i:ans) cout<<i<<' ';
        cout<<'\n';
    }
    return 0;
}
