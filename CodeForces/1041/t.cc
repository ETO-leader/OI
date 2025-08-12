#include <bits/stdc++.h>
using namespace std;

#define SZ(x) int(x.size())

const int MXN = 1003;

int n, k, p[MXN], q[MXN], cnt=0;

int ask() {
    cout << "? ";
    for(int i=1; i<=n; i++) cout << q[i] << ' ';
    cout << endl;
    int r;
    cin >> r;
    return r;
}

void ans() {
    cout << "! ";
    for(int i=1; i<=n; i++) cout << p[i] << ' ';
    cout << endl;
}

bool mark[MXN];

void build(int i, vector<int> opt, vector<int> optbad) {
    fill(mark+1, mark+n+1, 0);
    fill(q+1, q+n+1, 0);
    q[k] = i;
    mark[i] = 1;
    for(int j=1; j<k && !opt.empty(); j++) {
        mark[q[j] = opt.back()] = 1;
        opt.pop_back();
    }
    for(int j=n; !opt.empty(); j--) {
        mark[q[j] = opt.back()] = 1;
        opt.pop_back();
    }
    for(int j=k+1; !optbad.empty(); j++) {
        mark[q[j] = optbad.back()] = 1;
        optbad.pop_back();
    }
    for(int j=1; j<=n; j++)
        if(!mark[j])
            opt.push_back(j);
    for(int j=1; j<=n; j++)
        if(!q[j]) {
            q[j] = opt.back();
            opt.pop_back();
        }
}

void rev() {
    vector<int> vec;
    for(int i=1; i<=n; i++)
        if(i!=k)
            vec.push_back(q[i]);
    for(int i=1; i<=n; i++)
        if(i!=k) {
            q[i] = vec.back();
            vec.pop_back();
        }
}

void Main() {
    cin >> n;
    k = (n+1)/4+1;
    cout << k << endl;
    for(int i=1; i<=n; i++) {
        vector<int> opt;
        for(int j=1; j<=n; j++)
            if(j!=i)
                opt.push_back(j);
        while(opt.size()>1) {
            int sz = SZ(opt) - min((SZ(opt)+1)/2, n-(2*k-1));
            build(i,
            vector<int>(opt.begin(), opt.begin()+sz),
            vector<int>(opt.begin()+sz, opt.end()));
            int val = ask();
            rev();
            val += ask();
            if(val==n-1) opt = vector<int>(opt.begin(), opt.begin()+sz);
            else opt = vector<int>(opt.begin()+sz, opt.end());
        }
        p[opt.back()] = i;
    }
    ans();
}

int32_t main() {
    int tc;
    cin >> tc;
    while(tc--) Main();
}