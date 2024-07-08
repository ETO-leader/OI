#include<bits/stdc++.h>
#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
#define cirr(i,a,b) for(int i=(b)-1;i>=(a);--i)
using namespace __gnu_pbds;
using namespace std;
template<typename T>
using vector_t=unordered_map<int,T>;
using lint=long long;
const lint _inf=1e15+7;
struct seg{lint l,r;};
void init(vector<seg>&s){
    vector<seg> vs;
    const int n=s.size();
    cir(i,0,n){
        bool deltag=false;
        cir(j,i+1,n){
            if(s[j].l>s[i].r){
                vs.push_back(s[i]);deltag=true;
                break;
            }
            if(s[j].r<=s[i].r){
                deltag=true;break;
            }
        }
        if(!deltag) vs.push_back(s[i]);
    }
    s=vs;
}
lint dist(lint p,seg&s){
    return p>s.r?p-s.r:s.l-p;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n,m;cin>>n>>m;
        vector<lint> pnt(n);
        vector<seg> sgm;
        //Input
        [&](){
            set<lint> sln;
            for(auto&i:pnt) cin>>i,sln.insert(i);
            cir(i,0,m){
                int l,r;cin>>l>>r;
                if(sln.lower_bound(l)
                    ==sln.lower_bound(r))
                        sgm.push_back({l,r});
            }
            sort(pnt.begin(),pnt.end());
            sort(sgm.begin(),sgm.end(),[](seg&a,seg&b){
                return a.l==b.l?a.r>b.r:a.l<b.l;
            });
            init(sgm);
            m=sgm.size();
        }();
//        cout<<"\n\n";
//        for(auto&[l,r]:sgm) cout<<l<<' '<<r<<'\n';
        auto posi=[&](){
            vector<lint> res(n+1,m);
            int cx=0;
            cir(i,0,m) while(cx<n&&sgm[i].l>pnt[cx])
                res[cx]=i,++cx;
            return res;
        }();
//        cout<<"\n\n";
//        for(auto&i:posi) cout<<i<<' ';
//        cout<<"\n\n";
        vector<vector_t<lint>> D(n);
        lint ans=_inf;
        cir(i,0,n){
            lint mnr1=_inf,mnr2=_inf;
            if(!i){
                if(!posi[i]) D[i][posi[i]-1]=0;
                else D[i][posi[i]-1]=dist(pnt[i],sgm[0]);
                mnr1=D[i][posi[i]-1]*2,mnr2=D[i][posi[i]-1];
            }else{
                mnr1=mnr2=D[i-1][posi[i-1]];
                cir(j,posi[i-1],posi[i]){
                    mnr1=min(mnr1,D[i-1][j-1]+dist(pnt[i],sgm[j])*2);
                    mnr2=min(mnr2,D[i-1][j-1]+dist(pnt[i],sgm[j]));
                }
                D[i][posi[i]-1]=mnr2;
            }
            cir(j,posi[i],posi[i+1]){
                if(!D[i].count(j)) D[i][j]=_inf;
                D[i][j]=min({D[i][j],mnr1+dist(pnt[i],sgm[j])
                    ,mnr2+dist(pnt[i],sgm[j])*2});
            }
            if(D[i].count(m-1)) ans=min(D[i][m-1],ans);
//            cout<<i<<":\n";
//            for(auto&j:D[i]) cout<<j.first<<' '<<j.second<<'\n';
        }
        cout<<ans<<'\n';
    }
    return 0;
}
