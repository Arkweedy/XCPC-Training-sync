#include <bits/stdc++.h>

using i64 = long long;

struct PAM {
    static constexpr int ALPHABET_SIZE = 28;
    struct Node {
        int len;
        int link;
        int cnt;
        std::array<int, ALPHABET_SIZE> next;
        Node() : len{}, link{}, cnt{}, next{} {}
    };
    std::vector<Node> t;
    int suff;
    std::string s;
    PAM() {
        init();
    }
    void init() {
        t.assign(2, Node());
        t[0].len = -1;
        suff = 1;
        s.clear();
    }
    int newNode() {
        t.emplace_back();
        return t.size() - 1;
    }
    int getval(char c) {
        if (c == '*') {
            return 26;
        }
        if (c == '#') {
            return 27;
        }
        return c - 'a';
    }
    bool add(char c) {
        int pos = s.size();
        s += c;
        int let = getval(c);
        int cur = suff, curlen = 0;
        while (true) {
            curlen = t[cur].len;
            if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos]) {
                break;
            }
            cur = t[cur].link;
        }
        if (t[cur].next[let]) {
            suff = t[cur].next[let];
            return false;
        }
        int num = newNode();
        suff = num;
        t[num].len = t[cur].len + 2;
        t[cur].next[let] = num;
        if (t[num].len == 1) {
            t[num].link = 1;
            t[num].cnt = 1;
            return true;
        }
        while (true) {
            cur = t[cur].link;
            curlen = t[cur].len;
            if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos]) {
                t[num].link = t[cur].next[let];
                break;
            }
        }
        t[num].cnt = 1 + t[t[num].link].cnt;
        return true;
    }
    int next(int p, int x) {
        return t[p].next[x];
    }
    int link(int p) {
        return t[p].link;
    }
    int len(int p) {
        return t[p].len;
    }
    int size() {
        return t.size();
    }
};

struct SA {
    int n;
    std::vector<int> sa, rk, lc;

    SA(std::string s) {
        n = s.size();
        sa.resize(n);
        lc.resize(n - 1);
        rk.resize(n);

        std::iota(sa.begin(), sa.end(), 0);
        std::sort(sa.begin(), sa.end(),
            [&](int a, int b) {
                return s[a] < s[b];
            });

        rk[sa[0]] = 0;
        for (int i = 1; i < n; ++ i) {
            rk[sa[i]] = rk[sa[i - 1]] + (s[sa[i]] != s[sa[i - 1]]);
        }

        int k = 1;
        std::vector<int> tmp, cnt(n);
        tmp.reserve(n);
        while (rk[sa[n - 1]] < n - 1) {
            tmp.clear();
            for (int i = 0; i < k; ++ i) {
                tmp.push_back(n - k + i);
            }
            for (auto i : sa) {
                if (i >= k) {
                    tmp.push_back(i - k);
                }
            }
            std::fill(cnt.begin(), cnt.end(), 0);
            for (int i = 0; i < n; ++ i) {
                cnt[rk[i]] ++;
            }
            for (int i = 1; i < n; ++ i) {
                cnt[i] += cnt[i - 1];
            }
            for (int i = n - 1; i >= 0; -- i) {
                sa[-- cnt[rk[tmp[i]]]] = tmp[i];
            }
            std::swap(rk, tmp);
            rk[sa[0]] = 0;
            for (int i = 1; i < n; ++ i) {
                rk[sa[i]] = rk[sa[i - 1]] + (tmp[sa[i - 1]] < tmp[sa[i]] || sa[i - 1] + k == n || tmp[sa[i - 1] + k] < tmp[sa[i] + k]);
            }
            k *= 2;
        }
        
        for (int i = 0, j = 0; i < n; ++ i) {
            if (rk[i] == 0) {
                j = 0;
            } else {
                for (j -= (j > 0); i + j < n && sa[rk[i] - 1] + j < n && s[i + j] == s[sa[rk[i] - 1] + j]; ) {
                    j ++;
                }
                lc[rk[i] - 1] = j;
            }
        }
    }
};

void solve() {
	int n, q;
	std::cin >> n >> q;

	std::string s;
	std::cin >> s;

	s.push_back('*');
	s.push_back('#');
	for (int i = n - 1; i >= 0; -- i) {
		s.push_back(s[i]);
	}
    // rev i -> n + 1 + (n - i);

	PAM pam;
    std::vector<int> x;
    for (auto c : s) {
        pam.add(c);
        x.push_back(pam.suff);
    }
    
    std::vector<std::vector<int>> adj(pam.size());
    for (int i = 2; i < pam.size(); i++) {
        adj[pam.link(i)].push_back(i);
    }
    
    std::vector<int> diff(pam.size()), slink(pam.size());
    
    auto dfs = [&](auto self, int x) -> void {
        for (auto y : adj[x]) {
            diff[y] = pam.len(y) - pam.len(x);
            if (diff[y] == diff[x]) {
                slink[y] = slink[x];
            } else {
                slink[y] = x;
            }
            self(self, y);
        }
    };
    dfs(dfs, 1);

    SA sa(s);
	int m = sa.lc.size();
	int lgm = (std::__lg(m) == -1 ? 0 : std::__lg(m));

	std::vector st(lgm + 1, std::vector<int> (m));
	st[0] = sa.lc;
	for (int j = 0; j < lgm; ++ j) {
	    for (int i = 0; i + (2 << j) <= m; ++ i) {
	        st[j + 1][i] = std::min(st[j][i], st[j][i + (1 << j)]);
	    }
	}

	auto ask = [&](int l, int r) -> int {
	    if (l > r) {
	        std::swap(l, r);
	    }
	    r--;
	    if (l > r) {
	        return 0;
	    }
	    int t = std::__lg(r - l + 1);
	    return std::min(st[t][l], st[t][r - (1 << t) + 1]);
	};

	std::vector<int> pre(n), suf(n);
	for (int i = 0; i < n; ++ i) {
		pre[i] = pam.len(x[i]);
		if (i) {
			pre[i] = std::max(pre[i], pre[i - 1]);
		}
	}
	for (int i = n - 1; i >= 0; -- i) {
		suf[i] = pam.len(x[n + 1 + n - i]);
		if (i < n - 1) {
			suf[i] = std::max(suf[i], suf[i + 1]);
		}
	}

	while (q --) {
		int l, r;
		std::cin >> l >> r;
		l -= 2;

        if (l < 0) {
            if (r >= n) {
                std::cout << "0\n";
            } else {
                std::cout << suf[r] << '\n';
            }
            continue;
        } else {
            if (r >= n) {
                std::cout << pre[l] << '\n';
                continue;
            }
        }

		int ans = std::max({pre[l], suf[r], 2 * ask(sa.rk[n + 1 + n - l], sa.rk[r])});
		int cur = x[l];
		while (cur > 1) {
			int curd = diff[cur];
			int maxlen = pam.len(cur);
			int toplen = pam.len(slink[cur]);
			int num = (maxlen - toplen) / curd;
			int pos1 = l - maxlen, pos2 = l - toplen;
			int len1 = (pos1 < 0 ? 0 : ask(sa.rk[n + 1 + n - pos1], sa.rk[n + 1 + n - pos2]));
			int len2 = ask(sa.rk[n + 1 + n - pos2], sa.rk[r]);
			int k = std::min(num, std::max(0, (len2 - len1) / curd));
			for (int i = std::max(0, k - 1); i <= std::min(num, k + 1); ++ i) {
				int len = maxlen - i * curd;
				int pos = l - len;
				ans = std::max(ans, len + 2 * (pos < 0 ? 0 : ask(sa.rk[n + 1 + n - pos], sa.rk[r])));
			}
            cur = slink[cur];
		}
		cur = x[n + 1 + n - r];
		while (cur > 1) {
			int curd = diff[cur];
			int maxlen = pam.len(cur);
			int toplen = pam.len(slink[cur]);
			int num = (maxlen - toplen) / curd;
			int pos1 = r + maxlen, pos2 = r + toplen;
			int len1 = (pos1 > 2 * n + 1 ? 0 : ask(sa.rk[pos1], sa.rk[pos2]));
			int len2 = ask(sa.rk[pos2], sa.rk[n + 1 + n - l]);
			int k = std::min(num, std::max(0, (len2 - len1) / curd));
			for (int i = std::max(0, k - 1); i <= std::min(num, k + 1); ++ i) {
				int len = maxlen - i * curd;
				int pos = r + len;
				ans = std::max(ans, len + 2 * (pos > 2 * n + 1 ? 0 : ask(sa.rk[pos], sa.rk[n + 1 + n - l])));
			}
            cur = slink[cur];
		}
		std::cout << ans << '\n';
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int T;
	std::cin >> T;

	while (T --) {
		solve();
	}

	return 0;
}