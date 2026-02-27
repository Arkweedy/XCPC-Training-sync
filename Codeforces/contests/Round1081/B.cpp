#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//B.cpp Create time : 2026.02.21 22:45

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    int a = count(s.begin(),s.end(), '0'), b =count(s.begin(), s.end(), '1');
    if(a % 2 == 0 && b % 2 == 1){
        cout << -1 << endl;
        return;
    }

    vector<int>ans;
    if(b % 2 == 0){
        for(int i = 0;i < n;i++){
            if(s[i] == '1'){
                ans.push_back(i + 1);
            }
        }
    }
    else{
        // 1 1
        cerr << "in"  << endl;
        int p = -1;
        for(int i = 0;i < n;i++){
            if(s[i] == '1'){
                p = i;
                break;
            }
        }
        for(int i = 0;i < n;i++){
            if(i != p){
                s[i] = '1' + '0' - s[i];
            }
        }
        
        for(int i = 0;i < n;i++){
            if(s[i] == '1' && i != p){
                ans.push_back(i + 1);
            }
        }
    }
    cout << ans.size() << endl;
    if(ans.size() > 0){
        for(int i = 0;i < ans.size();i++){
            cout << ans[i] << " ";
        }
        cout << endl;
    }
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