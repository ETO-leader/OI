#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class scanner{
private:
    struct randgen{
        int x,y,z;
        int next_int(){
            int t=x^(x<<11);
            x=y;y=z;
            z^=(z>>19)^t^(t>>8);
            return z;
        }
        randgen(){cin>>x>>y>>z;}
    };
    randgen rnd;lint cnx,fls;
public:
    template<typename T>
    scanner&operator>>(T&p){
        p=rnd.next_int();
        return *this;
    }
    template<typename T>
    scanner&operator<<(T p){
        cnx^=(fls*(lint)(p));return *this;
    }
    void flush(){cout<<cnx<<'\n';}
    void continues(){++fls;}
    scanner():rnd(),cnx(0),fls(0){}
};
template<typename T,const int siz=0>
class bit{
private:
    array<T,siz> v;int n;
    int lowbit(const int x) const{return (x)&(-x);}
public:
    void update(int p,T w){
        ++p;
        while(p<n) v[p]+=w,p+=lowbit(p);
    }
    T operator()(int p) const{
        T res=0;++p;
        while(p>0) res+=v[p],p-=lowbit(p);
        return res;
    }
    int size(){return n;}
    bit():n(siz){}
};
template<const int siz>
class bitset_t{
private:
    using ull=unsigned long long;
    const int sizeof_ull=64;
    bitset<siz> ar;
    bit<int,siz/64+3> nm{};
public:
    void reverse(int v){
        ar[v]=!ar[v];
        nm.update(v/sizeof_ull,ar[v]?1:-1);
    }
    int count(int v){
        int p=v/sizeof_ull,res=nm(p-1);
        cir(i,p*sizeof_ull,v+1) res+=ar[i];
        return res;
    }
};
const int nx=6e7+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;scanner stdiostream;
    bitset_t<nx> bx; 
    cir(i,0,m){
        int op;stdiostream>>op;
        if(op&1){
            int l,r;stdiostream>>l>>r;
            l%=n,r%=n;if(l>r) swap(l,r);
            stdiostream<<bx.count(r)-bx.count(l-1);
        }else{
            int p;stdiostream>>p;p%=n;
            bx.reverse(p);
        }
        stdiostream.continues();
    }
    stdiostream.flush();
    return 0;
}
