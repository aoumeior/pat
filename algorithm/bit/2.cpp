
#include <bits/stdc++.h>

using namespace std;
int n, m;
int a[50005] = {0};
int sum1[50005]; //(D[1] + D[2] + ... + D[n])
int sum2[50005]; //(1*D[1] + 2*D[2] + ... + n*D[n])

int lowbit(int x)
{
    return x & (-x);
}

void updata(int i, int k)
{
    int x = i; //因为x不变，所以得先保存i值
    while (i <= n)
    {
        sum1[i] += k;
        sum2[i] += k * (x - 1);
        i += lowbit(i);
    }
}

int getsum(int i)
{ //求前缀和
    int res = 0, x = i;
    while (i > 0)
    {
        res += x * sum1[i] - sum2[i];
        i -= lowbit(i);
    }
    return res;
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        updata(i, a[i] - a[i - 1]); //输入初值的时候，也相当于更新了值
    }
    int x, y, k;
    cin >> x >> k;
    //[x,y]区间内加上k
    updata(x, k);      //A[x] - A[x-1]增加k
    updata(y + 1, -k); //A[y+1] - A[y]减少k

    //求[x,y]区间和
    int sum = getsum(y) - getsum(x - 1);

    return 0;
}