#include<bits/stdc++.h>
#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
template<typename T>
class valdsu{
public:
    vector<size_t> F;vector<T> v,tag;
    pair<size_t,T> _findset(size_t x){
        assert((x>=0&&x<v.size()));
        if(F[x]==x) return {x,v[x]+tag[x]};
        auto fx=_findset(F[x]);
        F[x]=fx.first;v[x]=(fx.second+=tag[x]);
        return {fx.first,v[x]};
    }
public:
    size_t findset(size_t x){
        return _findset(x).first;}
    void setaddval(size_t x,T vx){
        tag[findset(x)]+=vx;}
    T operator()(size_t x){
        return _findset(x).second;}
    void merge(size_t x,size_t y){
        x=findset(x);y=findset(y);
        tag[y]-=tag[x];F[y]=x;
        findset(x);findset(y);
    }
    valdsu(size_t n=0):F(n),v(n),tag(n){
        iota(F.begin(),F.end(),0);}
    void resize(size_t n){
        (*this)=valdsu(n);}
};
template<typename T,class comp=less<T>>
using heap=__gnu_pbds::priority_queue<T,
    comp,__gnu_pbds::pairing_heap_tag>;
valdsu<int> vals;
struct heapnode{
    int v,id;
    bool operator<(const heapnode&hp) const{
        return v+vals(id)<hp.v+vals(hp.id);
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,aadd=0;cin>>n;vals.resize(n+1);
    vector<heap<heapnode>> hp(n+1);
    vector<int> v(n+1);
    heap<int> heapall;
    cir(i,1,n+1){
        cin>>v[i];hp[i].push({v[i],i});
    }
    int q;cin>>q;
    while(q--){
        string op;cin>>op;
        if(op=="U"){
            int x,y;cin>>x>>y;
            if(vals.findset(x)==vals.findset(y))
                continue;
            hp[vals.findset(x)].join(hp[vals.findset(y)]);
            vals.merge(x,y);
        }else if(op=="A1"){
            int x,vx;cin>>x>>vx;
            hp[vals.findset(x)].push({(v[x]+=vx),x});
            heapall.push(v[x]);
        }else if(op=="A2"){
            int x,vx;cin>>x>>vx;
            vals.setaddval(x,vx);
            auto tp=hp[vals.findset(x)].top();
            heapall.push(tp.v+vals(tp.id));
        }else if(op=="A3"){
            int vx;cin>>vx;aadd+=vx;
        }else if(op=="F1"){
            int x;cin>>x;cout<<v[x]+vals(x)+aadd<<'\n';
        }else if(op=="F2"){
            int x;cin>>x;
            auto tp=hp[vals.findset(x)].top();
            cout<<tp.v+vals(tp.id)+aadd<<'\n';
        }else{
            cout<<heapall.top()+aadd<<'\n';
        }
    }
    return 0;
}
