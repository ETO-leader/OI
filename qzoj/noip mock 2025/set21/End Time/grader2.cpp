#include <bits/stdc++.h>
std::pair<int, int> push_box(int _n);
namespace FGSDGGKJFDGKMVKFDHGKDSFJGKADKFSGJFGJISRJTGINITRNGISJFG{
    #define _rep(i, x, y) for(int i = x; i <= y; ++i)
    #define _req(i, x, y) for(int i = x; i >= y; --i)
    #define _rev(i, u) for(int i = head[u]; i; i = e[i].nxt)
    #define pb push_back
    #define fi first
    #define se second
    #define mst(f, i) memset(f, i, sizeof f)
    using namespace std;
    #ifdef ONLINE_JUDGE
    #define debug(...) 0
    #else
    #define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
    #endif
    typedef long long ll;
    typedef pair<int, int> PII;
    template<typename T> inline void read(T &t){
        T x = 0, f = 1;
        char c = getchar();
        while(!isdigit(c)){
            if(c == '-') f = -f;
            c = getchar();
        }
        while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
        t = x * f;
    }
    template<typename T, typename ... Args> inline void read(T &t, Args&... args){
        read(t);
        read(args...);
    }
    
    class ANS{
        private:
            int ansx, ansy;
            mt19937 rnd;
            ll getv(ll l, ll r){return rnd() % (r - l + 1) + l;}
            ll T, seed, n, m, x, y, tot;
            bool sol;
            ll dis(ll x, ll y){
                if(x > y) swap(x, y);
                return min(y - x, x + n - y);
            }
            bool check(PII ans){
                if(min(ans.fi, ans.se) == min(ansx, ansy) && max(ans.fi, ans.se) == max(ansx, ansy)){
                    return 1;
                }
                return 0;
            }
            void init(int n, int seed){
                if(sol){
                    ansy = getv(1, n - 2), ansx = ansy + 2;
                }else{
                    ansx = getv(1, n), ansy = getv(1, n);
                    while(dis(ansx, ansy) <= 1) ansy = getv(1, n);
                }
            }
        public:
            ANS(){
                rnd = mt19937(0721);
            }
            int Query(int x, int y){
                tot++;
                if(tot > 40){
                    puts("Operations Limit Exceeded, you got 8 pts.");
                    exit(0);
                }
                if(!(x >= 1 && y >= 1 && x <= n && y <= n)) return -1;
                int t = min({dis(x, y), dis(x, ansx) + 1 + dis(ansy, y), dis(x, ansy) + 1 + dis(ansx, y)});
                return t;
            }
            void solve(){
                read(T, m, seed);
                if(seed == 0721) sol = 1;
                if(!(T >= 1 && T <= 1000) || !(m >= 4 && m <= 1000000000)) return puts("Illegal input!"), void();
                rnd = mt19937(seed);
                seed = rnd();
                rnd = mt19937(seed);
                while(T--){
                    n = getv(max(4ll, m / 2), m), tot = 0;
                    init(n, seed);
                    PII ans = push_box(n);
                    if(check(ans)) continue;
                    puts("Wrong Answer, you got 72 pts.");
                    exit(0);
                }
                if(sol){
                    _rep(i, 1, 721){
                        puts("You are not allowed to onani!");
                        puts("Stop playing Limelight Lemonde Jam!");
                    }
                }else{
                    puts("Accepted, the boxes can be pushed!");
                    _rep(i, 1, 1000) puts("0d000721");
                    _rep(i, 1, 1000) printf("IWantToPlayLimelightLemondeJam");
                }
            }
    }res;
    int Query(int x, int y){
        return res.Query(x, y);
    }
    #undef debug
    #undef fi
    #undef se
    #undef pb
    #undef _rep
    #undef _req
    #undef _rev
}
// using yozosoft::Query;

extern int Query(int x, int y){
    return FGSDGGKJFDGKMVKFDHGKDSFJGKADKFSGJFGJISRJTGINITRNGISJFG::Query(x, y);
}

signed main(){
    FGSDGGKJFDGKMVKFDHGKDSFJGKADKFSGJFGJISRJTGINITRNGISJFG::res.solve();
    return 0;
}
