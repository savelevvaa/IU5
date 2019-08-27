#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

typedef double(*F)(double);
typedef double(*I)(double, double);

struct int_st
{
	char *name;
	double a, c;
	int n;
	int_st() { n = 0; }
};

double f0(double x)
{
	return x;
}

double f1(double x)
{
	return sin(22 * x);
}

double f2(double x)
{
	return x * x * x * x;
}

double f3(double x)
{
	return atan(x);
}

double i0(double a, double b)
{
	return (b * b - a * a) / 2;
}

double i1(double a, double b)
{
	return (cos(a * 22) - cos(b * 22)) / 22;
}

double i2(double a, double b)
{
	return (b * b * b * b * b - a * a * a * a * a) / 5;
}

double i3(double a, double b)
{
	return b * atan(b) - a * atan(a) - (log(b * b + 1) - log(a * a + 1)) / 2;
}

void print_tab(int_st *arr, int len)
{
	const int m = 4;
	int wn[m] = { 12, 18, 18, 10 };
	const char *title[m] = { "Function", "Integral", "IntSum", "N " };
	int size[m];
	for (int i = 0; i < m; i++)
		size[i] = strlen(title[i]);
	cout << char(218) << setfill(char(196));
	for (int j = 0; j < m - 1; j++)
		cout << setw(wn[j]) << char(194);
	cout << setw(wn[m - 1]) << char(191) << endl;
	cout << char(179);
	for (int j = 0; j < m; j++)
		cout << setw((wn[j] - size[j]) / 2) << setfill(' ') << ' ' << title[j]
		<< setw((wn[j] - size[j]) / 2) << char(179);
	cout << endl;
	for (int i = 0; i < len; i++)
	{
		cout << char(195) << fixed;
		for (int j = 0; j < m - 1; j++)
			cout << setfill(char(196)) << setw(wn[j]) << char(197);
		cout << setw(wn[m - 1]) << char(180) << setfill(' ') << endl;
		cout << char(179) << setw((wn[0] - strlen(arr[i].name)) / 2)
			<< ' ' << arr[i].name << setw((wn[0] - strlen(arr[i].name)) / 2) << char(179);
		cout << setw(wn[1] - 1) << setprecision(10) << arr[i].a << char(179)
			<< setw(wn[2] - 1) << arr[i].c << setprecision(6) << char(179)
			<< setw(wn[3] - 1) << arr[i].n << char(179) << endl;
	}
	cout << char(192) << setfill(char(196));
	for (int j = 0; j < m - 1; j++)
		cout << setw(wn[j]) << char(193);
	cout << setw(wn[m - 1]) << char(217) << setfill(' ') << endl;
}

double IntRect(F f, double a, double b, double eps, int &n)
{
	n = 1;
	double cur_res = f(a) * (b - a), prev_res, dx;
	do
	{
		prev_res = cur_res;
		cur_res = 0;
		n *= 2;
		dx = (b - a) / n;
		for (int i = 1; i <= n; i++)
			cur_res += f(a + dx * (i - 0.5));
		cur_res *= dx;
	} while (fabs(cur_res - prev_res) > eps);

	return cur_res;
}

double IntTrap(F f, double a, double b, double eps, int &n)
{
	n = 1;
	double cur_res = (f(a) + f(b)) / 2 * (b - a), prev_res, dx;
	do
	{
		prev_res = cur_res;
		cur_res = 0;
		n *= 2;
		dx = (b - a) / n;
		for (int i = 0; i < n; i++)
			cur_res += (f(a + dx * i) + f(a + dx * (i + 1))) / 2;
		cur_res *= dx;
	} while (fabs(cur_res - prev_res) > eps);

	return cur_res;
}

int mai()
{
	const short N = 4;
	double A, B;

	cout << "Enter A:\n";
	cin >> A;
	cout << "Enter B:\n";
	cin >> B;

	const F massiv_1[N] = { f0, f1, f2, f3 };
	const I massiv_2[N] = { i0, i1, i2, i3 };
	const char *massiv_3[N] = { "y=x ", "y=sin(22x)", "y=x^4 ", "y=arctg(x)" };

	double eps;
	int i;
	int_st *arr = new int_st[N];

	cout << "Region integration functions: " << A << " <= x <= " << B << endl << endl;

	for (eps = 1e-2; eps > 1e-6; eps /= 1e+1)
	{
		cout << "  - EPS = " << fixed << eps << endl;
		for (i = 0; i < 4; i++)
		{
		//	arr[i].name = massiv_3[i];
			arr[i].a = massiv_2[i](A, B);
			arr[i].n = 0;
			arr[i].c = IntRect(massiv_1[i], A, B, eps, arr[i].n);
		}
		cout << endl << "Results integrating by method of rectangles:" << endl;
		print_tab(arr, N);
		cout << endl;
		for (i = 0; i < N; i++)
		{
			arr[i].n = 0;
			arr[i].c = IntTrap(massiv_1[i], A, B, eps, arr[i].n);
		}
		cout << "Results integration by method of trapezoids:" << endl;
		print_tab(arr, N);
		cout << endl;
		system("pause");
	}

	delete[] arr;
	system("pause");

	return 0;
}