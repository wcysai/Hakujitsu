#pragma GCC optimize(3) 
#include <bits/stdc++.h>
#define path dskoasd
using namespace std;
 
const int maxn = 55;
char s[maxn][maxn];
 
int n, m;
 
struct node{
    int l, r, u, d;
    vector<pair<int, int> > lst;
    node(){
        lst.clear();
        l = m, r = 1;
        u = n, d = 1;
    }
};
 
void upd(node &a, int x, int y){
    a.l = min(a.l, y);
    a.r = max(a.r, y);
    a.u = min(a.u, x);
    a.d = max(a.d, x);
}
 
bool vis[maxn][maxn];
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
char op[4] = {'U', 'D', 'L', 'R'};
 
void find_block(int x, int y, node &cur){
    vis[x][y] = 1; 
    upd(cur, x, y);
    cur.lst.emplace_back(x, y);
    for (int i = 0; i < 4; i += 1) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(nx >= 1 && nx <= n && ny >= 1 && ny <= m && !vis[nx][ny] && s[nx][ny] == s[x][y]) {
            find_block(nx, ny, cur);
        }
    }
}
 
bool check_out(int x, int y){
    return x >= 1 && x <= n && y >= 1 && y <= m;
}
 
bool check(vector<pair<int, int> > &lst, int gx, int gy){
    for (auto [x, y] : lst) {
        x += gx;
        y += gy;
        if(check_out(x, y) && s[x][y] == '.') continue;
        return false;
    }
    return true;
}
 
void del(vector<pair<int, int> > &lst, int gx, int gy){
    for (auto [x, y] : lst) {
        s[x + gx][y + gy] = '.';
    }
}
 
void add(vector<pair<int, int> > &lst, int gx, int gy, char c){
    for (auto [x, y] : lst) {
        s[x + gx][y + gy] = c;
    }
}
 
tuple<string, int, int> bfs(node &cur){
    
    memset(vis, 0, sizeof(vis));
    queue<tuple<int, int, string> > q;
    q.emplace(cur.lst[0].first, cur.lst[0].second, "");
    vis[cur.lst[0].first][cur.lst[0].second] = 1;
    char tmp = s[cur.lst[0].first][cur.lst[0].second];
    del(cur.lst, 0, 0);
    while(!q.empty()) {
        auto [x, y, path] = q.front();
        q.pop();
        int gx = x - cur.lst[0].first;
        int gy = y - cur.lst[0].second;
        if(1 - cur.u == gx){
            add(cur.lst, 0, 0, tmp);
            reverse(path.begin(), path.end());
 
            int mn = n;
            for (auto[x, y] : cur.lst) {
                mn = min(mn, x);
            }
            int last = m;
            for (auto [x, y] : cur.lst) {
                if(x == mn) last = min(last, y);
            }
            return make_tuple(path, gx, last + gy);
        }
        for (int i = 0; i < 4; i += 1) {
            if(!check_out(x + dx[i], y + dy[i]) || vis[x + dx[i]][y + dy[i]]) continue;
            bool ok = check(cur.lst, gx + dx[i], gy + dy[i]);
            if(!ok) {
                continue;
            }
            vis[x + dx[i]][y + dy[i]] = 1;
            q.emplace(x + dx[i], y + dy[i], path + op[i]);
        }
    }
    add(cur.lst, 0, 0, tmp);
    return make_tuple("-1", -1, -1);
}
 
void print(){
    for (int i = 1; i <= n; i += 1){
        puts(s[i] + 1);
    }
}
 
int main(){
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i += 1) {
        scanf("%s", s[i] + 1);
    }
    vector<node> com;
    for (int i = 1; i <= n; i += 1) {
        for (int j = 1; j <= m; j += 1){
            if(s[i][j] == '.' || vis[i][j]) continue;
            node cur;
            find_block(i, j, cur);
            com.emplace_back(cur);
        }
    }
 
    int _o = com.size();
    vector<pair<int, string> > res;
    sort(com.begin(), com.end(), [&](node a, node b){
        return a.u < b.u;
    });
    for (int o = 0; o < _o; o += 1) {
        int can = -1;
        for (int i = 0; i < com.size(); i += 1) {
            auto[path, gx, gy] = bfs(com[i]);
            if(path != "-1") {
                path += "S";
                res.emplace_back(gy, path);
                can = i;
                del(com[i].lst, 0, 0);
                swap(com[i], com.back());
                com.pop_back();
                //print();
                //puts("");
                break;
            }
        }
        if(can == -1) {
            cout << "-1" << "\n";
            return 0;
        }
    }
    reverse(res.begin(), res.end());
    cout << res.size() << "\n";
    for (auto [x, y] : res) {
        cout << x << " " << y << "\n";
    }
    return 0;
}