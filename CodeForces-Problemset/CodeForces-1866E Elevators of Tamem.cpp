#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infs=(lint)(1e12l);
static constexpr auto _infl=(lint)(1e18l);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,q;cin>>n>>q;vector<lint> a(q);
    for(auto&i:a) cin>>i;
    vector<tuple<int,int,int>> req(q);
    for(auto&[tp,u,v]:req){
        cin>>tp;
        if(tp==1) cin>>u>>v;
        else cin>>u,--u;
    }
    a.insert(a.begin(),_infs);
    req.insert(req.begin(),tuple(1,1,1));
    ++q;
    vector cost(3,a);
    vector<int> curban(3);
    cir(i,0,q){
        const auto[tp,u,v]=req[i];
        if(tp==2) curban[u]^=1;
        cir(c,0,3) if(curban[c]) cost[c][i]=_infs;
    }
    vector mn(q,vector(q,vector<lint>(3)));
    cir(i,0,q) cir(c,0,3){
        auto mnx=_infs;
        cir(j,i,q) mn[i][j][c]=(mnx=min(mnx,cost[c][j]));
    }
    auto cnt=0;
    for(auto&[tp,u,v]:req) cnt+=(tp==1);
    q=cnt;
    const auto nr=req;
    req.clear();
    vector<vector<int>> banned;
    ranges::fill(curban,false);
    vector<int> rkid;
    for(auto c=-1;auto&[tp,u,v]:nr){
        ++c;
        if(tp==2) curban[u]^=true;
        else req.emplace_back(tp,u,v),banned.push_back(curban),rkid.push_back(c);
    }
    auto check=[](const int q,auto&req,auto&banned,auto&mn,auto&rkid,auto&cost){
        vector f(q,vector(q,vector(q,_infl)));
        f[0][0][0]=0;
        const auto chkmin=[&](auto&a,auto b){
            return a=min(a,b);
        };
        cir(i,0,q-1) cir(j,0,i+1) cir(k,0,j+1){
            array order{i,j,k};
            ranges::sort(order);
            const auto ban=banned[i+1];
            do{
                const auto[x,y,z]=order;
                const auto[tpx,ux,vx]=req[x];
                const auto[tpy,uy,vy]=req[y];
                const auto[tpz,uz,vz]=req[z];
                const auto[tpi,ui,vi]=req[i+1];
                const auto rx=rkid[x],ry=rkid[y],rz=rkid[z],ri=rkid[i+1];
                if(!ban[0]) chkmin(f[i+1][y][z],f[x][y][z]+abs(ui-vx)*mn[rx][ri][0]+abs(ui-vi)*cost[0][ri]);
                if(!ban[1]) chkmin(f[x][i+1][z],f[x][y][z]+abs(ui-vy)*mn[ry][ri][1]+abs(ui-vi)*cost[1][ri]);
                if(!ban[2]) chkmin(f[x][y][i+1],f[x][y][z]+abs(ui-vz)*mn[rz][ri][2]+abs(ui-vi)*cost[2][ri]);
            }while(ranges::next_permutation(order).found);
        }
        auto ans=_infl;
        cir(i,0,q) cir(j,0,q) cir(k,0,q) if(max({i,j,k})==q-1){
            ans=min(ans,f[i][j][k]);
        }
        return ans;
    };
    const auto ans=check(q,req,banned,mn,rkid,cost);
    println("{}",ans);
    return 0;
}
