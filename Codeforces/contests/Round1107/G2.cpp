#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//G2.cpp Create time : 2026.07.04 18:41

ostream &operator<<(ostream &os, i128 n) {
    if (n == 0) {
        return os << 0;
    }
    string s;
    while (n > 0) {
        s += char('0' + n % 10);
        n /= 10;
    }
    reverse(s.begin(), s.end());
    return os << s;
}

void solve()
{
    int n;
    cin >> n;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }

    i128 ans = 0;
    stack<int>st;
    st.push(0);
    for(int i = 1;i < n;i++){
        while(!st.empty() && a[i] % a[st.top()] != 0){
            ans += 1ll * (n - i) * min(a[i] % a[st.top()], a[st.top()] - a[i] % a[st.top()]);
            st.pop();
        }
        st.push(i);
    }
    cout << ans << endl;
    return;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}