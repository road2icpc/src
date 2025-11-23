//@ Author: Håkan Terelius
//@ Date: 2009-09-25
//@ License: CC0
//@ Source: http://en.wikipedia.org/wiki/Euler's_totient_function
//@ Status: Tested

//# Title: Phi Function
//# Description: [kactl] \emph{Euler's $\phi$} function is defined as $\phi(n):=\#$ of positive integers $\leq n$ that are coprime with $n$.

#pragma once

const int LIM = 5000000;
int phi[LIM];

void calculatePhi() {
	for (int i = 0; i < LIM; i++) phi[i] = i&1 ? i : i/2;
	for (int i = 3; i < LIM; i += 2) if(phi[i] == i)
		for (int j = i; j < LIM; j += i) phi[j] -= phi[j] / i;
}
