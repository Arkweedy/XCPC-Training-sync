#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.07.29 13:54:14

int Duval(const vector<int>& s)//return begin of min expression
{
    int n = s.size();
    int last = -1;
    for(int i = 0;i < n;){
        int j = i + 1, k = i;
        while(j < n && s[k] <= s[j]){
            if(s[j] > s[k])k = i;
            else k++;
            j++;
        }
        
        last = i;
        while(i <= k){//i + j - k <= j
            i += j - k;
        }
        if(j == n)break;//find last but not empty
    }
    return last;
};

vector<int> minExpr(const vector<int>&a)
{
    int n = a.size();
    int p = Duval(a);
    vector<int>res(n);
    for(int i = 0;i < n;i++){
        if(i + p < n)res[i] = a[i + p];
        else res[i] = a[i + p - n];
    }
    return res;
}

void solve()
{
    int n;
    cin >> n;
    vector<int>a(n);
    if(n == 1){
        a[0] = 1;
    }
    else if(n % 2 == 0){
        for(int i = 0;i < n / 2;i++){
            a[n - i * 2 - 1] = i + 1;
            a[n - i * 2 - 2] = n - i;
        }
        a = minExpr(a);
    }
    else{
        int k = n / 2;
        a[n - 2] = 1;
        a[n - 1] = k + 2;
        for(int i = 1;i < k;i++){
            a[n - i * 2 - 1] = n - i + 1;
            a[n - i * 2 - 2] = i + 2;
        }
        a[0] = 2;
        a = minExpr(a);
    }
    for(int i = 0;i < n;i++){
        cout << a[i] << " ";
    }
    cout << endl;
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