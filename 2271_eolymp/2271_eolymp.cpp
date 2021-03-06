#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <math.h>
using namespace std;

vector<vector<int>>v;
set<int> answer;
vector<int> used;
vector<int> tin;
vector<int> fup;
int time;
void dfs(int vertex, int p) {
	used[vertex] = 1;
	tin[vertex] = fup[vertex] = time++;
	int children = 0;
	for (size_t i = 0; i < v[vertex].size(); ++i) {
		int to = v[vertex][i];
		if (to == p)  continue; // обратное ребро
		if (used[to] == 1)
			fup[vertex] = min(fup[vertex], tin[to]);
		else if (!used[to]) {
			dfs(to, vertex);
			fup[vertex] = min(fup[vertex], fup[to]);
			if (fup[to] >= tin[vertex] && p != -1)
				answer.emplace(vertex);
			++children;
		}
	}
	if (p == -1 && children > 1)
		answer.emplace(vertex);
}

int main()
{
	int vertices, edges;
	cin >> vertices >> edges;
	v.resize(vertices + 1);
	tin.resize(vertices + 1);
	fup.resize(vertices + 1);
	used.resize(vertices + 1, 0);
	for (int i = 0; i < edges; ++i) {
		int a, b; cin >> a >> b;
		v[a].push_back(b);
		v[b].push_back(a);
	}
	time = 1;
	for (int i = 1; i <= vertices; ++i) {
		if(used[i] == 0) dfs(i, -1);
	}
	cout << answer.size() << endl;
	for (int e : answer) cout << e << endl;
    return 0;
}
/*#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int a, b, i, n, m, vaxt;
vector<vector<int>> graph;
vector<int> used, d, up;
set<int> ArtPoints;

//В функции dfs совершается поиск точек сочленения при помощи поиск в
//глубину. Найденные точки сочленения сохраняются в ArtPoints.
void dfs(int v, int p = -1)
{
	int children = 0;
	used[v] = 1;
	d[v] = up[v] = vaxt++;
	for (int i = 0; i < graph[v].size(); i++)
	{
		int to = graph[v][i];
		if (to == p) continue;
		if (used[to]) up[v] = min(up[v], d[to]);
		else
		{
			dfs(to, v);
			up[v] = min(up[v], up[to]);
			if (up[to] >= d[v] && p != -1) ArtPoints.insert(v);
			children++;
		}
	}
	if (p == -1 && children > 1) ArtPoints.insert(v);
}

int main()
{
	//Считываем неориентированный граф в список смежности graph.
	scanf("%d %d", &n, &m);
	graph.resize(n + 1);
	used.resize(n + 1);
	d.resize(n + 1);
	up.resize(n + 1);
	for (i = 0; i < m; i++)
	{
		scanf("%d %d", &a, &b);
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	vaxt = 1;
	for (i = 1; i <= n; i++) if (!used[i]) dfs(i);
	//Выводим количество точек сочленения, а также их самих в возрастающем порядке.
	printf("%d\n", ArtPoints.size());
	for (set<int>::iterator iter = ArtPoints.begin(); iter != ArtPoints.end(); ++iter) printf("%d\n", *iter);
	return 0;
}*/
