#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("zu.in");
ofstream ouf("zu.out");
class fileio{
public:
    ~fileio(){
        inf.close();ouf.close();
    }
} use_fileio;
static constexpr auto _inf=(int)(1e9+7);
enum user_type{usr_red,usr_black,TBD};
class graph{
private:
    struct statu{
        user_type win_usr;
        int step;
        statu(user_type w=TBD,int _step=_inf):win_usr(w),step(_step){}
    };
    vector<user_type> usr;
    vector<vector<int>> gr;
    vector<vector<int>> rgr;
    vector<statu> res;
    vector<int> vis;
    auto update(int u){
        for(auto&v:rgr[u]) if(res[v].win_usr==usr[u]){
            if(res[u].win_usr==usr[u]) res[u].step=min(res[u].step,res[v].step+1);
            else res[u].step=res[v].step+1;
            res[u].win_usr=usr[u];
        }else if(res[u].win_usr!=usr[u]&&res[v].win_usr!=TBD){
            if(res[u].win_usr!=TBD) res[u].step=max(res[u].step,res[v].step+1);
            else res[u].step=res[v].step+1;
            res[u].win_usr=res[v].win_usr;
        }
    }
    auto accessable(int u){
        auto ok=true;
        for(auto&v:rgr[u]) if(ok&=res[v].win_usr!=TBD;res[v].win_usr==usr[u]) return true;
        return ok;
    }
public:
    auto link(int u,int v){
        gr[u].emplace_back(v);
        rgr[v].emplace_back(u);
    }
    auto bfs(vector<int> rwin,vector<int> bwin,int qs){
        queue<int> qwq;
        for(auto&u:rwin) if(!vis[u]) res[u]=statu(usr_red,0),qwq.emplace(u),vis[u]=true;
        for(auto&u:bwin) if(!vis[u]) res[u]=statu(usr_black,0),qwq.emplace(u),vis[u]=true;
        while(!qwq.empty()){
            const auto u=qwq.front();qwq.pop();
            for(auto&v:gr[u]) if((!vis[v])&&accessable(v)){
                update(v);
                vis[v]=true;qwq.emplace(v);
            }
        }
        return res[qs];
    }
    graph(int _n,vector<int> rusr,vector<int> busr):gr(_n),rgr(_n),usr(_n,TBD),res(_n),vis(_n){
        for(auto&u:rusr) usr[u]=usr_red;
        for(auto&u:busr) usr[u]=usr_black;
    }
};
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int tid,T;inf>>tid>>T;
    while(T--) []{
        int n,m;inf>>n>>m;
        vector<string> script(n);
        for(auto&s:script) inf>>s;
        vector<pair<int,int>> posb,posr;
        cir(i,0,n) cir(j,0,m){
            if(script[i][j]=='O') posr.emplace_back(i,j);
            if(script[i][j]=='X') posb.emplace_back(i,j);
        }
        int cnt;
        auto st_hash=[&](int usr,int uxb,int uyb,int rx1,int ry1,int rx2,int ry2){
            return
                usr*1000000+
                uxb*100000+
                uyb*10000+
                rx1*1000+
                ry1*100+
                rx2*10+
                ry2*1;
        };
        auto vaild=[&](int uxb,int uyb,int rx1,int ry1,int rx2,int ry2){
            if(uxb<0||uxb>n-1||uyb<0||uyb>m-1||rx1<0||rx1>n-1||ry1<0||ry1>m-1||rx2<0||rx2>n-1||ry2<0||ry2>m-1) return false;
            return script[uxb][uyb]!='#'&&script[rx1][ry1]!='#'&&script[rx2][ry2]!='#';
        };
        const auto limrng=st_hash(2,0,0,0,0,0,0);
        vector<int> rusr,busr;
        cir(uxb,0,n) cir(uyb,0,m) cir(rx1,0,n) cir(ry1,0,m) cir(rx2,0,n) cir(ry2,0,m){
            rusr.emplace_back(st_hash(usr_red,uxb,uyb,rx1,ry1,rx2,ry2));
            busr.emplace_back(st_hash(usr_black,uxb,uyb,rx1,ry1,rx2,ry2));
        }
        graph gr(limrng,rusr,busr);
        vector<int> rwin,bwin;
        cir(uxb,0,n) cir(uyb,0,m) cir(rx1,0,n) cir(ry1,0,m) cir(rx2,0,n) cir(ry2,0,m){
            if(!vaild(uxb,uyb,rx1,ry1,rx2,ry2)) continue;
            // Move Red
            [&]{
                if(uxb==rx1&&uyb==ry1) return;
                if(uxb==rx2&&uyb==ry2) return;
                auto cnt=0;
                cir(dx,-1,2) cir(dy,-1,2) if(abs(dx)^abs(dy)){
                    if(vaild(uxb,uyb,rx1+dx,ry1+dy,rx2,ry2)){
                        ++cnt;
                        gr.link(st_hash(usr_black,uxb,uyb,rx1+dx,ry1+dy,rx2,ry2),st_hash(usr_red,uxb,uyb,rx1,ry1,rx2,ry2));
                    }
                    if(vaild(uxb,uyb,rx1,ry1,rx2+dx,ry2+dy)){
                        ++cnt;
                        gr.link(st_hash(usr_black,uxb,uyb,rx1,ry1,rx2+dx,ry2+dy),st_hash(usr_red,uxb,uyb,rx1,ry1,rx2,ry2));
                    }    
                }
                if(!cnt) bwin.emplace_back(st_hash(usr_red,uxb,uyb,rx1,ry1,rx2,ry2)); // Can't move
            }();
            // Move Black
            [&]{
                set<pair<int,int>> ok{{-1,0},{0,1},{0,-1}};
                if(uxb==rx1&&uyb==ry1) return;
                if(uxb==rx2&&uyb==ry2) return;
                auto cnt=0;
                cir(dx,-1,2) cir(dy,-1,2) if(ok.count({dx,dy})){
                    const auto nx=uxb+dx,ny=uyb+dy;
                    if(vaild(uxb+dx,uyb+dy,rx1,ry1,rx2,ry2)){
                        ++cnt;
                        gr.link(st_hash(usr_red,uxb+dx,uyb+dy,rx1,ry1,rx2,ry2),st_hash(usr_black,uxb,uyb,rx1,ry1,rx2,ry2));
                    }
                }
                if(!cnt) rwin.emplace_back(st_hash(usr_black,uxb,uyb,rx1,ry1,rx2,ry2));
            }();
        }
        // Eaten
        cir(uxb,0,n) cir(uyb,0,m) cir(rx,0,n) cir(ry,0,m){
            if(vaild(uxb,uyb,uxb,uyb,rx,ry)){
                rwin.emplace_back(st_hash(usr_black,uxb,uyb,uxb,uyb,rx,ry));
                bwin.emplace_back(st_hash(usr_red,uxb,uyb,uxb,uyb,rx,ry));
            }
            if(vaild(uxb,uyb,rx,ry,uxb,uyb)){
                rwin.emplace_back(st_hash(usr_black,uxb,uyb,rx,ry,uxb,uyb));
                bwin.emplace_back(st_hash(usr_red,uxb,uyb,rx,ry,uxb,uyb));
            }
        }
        // Arrive
        cir(uyb,0,m) cir(rx1,0,n) cir(ry1,0,m) cir(rx2,0,n) cir(ry2,0,m){
            if(vaild(0,uyb,rx1,ry1,rx2,ry2)) bwin.emplace_back(st_hash(usr_red,0,uyb,rx1,ry1,rx2,ry2));
        }
        // Get Answer
        const auto[result,step]=gr.bfs(
            rwin,bwin,
            st_hash(usr_red,posb[0].first,posb[0].second,posr[0].first,posr[0].second,posr[1].first,posr[1].second)
        );
        if(result==TBD) ouf<<"Tie\n";
        else ouf<<(result==usr_red?"Red":"Black")<<' '<<step<<'\n';
    }();
    return 0;
}
