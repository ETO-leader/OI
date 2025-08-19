#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto maxv=(int)(1e5+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    vector<int> isnp(maxv),pr;
    vector<vector<pair<int,int>>> px(maxv);
    cir(i,2,maxv) if(!isnp[i]){
        pr.emplace_back(i);
        for(auto j=i;j<maxv;j+=i){
            isnp[j]=true;
            auto w=j;
            while(!(w%i)) w/=i;
            px[j].emplace_back(i,j/w);
        }
    }
    vector<vector<pair<int,int>>> vaild(7);
    cir(c,2,6) cir(x,0,(int)(pr.size())){
        if((int64_t)(pr[x])*pr[x]>maxv) break;
        auto w=pr[x];
        while(w<maxv){
            cir(i,pr[x]+1,maxv) if((int)(px[i].size())>c-1) if(px[i].front().first>pr[x]) vaild[c].emplace_back(w,i);
            w*=pr[x];
        }
    }
    while(T--) [&]{
        int n;cin>>n;
        vector<int> a(n);
        vector<int> fctc(maxv);
        for(auto&i:a) cin>>i,fctc[i]=1;
        ranges::sort(a);
        vector<int> cnt(maxv);
        for(auto i=maxv-1;i;--i){
            for(auto j=i;j<maxv;j+=i) cnt[i]+=fctc[j];
        }
        vector<int> ansstk;
        for(auto&[w,i]:vaild[max<int>(ansstk.size(),2)]) [&]{
            const auto x=(int64_t)(w)*i;
            const auto cx=(x>maxv-1?0:cnt[x]);
            if(px[i].size()<ansstk.size()) return;
            if(cnt[i]==cx) return;
            for(auto&[p,v]:px[i]) if(x/v>maxv-1) return;
            for(auto&[p,v]:px[i]) if(cnt[x/v]==cx) return;
            ansstk.clear();
            ansstk.emplace_back(w);
            for(auto&[p,v]:px[i]) ansstk.emplace_back(v);
        }();
        if(ansstk.size()<3){
            [&]{
                cir(i,1,n) if(a[i]%a[i-1]){
                    cout<<2<<'\n';
                    cout<<a[i-1]<<' '<<a[i]<<'\n';
                    return;
                }
                cout<<1<<'\n';
                cout<<a[0]<<'\n';
            }();
        }else{
            cout<<ansstk.size()<<'\n';
            vector<int> ban(maxv);
            auto pd=1ll;
            for(auto&x:ansstk) pd*=x;
            for(auto&i:ansstk){
                const auto v=pd/i;
                for(auto x=v;x<maxv;x+=v) if(fctc[x]&&(!ban[x])&&(x%pd)){
                    cout<<x<<' ';
                    ban[x]=true;
                    break;
                }
            }
            cout<<'\n';
        }
    }();
    return 0;
}
