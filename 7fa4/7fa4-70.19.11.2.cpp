#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _inf=(int)(1e9+7);
class railway{
public:
    int pos,type;
    railway(int _p,int _t):pos(_p),type(_t){}
};
class event{
public:
    int type;
    union{
        railway rail;
        pair<int,int> pos;
    };
    event(int _tp,int _a,int _b):type(_tp){
        if(_tp) pos=pair(_a,_b);
        else rail=railway(_a,_b);
    }
};
auto vaild_time(const int r,const int c,map<int,vector<event>> info,vector<pair<pair<int,int>,pair<int,int>>> q){
    auto global_airport=_inf;
    auto airport_vaild=false;
    auto global_railway=_inf;
    auto x_railway=false,y_railway=false;
    vector rail_airport_x(r,_inf),rail_airport_y(c,_inf);
    vector contains_x(r,false),contains_y(c,false);
    vector in_use_x(r,false),in_use_y(c,false);
    vector unlock_x(r,_inf),unlock_y(c,_inf);
    map<pair<int,int>,int> airport;
    for(auto&[unlock,lst]:info) for(auto&x:lst){
        if(x.type){                            // Is an airport
            airport[x.pos]=unlock;
            if(in_use_x[x.pos.first]||in_use_y[x.pos.second]){
                airport_vaild=true;
            }
            if(global_railway<_inf&&global_airport==_inf&&(in_use_x[x.pos.first]||in_use_y[x.pos.second])){
                global_airport=unlock;
            }
            contains_x[x.pos.first]=true;
            contains_y[x.pos.second]=true;
            if(in_use_x[x.pos.first]) rail_airport_x[x.pos.first]=min(rail_airport_x[x.pos.first],unlock);
            if(in_use_y[x.pos.second]) rail_airport_y[x.pos.second]=min(rail_airport_y[x.pos.second],unlock);
        }else if(!x.rail.type){                // On direct X
            x_railway=true;
            in_use_x[x.rail.pos]=true;
            if(contains_x[x.rail.pos]){
                rail_airport_x[x.rail.pos]=unlock;
                airport_vaild=true;
                if(global_railway<_inf&&global_airport==_inf) global_airport=unlock;
            }
            unlock_x[x.rail.pos]=unlock;
        }else{                                 // On direct Y
            y_railway=true;
            in_use_y[x.rail.pos]=true;
            if(contains_y[x.rail.pos]){
                rail_airport_y[x.rail.pos]=unlock;
                airport_vaild=true;
                if(global_railway<_inf&&global_airport==_inf) global_airport=unlock;
            }
            if(contains_y[x.rail.pos]) rail_airport_y[x.rail.pos]=unlock;
            unlock_y[x.rail.pos]=unlock;
        }
        if(x_railway&&y_railway&&(global_railway==_inf)){
            global_railway=unlock;
            if(airport_vaild&&global_airport==_inf) global_airport=unlock;
        }
    }
    vector<int> ans(q.size());
    for(auto cnt=-1;auto&[u,v]:q){
        ++cnt;
        if(u==v){
            ans[cnt]=0;
            continue;
        }
        const auto[ux,uy]=u;
        const auto[vx,vy]=v;
        ans[cnt]=min({
            max({
                global_railway,
                min({
                    unlock_x[ux],
                    unlock_y[uy]
                }),
                min({
                    unlock_x[vx],
                    unlock_y[vy]
                })
            }),
            max({
                min(
                    rail_airport_x[ux],
                    rail_airport_y[uy]
                ),
                min(
                    rail_airport_x[vx],
                    rail_airport_y[vy]
                ),
            })
        });
        if(ux==vx){
            ans[cnt]=min({ans[cnt],unlock_x[ux]});
        }
        if(uy==vy){
            ans[cnt]=min({ans[cnt],unlock_y[uy]});
        }
        if(airport.count({ux,uy})){
            ans[cnt]=min({
                ans[cnt],
                max({
                    min({
                        global_airport,
                        rail_airport_x[vx],
                        rail_airport_y[vy]
                    }),
                    min({
                        unlock_x[vx],
                        unlock_y[vy]
                    }),
                    airport[{ux,uy}]
                })
            });
        }
        if(airport.count({vx,vy})){
            ans[cnt]=min({
                ans[cnt],
                max({
                    min({
                        global_airport,
                        rail_airport_x[ux],
                        rail_airport_y[uy]
                    }),
                    min({
                        unlock_x[ux],
                        unlock_y[uy]
                    }),
                    airport[{vx,vy}]
                })
            });
        }
        if(airport.count({ux,uy})&&airport.count({vx,vy})){
            ans[cnt]=min({ans[cnt],max({airport[{ux,uy}],airport[{vx,vy}]})});
        }
    }
    return ans;
}
auto min_cost(const int r,const int c,const int q,map<int,vector<event>> info,map<int,vector<tuple<pair<int,int>,pair<int,int>,int>>> t,vector<int> cx,vector<int> cy,const auto ca){
    vector contains_x(r,false),contains_y(c,false);
    vector in_use_x(r,false),in_use_y(c,false);
    vector unlock_x(r,_inf),unlock_y(c,_inf);
    map<pair<int,int>,int> airport;
    vector ans(q,_inf);
    auto min_x=_inf,min_y=_inf;
    auto airway_min_x=_inf,airway_min_y=_inf;
    for(auto&[unlock,lst]:info){
        for(auto&x:lst){
            if(x.type){                        // Is an airport
                airport[x.pos]=unlock;
                contains_x[x.pos.first]=true;
                contains_y[x.pos.second]=true;
                if(in_use_x[x.pos.first]) airway_min_x=min(airway_min_x,cx[x.pos.first]);
                if(in_use_y[x.pos.second]) airway_min_y=min(airway_min_y,cy[x.pos.second]);
            }else if(!x.rail.type){            // On direct X
                in_use_x[x.rail.pos]=true;
                if(contains_x[x.rail.pos]) airway_min_x=min(airway_min_x,cx[x.rail.pos]);
                unlock_x[x.rail.pos]=unlock;
                min_x=min(min_x,cx[x.rail.pos]);
            }else{                             // On direct Y
                in_use_y[x.rail.pos]=true;
                if(contains_y[x.rail.pos]) airway_min_y=min(airway_min_y,cy[x.rail.pos]);
                unlock_y[x.rail.pos]=unlock;
                min_y=min(min_y,cy[x.rail.pos]);
            }
        }
        for(auto&[u,v,id]:t[unlock]){
            const auto[ux,uy]=u;
            const auto[vx,vy]=v;
            if(u==v){
                ans[id]=0;
                continue;
            }
            if(in_use_x[ux]&&in_use_y[vy]){    // Type 'L' - 1
                ans[id]=min(ans[id],cx[ux]+cy[vy]);
            }
            if(in_use_y[uy]&&in_use_x[vx]){    // Type 'L' - 2
                ans[id]=min(ans[id],cy[uy]+cx[vx]);
            }
            if(in_use_x[ux]&&in_use_x[vx]){    // Type 'H' - 1
                ans[id]=min(ans[id],cx[ux]+cx[vx]+min_y);
            }
            if(in_use_y[uy]&&in_use_y[vy]){    // Type 'H' - 2
                ans[id]=min(ans[id],cy[uy]+cy[vy]+min_x);
            }
            if(ux==vx&&in_use_x[ux]){          // Type 'I' - 1
                ans[id]=min(ans[id],cx[ux]);
            }
            if(uy==vy&&in_use_y[uy]){          // Type 'I' - 2
                ans[id]=min(ans[id],cy[uy]);
            }
            auto min_air_u=_inf,min_air_v=_inf;
            if(airport.count(u)) min_air_u=0;
            if(in_use_x[ux]&&contains_x[ux]){  // Type 'I' - A1
                min_air_u=min(min_air_u,cx[ux]);
            }
            if(in_use_y[uy]&&contains_y[uy]){  // Type 'I' - A2
                min_air_u=min(min_air_u,cy[uy]);
            }
            if(in_use_x[ux]){                  // Type 'L' - A1
                min_air_u=min(min_air_u,cx[ux]+airway_min_y);
            }
            if(in_use_y[uy]){                  // Type 'L' - A2
                min_air_u=min(min_air_u,cy[uy]+airway_min_x);
            }
            if(in_use_x[ux]){                  // Type 'H' - A1
                min_air_u=min(min_air_u,cx[ux]+min_y+airway_min_x);
            }
            if(in_use_y[uy]){                  // Type 'H' - A2
                min_air_u=min(min_air_u,cy[uy]+min_x+airway_min_y);
            }
            if(airport.count(v)) min_air_v=0;
            if(in_use_x[vx]&&contains_x[vx]){  // Type 'I' - A1
                min_air_v=min(min_air_v,cx[vx]);
            }
            if(in_use_y[vy]&&contains_y[vy]){  // Type 'I' - A2
                min_air_v=min(min_air_v,cy[vy]);
            }
            if(in_use_x[vx]){                  // Type 'L' - A1
                min_air_v=min(min_air_v,cx[vx]+airway_min_y);
            }
            if(in_use_y[vy]){                  // Type 'L' - A2
                min_air_v=min(min_air_v,cy[vy]+airway_min_x);
            }
            if(in_use_x[vx]){                  // Type 'H' - A1
                min_air_v=min(min_air_v,cx[vx]+min_y+airway_min_x);
            }
            if(in_use_y[vy]){                  // Type 'H' - A2
                min_air_v=min(min_air_v,cy[vy]+min_x+airway_min_y);
            }
            ans[id]=min(ans[id],min_air_u+min_air_v+ca);
        }
    }
    return ans;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int r,c;cin>>r>>c;
    vector<int> tlx(r),tly(c);
    vector<int> cx(r),cy(c);
    for(auto&i:cx) cin>>i;
    for(auto&i:cy) cin>>i;
    int m;cin>>m;
    cir(i,0,m){
        int x,y,d;cin>>x>>y>>d;--x;--y;
        tlx[x]=max(tlx[x],d);
        tly[y]=max(tly[y],d);
    }
    int a,ca;cin>>a>>ca;
    vector<tuple<int,int,int>> airport(a);
    for(auto&[x,y,d]:airport) cin>>x>>y>>d,--x,--y;
    int q;cin>>q;
    vector<pair<pair<int,int>,pair<int,int>>> qx(q);
    for(auto&[u,v]:qx){
        cin>>u.first>>u.second>>v.first>>v.second;
        --u.first;--u.second;--v.first;--v.second;
    }
    map<int,vector<event>> info;
    info.emplace(0,vector<event>());
    cir(x,0,r) info[tlx[x]].emplace_back(0,x,0);
    cir(y,0,c) info[tly[y]].emplace_back(0,y,1);
    for(auto&[x,y,d]:airport) info[d].emplace_back(1,x,y);
    const auto ans=vaild_time(r,c,info,qx);
    map<int,vector<tuple<pair<int,int>,pair<int,int>,int>>> t;
    cir(i,0,q) t[ans[i]].emplace_back(qx[i].first,qx[i].second,i);
    const auto alx=min_cost(r,c,q,info,t,cx,cy,ca);
    cir(i,0,q) cout<<ans[i]<<' '<<alx[i]<<'\n';
    return 0;
}
