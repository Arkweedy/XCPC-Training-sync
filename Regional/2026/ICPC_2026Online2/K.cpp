#include<bits/stdc++.h>

using i64 = long long;
using ll = long long;
using namespace std;
const int N = 5e3 + 9;
void solve()
{
    int n;
    cin >> n;
    vector<int> v;
    for(int i = 1;i <= n;i++)
    {
        int a;
        cin >> a;
        v.push_back(a);
    }
    sort(v.begin(),v.end());
    int least = 0;
    vector<int> cy;
    map<int,bool> ma;
    for(int i = 0;i < n;i++)
    {
        if(v[i] == least)
        {
            least++;
        }
        else 
        {
            ma[v[i]] = true;
            cy.push_back(v[i]);
        }
    }
    v = cy;
    int ans = 0;
    int q;
    cin >> q;
    map<int,int> aa;
    map<int,bool> mm;
    while(q--)
    {
        int k;
        cin >> k;
        if(!ma[k- least])
        {
            ans ^= least;
            continue;
        }

        if(mm[k])
        {
            ans ^= aa[k];
            continue;
        }
        
        int en = (int) v.size() - 1;
        vector<bool> mark(v.size(),false);
        int be = 0;
        int cur = least;
        while(1)
        {
            //cerr << be << ' ' << en << '\n';
            //cerr << v.size() << ' ' << mark.size() << '\n';
            while(be < v.size())
            {
                if(mark[be]) be++;
                else if(v[be] < cur) be++;
                else break;
            }
            while(en >= 0)
            {
                if(mark[en]) en--;
                else if(v[en] > k - cur) en--;
                else break;
            }
            if(be < v.size() && v[be] == cur)
            {
                mark[be] = true;
                be++;
                cur++;
            }
            else if(en >= 0 && v[en] == k - cur)
            {
                mark[en] = true;
                en--;
                cur++;
            }
            else  break;
        }
        //cerr << cur << '\n';
        mm[k] = true;
        aa[k] = cur;
        ans ^= cur;
    }
    cout << ans << '\n';
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



