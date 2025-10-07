#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
namespace __gnu_pbds{
    template<typename _Ty,class comp=less<_Ty>>
    using rbt=tree<_Ty,null_type,comp,rb_tree_tag,
        tree_order_statistics_node_update>;
}
using __gnu_pbds::rbt;
class chtholly{
private:
    struct node{
        int l,r,col;
        friend auto operator<(const node&a,const node&b){
            return a.l==b.l?a.r<b.r:a.l<b.l;
        }
        node(auto _l,auto _r,auto _c):l(_l),r(_r),col(_c){}
    };
    rbt<node> rb;
    auto split(int x){
        if(x>rb.rbegin()->r) return rb.end();
        auto f=rb.lower_bound(node(x,-1,-1));
        if(f==rb.begin()||(f!=rb.end()&&f->l==x)) return f;
        f=prev(f);
        if(f->r<x) return next(f);
        const auto[l,r,c]=*f;
        rb.insert(node(l,x-1,c));
        return rb.insert(node(x,r,c)).first;
    }
public:
    auto assign(int l,int r,int c){
        const auto sr=split(r+1),sl=split(l);
        tr.erase(sl,sr);
        tr.insert(node(l,r,c));
    }
};
