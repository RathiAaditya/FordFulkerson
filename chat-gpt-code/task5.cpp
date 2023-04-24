#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const double INF = 1e9; // infinity

// returns the error (sum of squared residuals) of fitting a line to points from index start to end
double error(vector<int> &x, vector<int> &y, int start, int end, double slope, double intercept)
{
    double sum = 0;
    for (int i = start; i <= end; i++)
    {
        double residual = y[i] - (slope * x[i] + intercept);
        sum += residual * residual;
    }
    return sum;
}

// returns the minimum error of fitting k lines to points from index 0 to i
double dp(vector<int> &x, vector<int> &y, int k)
{
    int n = x.size();
    double dpTable[n][k + 1];
    // initialize base cases
    for (int i = 0; i < n; i++)
    {
        dpTable[i][0] = INF;
    }
    for (int j = 1; j <= k; j++)
    {
        dpTable[0][j] = 0;
    }
    // fill in the table using dynamic programming
    for (int j = 1; j <= k; j++)
    {
        for (int i = j; i < n; i++)
        {
            dpTable[i][j] = INF;
            double slope = 0, intercept = 0;
            for (int l = i; l >= j; l--)
            {
                slope += x[l];
                intercept += y[l];
                double errorL = error(x, y, l, i, slope / (i - l + 1), intercept / (i - l + 1));
                dpTable[i][j] = min(dpTable[i][j], dpTable[l - 1][j - 1] + errorL);
            }
        }
    }
    return dpTable[n - 1][k];
}

int main()
{
    int n, k;
    cin >> n >> k;
    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++)
    {
        cin >> x[i] >> y[i];
    }
    double minError = dp(x, y, k);
    cout << "Minimum Error: " << minError << endl;
    return 0;
}
