#include<bits/stdc++.h>

using i64 = long long;
using ll = long long;
using namespace std;
const int N = 6;
string s[N] = {"WrongProblem","SameProblem","UnreasonableProblemArrangement","UnreasonableLimitForProblem","WeakTestsForProblem","BadProblem"};
int a[N] = {100,30,10,5,3,1};
bool ck1(string str,int i)
{
    return str == s[i];
}
bool ck2(string str,int i)
{
    if(str.size() != s[i].size() + 1) return false;
    for(int j = 0;j < s[i].size();j++)
    {
        if(s[i][j] != str[j]) return false;
    }
    if(str.back()> 'L' || str.back() < 'A') return false;
    
    return true;
}
int ck(string str)
{
    for(int i = 0;i < 6;i++)
    {
        if(i == 2)
        {
            if(ck1(str,i)) return a[i];
        }
        else
        {
            if(ck2(str,i)) return a[i];
        }
    }
    return 0;
}
void solve()
{
    int n,p;
    int ans = 0;
    cin >> n >> p;
    while(n--)
    {
        string str;
        cin >> str;
        ans += ck(str);
    }
    //cerr << ans << '\n';
    if(ans > p)
    {
        cout <<"Joker\n";
    }
    else cout << "Judger\n";
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}



