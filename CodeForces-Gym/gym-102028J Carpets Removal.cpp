#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
template<typename _Ty>
class prefixd{
private:
    vector<vector<_Ty>> cnt;
public:
    auto update(int l,int r,int al,int ar,const _Ty w){
        cnt[l][al]+=w;cnt[r+1][al]-=w;
        cnt[l][ar+1]-=w;cnt[r+1][ar+1]+=w;
    }
    auto calc(){
        cir(i,0,(int)(cnt.size())) cir(j,0,(int)(cnt.size())){
            if(i) cnt[i][j]+=cnt[i-1][j];
            if(j) cnt[i][j]+=cnt[i][j-1];
            if(i&&j) cnt[i][j]-=cnt[i-1][j-1];
        }
    }
    auto at(int x,int y) const{return cnt[x][y];};
    prefixd(int _k):cnt(_k,vector<_Ty>(_k)){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--) [](){
        int n,m;cin>>n>>m;
        vector<array<int,4>> q;
        prefixd<int> cnt(m+7);
        prefixd<long long> pre(m+7),pres(m+7);
        cir(i,0,n){
            int l,r,al,ar;cin>>l>>r>>al>>ar;
            --l;--r;--al;--ar;
            cnt.update(l,r,al,ar,1);
            pre.update(l,r,al,ar,i);
            pres.update(l,r,al,ar,1ll*i*i);
        }
        if(n<2) return cout<<0<<'\n',void();
        cnt.calc();pre.calc();pres.calc();
        clog.flush();
        auto cntc=0;
        vector<int> ansi(n);
        map<pair<int,int>,int> cntp;
        cir(i,0,m) cir(j,0,m){
            if(!cnt.at(i,j)) continue;
            ++cntc;
            if(cnt.at(i,j)>2) continue;
            if(cnt.at(i,j)==1){
                ++ansi[pre.at(i,j)];
                continue;
            }
            const auto k=sqrtl(pres.at(i,j)*2-pre.at(i,j)*pre.at(i,j));
            const auto ida=(pre.at(i,j)+k)/2;
            const auto idb=(pre.at(i,j)-k)/2;
            ++cntp[{ida,idb}];
        }
        const auto cp=ansi;
        sort(ansi.begin(),ansi.end(),greater<int>());
        auto ans=ansi[0]+ansi[1];
        ansi=cp;
        for(auto&[p,w]:cntp){
            ans=max(ans,ansi[p.first]+ansi[p.second]+w);
        }
        cout<<(cntc-ans)<<'\n';
    }();
    return 0;
}
