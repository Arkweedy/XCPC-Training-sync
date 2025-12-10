#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

int Duval(const string& s)//return begin of min expression
{
    int n = s.length();
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

void solve()
{
    int n;
    cin>>n;
    string s;
    cin>>s;
    int bg = Duval(s);
    for(int i = bg;i < n;i++){
        cout<<s[i];
    }
    for(int i = 0;i < bg;i++){
        cout<<s[i];
    }
    cout<<endl;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}