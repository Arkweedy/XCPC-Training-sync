#include<bits/stdc++.h>

using ll = long long;

using namespace std;

constexpr int N = 1e5 + 10;

using AAC = array<string, 13>;

void solve()
{
    map<string, int>mp;
    mp["Ala"] = 0;
    mp["Asn"] = 1;
    mp["Asp"] = 2;
    mp["Cys"] = 3;
    mp["Gln"] = 4;
    mp["Glu"] = 5;
    mp["Gly"] = 6;
    mp["Met"] = 7;
    mp["Ser"] = 8;
    mp["Thr"] = 9;

    
    vector<AAC>aac(10);

    aac[0] = {
        "  H H O    ",
        "  | | ||   ",
        "H-N-C-C-O-H",
        "    |      ",
        "  H-C-H    ",
        "    |      ",
        "    H      ",
        "           ",
        "           ",
        "           ",
        "           ",
        "           ",
        "           "
    };

    aac[1] = {
        "  H H O    ",
        "  | | ||   ",
        "H-N-C-C-O-H",
        "    |      ",
        "  H-C-H    ",
        "    |      ",
        "  O=C-N-H  ",
        "      |    ",
        "      H    ",
        "           ",
        "           ",
        "           ",
        "           "
    };

    aac[2] = {
        "  H H O    ",
        "  | | ||   ",
        "H-N-C-C-O-H",
        "    |      ",
        "  H-C-H    ",
        "    |      ",
        "  O=C-O-H  ",
        "           ",
        "           ",
        "           ",
        "           ",
        "           ",
        "           "
    };

    aac[3] = {
        "  H H O    ",
        "  | | ||   ",
        "H-N-C-C-O-H",
        "    |      ",
        "  H-C-S-H  ",
        "    |      ",
        "    H      ",
        "           ",
        "           ",
        "           ",
        "           ",
        "           ",
        "           "
    };

    //Gln
    aac[4] = {
        "  H H O    ",
        "  | | ||   ",
        "H-N-C-C-O-H",
        "    |      ",
        "  H-C-H    ",
        "    |      ",
        "  H-C-H    ",
        "    |      ",
        "  O=C-N-H  ",
        "      |    ",
        "      H    ",
        "           ",
        "           "
    };

    //Glu
    aac[5] = {
        "  H H O    ",
        "  | | ||   ",
        "H-N-C-C-O-H",
        "    |      ",
        "  H-C-H    ",
        "    |      ",
        "  H-C-H    ",
        "    |      ",
        "  O=C-O-H  ",
        "           ",
        "           ",
        "           ",
        "           "
    };

    //Gly
    aac[6] = {
        "  H H O    ",
        "  | | ||   ",
        "H-N-C-C-O-H",
        "    |      ",
        "    H      ",
        "           ",
        "           ",
        "           ",
        "           ",
        "           ",
        "           ",
        "           ",
        "           "
    };

    //Met
    aac[7] = {
        "  H H O    ",
        "  | | ||   ",
        "H-N-C-C-O-H",
        "    |      ",
        "  H-C-H    ",
        "    |      ",
        "  H-C-H    ",
        "    |      ",
        "    S      ",
        "    |      ",
        "  H-C-H    ",
        "    |      ",
        "    H      "
    };

    //Ser
    aac[8] = {
        "  H H O    ",
        "  | | ||   ",
        "H-N-C-C-O-H",
        "    |      ",
        "  H-C-O-H  ",
        "    |      ",
        "    H      ",
        "           ",
        "           ",
        "           ",
        "           ",
        "           ",
        "           "
    };

    //Thr
    aac[9] = {
        "  H H O    ",
        "  | | ||   ",
        "H-N-C-C-O-H",
        "    |      ",
        "  H-C-O-H  ",
        "    |      ",
        "  H-C-H    ",
        "    |      ",
        "    H      ",
        "           ",
        "           ",
        "           ",
        "           "
    };

    vector<int>len = {7,9,7,7,11,9,5,13,7,9};
    vector<int>mol = {89,132,133,121,146,147,75,149,105,119};
    constexpr int M = 13;

    auto merge = [&](AAC & A, AAC & B)->AAC
    {
        AAC res = A;
        int x = A[0].size();
        for(int i = 0;i < M;i++){
            res[i].pop_back();
        }
        res[2][x - 3] = '-';
        for(int i = 0;i < M;i++){
            res[i] += B[i].substr(2, B[i].size() - 2);
        }
        return res;
    };

    int n, m;
    cin>>n>>m;
    vector<int>chs;
    for(int i = 0;i < n;i++){
        string s;
        cin>>s;
        chs.push_back(mp[s]);
    }
    sort(chs.begin(),chs.end());

    vector<pair<AAC, int>>ans;
    constexpr int H2O = 18;

    auto dfs = [&](auto&&self, AAC ac, int mass, int outlen, int cnt)->void
    {
        if(mass > m)return;
        if(cnt >= 2){
            ans.emplace_back(ac, outlen);
        }
        for(int i = 0;i <chs.size();i++){
            int x = chs[i];
            self(self, merge(ac, aac[x]), mass + mol[x] - H2O, max(outlen, len[x]),cnt + 1);
        }
        return;
    };

    for(auto x : chs){
        dfs(dfs, aac[x], mol[x], len[x], 1);
    }

    auto output = [&](AAC& A, int outlen)->void
    {
        for(int i = 0;i < outlen;i++){
            cout<<A[i]<<endl;
        }
        cout<<endl;
    };

    cout<<ans.size()<<endl;
    for(auto& [A,outlen] : ans){
        output(A,outlen);
    }
    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tt = 1;
    //cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}