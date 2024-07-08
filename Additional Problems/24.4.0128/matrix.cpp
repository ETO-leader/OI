#include<bits/stdc++.h>
#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace __gnu_pbds;
using namespace std;
ifstream fcin("matrix.in");
ofstream fcout("matrix.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
using lint=long long;
template<typename _Ty,class comp=less<_Ty>>
using rbt=tree<_Ty,null_type,comp,rb_tree_tag,
    tree_order_statistics_node_update>;
class dirx_state{
private:
    lint lefnum;rbt<int> ops;
    __gnu_cxx::rope<lint> usr;
    size_t siz,rk;
    auto getpos(size_t p){
        int l=0,r=siz+usr.size(),res=-1;
        while(l-1<r){
            const auto mid=(l+r)/2;
            (mid-(int)(ops.order_of_key(mid))>(int)(p))?
                ((r=mid-1),(res=mid)):(l=mid+1);
        }
        return res-1;
    }
    auto visc(size_t p)->lint{return lefnum+p;}
    auto visnc(size_t p){
        return usr.at(p-rk);
    }
    auto rmvc(size_t p){--rk;ops.insert(p);}
    auto rmvnc(size_t p){
        usr.erase(p-rk,1);
    }
public:
    auto at(size_t p){
        if(rk<p+1) return visnc(p);
        return visc(getpos(p));
    }
    auto remove(size_t p){
        if(rk<p+1) return rmvnc(p);
        rmvc(getpos(p));
    }
    auto push_back(lint x){
        usr.append(x);
    }
    dirx_state(lint lfn,size_t sz):lefnum(lfn),
        siz(sz),rk(sz){}
    dirx_state()=default;
};
int main(){
    ios::sync_with_stdio(false),fcin.tie(0);
    int n,m,q;fcin>>n>>m>>q;
    vector<dirx_state> drx(n);
    cir(i,0,n) drx[i]=dirx_state((lint)(i)*m+1,m-1);
    __gnu_cxx::rope<int> rp;
    cir(i,0,n) rp.append((lint)(i)*m+m);
    cir(i,0,q){
        int x,y;fcin>>x>>y;--x;--y;
        if(y!=m-1){
            auto w=drx[x].at(y);
            fcout<<w<<'\n';
            drx[x].remove(y);
            drx[x].push_back(rp[x]);
            rp.erase(x,1);
            rp.append(w);
        }else{
            auto w=rp[x];
            fcout<<w<<'\n';
            rp.erase(x,1);
            rp.append(y);
        }
    }
    return 0;
}
