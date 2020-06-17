#include <iostream>
template<class T> void swap(T& a, T& b)
{
	T c(std::move(a)); a = std::move(b); b = std::move(c);
}
template <class T, size_t N> void swap(T(&a)[N], T(&b)[N])
{
	for (size_t i = 0; i < N; ++i) {
		swap(a[i], b[i]);
	}
}

template<class RandomIterate, class RNG>
void shuffle_deck(RandomIterate first, RandomIterate last, RNG& g) {
	int i, n;
	n = (last - first);
	for (i = n - 1; i > 0; --i) {
		swap (first[i], first[g(i+1)])
	}
}