#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
using namespace std;
double a[100][1000];
double c[100][1000];
double d[100][1000];
double e[100][1000];
double sum[100]; //规范化

double all_max_d[100][1000];
double oneside_max_d[100][1000];

int n, m;

void print_matrix(double b[100][1000])
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << fixed << setprecision(3) << b[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    cin >> m >> n; // m行 n列
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> a[i][j];
        }
    }
    //print_matrix(a);
    //cout<<endl;
    for (int j = 0; j < n; j++)
        cin >> a[m][j];
    // 矩阵规范化
    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < m; i++)
        {
            sum[j] += a[i][j] * a[i][j];
        }
        sum[j] = sqrt(sum[j]);
    }
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            a[i][j] /= sum[j];
            a[i][j] *= a[m][j];
        }
    }
    //end
    //get C
    for (int j = 0; j < n; j++)
    {
        for (int l = 0; l < m; l++)
        {
            for (int k = l + 1; k < m; k++)
            {
                if (a[l][j] >= a[k][j]) // l 优秀于 k
                {
                    c[l][k] += a[m][j];
                    oneside_max_d[k][l] = max(oneside_max_d[k][l], (double)std::abs(a[l][j] - a[k][j]));
                }
                if (a[l][j] <= a[k][j])
                {
                    c[k][l] += a[m][j];
                    oneside_max_d[l][k] = max(oneside_max_d[l][k], (double)std::abs(a[l][j] - a[k][j]));
                }
                all_max_d[l][k] = max(all_max_d[l][k], (double)std::abs(a[l][j] - a[k][j]));
                all_max_d[k][l] = all_max_d[l][k];
            }
        }
    }
    //end
    double alpha, beta;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (i == j)
                continue;
            alpha += c[i][j];
            d[i][j] = oneside_max_d[i][j] / all_max_d[i][j];
            beta += d[i][j];
        }
    }
    alpha /= (m - 1) * m;
    beta /= (m - 1) * m;
    cout << alpha << " " << beta << endl;

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (c[i][j] >= alpha)
                c[i][j] = 1;
            else
                c[i][j] = 0;
            if (d[i][j] > beta)
                d[i][j] = 0;
            else
                d[i][j] = 1;
        }
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            e[i][j] = c[i][j] * d[i][j];
        }
    }
    print_matrix(e);
    return 1;
}
