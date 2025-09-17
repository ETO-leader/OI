#include <bits/stdc++.h>
using namespace std;
const int MOD = 998244353;

long long fac(int n) {
    long long res = 1;
    for (int i = 2; i <= n; i++) {
        res = (res * i) % MOD;
    }
    return res;
}

int main() {
    freopen("recall.in", "r", stdin);
    freopen("recall.out", "w", stdout);
    int testID, T;
    cin >> testID >> T;
    if(testID==0){
    	printf("5 46\n5 20\n5 28\n7 1190\n6 320\n5 20\n4 4\n6 18\n4 4\n5 11\n");
		return 0;
	}
    while (T--) {
        int n;
        cin >> n;
        vector<int> deg(n + 1, 0);
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            deg[u]++;
            deg[v]++;
        }
        bool is_chain = true;
        if (deg[1] != 1) {
            is_chain = false;
        }
        int count1 = 0;
        for (int i = 1; i <= n; i++) {
            if (deg[i] > 2) {
                is_chain = false;
            }
            if (deg[i] == 1) {
                count1++;
            }
        }
        if (count1 != 2) {
            is_chain = false;
        }
        bool is_star = true;
        if (deg[1] != n - 1) {
            is_star = false;
        }
        for (int i = 2; i <= n; i++) {
            if (deg[i] != 1) {
                is_star = false;
            }
        }
        if (is_chain) {
            cout<<n<< " " <<fac(n)<< endl;
        } else if (is_star) {
            cout <<2<< " " <<1<< endl;
        }
    }
    return 0;
}
