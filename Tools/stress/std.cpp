#include<bits/stdc++.h>

#define ll long long
#define i64 long long
#define ull unsigned long long

using namespace std;

void merge(vector<pair<ll, ll>>& py, int l, int r)
{
    int mid = (l + r) / 2;
    vector<pair<ll,ll>>tmp;
    int p = l, q = mid + 1;
    while (p <= mid && q <= r) {
        if (py[p].first <= py[q].first) {
            tmp.push_back(py[p]);
            p++;
        }
        else {
            tmp.push_back(py[q]);
            q++;
        }
    }
    while (p <= mid) {
        tmp.push_back(py[p]);
        p++;
    }
    while (q <= r) {
        tmp.push_back(py[q]);
        q++;
    }
    for (int i = l; i <= r; i++) {
        py[i] = tmp[i - l];
    }
    return;
}

ll dq(const vector<pair<ll, ll>>& px, vector<pair<ll, ll>>& py, int l, int r)
{
    if (l == r) {
        swap(py[l].first, py[l].second);
        return LLONG_MAX;
    }
    else if (r - l == 1) {
        if (py[l].second > py[r].second)
            swap(py[l], py[r]);
        swap(py[l].first, py[l].second);
        swap(py[r].first, py[r].second);
        return (px[r].first - px[l].first) * (px[r].first - px[l].first) + (px[r].second - px[l].second) * (px[r].second - px[l].second);
    }
    int mid = (l + r) / 2;
    ll midx = px[mid].first;
    ll sigma = min(dq(px, py, l, mid), dq(px, py, mid + 1, r));
    merge(py, l, r);
    vector<int>in;
    ll lx = px[l].first, rx = px[r].first;
    for (int i = l; i <= r; i++) {
        if ((py[i].second - midx) * (py[i].second - midx) <= sigma ) {//&& py[i].second >= lx && py[i].second <= rx
            in.push_back(i);
        }
    }
    ll mindis = sigma;
    for (int i = 0; i < in.size(); i++) {
        for (int j = i + 1; j < in.size(); j++) {
            if ((py[in[j]].first - py[in[i]].first) * (py[in[j]].first - py[in[i]].first) >= sigma) {
                break;
            }
            else {
                mindis = min(mindis,
                    (py[in[j]].first - py[in[i]].first) * (py[in[j]].first - py[in[i]].first) +
                    (py[in[j]].second - py[in[i]].second) * (py[in[j]].second - py[in[i]].second));
            }
        }
    }
    return mindis;
}


void solve()
{
    int n;
    cin >> n;
    vector<pair<ll, ll>>px, py;
    for (int i = 0; i < n; i++) {
        ll x, y;
        cin >> x >> y;
        px.emplace_back(pair<int, int>(x, y));
        py.emplace_back(pair<int, int>(x, y));
    }
    sort(px.begin(), px.end());
    sort(py.begin(), py.end());
    cout << (dq(px, py, 0, n - 1)) << endl;
    //printf("%.4lf",sqrt(dq(px, py, 0, n - 1)));
    return;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    
        solve();
    return 0;
}
