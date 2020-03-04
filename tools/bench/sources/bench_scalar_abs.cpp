////////////////////////////////////////////////////////////////////////////////
// The MIT License (MIT)
//
// Copyright (c) 2019 Nicholas Frechette & Realtime Math contributors
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

#include <benchmark/benchmark.h>

#include <rtm/scalarf.h>

using namespace rtm;

inline float RTM_SIMD_CALL scalar_abs_scalar(float input) RTM_NO_EXCEPT
{
	return std::fabs(input);
}

#if defined(RTM_SSE2_INTRINSICS)
inline float RTM_SIMD_CALL vector_abs_sse2_and(float input) RTM_NO_EXCEPT
{
#if defined(_MSC_VER)
	constexpr __m128i masks = { 0xFFU, 0xFFU, 0xFFU, 0x7FU, 0xFFU, 0xFFU, 0xFFU, 0x7FU, 0xFFU, 0xFFU, 0xFFU, 0x7FU, 0xFFU, 0xFFU, 0xFFU, 0x7FU };
#else
	constexpr __m128i masks = { 0x7FFFFFFF7FFFFFFFULL, 0x7FFFFFFF7FFFFFFFULL };
#endif
	return _mm_cvtss_f32(_mm_and_ps(_mm_set_ps1(input), _mm_castsi128_ps(masks)));
}
#endif

static void bm_scalar_abs_scalar(benchmark::State& state)
{
	float f0 = -123.134f;
	float f1 = -123.134f;
	float f2 = -123.134f;
	float f3 = -123.134f;
	float f4 = -123.134f;
	float f5 = -123.134f;
	float f6 = -123.134f;
	float f7 = -123.134f;

	for (auto _ : state)
	{
		f0 = scalar_abs_scalar(f0);
		f1 = scalar_abs_scalar(f1);
		f2 = scalar_abs_scalar(f2);
		f3 = scalar_abs_scalar(f3);
		f4 = scalar_abs_scalar(f4);
		f5 = scalar_abs_scalar(f5);
		f6 = scalar_abs_scalar(f6);
		f7 = scalar_abs_scalar(f7);
	}

	benchmark::DoNotOptimize(f0);
	benchmark::DoNotOptimize(f1);
	benchmark::DoNotOptimize(f2);
	benchmark::DoNotOptimize(f3);
	benchmark::DoNotOptimize(f4);
	benchmark::DoNotOptimize(f5);
	benchmark::DoNotOptimize(f6);
	benchmark::DoNotOptimize(f7);
}

BENCHMARK(bm_scalar_abs_scalar);

#if defined(RTM_SSE2_INTRINSICS)
static void bm_scalar_abs_sse2_and(benchmark::State& state)
{
	float f0 = -123.134f;
	float f1 = -123.134f;
	float f2 = -123.134f;
	float f3 = -123.134f;
	float f4 = -123.134f;
	float f5 = -123.134f;
	float f6 = -123.134f;
	float f7 = -123.134f;

	for (auto _ : state)
	{
		f0 = vector_abs_sse2_and(f0);
		f1 = vector_abs_sse2_and(f1);
		f2 = vector_abs_sse2_and(f2);
		f3 = vector_abs_sse2_and(f3);
		f4 = vector_abs_sse2_and(f4);
		f5 = vector_abs_sse2_and(f5);
		f6 = vector_abs_sse2_and(f6);
		f7 = vector_abs_sse2_and(f7);
	}

	benchmark::DoNotOptimize(f0);
	benchmark::DoNotOptimize(f1);
	benchmark::DoNotOptimize(f2);
	benchmark::DoNotOptimize(f3);
	benchmark::DoNotOptimize(f4);
	benchmark::DoNotOptimize(f5);
	benchmark::DoNotOptimize(f6);
	benchmark::DoNotOptimize(f7);
}

BENCHMARK(bm_scalar_abs_sse2_and);
#endif
