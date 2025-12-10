#include <bits/stdc++.h>
using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
int query1(int a, int b) {
    std::cout << "1 " << a << " " << b << std::endl;
    int ans;
    std::cin >> ans;
    return ans;
}
int query2(int a, std::vector<int> b) {
    std::cout << "2 " << a << " " << b.size();
    for (auto x : b) {
        std::cout << " " << x;
    }
    std::cout << std::endl;
    int ans;
    std::cin >> ans;
    return ans;
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) {
        int n;
        std::cin >> n;
        std::vector<int> a{0};
        for (int i = 1; i < n; i++) {
            if (query1(i, a[0])) {
                a.insert(a.begin(), i);
                continue;
            }
            if (query1(a.back(), i)) {
                a.insert(a.end(), i);
                continue;
            }
            int l = 0, r = a.size() - 1;
            while (l + 1 < r) {
                int m = (l + r) / 2;
                if (query1(i, a[m])) {
                    r = m;
                } else {
                    l = m;
                }
            }
            a.insert(a.begin() + r, i);
        }

        std::vector<std::string> ans(n, std::string(n, '0'));
        
        std::vector<int>st(n);
        for(int i=0;i<n-1;i++){
            st[i] = query2(a[i+1],{a[i]});
            // i i + 1
        }

        for(int i=0;i<n;i++){
            for(int j=i;j<n;j++){
                ans[a[i]][a[j]] = '1';
            }
        }

        for(int i=0;i<n-1;){
            if(!st[i]){
                i++;
                continue;
            }
            int j = i;
            while(j < n-1 && st[j])j++;

            //[i,j]
            for(int u=i;u<=j;u++){
                for(int v=i;v<=j;v++){
                    ans[a[u]][a[v]] = '1';
                    assert(a[u] < n && a[v] < n);
                }
            }

            i = j;
        }

        ans[0] = 

        std::cout << "3\n";
        for (int i = 0; i < n; i++) {
            std::cout << ans[i] << "\n";
        }
        std::cout.flush();
        int result;
        std::cin >> result;
    }
    return 0;
}