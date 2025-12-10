#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

template<class T>
struct MaxAssignment {
public:
	T solve(int nx, int ny, std::vector<std::vector<T>> a) {
		assert(0 <= nx && nx <= ny);
		assert(int(a.size()) == nx);
		for (int i = 0; i < nx; ++i) {
			assert(int(a[i].size()) == ny);
			for (auto x : a[i])
				assert(x >= 0);
		}

		auto update = [&](int x) {
			for (int y = 0; y < ny; ++y) {
				if (lx[x] + ly[y] - a[x][y] < slack[y]) {
					slack[y] = lx[x] + ly[y] - a[x][y];
					slackx[y] = x;
				}
			}
		};

		costs.resize(nx + 1);
		costs[0] = 0;
		lx.assign(nx, std::numeric_limits<T>::max());
		ly.assign(ny, 0);
		xy.assign(nx, -1);
		yx.assign(ny, -1);
		slackx.resize(ny);
		for (int cur = 0; cur < nx; ++cur) {
			std::queue<int> que;
			visx.assign(nx, false);
			visy.assign(ny, false);
			slack.assign(ny, std::numeric_limits<T>::max());
			p.assign(nx, -1);

			for (int x = 0; x < nx; ++x) {
				if (xy[x] == -1) {
					que.push(x);
					visx[x] = true;
					update(x);
				}
			}

			int ex, ey;
			bool found = false;
			while (!found) {
				while (!que.empty() && !found) {
					auto x = que.front();
					que.pop();
					for (int y = 0; y < ny; ++y) {
						if (a[x][y] == lx[x] + ly[y] && !visy[y]) {
							if (yx[y] == -1) {
								ex = x;
								ey = y;
								found = true;
								break;
							}
							que.push(yx[y]);
							p[yx[y]] = x;
							visy[y] = visx[yx[y]] = true;
							update(yx[y]);
						}
					}
				}
				if (found)
					break;

				T delta = std::numeric_limits<T>::max();
				for (int y = 0; y < ny; ++y)
					if (!visy[y])
						delta = std::min(delta, slack[y]);
				for (int x = 0; x < nx; ++x)
					if (visx[x])
						lx[x] -= delta;
				for (int y = 0; y < ny; ++y) {
					if (visy[y]) {
						ly[y] += delta;
					} else {
						slack[y] -= delta;
					}
				}
				for (int y = 0; y < ny; ++y) {
					if (!visy[y] && slack[y] == 0) {
						if (yx[y] == -1) {
							ex = slackx[y];
							ey = y;
							found = true;
							break;
						}
						que.push(yx[y]);
						p[yx[y]] = slackx[y];
						visy[y] = visx[yx[y]] = true;
						update(yx[y]);
					}
				}
			}

			costs[cur + 1] = costs[cur];
			for (int x = ex, y = ey, ty; x != -1; x = p[x], y = ty) {
				costs[cur + 1] += a[x][y];
				if (xy[x] != -1)
					costs[cur + 1] -= a[x][xy[x]];
				ty = xy[x];
				xy[x] = y;
				yx[y] = x;
			}
		}
		return costs[nx];
	}
	std::vector<int> assignment() {
		return xy;
	}
	std::pair<std::vector<T>, std::vector<T>> labels() {
		return std::make_pair(lx, ly);
	}
	std::vector<T> weights() {
		return costs;
	}
private:
	std::vector<T> lx, ly, slack, costs;
	std::vector<int> xy, yx, p, slackx;
	std::vector<bool> visx, visy;
};

template <typename T>
struct hungarian {  // km
  int n;
  vector<int> matchx, matchy, pre;
  vector<bool> visx, visy;
  vector<T> lx, ly;
  vector<vector<T>> g;
  vector<T> slack;
  T inf, res;
  queue<int> q;
  int org_n, org_m;

  hungarian(int _n, int _m) {
    org_n = _n;
    org_m = _m;
    n = max(_n, _m);
    inf = numeric_limits<T>::max();
    res = 0;
    g = vector<vector<T>>(n, vector<T>(n));
    matchx = vector<int>(n, -1);
    matchy = vector<int>(n, -1);
    pre = vector<int>(n);
    visx = vector<bool>(n);
    visy = vector<bool>(n);
    lx = vector<T>(n, -inf);
    ly = vector<T>(n);
    slack = vector<T>(n);
  }

  void addEdge(int u, int v, int w) {
    g[u][v] = max(w, 0);  // 负值还不如不匹配 因此设为0不影响
  }

  bool check(int v) {
    visy[v] = true;
    if (matchy[v] != -1) {
      q.push(matchy[v]);
      visx[matchy[v]] = true;
      return false;
    }
    while (v != -1) {
      matchy[v] = pre[v];
      swap(v, matchx[pre[v]]);
    }
    return true;
  }

  void bfs(int i) {
    while (!q.empty()) {
      q.pop();
    }
    q.push(i);
    visx[i] = true;
    while (true) {
      while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 0; v < n; v++) {
          if (!visy[v]) {
            T delta = lx[u] + ly[v] - g[u][v];
            if (slack[v] >= delta) {
              pre[v] = u;
              if (delta) {
                slack[v] = delta;
              } else if (check(v)) {
                return;
              }
            }
          }
        }
      }
      // 没有增广路 修改顶标
      T a = inf;
      for (int j = 0; j < n; j++) {
        if (!visy[j]) {
          a = min(a, slack[j]);
        }
      }
      for (int j = 0; j < n; j++) {
        if (visx[j]) {  // S
          lx[j] -= a;
        }
        if (visy[j]) {  // T
          ly[j] += a;
        } else {  // T'
          slack[j] -= a;
        }
      }
      for (int j = 0; j < n; j++) {
        if (!visy[j] && slack[j] == 0 && check(j)) {
          return;
        }
      }
    }
  }

  T solve() {
    // 初始顶标
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        lx[i] = max(lx[i], g[i][j]);
      }
    }

    for (int i = 0; i < n; i++) {
      fill(slack.begin(), slack.end(), inf);
      fill(visx.begin(), visx.end(), false);
      fill(visy.begin(), visy.end(), false);
      bfs(i);
    }

    // custom
    for (int i = 0; i < n; i++) {
      if (g[i][matchx[i]] > 0) {
        res += g[i][matchx[i]];
      } else {
        matchx[i] = -1;
      }
    }
    return res;
    //cout << res << "\n";
    // for (int i = 0; i < org_n; i++) {
    //   cout << matchx[i] + 1 << " ";
    // }
    // cout << "\n";
  }
};



void solve()
{
    int n;
    cin>>n;
    vector<string>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    string s = "luolikong";
    vector<array<int,9>>to(n,array<int,9>{0});
    for(int i = 0;i < n;i++){
        for(int j = 0;j < 9;j++){
            int p = j;
            for(int k = 0;k < a[i].length();k++){
                if(p < 9 && s[p] == a[i][k]){
                    p++;
                }
            }
            to[i][j] = p;
        }
    }

    array<array<vector<pair<int,int>>,9>,9>g;//g[i][j] -> all edge (i->j) [length , idx(color)]
    
    for(int i = 0;i < n;i++){
        for(int j = 0;j < 9;j++){
            if(to[i][j] != 9){
                g[j][to[i][j]].push_back({a[i].length(),i});
            }
        }
    }

    vector<vector<vector<int>>>path(9);
    vector<vector<int>>allpath;
    path[0].push_back(vector<int>(1,0));
    allpath.push_back(vector<int>(1,0));
    for(int i = 1;i < 9;i++){ ////update 1 : i < m -> i < 9
        for(int j = 0;j < i;j++){
            for(auto vec : path[j]){
                vec.push_back(i);
                path[i].push_back(vec);
            }
        }
        for(const auto &vec : path[i]){
            allpath.push_back(vec);
        }
    }

    vector<int>f(n, -1);

    ll ans = 0;
    constexpr ll inf = 1e9;

    int xx = 0;
    for(const auto & vec : allpath){
        //calc self loop
        int m = vec.size() - 1;
        int sum = 0;
        vector<int>isloop(n);
        vector<vector<pair<int,int>>>ng(m);//vec0->vec1, vec1->vec2...
        for(auto s : vec){//s : point on path
            for(const auto& [len,clr] : g[s][s]){
                if(!isloop[clr]){
                    isloop[clr] = true;
                    sum += len;
                }
            }
        }

        //rebuild graph
        for(int i = 0;i < m;i++){
            for(const auto& [len,clr] : g[vec[i]][vec[i + 1]]){
                if(isloop[clr]){
                    ng[i].push_back(make_pair(0,clr));
                }
                else{
                    ng[i].push_back(make_pair(len,clr));
                }
            }
            sort(ng[i].begin(),ng[i].end(),greater<>());
        }

        //binary graph
        hungarian<ll>solver(m,m*m);
        int tot = 0;
        for(int j = 0;j < m;j++){
            const auto&v = ng[j];
            for(int i = 0;i < min(m,(int)v.size());i++){
                const auto& [len, clr] = v[i];
                if(f[clr] == -1){
                    f[clr] = tot++;
                }
                solver.addEdge(j,f[clr],len + inf);//update 2 : addEdge(i,..)->addEdge(j,...)
            }
        }
        for(int j = 0;j < m;j++){
            const auto&v = ng[j];
            for(int i = 0;i < min(m,(int)v.size());i++){
                const auto& [len, clr] = v[i];
                f[clr] = -1;
            }
        }
        ll res = sum + solver.solve() - m * inf;
        ans = max(ans,res);
    }
    
    
    cout<<ans<<endl;
    return;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}