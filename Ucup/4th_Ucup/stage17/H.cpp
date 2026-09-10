#include<bits/stdc++.h>

using i64 = long long;
using ll = long long;

using namespace std;
using pii = pair<int,int>;
const ll N = 5e5 + 9;
ll n,m;
ll a[N];
vector<pii> v;
ll b[N];

void solve()
{
    cin >> n >> m;
    ll all = 2 * n - 2;
    v.clear();
    ll sum = 0;
    int id = 0;
    for(int i = 1;i <= n;i++)
    {
        cin >> a[i];
    }
    if(n == 1)
    {
        if(a[1] == 0 || a[1] == -1)
        {
            cout << "YES\n";
            return;
        }
        else
        {
            cout << "NO\n";
            return;
        }
    }

    for(int i = 1;i <= n;i++)
    {
        if(a[i] == 0)
        {
            a[i] = m;
        }

        if(a[i] == -1)
        {
            id = i;
            sum++;
        }
        else
        {
            sum += a[i];
            if(a[i] >= n)
            {
                cout << "NO\n";
                return;
            }
        }
    }
    if(sum > all)
    {
        cout << "NO\n";
        return;
    }
    else
    {
        ll left = all - sum;
        if(id)
        {
            for(int i = 1;i <= n;i++)
            {
                if(a[i] == -1)
                {
                    if(i == id) v.push_back({left + 1,i});
                    else v.push_back({1,i});
                }
                else v.push_back({a[i],i});
            }
        }
        else
        {
            if( (left % m) != 0)
            {
                cout << "NO\n";
                return;
            }
            for(int i = 1;i <= n;i++)
            {
                while(a[i] + m < n && left > 0)
                {
                    a[i] += m;
                    left -= m;
                }
            }

            if(left != 0)
            {
                cout << "NO\n";
                return;
            }
            for(int i = 1;i <= n;i++)
            {
                v.push_back({a[i],i});
            }
        }
        cout << "YES\n";
        sort(v.begin(),v.end());

        for(int i = 0;i < n;i++)
        {
            b[v[i].second] = v[i].first;
            //cerr << v[i].second << ' ' << v[i].first << '\n';
        }
        int cur = n - 1;
        for(int i = n - 2;i >= 0;i--)
        {

            while( b[v[cur].second] == 0 && cur >= 1) 
            {
                //cerr << cur << ' ' << i << ' ' << v.size() << '\n';
                //cerr << v[cur].second << ' ' << b[v[cur].second] << '\n';
                cur--;
            }
            if(cur == i)
            {
                cout << v[cur].second << ' ' << v[i-1].second << '\n';
                b[v[cur].second]--;
                b[v[i-1].second]--;
                i--;                    
            }
            else
            {
                //cerr << cur << ' ' << i << endl;
                cout << v[cur].second << ' ' << v[i].second << '\n';

                b[v[cur].second]--;
                b[v[i].second]--;
            }
        }
    }
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
