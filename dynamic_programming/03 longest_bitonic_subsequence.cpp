// Using tabulation [bottom-up]
#include <iostream>
#include <vector>

#define FOR(x, to) for (x = 0; x < to; x++)
#define FORI(i, to) for (i; i < to; i++)
#define FORN(i, to) for (i; i >= to; i--)
#define FORR(x, arr) for (auto &x : arr)
#define ALL(a) (a.begin(), a.end())

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vii;

int solve(int N, vi &arr)
{

    vi dp_lis(N, 1);
    vi dp_lds(N, 1);

    int i = 1;
    FORI(i, N)
    {
        int j = 0;
        FORI(j, i)
        {
            if (arr[j] < arr[i])
                // Update the value of dp_lis[i] by using the previous value at dp_lis[j] + 1
                dp_lis[i] = max(dp_lis[i], 1 + dp_lis[j]);
        }
    }

    i = N - 2;
    FORN(i, 0)
    {
        int j = N - 1;
        FORN(j, i + 1)
        {
            if (arr[i] > arr[j])
                dp_lds[i] = max(dp_lds[i], dp_lds[j] + 1);
        }
    }

    int maxLength = 0;

    for (int i = 0; i < N; i++)
    {
        if (dp_lis[i] > 1 && dp_lds[i] > 1)
            maxLength = max(maxLength, dp_lis[i] + dp_lds[i] - 1);
    }
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