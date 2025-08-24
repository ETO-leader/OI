#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _infl=(int64_t)(1e12l);
class sp{
private:
    vector<int64_t> d;
    vector<int64_t> sd,td;
    vector<int> pos,visd,ord,fr,vis;
    auto init(int s){
        const auto n=(int)(d.size());
        vector<int> vis(n);
        sd[s]=0;
        cir(i,0,min(400,n)){
            auto mns=pair(_infl,-1);
            cir(i,0,n) if(!vis[i]) mns=min(mns,{sd[i],i});
            const auto u=mns.second;
            vis[u]=true;
            cir(i,0,n) sd[(u+i)%n]=min(sd[(u+i)%n],sd[u]+d[i]);
        }
        ord.resize(n);
        iota(ord.begin(),ord.end(),0);
        sort(ord.begin(),ord.end(),[&](auto u,auto v){return d[u]<d[v];});
    }
public:
    auto calc(int t){
        const auto n=(int)(d.size());
        auto ans=sd[t];
        priority_queue<pair<int64_t,int>,vector<pair<int64_t,int>>,greater<>> q;
        q.emplace(0,t);
        visd.emplace_back(t);
        td[t]=0;
        cir(i,0,min(400,n)){
            const auto[w,u]=q.top();q.pop();
            const auto f=fr[u];
            // cerr<<u<<": "<<pos[u]<<'\n';
            ans=min(ans,w+sd[u]);
            if(vis[u]) continue;
            vis[u]=true;
            if(u!=t){
                ++pos[f];
                if(pos[f]<n){
                    const auto v=(f+n-ord[pos[f]])%n;
                    if(td[v]>td[f]+d[ord[pos[f]]]){
                        td[v]=td[f]+d[ord[pos[f]]];
                        fr[v]=f;
                        q.emplace(td[f]+d[ord[pos[f]]],(f+n-ord[pos[f]])%n);
                        visd.emplace_back(v);
                        ans=min(ans,td[v]+sd[v]);
                    }
                }
            }
            const auto v=(u+n-ord[pos[u]])%n;
            if(td[v]>td[u]+d[ord[pos[u]]]){
                td[v]=td[u]+d[ord[pos[u]]];
                fr[v]=u;
                q.emplace(td[u]+d[ord[pos[u]]],(u+n-ord[pos[u]])%n);
                visd.emplace_back(v);
                ans=min(ans,td[v]+sd[v]);
            }
        }
        for(auto&x:visd) pos[x]=0,vis[x]=false,fr[x]=0,td[x]=_infl;
        visd.clear();
        return ans;
    }
    sp(vector<int64_t> _d,int s):d(_d),pos(_d.size()),sd(_d.size(),_infl),td(_d.size(),_infl),fr(_d.size()),vis(_d.size()){init(s);}
};
