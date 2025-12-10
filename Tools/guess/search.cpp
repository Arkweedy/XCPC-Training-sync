#include <bits/stdc++.h>
using namespace std;

static inline string trim(const string& s) {
    size_t l = 0, r = s.size();
    while (l < r && isspace((unsigned char)s[l])) ++l;
    while (r > l && isspace((unsigned char)s[r-1])) --r;
    return s.substr(l, r - l);
}

struct IndexByLen {
    int L = 0;
    vector<string> items;                       // id -> string（插入顺序）
    vector<char>   alive;                       // id -> 是否有效
    vector<array<vector<int>, 256>> pos_char_ids; // [pos][byte] -> ids（包含已删 id，查询再过滤）
    unordered_set<string> present;              // 去重（仅存活字符串）
    unordered_map<string,int> id_of;            // 快速定位要删的 id（最近一次 add 的 id）

    explicit IndexByLen(int L=0): L(L), pos_char_ids(L) {}

    bool add_unique(const string& s) {
        if ((int)s.size() != L) return false;
        if (!present.insert(s).second) return false; // 已存在（且存活）
        int id = (int)items.size();
        items.push_back(s);
        alive.push_back(1);
        id_of[s] = id;
        for (int i = 0; i < L; ++i) {
            unsigned char uc = static_cast<unsigned char>(s[i]);
            pos_char_ids[i][uc].push_back(id);
        }
        return true;
    }

    bool remove_word(const string& s) {
        auto it = id_of.find(s);
        if (it == id_of.end()) return false;          // 没有这个词（或已被删除且未再添加）
        int id = it->second;
        if (id < 0 || id >= (int)alive.size() || !alive[id]) return false; // 已是无效
        alive[id] = 0;
        present.erase(s);
        id_of.erase(it);                              // 删除映射，便于将来重新 ADD 成为新 id
        return true;
    }

    static vector<int> intersectLists(vector<const vector<int>*>& lists, int totalN) {
        if (lists.empty()) {
            vector<int> all(totalN);
            iota(all.begin(), all.end(), 0);
            return all;
        }
        sort(lists.begin(), lists.end(),
             [](auto a, auto b){ return a->size() < b->size(); });
        vector<int> cur = *lists[0];
        vector<int> nxt;
        for (size_t k = 1; k < lists.size(); ++k) {
            const auto& v = *lists[k];
            nxt.clear();
            size_t i = 0, j = 0;
            while (i < cur.size() && j < v.size()) {
                if (cur[i] == v[j]) { nxt.push_back(cur[i]); ++i; ++j; }
                else if (cur[i] < v[j]) ++i;
                else ++j;
            }
            cur.swap(nxt);
            if (cur.empty()) break;
        }
        return cur;
    }

    vector<int> queryIDs(const string& pattern) {
        vector<const vector<int>*> lists;
        lists.reserve(L);
        for (int i = 0; i < L; ++i) {
            char ch = pattern[i];
            if (ch == '*') continue;
            unsigned char uc = static_cast<unsigned char>(ch);
            const vector<int>& bucket = pos_char_ids[i][uc];
            if (bucket.empty()) return {};
            lists.push_back(&bucket);
        }
        vector<int> ids = intersectLists(lists, (int)items.size());
        // 过滤掉已删除的
        ids.erase(remove_if(ids.begin(), ids.end(),
                            [&](int id){ return id < 0 || id >= (int)alive.size() || !alive[id]; }),
                  ids.end());
        return ids;
    }

    // 将存活的词输出到流
    void dump_alive(ostream& os) const {
        for (int id = 0; id < (int)items.size(); ++id) {
            if (id < (int)alive.size() && alive[id]) {
                os << items[id] << endl;
            }
        }
    }
};

struct Engine {
    unordered_map<int, IndexByLen> byLen; // length -> index

    IndexByLen& ensureLen(int L) {
        auto it = byLen.find(L);
        if (it == byLen.end()) it = byLen.emplace(L, IndexByLen(L)).first;
        return it->second;
    }

    bool add_unique(const string& s) {
        int L = (int)s.size();
        if (L == 0) return false;
        return ensureLen(L).add_unique(s);
    }

    bool remove_word(const string& s) {
        int L = (int)s.size();
        auto it = byLen.find(L);
        if (it == byLen.end()) return false;
        return it->second.remove_word(s);
    }

    pair<long long,long long> load_dict(const string& fname = "dict.txt") {
        ifstream fin(fname);
        if (!fin) {
            return {0, 0};
        }
        long long added = 0, skipped = 0;
        string line;
        while (getline(fin, line)) {
            string s = trim(line);
            if (s.empty()) { ++skipped; continue; }
            if (!s.empty() && s[0] == '#') { ++skipped; continue; } // 注释行
            if (add_unique(s)) ++added;
            else ++skipped;
        }
        return {added, skipped};
    }

    // 将当前“存活”的全部词重写保存到文件（截断重写）
    bool save_all(const string& fname = "dict.txt") const {
        ofstream fout(fname, ios::trunc);
        if (!fout) return false;
        // 为了稳定的遍历顺序，按长度递增写回
        vector<int> lens;
        lens.reserve(byLen.size());
        for (auto& kv : byLen) lens.push_back(kv.first);
        sort(lens.begin(), lens.end());
        for (int L : lens) {
            const auto& idx = byLen.at(L);
            idx.dump_alive(fout);
            if (!fout.good()) return false;
        }
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const string dictFile = "dict.txt";
    Engine eng;

    // 启动时加载字典
    {
        auto [added, skipped] = eng.load_dict(dictFile);
        cerr << "[INFO] Loaded dict: +" << added << ", skipped " << skipped << endl;
    }

    string cmd;
    auto printMatches = [&](IndexByLen& idx, const vector<int>& ids) {
        cout << ids.size() << endl;
        for (int id : ids) cout << idx.items[id] << endl;
    };

    // 交互命令：
    // ADD <string>              —— 新增并写回 dict.txt（已存在则忽略并提示）
    // DEL <string>              —— 删除并重写 dict.txt（不存在则提示）
    // QUERY <pattern-with-*>    —— 通配查询（长度必须一致；* 表示单字符任意）
    // EXIT                      —— 退出
    while (cin >> cmd) {
        if (cmd == "ADD") {
            string s;
            if (!(cin >> s)) break;

            if (eng.add_unique(s)) {
                ofstream fout(dictFile, ios::app);
                if (fout) {
                    fout << s << endl;
                    if (fout.good()) {
                        cerr << "[OK] Added and saved: " << s << endl;
                    } else {
                        cerr << "[WARN] Added in memory, but failed to write to " << dictFile << endl;
                    }
                } else {
                    cerr << "[WARN] Added in memory, cannot open " << dictFile << " for append" << endl;
                }
            } else {
                cerr << "[INFO] Exists (ignored): " << s << endl;
            }

        } else if (cmd == "DEL") {
            string s;
            if (!(cin >> s)) break;

            if (eng.remove_word(s)) {
                if (eng.save_all(dictFile)) {
                    cerr << "[OK] Deleted and saved: " << s << endl;
                } else {
                    cerr << "[WARN] Deleted in memory, but failed to rewrite " << dictFile << endl;
                }
            } else {
                cerr << "[INFO] Not found: " << s << endl;
            }

        } else if (cmd == "QUERY") {
            string p;
            if (!(cin >> p)) break;
            int L = (int)p.size();
            auto it = eng.byLen.find(L);
            if (it == eng.byLen.end()) {
                cout << 0 << endl;
                continue;
            }
            auto ids = it->second.queryIDs(p);
            printMatches(it->second, ids);

        } else if (cmd == "EXIT") {
            break;

        } else {
            string rest;
            getline(cin, rest); // 忽略未知命令后面的整行
        }
    }
    return 0;
}
