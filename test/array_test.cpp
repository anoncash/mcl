#include <mcl/array.hpp>
#include <cybozu/test.hpp>

template<class Array, size_t an, size_t bn>
void swapTest(const int (&a)[an], const int (&b)[bn])
{
	Array s, t;
	CYBOZU_TEST_ASSERT(s.resize(an));
	CYBOZU_TEST_ASSERT(t.resize(bn));
	for (size_t i = 0; i < an; i++) s[i] = a[i];
	for (size_t i = 0; i < bn; i++) t[i] = b[i];
	s.swap(t);
	CYBOZU_TEST_EQUAL(s.size(), bn);
	CYBOZU_TEST_EQUAL(t.size(), an);
	CYBOZU_TEST_EQUAL_ARRAY(s, b, s.size());
	CYBOZU_TEST_EQUAL_ARRAY(t, a, t.size());
}

CYBOZU_TEST_AUTO(resize)
{
	mcl::Array<int> a, b;
	CYBOZU_TEST_EQUAL(a.size(), 0);
	CYBOZU_TEST_EQUAL(b.size(), 0);

	const size_t n = 5;
	bool ok = a.resize(n);
	CYBOZU_TEST_ASSERT(ok);
	CYBOZU_TEST_EQUAL(n, a.size());
	for (size_t i = 0; i < n; i++) {
		a[i] = i;
	}
	ok = b.copy(a);
	CYBOZU_TEST_ASSERT(ok);
	CYBOZU_TEST_EQUAL(b.size(), n);
	CYBOZU_TEST_EQUAL_ARRAY(a.data(), b.data(), n);

	const size_t small = n - 1;
	ok = b.resize(small);
	CYBOZU_TEST_ASSERT(ok);
	CYBOZU_TEST_EQUAL(b.size(), small);
	CYBOZU_TEST_EQUAL_ARRAY(a.data(), b.data(), small);
	const size_t large = n * 2;
	ok = b.resize(large);
	CYBOZU_TEST_ASSERT(ok);
	CYBOZU_TEST_EQUAL(b.size(), large);
	CYBOZU_TEST_EQUAL_ARRAY(a.data(), b.data(), small);

	const int aTbl[] = { 3, 4 };
	const int bTbl[] = { 7, 6, 5, 3 };
	swapTest<mcl::Array<int> >(aTbl, bTbl);
	swapTest<mcl::Array<int> >(bTbl, aTbl);
}

CYBOZU_TEST_AUTO(FixedArray)
{
	const size_t n = 5;
	mcl::FixedArray<int, n> a, b;
	CYBOZU_TEST_EQUAL(a.size(), 0);
	CYBOZU_TEST_EQUAL(b.size(), 0);

	bool ok = a.resize(n);
	CYBOZU_TEST_ASSERT(ok);
	CYBOZU_TEST_EQUAL(n, a.size());
	for (size_t i = 0; i < n; i++) {
		a[i] = i;
	}
	ok = b.copy(a);
	CYBOZU_TEST_ASSERT(ok);
	CYBOZU_TEST_EQUAL(b.size(), n);
	CYBOZU_TEST_EQUAL_ARRAY(a.data(), b.data(), n);

	const size_t small = n - 1;
	ok = b.resize(small);
	CYBOZU_TEST_ASSERT(ok);
	CYBOZU_TEST_EQUAL(b.size(), small);
	CYBOZU_TEST_EQUAL_ARRAY(a.data(), b.data(), small);
	const size_t large = n + 1;
	ok = b.resize(large);
	CYBOZU_TEST_ASSERT(!ok);

	const int aTbl[] = { 3, 4 };
	const int bTbl[] = { 7, 6, 5, 3 };
	swapTest<mcl::FixedArray<int, n> >(aTbl, bTbl);
	swapTest<mcl::FixedArray<int, n> >(bTbl, aTbl);
}
