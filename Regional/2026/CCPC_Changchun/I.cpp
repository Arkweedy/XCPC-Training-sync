#include<bits/stdc++.h>

using ll = long long;
using i64 = long long;

using namespace std;

vector<string>p = {
    "",
    "00",
    "01",
    "10",
    "11"
};

vector<string>q = {
    "",
    "001",
    "010",
    "011",
    "100",
    "101",
    "110"
};



void solve1()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    //
    map<string, string>bg;
    bg[p[1]] = q[1];
    bg[p[2]] = q[2];
    bg[p[3]] = q[5];
    bg[p[4]] = q[6];

    map<string, map<string, string>>ne;
    ne[q[1]][p[1]] = q[1];
    ne[q[1]][p[2]] = q[2];
    ne[q[1]][p[3]] = q[3];
    ne[q[1]][p[4]] = q[5];

    ne[q[2]][p[1]] = q[2];
    ne[q[2]][p[2]] = q[3];
    ne[q[2]][p[3]] = q[5];
    ne[q[2]][p[4]] = q[6];

    ne[q[3]][p[1]] = q[1];
    ne[q[3]][p[2]] = q[2];

    ne[q[4]][p[3]] = q[5];
    ne[q[4]][p[4]] = q[6];

    ne[q[5]][p[1]] = q[1];
    ne[q[5]][p[2]] = q[2];
    ne[q[5]][p[3]] = q[3];
    ne[q[5]][p[4]] = q[5];

    ne[q[6]][p[1]] = q[2];
    ne[q[6]][p[2]] = q[3];
    ne[q[6]][p[3]] = q[5];
    ne[q[6]][p[4]] = q[6];
    

    string pre;

    string ans;

    int flg = 0;

    for(int i = 0;i < n; i += 2){
        string t = s.substr(i, 2);
        //cerr << t << endl;
        if(pre.empty()){
            string x = bg[t];
            ans += x;
            pre = x;
            //cerr << x << endl;
        }
        else{
            string x = ne[pre][t];
            if(x == q[3]){
                if(i + 3 < n){
                    string y = s.substr(i + 2, 2);
                    if(y == p[1] || y == p[2]){
                        // x = q[3]
                    }
                    else{// p[3] p[4]
                        x = q[4];
                    }
                }
                else{
                    if(i + 2 < n){
                        flg = 1;
                        if(s[i + 2] == '0'){
                            // x = q[3]
                        }
                        else{
                            x = q[4];
                        }
                    }
                }
            }
            ans += x;
            //cerr << x << endl;
            pre = x;
        }
    }

    if(n % 2 == 1){
        ans += s[n - 1];
    }
    cout << ans.size() << endl;
    cout << ans << endl;
    return;
}

void solve2()
{
    int n;
    string s;
    cin >> n >> s;

    map<string, string>bg;
    bg[q[1]] = p[1];
    bg[q[2]] = p[2];
    bg[q[5]] = p[3];
    bg[q[6]] = p[4];

    map<string, map<string, string>>ne;
    ne[q[1]][q[1]] = p[1];
    ne[q[1]][q[2]] = p[2];
    ne[q[1]][q[3]] = p[3];
    ne[q[1]][q[4]] = p[3];
    ne[q[1]][q[5]] = p[4];

    ne[q[2]][q[2]] = p[1];
    ne[q[2]][q[3]] = p[2];
    ne[q[2]][q[4]] = p[2];
    ne[q[2]][q[5]] = p[3];
    ne[q[2]][q[6]] = p[4];

    ne[q[3]][q[1]] = p[1];
    ne[q[3]][q[2]] = p[2];

    ne[q[4]][q[5]] = p[3];
    ne[q[4]][q[6]] = p[4];

    ne[q[5]][q[1]] = p[1];
    ne[q[5]][q[2]] = p[2];
    ne[q[5]][q[3]] = p[3];
    ne[q[5]][q[4]] = p[3];
    ne[q[5]][q[5]] = p[4];

    ne[q[6]][q[2]] = p[1];
    ne[q[6]][q[3]] = p[2];
    ne[q[6]][q[4]] = p[2];
    ne[q[6]][q[5]] = p[3];
    ne[q[6]][q[6]] = p[4];

    string pre;

    string ans;

    for(int i = 0;i < n;i += 3){
        string t = s.substr(i, 3);
        //cerr << t << endl;
        if(pre.empty()){
            string x = bg[t];
            ans += x;
            pre = t;
            //cerr << x << endl;
        }
        else{
            string x = ne[pre][t];
            ans += x;
            pre = t;
            //cerr << x << endl;
        }
        
    }

    if(n % 3 == 1){
        ans += s[n - 1];
    }

    cout << ans.size() << endl;
    cout << ans << endl;

    return;
}


int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    int r;
    cin >> tt >> r;
    if(r == 1){
        while(tt--){
            solve1();
        }
    }
    else{
        while(tt--){
            solve2();
        }
    }
    return 0;
}