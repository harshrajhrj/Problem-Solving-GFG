// Using memoization [top-down]
#include <iostream>
#include <vector>

#define FOR(x, to) for (x = 0; x < to; x++)
#define FORI(i, to) for (i; i < to; i++)
#define FORR(x, arr) for (auto &x : arr)
#define ALL(a) (a.begin(), a.end())

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vii;

int LIS(int curr, int prev, vi &arr, vii& dp_lis)
{
    if (curr < 0)
        return 0;

    if(dp_lis[prev][curr] != -1) return dp_lis[prev][curr];

    int currLen = 0;
    if (arr[curr] < arr[prev])
        currLen = 1 + LIS(curr - 1, curr, arr, dp_lis);

    return dp_lis[prev][curr] = max(currLen, LIS(curr - 1, prev, arr, dp_lis));
}

int LDS(int curr, int prev, vi &arr, vii& dp_lds)
{
    if (curr >= arr.size())
        return 0;

    if(dp_lds[prev][curr] != -1) return dp_lds[prev][curr];

    int currLen = 0;
    if (arr[curr] < arr[prev])
        currLen = 1 + LDS(curr + 1, curr, arr, dp_lds);

    return dp_lds[prev][curr] = max(currLen, LDS(curr + 1, prev, arr, dp_lds));
}

int solve(int N, vi &arr)
{
    // [1,2,5,3,2]
    // [1,11,2,10,4,5,2,1]
    int maxLength = 0;
    int i = 1;
    vii dp_lis(N, vi(N, -1));
    vii dp_lds(N, vi(N, -1));

    FORI(i, N - 1)
    {
        int leftLen = LIS(i - 1, i, arr, dp_lis);
        int rightLen = LDS(i + 1, i, arr, dp_lds);

        maxLength = max(maxLength, leftLen + rightLen + 1);
    }

    // if no valid subsequence then return 0
    return maxLength < 3 ? 0 : maxLength;
}
int main()
{
    int n;
    cin >> n;

    vi arr(n);
    int i;
    FOR(i, n)
    {
        cin >> arr[i];
    }

    cout << solve(n, arr);

    return 0;
}