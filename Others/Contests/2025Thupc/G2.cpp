#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.12.14 13:20:30

string operator+ (string a, string b)
{
    reverse(a.begin(),a.end());
    reverse(b.begin(),b.end());
    string c;
    int carry = 0;
    for(int i = 0;i < max(a.size(), b.size());i++){
        int x = 0;
        if(i < a.size())x += a[i] - '0';
        if(i < b.size())x += b[i] - '0';
        if(carry)x++;
        c.push_back(x % 2 + '0');
        if(x >= 2)carry = 1;
        else carry = 0;
    }
    reverse(c.begin(),c.end());
    return c;
}

string minstr(string a, string b)
{
    if(a.size() < b.size())return a;
    else if(b.size() < a.size())return b;
    else{
        for(int i = 0;i < a.size();i++){
            if(a[i] < b[i])return a;
            else if(b[i] < a[i])return b;
        }
        return a;
    }
}



void solve()
{
    int len;
    cin >> len;
    string s;
    cin >> s;

    auto get = [&](int n)->string // prefix 0 = x
    {
        string a, b;
        int rem = s.length() - n;
        int bita = rem / 2, bitb = (rem + 1) / 2;
        int pa = 0, pb = 0;
        for(int i = 0;i < s.length();i++){
            if(n > 0){
                if(s[i] == '0'){
                    b.push_back(s[i]);
                    n--;
                }
                else{
                    a.push_back(s[i]);
                    pa++;
                }
            }
            else{
                if(s[i] == '0'){
                    if(pa < pb){
                        a.push_back('0');
                        pa++;
                    }
                    else{
                        b.push_back('0');
                        pb++;
                    }
                } 
                else{
                    if(pa > pb && pa < bita){
                        a.push_back('1');
                        pa++;
                    }
                    else if(pb > pa && pb < bitb){
                        b.push_back('1');
                        pb++;
                    }
                    else{
                        a.push_back('1');
                        pa++;
                    }
                }
            }
        }
        string c = a + b;
        reverse(c.begin(),c.end());
        while(!c.empty() && c.back() == '0')c.pop_back();
        reverse(c.begin(),c.end());
        return c;
    };


    int cnt = 0;
    int pre = 0;
    for(int i = 0;i < s.length();i++){
        if(s[i] == '0'){
            cnt++;
        }
        if(i - cnt < s.length() - i){
            break;
        }
    }
    cnt--;

    int cnt0 = count(s.begin(),s.end(), '0');
    string ans = s;
    reverse(ans.begin(),ans.end());
    while(!ans.empty() && ans.back() == '0')ans.pop_back();
    reverse(ans.begin(),ans.end());
    for(int i = max(0, cnt - 20);i <= min(cnt0, cnt+20);i++){
        ans = minstr(get(i), ans);
    }
    if(ans.empty())ans = '0';
    cout << ans << endl;
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