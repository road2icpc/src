//# Title: Fast Fourier Transform
//# Description: Converts a sequence $f_j$ of $n$ complex numbers into another sequence $F_k$ of $n$ complex numbers such that $F_k = \sum_{ j = 0 }^{ n - 1 } f_j e^{ -2 \pi i j k / n }$. \texttt{conv()} multiplies two polynomials using FFT. Rounding is safe if $(\sum A_j^2 + \sum B_j^2) \log_2{ n } < 9 \cdot 10^{ 14 }$ (for random inputs $10^{ 16 }$ should be safe). NOTE!!: inputs for \texttt{FFT()} should have size $2^k$ for some integer $k > 0$ (\texttt{conv()} handles any sizes).
//# Usage: \texttt{fft(f)} computes the FFT of \texttt{f} in place. \texttt{conv(A, B)} returns the polynomial $P(x) = A(x) \cdot B(x)$.
//# Complexity: Both FFT and \texttt{conv()} are $\mathcal{O}(n \log n)$.

//@ tested on:
//@  1. https://cses.fi/problemset/task/2111/

#pragma once

typedef complex <double> C;
typedef vector <double> vd;

void fft(vector <C>& f) {
	int n = siz(f);
	static vector <C> roots(2, 1);
	for (static int i = 2; i < n; i <<= 1) {
		static constexpr double pi = acos(-1);
		C w[] = { 1, polar(1., pi / i) };
		roots.resize(n);
		for (int j = i; j < i << 1; j++)
			roots[j] = roots[j >> 1] * w[j & 1];
	}
	vi rv(n); // consider precomputing rv[]
	for (int i = 0; i < n; i++)
		rv[i] = ((i & 1) * n | rv[i >> 1]) >> 1;
	for (int i = 0; i < n; i++)
		if (i < rv[i]) swap(f[i], f[rv[i]]);
	for (int k = 1; k < n; k <<= 1)
		for (int i = 0; i < n; i += k << 1)
			for (int j = 0; j < k; j++) {
				C z = f[i + j + k] * roots[j + k];
				f[i + j + k] = f[i + j] - z;
				f[i + j] += z;
			}
}

vd conv(const vd& A, const vd& B) {
	if (A.empty() || B.empty()) return { };
	vd res(siz(A) + siz(B) - 1);
	int n = 1 << (32 - __builtin_clz(siz(res)));
	vector <C> in(n), out(n);
	for (int i = 0; i < siz(A); i++) in[i].real(A[i]);
	for (int i = 0; i < siz(B); i++) in[i].imag(B[i]);
	fft(in);
	for (C& c : in) c *= c;
	for (int i = 0; i < n; i++) out[i] = in[-i & (n - 1)] - conj(in[i]);
	fft(out);
	for (int i = 0; i < siz(res); i++) res[i] = imag(out[i]) / (n << 2);
	return res;
}
