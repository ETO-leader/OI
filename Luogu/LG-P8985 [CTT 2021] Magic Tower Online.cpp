#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto v=(int)(1e4+7);
struct monster{
    lint x,y,z,a,b,l,r;
};
struct query{int g,l,d,p;};
constexpr auto highbitp(int x){
    return 31-__builtin_clz(x);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<monster> ms;
    vector<query> q;
    auto cnt=-1,qcnt=-1;
    cir(i,0,n){
        char op;cin>>op;
        if(op=='+'){
            ++cnt;
            ms.push_back(monster());
            cin>>ms[cnt].x>>ms[cnt].y>>ms[cnt].z>>ms[cnt].a>>ms[cnt].b;
            ms[cnt].l=i;ms[cnt].r=n+7;
        }else if(op=='-'){
            int id;cin>>id;--id;
            ms[id].r=i;
        }else if(op=='?'){
            ++qcnt;
            q.push_back(query());
            cin>>q[qcnt].g>>q[qcnt].l>>q[qcnt].d;
            q[qcnt].p=i;
        }
    }
    sort(ms.begin(),ms.end(),[&](auto&a,auto&b){
        return max(a.a,a.a-a.b+b.a)<max(b.a,b.a-b.b+a.a);
    });
    const auto m=(int)(ms.size()),qn=(int)(q.size());
    const auto lg=(int)(log2(m+2));
    vector<lint> g(v),l(v),d(v),fx(1<<lg),gx(1<<lg),pre(qn),ans(qn);
    auto upd=[&](int ql,int qr){
        for(auto x:{&g,&l,&d}) fill(x->begin(),x->end(),0);
        const auto ln=qr-ql+1;
        cir(s,1,(1<<ln)){
            const auto hb=highbitp(s);
            fx[s]=fx[s-(1<<hb)]+(ms[ql+hb].b-ms[ql+hb].a);
            if(s-(1<<hb)) gx[s]=max<lint>(gx[s-(1<<hb)],ms[ql+hb].a-fx[s-(1<<hb)]);
            else gx[s]=ms[ql+hb].a;
        }
        deque<pair<int,int>> st;
        cir(i,ql,qr+1){
            g[ms[i].x]|=(1<<(i-ql));
            l[ms[i].y]|=(1<<(i-ql));
            d[ms[i].z]|=(1<<(i-ql));
            st.emplace_back(ms[i].l,1<<(i-ql));
            st.emplace_back(ms[i].r+1,1<<(i-ql));
        }
        sort(st.begin(),st.end());
        cir(i,1,v) g[i]|=g[i-1],l[i]|=l[i-1],d[i]|=d[i-1];
        auto nw=0;
        cir(i,0,qn){
            while((!st.empty())&&st.front().first<q[i].p+1){
                nw^=st.front().second;st.pop_front();
            }
            const auto s=g[q[i].g]&l[q[i].l]&d[q[i].d]&nw;
            ans[i]=max(ans[i],gx[s]-pre[i]);
            pre[i]+=fx[s];
        }
    };
    for(auto i=0;i<m;i+=lg) upd(i,min(i+lg-1,m-1));
    for(auto&i:ans) cout<<i<<'\n';
    return 0;
}
