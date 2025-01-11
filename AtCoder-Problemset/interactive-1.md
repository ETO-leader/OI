# 8pts 做法

$X$ 存两遍，或起来即可。

# 约 50pts 

一个可能的做法是，我们发现 $X$ 存两遍做法比较有道理，如果我们可以规避掉不合法的情况就更好了。

维护一个尾指针 $pos$，对于第 $i$ 位考虑一个可能的放置策略:

1. 如果 $X$ 的第 $i$ 位是 $0$，将 $pos$ 和 $pos+1$ 设为 $0$。
2. 否则如果 $pos$ 位可用，就将 $pos$ 位设为 $1$。
3. 否则如果 $pos+1$ 位可用，将 $pos+1$ 位设为 $1$。
4. 否则方案不合法。

然后发现这个方案至多会用到 $120$ 位，考虑剩下的 $30$ 位，我们考虑按随机数生成操作序列，这些位存合法的种子在 $8 \sim 10$ 位左右，多存几遍，解码的时候先或起来求出种子，再解密。

理论上每个种子正确的概率是 $0.01$ 左右，但会被多测炸死 /kk。

### Code (53pts)

```cpp
#include"Broken_device_lib.h"
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;

using random_engine=mt19937_64;
using randint=uniform_int_distribution<int>;
static constexpr auto _seed='MikeMirzayanov';

void Anna(int N,long long X,int K,int P[]){
    random_engine eng(_seed);
    set<int> cfpos;
    vector<int> fpos;
    randint ri(0,N-1);
    while(cfpos.size()<30){
        const auto w=ri(eng);
        if(!cfpos.contains(w)) cfpos.emplace(w),fpos.emplace_back(w);
    }
    vector chkP(N,true);
    cir(i,0,K) chkP[P[i]]=false;
    vector<int> vaild;
    cir(i,0,N) if(!cfpos.contains(i)) vaild.emplace_back(i);
    auto ans=0;
    cir(__seed,0,128) if([&]{
        auto cv=vaild;
        random_engine ueng(__seed);
        ranges::shuffle(cv,ueng);
        auto pos=0;
        if(__seed<127){
            cir(i,0,60){
                const auto x=(X>>i)&1;
                if(!x) pos+=2;
                else if(chkP[cv[pos]]) ++pos;
                else if(!chkP[cv[pos+1]]) return false;
                else pos+=2;
            }
        }
        pos=0;
        cir(i,0,60){
            const auto x=(X>>i)&1;
            if(!x) Set(cv[pos++],false),Set(cv[pos++],false);
            else if(chkP[cv[pos]]) Set(cv[pos++],true);
            else Set(cv[pos++],true),Set(cv[pos++],true);
        }
        while(pos<120) Set(cv[pos++],false);
        return true;
    }()){
        ans=__seed;
        break;
    }
    cir(i,0,30){
        const auto b=i%10;
        const auto bi=(ans>>b)&1;
        Set(fpos[i],bi);
    }
}

long long Bruno(int N,int A[]){
    random_engine eng(_seed);
    set<int> cfpos;
    vector<int> fpos;
    randint ri(0,N-1);
    while(cfpos.size()<30){
        const auto w=ri(eng);
        if(!cfpos.contains(w)) cfpos.emplace(w),fpos.emplace_back(w);
    }
    auto __seed=0;
    cir(i,0,30){
        __seed|=(A[fpos[i]]<<(i%10));
    }
    auto ans=0ll;
    vector<int> vaild;
    cir(i,0,N) if(!cfpos.contains(i)) vaild.emplace_back(i);
    random_engine ueng(__seed);
    ranges::shuffle(vaild,ueng);
    auto pos=0;
    cir(i,0,60){
        if(A[vaild[pos]]){
            ans|=(1ll<<i);++pos;
            continue;
        }
        ++pos;
        ans|=((long long)(A[vaild[pos]])<<i);
        ++pos;
    }
    return ans;
}

```

另外一种可能的优化是把定种子换成 `chenlinxuan0226` @陈霖瑄0226 可以获得 61pts。

另外 `clx0226` 和 `陈霖瑄0226` 都是 61pts，比 `MikeMirzayanov` 高，更比 `ZengDingjun_EggArmy` 高出了 20pts。

# 约 70pts

考虑上面的做法一个比较大的问题是种子的存储有问题，我们考虑在更少的位数中存下这个数，然后把种子存 $4$ 遍。

不难发现 $1$ 的位数越多越能节约位数，考虑让 $1$ 尽量多，这样我们可以考虑反转，然后拿 $4$ 位出来存是否反转，这样可以获得 60pts 左右。

### Code (75pts，by juruoA，有删改)

```cpp
#include"Broken_device_lib.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long li;
typedef long double lf; 

inline li read(){
	long long ans = 0, f = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9'){
		f = (ch == '-') ? -1 : 1;
		ch = getchar();
	}
	while(ch <= '9' && ch >= '0'){
		ans = ans * 10 + (ch ^ 48);
		ch = getchar();
	}
	return ans * f;
} 

li Get(li s, li i){return s >> i & 1;}

#define SEED 569490

void Anna(int N,long long X,int K,int P[]){
    li vis[160];
    li p[160], p2[160];
    std::mt19937 rng2(SEED);
	li FL = 0, cnt0 = 0, cnt1 = 0;
	for(li i = 0; i <= 59; i++){
		if(Get(X, i)) cnt1++;
		else cnt0++;
	}
	if(cnt1 > cnt0) FL = 1;
	if(FL){
		for(li i = 0; i <= 59; i++){
			li temp = Get(X, i);
			X -= (1ll << i) * temp;
			X += (1ll << i) * (!temp);
		}
	}
    memset(vis, 0, sizeof vis);
    for(li i = 0; i < K; i++) vis[P[i]] = 1;
    li S;
	li len = 120;
	for(li i = 0; i < 150; i++) p[i] = i;
	shuffle(p, p + 150, rng2);
    for(li seed = 1; 1; seed++){
        li fl = 1;
        std::mt19937 rng1(seed);
		for(li i = 0; i < len; i++) p2[i] = p[i];
		shuffle(p2, p2 + len, rng1);
        for(li i = 0; i <= 59; i++){
			li r1 = p2[i * 2], r2 = p2[i * 2 + 1];
            if(Get(X, i) == 1 && (vis[r1] == 1 && vis[r2] == 1)){
                fl = 0;
				break;
            }
        }
        if(fl){
            S = seed;
            break;
        }
    }
    std::mt19937 rng1(S);
	for(li i = 0; i < len; i++) p2[i] = p[i];
	shuffle(p2, p2 + len, rng1);
    for(li i = 0; i <= 59; i++){
		li r1 = p2[i * 2], r2 = p2[i * 2 + 1];
		Set(r1, Get(X, i)), Set(r2, Get(X, i));
    }
	li cnt = 0, i;
	for(i = 120; i + 4 < 145; i += 4, cnt++){
		Set(p[i], Get(S, cnt));
		Set(p[i + 1], Get(S, cnt));
		Set(p[i + 2], Get(S, cnt));
		Set(p[i + 3], Get(S, cnt));
	}
	for(; i < 145; i++){
		Set(p[i], 0);
	}
	for(; i < 150; i++){
		Set(p[i], FL);
	}
}



long long Bruno( int N, int A[] ){
    li ans = 0;
    li p[160], p2[160];
    std::mt19937 rng2(SEED);
	li len = 120;
	for(li i = 0; i < 150; i++) p[i] = i;
	shuffle(p, p + 150, rng2);
    li S = 0, cnt = 0;
    li fl = 0;
    fl = (A[p[147]]) | (A[p[148]]) | (A[p[149]]) | (A[p[146]]) | (A[p[145]]);
    for(li i = 120; i + 4 < 146; i += 4, cnt++){
        S |= (A[p[i]] * (1ll << cnt));
        S |= (A[p[i + 1]] * (1ll << cnt));
        S |= (A[p[i + 2]] * (1ll << cnt));
        S |= (A[p[i + 3]] * (1ll << cnt));
    }
    std::mt19937 rng1(S);
	for(li i = 0; i < len; i++) p2[i] = p[i];
	shuffle(p2, p2 + len, rng1);
    for(li i = 0; i <= 59; i++){
		li r1 = p2[i * 2], r2 = p2[i * 2 + 1];
        ans |= (A[r1] * (1ll << i));
        ans |= (A[r2] * (1ll << i));
    }
    if(fl){
		for(li i = 0; i <= 59; i++){
			li temp = ((ans >> i) & 1);
			ans -= (1ll << i) * temp;
			ans += (1ll << i) * (!temp);
		}
    }
    return ans;
}

```

# 100pts

~~多试几个种子大家加油。~~

考虑传种子错误率太高啦，这样显然无法冲击更高分了。

这个时候 [IGM $\color{red}{\text{251Sec}}$](https://www.luogu.com.cn/user/363415) 提出了一些见解，他说他会做 $3^{35}$，具体就是考虑相邻两位如果有至少一位坏掉了就不用设为 $0$，否则设为一个非零数就可以存 $0,1,2$。

有一个剪枝就是如果一个位本来就是 $0$ 那么它坏掉了也不影响，所以可以不管这种情况。

剩下的可以使用定种子随机打乱避免被干掉。

### Code (100pts)

```cpp
#include"Broken_device_lib.h"
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;

using random_engine=mt19937_64;
using randint=uniform_int_distribution<int>;
static constexpr auto _seed='MikeMirzayanov';

void Anna(int N,long long X,int K,int P[]){
    random_engine eng(_seed);
    vector<int> a(N);
    iota(a.begin(),a.end(),0);
    ranges::shuffle(a,eng);
    vector<int> ternary;
    while(X) ternary.emplace_back(X%3),X/=3;
    ranges::reverse(ternary);
    auto pos=0;
    set<int> invaild(P,P+K);
    for(auto&i:ternary){
        if(!i){            // Type '01'
            while(pos+2<N&&invaild.contains(a[pos+1])){
                Set(a[pos++],false);
                Set(a[pos++],false);
            }
            Set(a[pos++],false);
            Set(a[pos++],true);
        }else if(i==1){    // Type '10'
            while(pos+2<N&&invaild.contains(a[pos])){
                Set(a[pos++],false);
                Set(a[pos++],false);
            }
            Set(a[pos++],true);
            Set(a[pos++],false);
        }else{             // Type '11'
            while(pos+2<N&&(invaild.contains(a[pos])||invaild.contains(a[pos+1]))){
                Set(a[pos++],false);
                Set(a[pos++],false);
            }
            Set(a[pos++],true);
            Set(a[pos++],true);
        }
        if(pos+2>N-1) break;
    }
    for(;pos<N;++pos) Set(a[pos],false);
}

long long Bruno(int N,int A[]){
    random_engine eng(_seed);
    vector<int> a(N);
    iota(a.begin(),a.end(),0);
    ranges::shuffle(a,eng);
    auto ans=0ll;
    for(auto pos=0;pos<N;pos+=2){
        if(A[a[pos]]||A[a[pos+1]]){
            (ans*=3)+=(map{
                pair(pair(0,1),0),
                pair(pair(1,0),1),
                pair(pair(1,1),2)
            })[{A[a[pos]],A[a[pos+1]]}];
        }
    }
    return ans;
}
```
