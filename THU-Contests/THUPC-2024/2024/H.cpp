#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
template<typename T>
class bit{
private:
    vector<T> a;
    static auto lowbit(int x){return x&(-x);}
public:
    auto update(int x,T w){
        ++x;
        for(;x<a.size();x+=lowbit(x)) a[x]+=w;
    }
    auto query(int x){
        T res=0;++x;
        for(;x;x-=lowbit(x)) res+=a[x];
        return res;
    }
    bit(int _x):a(_x+1){}
};
template<typename T>
auto log2x(T x){
    return sizeof(T)*8-__builtin_clz(x);
}
auto gethash(int x){
    return x;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;string s;cin>>s;
    for(auto&i:s) i-='0';
    vector<int> f,p;
    vector<set<int>> pos;
    bit<int>*bx=nullptr;
    vector<bool> del;
    auto init=[&](int l){
        if(bx) delete bx;
        if(bx){
            string ns;
            cir(i,0,s.size()) if(!del[i])
                ns.push_back(s[i]);
            s=ns;
        }
        pos.clear();pos.resize(1<<(log2x(n)+1));
        bx=new bit<int>(s.size());
        del.clear();del.resize(s.size());
        cir(i,0,s.size()) if(i+l<s.size()){
            int h=0;
            cir(x,0,l+1) (h<<=1)+=s[i+x];
            pos[h].insert(i);
        }
        f.clear();f.resize(s.size());
        p.clear();p.resize(s.size());
        iota(f.begin(),f.end(),1);
        iota(p.begin(),p.end(),-1);
    };
    int nowlen=-1;
    cir(i,1,n+1){
        if((!s.empty())&&log2x(i)!=nowlen){
            nowlen=log2x(i);init(log2x(i)-1);
        }
        if(s.empty()){
            cout<<"-1 0\n";continue;
        }
        auto hx=gethash(i);
        const auto lg=log2x(i);
        if(pos[hx].empty()){
            cout<<"-1 0\n";
            continue;
        }
        deque<int> fx,cp;
        int u=*pos[hx].begin();
        assert(bx);
        cout<<u+1-(bx->query(u))<<' '<<pos[hx].size()<<'\n';
        cir(c,0,lg) if(p[u]>-1){
            fx.push_front(u=p[u]);
            cp.push_front(u);
        }
        int las=cp.empty()?-1:cp.back();
        u=*pos[hx].begin();
        cir(c,0,lg){
            assert(u<s.size());
            bx->update(u,1);del[u]=true;
            fx.push_back(u);u=f[u];
        }
        int fs=-1;
        cir(c,0,lg) if(u<s.size()){
            fx.push_back(u);
            if(fs<0) fs=u;
            cp.push_back(u);u=f[u];
        }
        if(las>-1&&fs>-1){
            f[las]=fs;p[fs]=las;
        }else if(las>-1){
            f[las]=n;
        }else if(fs>-1){
            p[fs]=-1;
        }
        cir(c,0,fx.size()-lg+1){
            int h=0;
            cir(x,0,lg) (h<<=1)+=s[fx[x+c]];
            if(pos[h].count(fx[c])){
                pos[h].extract(fx[c]);
            }
        }
        if(cp.size()+1>lg-1) cir(c,0,cp.size()-lg+1){
            int h=0;
            cir(x,0,lg) (h<<=1)+=s[cp[x+c]];
            pos[h].insert(cp[c]);
        }
    }
    if(bx) delete bx;
    return 0;
}
