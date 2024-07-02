#include <iostream>
#include <complex>
const int N = 5;
const float pi = 3.1415;
using namespace std;
void DPF(complex<float> A[N], complex<float> i)
{
	int j, k, M = 0;
	float j2, k2, n = N;
	complex<float> f[N] = { 0 }, A1[N] = { 0 };
	cout << endl << endl << " Прямое ДПФ:";
	for (j = 0; j < N; j++)
	{
		j2 = j;
		for (k = 0; k < N; k++)
		{
			k2 = k;
			f[j] += exp(-2 * pi * i * j2 * k2 / n) * A[k];
			M += 5;
		}
		f[j] /= n;
		//cout << endl << " " << f[j];
		printf("\n (%0.10f, %0.10f)", f[j].real(), f[j].imag());
	}
	cout << endl << endl << " Обратное ДПФ:";
	for (j = 0; j < N; j++)
	{
		j2 = j;
		for (k = 0; k < N; k++)
		{
			k2 = k;
			A1[j] += exp(2 * pi * i * j2 * k2 / n) * f[k];
			M += 5;
		}
		//cout << endl << A[j];
		printf("\n (%0.10f, %0.10f)", A1[j].real(), A1[j].imag());
	}
	cout << "\n\n Количество операций: " << M;
}

void PBPF(complex<float> A[N], complex<float> i)
{
	int M = 0, p1 = 1, p2 = 5, j1, j2, k1, k2, j, k;
	float n = N, fp1 = p1, fp2 = p2, fj1, fj2, fk1, fk2;
	complex<float> A1[N][N] = { 0 }, A2[N][N] = { 0 }, f1[N][N] = { 0 }, f[N][N];
	cout << endl << endl << " ПБПФ:\n A1(k1, j2):\n";
	for (k1 = 0; k1 < p1; k1++)
	{
		fk1 = k1;
		for (j2 = 0; j2 < p2; j2++)
		{
			fj2 = j2;
			for (j1 = 0; j1 < p1; j1++)
			{
				fj1 = j1;
				A1[k1][j2] += A[j2 + p2 * j1] * exp(-2 * pi * i * fj1 * fk1 / fp1);
				M++;
			}
			A1[k1][j2] /= fp1;
			printf("\n (%0.10f, %0.10f)", A1[k1][j2].real(), A1[k1][j2].imag());
		}
	}
	cout << endl << endl << " A2(k1, k2):\n";
	for (k1 = 0; k1 < p1; k1++)
	{
		fk1 = k1;
		for (k2 = 0; k2 < p2; k2++)
		{
			fk2 = k2;
			for (j2 = 0; j2 < p2; j2++)
			{
				fj2 = j2;
				A2[k1][k2] += A1[k1][j2] * exp(-2 * pi * i * ((fk1 + fp1 * fk2) * fj2 / (fp1 * fp2)));
				M++;
			}
			A2[k1][k2] /= fp2;
		}
	}
	for (j = 0; j < p2; j++)
	{
		for (k = 0; k < p1; k++)
			printf("\n (%0.10f, %0.10f)", A2[k][j].real(), A2[k][j].imag());
	}
	cout << "\n\n Количество операций: " << M;



	cout << "\n\n Обратное ПБПФ:";
	for (k1 = 0; k1 < p1; k1++)
	{
		fk1 = k1;
		for (k2 = 0; k2 < p2; k2++)
		{
			fk2 = k2;
			for (j2 = 0; j2 < p2; j2++)
			{
				fj2 = j2;
				f1[k1][j2] += A2[k1][k2] * exp(2 * pi * i * ((fk1 + fp1 * fk2) * fj2 / (fp1 * fp2)));
				M++;
			}
			printf("\n (%0.10f, %0.10f)", f1[k1][k2].real(), f1[k1][k2].imag());
		}
	}
	cout << endl;
	for (k1 = 0; k1 < p1; k1++)
	{
		fk1 = k1;
		for (j2 = 0; j2 < p2; j2++)
		{
			fj2 = j2;
			for (j1 = 0; j1 < p1; j1++)
			{
				fj1 = j1;
				f[k1][j2] += f1[j1][j2] * exp(2 * pi * i * fj1 * fk1 / fp1);
				M++;
			}
			printf("\n (%0.10f, %0.10f)", f[k1][j2].real(), f[k1][j2].imag());
		}
	}
	//for (k1 = 0; k1 < p1; k1++)
	//{
	//	fk1 = k1;
	//	for (j2 = 0; j2 < p2; j2++)
	//	{
	//		fj2 = j2;
	//		for (j1 = 0; j1 < p1; j1++)
	//		{
	//			fj1 = j1;
	//			f1[k1][j2] += A2[j1][j2] * exp(2 * pi * i * fj1 * fk1 / fp1);
	//			M++;
	//		}
	//		//printf("\n (%0.10f, %0.10f)", f1[k1][j2].real(), f1[k1][j2].imag());
	//	}
	//}
	//cout << endl << endl << " A2(k1, k2):\n";
	//for (k1 = 0; k1 < p1; k1++)
	//{
	//	fk1 = k1;
	//	for (k2 = 0; k2 < p2; k2++)
	//	{
	//		fk2 = k2;
	//		for (j2 = 0; j2 < p2; j2++)
	//		{
	//			fj2 = j2;
	//			f[k1][k2] += f1[k1][j2] * exp(2 * pi * i * ((fk1 + fp1 * fk2) * fj2 / (fp1 * fp2)));
	//			M++;
	//		}
	//		printf("\n (%0.10f, %0.10f)", f[k1][k2].real(), f[k1][k2].imag());
	//	}
	//}
}
int main()
{
	setlocale(LC_ALL, "Russian");
	int j;
	float k;
	complex<float> A[N] = { 1, 0, 1, 0, 1 }, i(0, 1);
	cout << " Исходный массив:";
	for (j = 0; j < N; j++)
	{
		//k = rand() % 100;
		//A[j] = (cos(k) + i * sin(k)) * (float)10;
		cout << " " << A[j];
	}
	DPF(A, i);
	cout << endl << "_______________";
	PBPF(A, i);
	return 0;
}