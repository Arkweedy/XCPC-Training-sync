#include <bits/stdc++.h>

using ll = long long;
using i64 = long long;

using namespace std;
using a3 = array<int,3>;
a3 f(vector<a3> v)
{
    
    //cout << v.size() << endl;
    if(v.size() == 1) return v[0];
    int s = v.size();
    vector<int> a,b,c;
    for(int i = 0;i < s;i++)
    {
        a.push_back(v[i][0]);
    }
    sort(a.begin(),a.end());
    int ja,jb,jc;
    ja = a[s/2];
    
    for(int i = 0;i < s;i++)
    {
        if(v[i][0] >= ja)
        {
            b.push_back(v[i][1]);
        }
        else
        {
            c.push_back(v[i][2]);
        }
    }

    sort(b.begin(),b.end());
    int ss = b.size();
    ss /= 2;
    jb = b[ss];

    sort(c.begin(),c.end());
    ss = c.size();
    ss /= 2;
    jc = c[ss];


    cout << "? " << ja << ' ' << jb << ' ' << jc << endl;
    cout.flush();

    string tt;
    cin >> tt;
    vector<a3> vv;
    for(int i = 0;i < s;i++)
    {
        if(tt[0] == '1' && v[i][0] >= ja) continue;
        if(tt[0] == '0' && v[i][0] < ja) continue;
        if(tt[1] == '1' && v[i][1] >= jb) continue;
        if(tt[1] == '0' && v[i][1] < jb) continue;
        if(tt[2] == '1' && v[i][2] >= jc) continue;
        if(tt[2] == '0' && v[i][2] < jc) continue;
        vv.push_back(v[i]);
    }
    return f(vv);
}
void solve()
{
    int n;
    cin >> n;
    vector<a3> v;
    for(int i = 0;i < n;i++)
    {
        int a,b,c;
        cin >> a >> b >> c;
        v.push_back({a,b,c});
    }
    a3 ans = f(v);
    cout << "! " << ans[0] << ' ' << ans[1] << ' ' << ans[2] << endl;
    cout.flush();
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
