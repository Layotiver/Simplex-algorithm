#include <bits/stdc++.h>
using namespace std;

int n, m;
double cc[1010], ba[1010][1010]; //价值向量和系数矩阵，b[i][0]是资源向量
int xx[1010];                    //基变量的下标

void input()
{
    int i, j;
    cin >> n >> m;
    for (i = 1; i <= n; i++)
    {
        cin >> cc[i];
    }
    for (i = 1; i <= m; i++)
    {
        for (j = 0; j <= n; j++)
        {
            cin >> ba[i][j];
        }
    }
    for (i = 1; i <= m; i++)
    {
        cin >> xx[i];
    }
}

void print()
{
    int i, j;
    printf("               c_j          ");
    for (i = 1; i <= n; i++)
    {
        printf(" %12.2lf", cc[i]);
    }
    printf("\nc_b          x_b         b      ");
    for (i = 1; i <= n; i++)
    {
        printf("      x_%d    ", i);
    }
    printf("\n");
    for (i = 1; i <= m; i++)
    {
        printf("%12.2lf x_%d %12.2lf", cc[xx[i]], xx[i], ba[i][0]);
        for (j = 1; j <= n; j++)
        {
            printf(" %12.2lf", ba[i][j]);
        }
        printf("\n");
    }
}

void change(int in)
{
    double th[1010], min = 99999999, div, mi; // th:Theta
    int i, j, out;

    for (i = 1; i <= m; i++)
    {
        th[i] = ba[i][0] / ba[i][in];
        if (th[i] < 0)
            continue;
        out = min < th[i] ? out : i;
        min = min < th[i] ? min : th[i];
    }
    div = ba[out][in];
    for (i = 0; i <= n; i++)
    {
        ba[out][i] /= div;
    }
    for (i = 1; i <= m; i++)
    {
        if (i == out)
            continue;
        mi = ba[i][in];
        for (j = 0; j <= n; j++)
        {
            ba[i][j] -= ba[out][j] * mi;
        }
    }
    xx[out] = in;
}

bool solve()
{
    double o[1010]; // o:检验数
    int i, j;
    for (i = 1; i <= n; i++)
    {
        o[i] = cc[i];
        for (j = 1; j <= m; j++)
        {
            o[i] -= cc[xx[j]] * ba[j][i];
        }
    }
    printf("                                    ");
    for (i = 1; i <= n; i++)
    {
        printf("%12.2lf", o[i]);
    }
    printf("\n\n");
    for (i = 1; i <= n; i++)
    {
        if (o[i] > 0)
        {
            change(i);
            return 1;
        }
    }
    // print();
    return 0;
}

int main()
{
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    input();
    do
    {
        print();
    } while (solve());
}