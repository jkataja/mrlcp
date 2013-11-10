// Flags for _mm_cmpistri intrisic in SSE4.2 optimized lcplen
// Unsigned bytes source
// Equal each compare: match a[i] with b[i]
// Negative polarity gives matching elements
//
// See Intel SSE4 Programming Reference, April 2007, page 101
// @see http://software.intel.com/file/17971/

#ifdef __SSE4_2__
#include <nmmintrin.h>

#define LCP_FLAGS (_SIDD_UBYTE_OPS | _SIDD_CMP_EQUAL_EACH | \
		_SIDD_NEGATIVE_POLARITY )
#endif

// Find longest common prefix of strings a and b.
// SSE4.2 version uses _mm_cmpistri intrisic to compare
// 16 characters at a time, matching also null characters.
// Behaviour is undefined if a == b
inline size_t lcplen(const char * a, const char * b)
{
#ifdef __SSE4_2__
	size_t l = 1;
	size_t n;
	__m128i xa, xb;
	if (*a++ != *b++) return 0;
	do {
		xa = _mm_loadu_si128((__m128i *)a);
		xb = _mm_loadu_si128((__m128i *)b);
	} while ( ((n = _mm_cmpistri(xa, xb, LCP_FLAGS)) == 16) 
			&& (l += n) && (a += 16) && (b += 16) );
	return l + n;
#else
	size_t l = 0;
	while (*a++ == *b++) ++l;
	return l;
#endif
}
