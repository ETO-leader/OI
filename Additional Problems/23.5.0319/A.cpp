#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
unordered_map<int,set<int>> wl,wp;
struct point{int x,y;};
namespace move{
    int h,w;
    void init(int _h,int _w){h=_h;w=_w;}
    point move_up(point&p,int l){
        int es=max(1,p.x-l);
        if(!wl.count(p.y)) return {es,p.y};
        if((*wl[p.y].begin())>p.x||(*--wl[p.y].end())<es)
            return {es,p.y};
        return {max(es,*(--wl[p.y].upper_bound(p.x))+1),p.y};
    }
    point move_down(point&p,int l){
        int es=min(h,p.x+l);
        if(!wl.count(p.y)) return {es,p.y};
        if((*wl[p.y].begin())>es||(*--wl[p.y].end())<p.x)
            return {es,p.y};
        return {min(es,*(wl[p.y].lower_bound(p.x))-1),p.y};
    }
    point move_left(point&p,int l){
        int es=max(1,p.y-l);
        if(!wp.count(p.x)) return {p.x,es};
        if((*wp[p.x].begin())>p.y||(*--wp[p.x].end())<es)
            return {p.x,es};
        return {p.x,max(es,*(--wp[p.x].upper_bound(p.y))+1)};
    };
    point move_right(point&p,int l){
        int es=min(p.y+l,w);
        if(!wp.count(p.x)) return {p.x,es};
        if((*wp[p.x].begin())>es||(*--wp[p.x].end())<p.y)
            return {p.x,es};
        return {p.x,min(es,*(wp[p.x].lower_bound(p.y))-1)};
    }
}
istream&operator>>(istream&is,point&p){
    return is>>p.x>>p.y;}
ostream&operator<<(ostream&os,point&p){
    return os<<p.x<<' '<<p.y;}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int h,w,k;point p;cin>>h>>w>>p>>k;
    move::init(h,w);
    cir(i,0,k){
        point p;cin>>p;
        wp[p.x].insert(p.y);wl[p.y].insert(p.x);
    }
    int mv;cin>>mv;
    cir(k,0,mv){
        string op;int l;cin>>op>>l;
        switch(op[0]){
            case 'U':cout<<(p=move::move_up(p,l))<<'\n';break;
            case 'D':cout<<(p=move::move_down(p,l))<<'\n';break;
            case 'L':cout<<(p=move::move_left(p,l))<<'\n';break;
            default:cout<<(p=move::move_right(p,l))<<'\n';break;
        }
    }
    return 0;
}
