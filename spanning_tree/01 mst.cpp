#include <iostream>
#include <vector>
#include <algorithm>

#define FOR(x, to) for (x = 0; x < to; x++)
#define FORI(i, to) for (i; i < to; i++)
#define FORN(i, to) for (i; i >= to; i--)
#define FORR(x, arr) for (auto &x : arr)
#define ALL(a) (a.begin(), a.end())

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vii;

int find(int i, vi &parent)
{
    if (parent[i] == i)
        return i;

    return find(parent[i], parent);
}

void unite(int x, int y, vi &parent, vi &rank)
{
    int s1 = find(x, parent);
    int s2 = find(y, parent);

    if (s1 != s2)
    {
        if (rank[s1] < rank[s2])
            parent[s1] = s2;
        else if (rank[s1] > rank[s2])
            parent[s2] = s1;
        else
            parent[s2] = s1, rank[s1]++;
    }
}

int solve(int V, int E, vii &edges)
{
    sort(edges.begin(), edges.end(), [](const vi &a, const vi &b)
         { return a[2] < b[2]; });

    int totalWeight = 0, count = 0;

    vi parent(V);
    vi rank(V, 1);
    int i;
    FOR(i, V)
    {
        // every node is parent of their own
        parent[i] = i;
    }

    for (const auto &edge : edges)
    {
        int u = edge[0];
        int v = edge[1];
        int wt = edge[2];

        if (find(u, parent) != find(v, parent))
        {
            unite(u, v, parent, rank);
            totalWeight += wt;
            if (++count == V - 1)
                break;
        }
    }

    return totalWeight;
}

int main()
{
    int V, E;

    cin >> V >> E;

    vii edges(E, vi(3));

    int i;
    FOR(i, E)
    {
        int j;
        FOR(j, 3)
        {
            cin >> edges[i][j];
        }
    }

    cout << solve(V, E, edges);
}