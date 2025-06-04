#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,k,q;cin>>n>>k>>q;
    vector<int> a(n);
    for(int i=0;i<n;++i) cin>>a[i],--a[i];
    if(n<5007&&q<5007){
        function<int()> check=[&]{
            int res=n+7;
            int l=0;
            vector<int> cnt(k);
            int vaild=0;
            cir(r,0,n){
                vaild+=(!cnt[a[r]]);
                ++cnt[a[r]];
                while(cnt[a[l]]>1) --cnt[a[l]],++l;
                if(vaild==k) res=min(res,r-l+1);
            }
            return res>n?-1:res;
        };
        cir(i,0,q){
            int op;cin>>op;
            if(op==1){
                int p,w;cin>>p>>w;--p;--w;
                a[p]=w;
            }else{
                cout<<check()<<'\n';
            }
        }
    }else{
        const int sqr=3000;
        multiset<int> ans;
        vector<pair<int,int> > blcs;
        vector<vector<int> > ublc(n);
        vector<int> blcans(sqr+7);
        function<void(int)> rebuild=[&](int b){
            if(ans.find(blcans[b])!=ans.end()) ans.erase(ans.lower_bound(blcans[b]));
            int ql=blcs[b].first,qr=blcs[b].second;
            int res=n+7;
            int l=ql;
            vector<int> cnt(k);
            int vaild=0;
            cir(r,ql,qr){
                vaild+=(!cnt[a[r]]);
                ++cnt[a[r]];
                while(cnt[a[l]]>1) --cnt[a[l]],++l;
                if(vaild==k) res=min(res,r-l+1);
            }
            ans.insert(res);
            blcans[b]=res;
        };
        for(int i=0;i<n;i+=sqr){
            int id=blcs.size();
            blcs.push_back(make_pair(i,min(i+sqr-1,n-1)));
            cir(j,blcs[id].first,blcs[id].second+1) ublc[j].push_back(id);
        }
        for(int i=500;i<n;i+=sqr){
            int id=blcs.size();
            blcs.push_back(make_pair(i,min(i+sqr-1,n-1)));
            cir(j,blcs[id].first,blcs[id].second+1) ublc[j].push_back(id);
        }
        if(n>sqr){
            int id=blcs.size();
            blcs.push_back(make_pair(n-sqr,n-1));
            cir(j,blcs[id].first,blcs[id].second+1) ublc[j].push_back(id);
        }
        cir(i,0,(int)(blcs.size())) rebuild(i);
        cir(i,0,q){
            int op;cin>>op;
            if(op==1){
                int p,v;cin>>p>>v;--p;--v;
                a[p]=v;
                for(int j=0;j<(int)ublc[p].size();++j) rebuild(ublc[p][j]);
            }else{
                int w=*ans.begin();
                cout<<(w>n?-1:w)<<'\n';
            }
        }
    }
    return 0;
}
