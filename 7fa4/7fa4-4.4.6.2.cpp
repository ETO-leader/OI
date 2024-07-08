#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
template<typename T>
class blocks{
private:
    struct block{
        int l,r;T w;vector<T> px;
        block():w(0){}
    };
    vector<T> arr;
    vector<block> blc;
    auto copy_vector(int l,int r){
        vector<T> res;res.reserve(r-l+1);
        cir(i,l,r+1) res.push_back(arr[i]);
        return res;
    }
    auto initblock(int l,int r){
        block res;res.px=copy_vector(l,r);
        sort(res.px.begin(),res.px.end());
        res.l=l;res.r=r;
        return res;
    }
    auto&initblock(int l,int r,block&res){
        cir(i,l,r+1) res.px[i-l]=arr[i];
        sort(res.px.begin(),res.px.end());
        return res;
    }
    int findblock(int p){
        cir(i,0,blc.size()) if(blc[i].r>=p) return i;
        return -1;
    }
    void init(){
        const int sqr=sqrt(
            arr.size()*2)+1;
        for(int i=0;i*sqr<arr.size();++i)
            blc.push_back(initblock(i*sqr,
                min<int>((i+1)*sqr-1,arr.size()-1)));
    };
    void add_part_block(int l,int r,int bid,T w){
        cir(i,l,r+1) arr[i]+=w;
        initblock(blc[bid].l,blc[bid].r,blc[bid]); 
    }
    int count_part_block(int l,int r,int bid,T w){
        int res=0;w-=blc[bid].w;
        cir(i,l,r+1) res+=(arr[i]<w);
        return res;
    }
public:
    void additional(int l,int r,T w){
        int fl=findblock(l),fr=findblock(r);
        if(fl==fr)
            return add_part_block(l,r,fl,w),void();
        add_part_block(l,blc[fl].r,fl,w);
        add_part_block(blc[fr].l,r,fr,w);
        cir(i,fl+1,fr) blc[i].w+=w;
    }
    int operator()(int l,int r,T w){
        const int fl=findblock(l),fr=findblock(r);
        if(fl==fr) return count_part_block(l,r,fl,w);
        int res=count_part_block(l,blc[fl].r,fl,w)+
            count_part_block(blc[fr].l,r,fr,w);
        cir(i,fl+1,fr){
            auto&px=blc[i].px;
            if(px.front()>=w) continue;
            res+=((lower_bound(px.begin(),px.end(),w-blc[i].w))
                -px.begin());
        }
        return res;
    }
    blocks(vector<T>&v){arr=v;init();}
};
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<int> arr(n);
    for(auto&i:arr) cin>>i;
    blocks<int> blc(arr);
    cir(i,0,n){
        int op,l,r;lint c;
        cin>>op>>l>>r>>c;--l,--r;
        if(!op) blc.additional(l,r,c);
        else cout<<blc(l,r,min<lint>(c*c,
            numeric_limits<int>::max()))<<'\n';
    }
    return 0;
}
