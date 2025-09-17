#include<iostream>
#include<fstream>
#include<algorithm> 
std::ifstream fin("reverse.in");
std::ofstream fout("reverse.out");

int a[2000005], id, n, k;

int b[2000005];
int lowbit(int x) {
	return x & -x;
}
int check(int x) {
	int ret = 0;
	while (x > 0) {
		ret += b[x];
		x -= lowbit(x);
	}
	return ret;
}
void update(int x, int va) {
	while (x <= n) {
		b[x] += va;
		x += lowbit(x);
	}
}

int main() {
	fin >> id >> n >> k; int kk = 0;
	for (int i = 1; i <= n; ++i) {
		fin >> a[i]; update(a[i], 1); kk += i-check(a[i]);
	}
	k = kk-k; if (k == 0) {fout << 0; return 0;}
	for (int i = 1; i <= n; ++i) {
		b[i] = 0;
	}
	int last = 2; int maxi = -1, out1, out2; update(a[1], 1); int now = 0; 
	for (int i = 1; i <= n; ++i) {
		while (1) {
			if (last == n+1) break; 
			if ((last-i)-check(a[last]) + now > k) {
				now -= check(a[i])-1;
				update(a[i], -1);
				break;
			}
			now = (last-i)-check(a[last]) + now; update(a[last], 1); last++; 
			if (now > maxi) {
				maxi = now; out1 = i, out2 = last-1;
			}
			if(last == n+1 || maxi == k) break;
		}
	}
	if (maxi == k) {
		fout << 1 <<"\n" <<out1 <<" "<<out2; return 0;
	}
	fout << 2 <<"\n" <<out1 <<" "<<out2 <<"\n";
	std::sort(a+out1, a+out2+1);
	k -= maxi;
	for (int i = 1; i<= n; ++i) b[i] = 0;
	last = 2; maxi = -1; update(a[1], 1); now = 0; 
	for (int i = 1; i <= n; ++i) {
		while (1) {
			if (last == n+1) break; 
			if ((last-i)-check(a[last]) + now > k) {
				now -= check(a[i])-1;
				update(a[i], -1);
				break;
			}
			now = (last-i)-check(a[last]) + now; update(a[last], 1); last++; 
			if (now > maxi) {
				maxi = now; out1 = i, out2 = last-1;
			}
			if(last == n+1 || maxi == k) break;
		}
	}
	fout << out1 <<" "<<out2 <<"\n";
} 
