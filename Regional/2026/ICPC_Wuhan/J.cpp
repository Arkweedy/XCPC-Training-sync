#include<bits/stdc++.h>

using ll = long long;
using i64 = long long;

using namespace std;
const int N = 2e5 + 9;
int n;
int a[N],b[N];
int cntb[N];
int cnta[N];
using pii = pair<int,int>;
void solve()
{
    cin >> n;
    map<int,int> m;
    for(int i = 0;i <= n;i++) cnta[i] = 0;
    for(int i = 1;i <= n;i++) 
    {
        cin >> a[i];
        if(a[i] <= n) cnta[a[i]]++;
        else m[a[i]]++;
    }
    for(int i = 1;i <= n;i++) cin >> b[i];
    
    for(int i = 0;i <= n;i++) cntb[i] = 0;
    for(int i = 1;i <= n;i++)
    {
        if(b[i] <= n) cntb[b[i]]++;
        else
        {
            m[b[i]]--;
            if(m[b[i]] == -1)
            {
                cout << "NO\=n";
                return;
            }
        }
    }
    for(const auto [x,y] : m) cnta[0] += y;
    pii x = {0,0};

    for(int i = 0;i <= n;i++) x.second += cnta[i];
    bool mark = true;
    int sum = x.second;
    for(int i = n;i >= 0;i--)
    {
        if(cnta[i] < cntb[i]) mark =false;
        if(mark)
        {
            if(cntb[i] >= i)
            {
                cout << "YES\n";
                return;
            }

            auto [ran,cur] = x;
            sum -= cntb[i];
            x = max(make_pair(ran - cntb[i],cur),make_pair(ran + cur - i,i - cntb[i]));
            x = max(x,make_pair(0,sum));
        }
        else
        {
            if(cntb[i] >= i)
            {
                cout << "YES\n";
                return;
            }
            auto [ran,cur] = x;
            x = max(make_pair(ran - cntb[i],cur),make_pair(ran + cur - i,i - cntb[i]));
            if(x.first < 0)
            {
                cout << "NO\n";
                return;
            }
        }
    }
    cout << "YES\n";

    
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