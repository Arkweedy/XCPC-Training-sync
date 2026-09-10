#include<bits/stdc++.h>

using i64 = long long;
using ll = long long;
#define int ll
using namespace std;
using pii = pair<int,int>;
const int N = 107;
const int M = 1007;
const int INF = 2e9 + 7;
bool markc[N];int xc[N],yc[N];

bool markb[M];int xb[M],yb[M];
int n,m,a,t;
int w,h;
int finc[N],finb[M];
int cntc[N],timec[N];
ll ansc[N];
ll cur;

vector<pii> eat;
int teat;
vector<int> die;
int tdie;
int dis(int i,int j)
{
    return abs(xc[i] - xb[j]) + abs(yc[i] - yb[j]);
}
bool ck1(int i,int j)
{
    if(finc[i] == 0) return true;
    int p1 = dis(i,j);
    int p2 = dis(i,finc[i]);
    if(p1 < p2) return true;
    else if(p1 == p2)
    {
        if(xb[j] < xb[ finc[i] ]) return true;
        else if(xb[j] == xb[finc[i]] && yb[j] < yb[finc[i]]) return true;
        return false; 
    }
    else return false;
}
bool ck2(int i,int j)
{
    if(finb[j] == 0) return true;
    int p1 = dis(i,j);
    int p2 = dis(finb[j],j);
    if(p1 < p2) return true;
    else if(p1 == p2 && i < finb[j]) return true;
    else return false;
}
void upd(int i,int t)
{
    if(finc[i] && markc[i])
    {
        int j = finc[i];
        int dis1 = abs(xc[i] - xb[j]);
        if(t < dis1)
        {
            if(xc[i] > xb[j])
            {
                xc[i] -= t;
            }
            else xc[i] += t;
        }
        else
        {
            if(xc[i] > xb[j])
            {
                xc[i] -= dis1;
            }
            else xc[i] += dis1;
            int left = t - dis1;
            if(yc[i] > yb[j])
            {
                yc[i] -= left;
            }
            else yc[i] += left;
        }
    }
}
void solve()
{
    cin >> n >> m >> a >> t;
    cin >> w >> h;
    for(int i = 1;i <= n;i++) 
    {
        markc[i] = true;
        cin >> xc[i] >> yc[i];
        cntc[i] = 0;
        timec[i] = -1;
        ansc[i] = -1;
    }
    for(int i = 1;i <= m;i++)
    {
        markb[i] = true;
        cin >> xb[i] >> yb[i];
    }
    cur = 0;
    while(1)
    {
        for(int i = 1;i <= n;i++) finc[i] = 0;
        for(int i = 1;i <= m;i++) finb[i] = 0;
        teat = INF;
        eat.clear();
        tdie = INF;
        die.clear();
        for(int i = 1;i <= n;i++)
        {
            if(markc[i])
            {
                for(int j = 1;j <= m;j++)
                {
                    if(markb[j])
                    {
                        if(ck1(i,j))
                        {
                            finc[i] = j;
                        }
                    }
                }
                if(finc[i] != 0 && ck2(i,finc[i]))
                {
                    finb[finc[i]] = i;
                }
            }
        }
        for(int j = 1;j <= m;j++)
        {
            if(markb[j] && finb[j])
            {
                int time = dis(finb[j],j);
                if(time < teat)
                {
                    teat = time;
                
                    eat.clear();
                    eat.push_back({finb[j],j});
                }
                else if(time == teat) eat.push_back({finb[j],j});
            }
        }
        for(int i = 1;i <= n;i++)
        {
            if(markc[i] && cntc[i] >= a)
            {
                int time = timec[i];
                if(time < tdie)
                {
                    tdie = time;
                    die.clear();
                    die.push_back(i);
                }
                else if(time == tdie) die.push_back(i);
            }
        }
        if(tdie == INF && teat == INF) break;
        if(teat <= tdie)
        {
            for(const auto [i,j] : eat)
            {
                cntc[i]++;
                markb[j] = false;
            }
            for(int i = 1;i <= n;i++)
            {
                if(cntc[i] >= a)
                {
                    if(timec[i] == -1) timec[i] = t;
                    else timec[i] -= teat;
                }
                upd(i,teat);
            }
            cur += teat;
        }
        else
        {
            for(const int i : die)
            {
                markc[i] = false;
                ansc[i] = cur + tdie;
            }
            for(int i = 1;i <= n;i++)
            {
                if(timec[i] != -1 &&cntc[i] >= a) timec[i] -= tdie;
                upd(i,tdie);
            }
            cur += tdie;
        }
    }
    for(int i = 1;i <= n;i++)
    {
        cout << ansc[i] << '\n';
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}
