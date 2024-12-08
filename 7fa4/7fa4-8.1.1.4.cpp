#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using point=complex<lint>;
using vector_t=complex<lint>;
class casereader{
private:
    union datatype{
        int i32;
        char chr;
        datatype(int x):i32(x){}
        datatype(char x):chr(x){}
    };
    vector<datatype> ax;
    int cur;
    auto readint(){
        int x;cin>>x;ax.emplace_back(x);
        return x;
    }
    auto readchar(){
        char x;cin>>x;ax.emplace_back(x);
        return x;
    }
public:
    auto init(){
        const auto n=readint(),m=readint(),c=readint();
        cir(i,0,n*2) readint();
        cir(i,0,m){
            const auto op=readchar();
            cir(i,0,(op=='H')+4) readint();
        }
        cur=0;
    }
    auto readargs(int&x){
        x=ax[cur].i32;++cur;
    }
    auto readargs(char&x){
        x=ax[cur].chr;++cur;
    }
    auto readargs(auto&a,auto&...args){
        readargs(a);readargs(args...);
    }
};
class line{
private:
    point u;
    vector_t dir;
    static auto cross(vector_t a,vector_t b){
        return imag(conj(a)*b);
    }
    static auto sorted(auto a,auto b){
        return a<b?pair(a,b):pair(b,a);
    }
public:
    const auto chkinter(line lx){
        const auto crsu=cross(u-lx.u,lx.dir);
        const auto crsv=cross(u+dir-lx.u,lx.dir);
        return !((crsu>0&&crsv>0)||(crsu<0&&crsv<0));
    }
    auto x() const{return sorted(real(u),real(u)+real(dir));}
    auto y() const{return sorted(imag(u),imag(u)+imag(dir));}
    auto un() const{return u;}
    auto vn() const{return u+dir;}
    line(point _u,vector_t _dir):u(_u),dir(_dir){}
    line(point _u,point v,bool isseg):u(_u),dir(isseg?v-_u:v){}
};
using segment=line;
class random_engine{
private:
    mt19937 eng;
public:
    template<typename _Ty>
    auto randint(auto l,auto r){
        return uniform_int_distribution<_Ty>(l,r)(eng);
    }
    random_engine():eng(
        #ifdef local
            251
        #else
            random_device().operator()()
        #endif
    ){}
} rnd;
class treap{
private:
    struct node{
        shared_ptr<node> ls,rs;
        lint mnx,mxx,mny,mxy;
        segment cur;
        int siz;
        auto selfinit(){
            const auto[gxa,gxb]=cur.x();
            const auto[gya,gyb]=cur.y();
            mnx=gxa;mxx=gxb;
            mny=gya;mxy=gyb;
        }
        auto maintain(){
            selfinit();
            siz=1;
            for(auto v:{ls,rs}) if(v){
                mnx=min(mnx,v->mnx);
                mny=min(mny,v->mny);
                mxx=max(mxx,v->mxx);
                mxy=max(mxy,v->mxy);
                siz+=v->siz;
            }
        }
        auto lsiz() const{return ls?ls->siz:0;}
        auto rsiz() const{return rs?rs->siz:0;}
        node(segment ln):ls(nullptr),rs(nullptr),cur(ln),siz(1){selfinit();}
        ~node(){}
    };
    auto copy(shared_ptr<node> u){
        assert(u);
        auto res=make_shared<node>(u->cur);
        *res=*u;
        return res;
    }
    auto split(shared_ptr<node> u,lint rk){
        if(!u) return pair<shared_ptr<node>,shared_ptr<node>>(nullptr,nullptr);
        u=copy(u);
        if(u->lsiz()>rk-1){
            const auto[ux,vx]=split(u->ls,rk);
            u->ls=vx;u->maintain();
            return pair(ux,u);
        }else{
            const auto[ux,vx]=split(u->rs,rk-u->lsiz()-1);
            u->rs=ux;u->maintain();
            return pair(u,vx);
        }
    }
    auto merge(shared_ptr<node> u,shared_ptr<node> v){
        if(!u) return v;
        if(!v) return u;
        u=copy(u);v=copy(v);
        if(rnd.randint<int>(0,u->siz+v->siz-1)<u->siz){
            u->rs=merge(u->rs,v);
            return u->maintain(),u;
        }else{
            v->ls=merge(u,v->ls);
            return v->maintain(),v;
        }
    }
    auto inter(shared_ptr<node> u,line x){
        if(!u) return 0;
        if(!(
            segment(point(u->mnx,u->mxy),point(u->mxx,u->mny),true).chkinter(x)||
            segment(point(u->mxx,u->mxy),point(u->mnx,u->mny),true).chkinter(x)
        )) return 0;
        return u->cur.chkinter(x)+inter(u->ls,x)+inter(u->rs,x);
    }
    auto first(shared_ptr<node> u)->point{
        if(u->ls) return first(u->ls);
        return u->cur.un();
    }
    auto last(shared_ptr<node> u)->point{
        if(u->rs) return last(u->rs);
        return u->cur.vn();
    }
    vector<shared_ptr<node>> v;
    auto getrange(int cv,int l,int r){
        const auto[al,rg]=split(v[cv],l);
        const auto[qr,ar]=split(rg,r-l+1);
        return tuple(al,qr,ar);
    }
public:
    auto rmvat(int cv,int x){
        const auto[al,rm,ar]=getrange(cv,x,x);
        const auto res=rm->cur;
        v.emplace_back(merge(al,ar));
        return res;
    }
    auto emplace_front(int cv,point x){
        v.emplace_back(merge(make_shared<node>(segment(x,first(v[cv]),true)),copy(v[cv])));
    }
    auto emplace_back(int cv,point x){
        v.emplace_back(merge(copy(v[cv]),make_shared<node>(segment(last(v[cv]),x,true))));
    }
    auto size(int cv){return v[cv]->siz;}
    auto emplace(int x,segment w){
        const auto[al,ar]=split(v.back(),x);
        v.back()=merge(merge(al,make_shared<node>(w)),ar);
    }
    auto inters(int cv,segment x){
        return inter(v[cv],x);
    }
    auto mkversion(int cv){v.emplace_back(copy(v[cv]));}
    treap():v({shared_ptr<node>(nullptr)}){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    casereader inf;inf.init();
    int n,m,c;inf.readargs(n,m,c);
    treap tr;
    int lasx=-1,lasy=-1;
    cir(i,0,n){
        int x,y;inf.readargs(x,y);
        if(i) tr.emplace(i-1,segment(point(lasx,lasy),point(x,y),true));
        lasx=x;lasy=y;
    }
    int las=0;
    cir(x,0,m){
        char op;inf.readargs(op);
        if(op=='H'){
            int t,x,y,dx,dy;inf.readargs(t,x,y,dx,dy);
            x^=(c*las);y^=(c*las);
            dx^=(c*las);dy^=(c*las);
            cout<<(las=tr.inters(t,line(point(x,y),vector_t(dx,dy))))<<'\n';
            tr.mkversion(t);
        }else{
            int t,i,x,y;inf.readargs(t,i,x,y);
            x^=(c*las);y^=(c*las);--i;
            if(i>-1&&i<tr.size(t)){
                const auto ln=tr.rmvat(t,i);
                const auto u=ln.un();
                const auto v=ln.vn();
                const auto w=point(x,y);
                tr.emplace(i,segment(u,w,true));
                tr.emplace(i+1,segment(w,v,true));
            }else if(i==-1){
                tr.emplace_front(t,point(x,y));
            }else{
                tr.emplace_back(t,point(x,y));
            }
        }
    }
    return 0;
}
