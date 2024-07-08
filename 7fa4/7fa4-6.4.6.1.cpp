#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
class ek_algorithm{
private:
    struct edge{
        int v,fl,w,rev;
    };
    vector<vector<edge>> gr;
    auto spfa(int ux,int vx){
        queue<int> q;q.push(ux);
        const auto n=(int)(gr.size());
        vector<int> dis(n,_inf),inq(n),fx(n),fe(n);
        dis[ux]=0;
        while(!q.empty()){
            const auto u=q.front();q.pop();
            inq[u]=false;
            for(auto c=-1;auto&[v,fl,w,rev]:gr[u]){
                ++c;
                if(!fl) continue;
                if(dis[u]+w>dis[v]-1) continue;
                dis[v]=dis[u]+w;fx[v]=u;fe[v]=c;
                if(!inq[v]) q.push(v);
                inq[v]=true;
            }
        }
        if(dis[vx]==_inf) return pair(-1,-1);
        auto u=vx,fl=_inf;
        while(u!=ux){
            fl=min(fl,gr[fx[u]][fe[u]].fl);
            u=fx[u];
        }
        u=vx;
        while(u!=ux){
            gr[fx[u]][fe[u]].fl-=fl;
            gr[u][gr[fx[u]][fe[u]].rev].fl+=fl;
            u=fx[u];
        }
        return pair(fl,dis[vx]*fl);
    }
public:
    auto insert(int u,int v,int fl,int w,bool tpdir){
        if(!tpdir) swap(u,v);
        gr[u].push_back({v,fl,w,(int)(gr[v].size())});
        gr[v].push_back({u,0,-w,(int)(gr[u].size())-1});
    }
    auto flow(int s,int t){
        auto fl=0,cst=0;
        while(true){
            const auto[fli,csti]=spfa(s,t);
            if(fli<0) break;
            fl+=fli;cst+=csti;
        }
        return pair(fl,cst);
    }
    ek_algorithm(int n):gr(n){}
};
class nodegen{
private:
    int cnt;
public:
    auto operator()(){return cnt++;}
    auto count(){return cnt;}
    nodegen():cnt(0){}
};
enum{leftdir,updir,rightdir,downdir};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;
    vector<vector<array<int,4>>> pid(
        n,vector<array<int,4>>(m));
    nodegen ngen;
    const auto s=ngen();
    cir(i,0,n) cir(j,0,m) cir(x,0,4){
        auto&pdi=pid[i][j];
        if(!pdi[x]) pdi[x]=ngen();
    }
    vector<vector<int>> nid(n,vector<int>(m));
    for(auto&i:nid) for(auto&x:i) x=ngen();
    const auto t=ngen();
    ek_algorithm gr(ngen.count());
    cir(i,0,n) cir(j,0,m){
        if(i){
            gr.insert(pid[i][j][updir],pid[i-1][j][downdir],1,0,false);
            gr.insert(pid[i][j][updir],pid[i-1][j][downdir],1,0,true);
        }
        if(j){
            gr.insert(pid[i][j][leftdir],pid[i][j-1][rightdir],1,0,false);
            gr.insert(pid[i][j][leftdir],pid[i][j-1][rightdir],1,0,true);
        }
    }
    auto cntk=0,cntx=0;
    cir(i,0,n) cir(j,0,m){
        int tp;cin>>tp;
        if(!tp) continue;
        const auto tpn=!((i+j)&1);
        const auto spn=tpn?s:t;
        const auto&idi=nid[i][j];
        const auto&pdi=pid[i][j];
        switch(tp){
            // Type "Q"
            case 1:{ // 0 0 0 1, Up
                if(tpn) cntk+=1;
                else cntx+=1;
                gr.insert(spn,idi,1,0,tpn);
                gr.insert(idi,pdi[updir],1,0,tpn);
                gr.insert(pdi[updir],pdi[leftdir],1,1,tpn);
                gr.insert(pdi[updir],pdi[rightdir],1,1,tpn);
                gr.insert(pdi[updir],pdi[downdir],1,2,tpn);
                break;
            }
            case 2:{ // 0 0 1 0, Right
                if(tpn) cntk+=1;
                else cntx+=1;
                gr.insert(spn,idi,1,0,tpn);
                gr.insert(idi,pdi[rightdir],1,0,tpn);
                gr.insert(pdi[rightdir],pdi[updir],1,1,tpn);
                gr.insert(pdi[rightdir],pdi[downdir],1,1,tpn);
                gr.insert(pdi[rightdir],pdi[leftdir],1,2,tpn);
                break;
            }
            case 4:{ // 0 1 0 0, Down
                if(tpn) cntk+=1;
                else cntx+=1;
                gr.insert(spn,idi,1,0,tpn);
                gr.insert(idi,pdi[downdir],1,0,tpn);
                gr.insert(pdi[downdir],pdi[leftdir],1,1,tpn);
                gr.insert(pdi[downdir],pdi[rightdir],1,1,tpn);
                gr.insert(pdi[downdir],pdi[updir],1,2,tpn);
                break;
            }
            case 8:{ // 1 0 0 0, Left
                if(tpn) cntk+=1;
                else cntx+=1;
                gr.insert(spn,idi,1,0,tpn);
                gr.insert(idi,pdi[leftdir],1,0,tpn);
                gr.insert(pdi[leftdir],pdi[updir],1,1,tpn);
                gr.insert(pdi[leftdir],pdi[downdir],1,1,tpn);
                gr.insert(pdi[leftdir],pdi[rightdir],1,2,tpn);
                break;
            }
            // type "I"
            case 5:{ // 0 1 0 1, Up & Down
                if(tpn) cntk+=2;
                else cntx+=2;
                gr.insert(spn,idi,2,0,tpn);
                gr.insert(idi,pdi[updir],1,0,tpn);
                gr.insert(idi,pdi[downdir],1,0,tpn);
                break;
            }
            case 10:{ // 1 0 1 0, Left & Right
                if(tpn) cntk+=2;
                else cntx+=2;
                gr.insert(spn,idi,2,0,tpn);
                gr.insert(idi,pdi[leftdir],1,0,tpn);
                gr.insert(idi,pdi[rightdir],1,0,tpn);
                break;
            }
            // type "L"
            case 3:{ // 0 0 1 1, Up & Right
                if(tpn) cntk+=2;
                else cntx+=2;
                gr.insert(spn,idi,2,0,tpn);
                gr.insert(idi,pdi[updir],1,0,tpn);
                gr.insert(idi,pdi[rightdir],1,0,tpn);
                gr.insert(pdi[updir],pdi[downdir],1,1,tpn);
                gr.insert(pdi[rightdir],pdi[leftdir],1,1,tpn);
                break;
            }
            case 12:{ // 1 1 0 0, Down & Left
                if(tpn) cntk+=2;
                else cntx+=2;
                gr.insert(spn,idi,2,0,tpn);
                gr.insert(idi,pdi[downdir],1,0,tpn);
                gr.insert(idi,pdi[leftdir],1,0,tpn);
                gr.insert(pdi[downdir],pdi[updir],1,1,tpn);
                gr.insert(pdi[leftdir],pdi[rightdir],1,1,tpn);
                break;
            }
            case 6:{ // 0 1 1 0, Down & Right
                if(tpn) cntk+=2;
                else cntx+=2;
                gr.insert(spn,idi,2,0,tpn);
                gr.insert(idi,pdi[downdir],1,0,tpn);
                gr.insert(idi,pdi[rightdir],1,0,tpn);
                gr.insert(pdi[downdir],pdi[updir],1,1,tpn);
                gr.insert(pdi[rightdir],pdi[leftdir],1,1,tpn);
                break;
            }
            case 9:{ // 1 0 0 1, Up & Left
                if(tpn) cntk+=2;
                else cntx+=2;
                gr.insert(spn,idi,2,0,tpn);
                gr.insert(idi,pdi[updir],1,0,tpn);
                gr.insert(idi,pdi[leftdir],1,0,tpn);
                gr.insert(pdi[updir],pdi[downdir],1,1,tpn);
                gr.insert(pdi[leftdir],pdi[rightdir],1,1,tpn);
                break;
            }
            // type "T"
            case 7:{ // 0 1 1 1 Up & Down & Right
                if(tpn) cntk+=3;
                else cntx+=3;
                gr.insert(spn,idi,3,0,tpn);
                gr.insert(idi,pdi[updir],1,0,tpn);
                gr.insert(idi,pdi[downdir],1,0,tpn);
                gr.insert(idi,pdi[rightdir],1,0,tpn);
                gr.insert(pdi[updir],pdi[leftdir],1,1,tpn);
                gr.insert(pdi[downdir],pdi[leftdir],1,1,tpn);
                gr.insert(pdi[rightdir],pdi[leftdir],1,2,tpn);
                break;
            }
            case 11:{ // 1 0 1 1 Up & Left & Right
                if(tpn) cntk+=3;
                else cntx+=3;
                gr.insert(spn,idi,3,0,tpn);
                gr.insert(idi,pdi[updir],1,0,tpn);
                gr.insert(idi,pdi[leftdir],1,0,tpn);
                gr.insert(idi,pdi[rightdir],1,0,tpn);
                gr.insert(pdi[updir],pdi[downdir],1,2,tpn);
                gr.insert(pdi[leftdir],pdi[downdir],1,1,tpn);
                gr.insert(pdi[rightdir],pdi[downdir],1,1,tpn);
                break;
            }
            case 13:{ // 1 1 0 1 Up & Down & Left
                if(tpn) cntk+=3;
                else cntx+=3;
                gr.insert(spn,idi,3,0,tpn);
                gr.insert(idi,pdi[updir],1,0,tpn);
                gr.insert(idi,pdi[leftdir],1,0,tpn);
                gr.insert(idi,pdi[downdir],1,0,tpn);
                gr.insert(pdi[updir],pdi[rightdir],1,1,tpn);
                gr.insert(pdi[leftdir],pdi[rightdir],1,2,tpn);
                gr.insert(pdi[downdir],pdi[rightdir],1,1,tpn);
                break;
            }
            case 14:{ // 1 1 1 0 Down & Left & Right
                if(tpn) cntk+=3;
                else cntx+=3;
                gr.insert(spn,idi,3,0,tpn);
                gr.insert(idi,pdi[downdir],1,0,tpn);
                gr.insert(idi,pdi[leftdir],1,0,tpn);
                gr.insert(idi,pdi[rightdir],1,0,tpn);
                gr.insert(pdi[downdir],pdi[updir],1,2,tpn);
                gr.insert(pdi[leftdir],pdi[updir],1,1,tpn);
                gr.insert(pdi[rightdir],pdi[updir],1,1,tpn);
                break;
            }
            // type "+"
            case 15:{ // 1 1 1 1 Up & Down & Left & Right
                if(tpn) cntk+=4;
                else cntx+=4;
                gr.insert(spn,idi,4,0,tpn);
                gr.insert(idi,pdi[updir],1,0,tpn);
                gr.insert(idi,pdi[downdir],1,0,tpn);
                gr.insert(idi,pdi[leftdir],1,0,tpn);
                gr.insert(idi,pdi[rightdir],1,0,tpn);
                break;
            }
        }
    }
    auto[fl,cst]=gr.flow(s,t);
    if(cntk!=fl||cntx!=cntk) exit((cout<<-1<<'\n',0));
    cout<<cst<<'\n';
    return 0;
}
