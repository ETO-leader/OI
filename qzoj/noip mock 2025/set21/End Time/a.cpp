#ifndef __SAMPLE_HEADER

#define __SAMPLE_HEADER 1

extern int Query(int,int);

#endif

#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;

constexpr auto nxt(int u,int x,const int n){
    return (u+x+n-1)%n+1;
}

pair<int,int> push_box(int n){
    mt19937_64 eng(251);
    auto u=1;
    auto qnxt=Query(u,nxt(u,n/2,n));
    while(qnxt==n/2){
        u=uniform_int_distribution<int>(1,n)(eng);
        qnxt=Query(u,nxt(u,n/2,n));
    }
    const auto vl=Query(u,nxt(u,n/2-1,n));
    const auto vr=Query(u,nxt(u,n/2+1,n));
    // Target v: u-nxt
    if(qnxt<vl+1&&qnxt<vr+1){
        const auto tdis=qnxt-1;
        const auto ux=nxt(u,n/2,n);
        const auto vx=nxt(u,tdis,n);
        const auto vy=nxt(u,-tdis,n);
        if(Query(vx,ux)==1) return make_pair(vx,ux);
        else return make_pair(vy,ux);
    }
    // v in the left part
    if(qnxt<vr+1){
        auto l=1,r=n/2,ans=-1,ansdis=-1;
        while(l-1<r){
            const auto mid=(l+r)/2;
            const auto ux=nxt(u,mid,n);
            const auto uxdis=Query(u,ux);
            if(uxdis==mid){
                l=mid+1;
            }else{
                const auto dismid=qnxt-(n/2-mid);
                if(dismid==uxdis){
                    ansdis=uxdis;
                    ans=mid;
                    r=mid-1;
                }else{
                    l=mid+1;
                }
            }
        }
        const auto tdis=ansdis-1;
        const auto ux=nxt(u,ans,n);
        const auto vx=nxt(u,tdis,n);
        const auto vy=nxt(u,-tdis,n);
        if(Query(vx,ux)==1) return make_pair(vx,ux);
        else return make_pair(vy,ux);
    }
    // v in the right part
    if(qnxt<vl+1){
        auto l=1,r=(n-n/2),ans=-1,ansdis=-1;
        while(l-1<r){
            const auto mid=(l+r)/2;
            const auto ux=nxt(u,-mid,n);
            const auto uxdis=Query(u,ux);
            if(uxdis==mid){
                l=mid+1;
            }else{
                const auto dismid=qnxt-((n-n/2)-mid);
                if(dismid==uxdis){
                    ansdis=uxdis;
                    ans=mid;
                    r=mid-1;
                }else{
                    l=mid+1;
                }
            }
        }
        const auto tdis=ansdis-1;
        const auto ux=nxt(u,-ans,n);
        const auto vx=nxt(u,tdis,n);
        const auto vy=nxt(u,-tdis,n);
        if(Query(vx,ux)==1) return make_pair(vx,ux);
        else return make_pair(vy,ux);
    }
    assert(false);
}
