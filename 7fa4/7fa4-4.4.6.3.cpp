#include<bits/stdc++.h>
#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace __gnu_pbds;
using namespace std;
template<typename T,class comp=less<T>>
using rbt=tree<T,null_type,comp,rb_tree_tag,
    tree_order_statistics_node_update>;
template<typename T>
class blocks{
private:
    struct block{
        int l,r;
        rbt<T,less_equal<T>> nx;
        rbt<T,greater_equal<T>> rx;
        void swapnum(T er,T ins){
            assert(nx.lower_bound(er*2)!=nx.end()/*&&
                (*nx.lower_bound(er*2))==er*2*/);
            nx.erase(nx.lower_bound(er*2));
            nx.insert(ins*2);
            //assert(rx.lower_bound(er*2)!=rx.end()&&
            //    (*rx.lower_bound(er*2))==er*2);
            rx.erase(rx.lower_bound(er*2));
            rx.insert(ins*2);
        }
    };
    vector<T> arr;
    vector<block> blc;
    using lint=long long;
    lint countb;vector<lint> cost;
    auto initblock(int l,int r){
        block res;res.l=l;res.r=r;
        cir(i,l,r+1)
            res.nx.insert(arr[i]*2),res.rx.insert(arr[i]*2);
        return res;
    }
    void init(){
        const int sqr=sqrt(arr.size()*
            log2(arr.size()*5))+1;
        for(int i=0;i*sqr<arr.size();++i){
            blc.push_back(initblock(i*sqr,
                min<int>((i+1)*sqr-1,arr.size()-1)));
        }
        rbt<T,greater_equal<T>> tr;
        for(auto&i:arr){
            auto w=tr.order_of_key(i*2+1);
            cost.push_back(w);countb+=w;
            tr.insert(i*2);
        }
    }
    int findblock(int p){
        cir(i,0,blc.size())
            if(blc[i].r>=p) return i;
        return -1;
    }
    //tp=0: less  tp=1 greater
    lint count_part_block(int l,int r,T w,int tp){
        lint res=0;
        cir(i,l,r+1) res+=(tp?(arr[i]>w):(arr[i]<w));
        return res;
    }
    lint count_tp(int l,int r,T w,int tp){
        const int fl=findblock(l);
        const int fr=findblock(r);
        if(fl==fr) return count_part_block(l,r,w,tp);
        lint res=count_part_block(l,blc[fl].r,w,tp)+
            count_part_block(blc[fr].l,r,w,tp);
        cir(i,fl+1,fr) res+=(tp?
            (blc[i].rx.order_of_key(w*2+1)):
            (blc[i].nx.order_of_key(w*2-1)));
        return res;
    }
public:
    void swapnum(int x,int y){
        if(x>y) swap(x,y);
        const int fl=findblock(x);
        const int fr=findblock(y);
        if(arr[x]==arr[y]) return;
        countb+=(arr[x]>arr[y]?-1:1);
        countb-=(count_tp(x+1,y-1,arr[x],0)+
            count_tp(x+1,y-1,arr[y],1));
        countb+=(count_tp(x+1,y-1,arr[x],1)+
            count_tp(x+1,y-1,arr[y],0));
        blc[fl].swapnum(arr[x],arr[y]);
        blc[fr].swapnum(arr[y],arr[x]);
        swap(arr[x],arr[y]);
    }
    lint check_ans(){return countb;}
    blocks(vector<T>&ar):arr(ar),
        countb(0){init();}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<int> arr(n);
    for(auto&i:arr) cin>>i;
    blocks<int> blc(arr);
    cout<<blc.check_ans()<<'\n';
    int q;cin>>q;
    cir(i,0,q){
        int pa,pb;cin>>pa>>pb;
        blc.swapnum(--pa,--pb);
        cout<<blc.check_ans()<<'\n';
    }
    return 0;
}
