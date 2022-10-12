#pragma once

namespace Tmpl8
{

	// Compile by using: cl /EHsc /W4 InstructionSet.cpp
	// processor: x86, x64
	// Uses the __cpuid intrinsic to get information about
	// CPU extended instruction set support.
	class CPUCaps // from https://github.com/Mysticial/FeatureDetector
	{
	public:
		static inline bool HW_MMX = false;
		static inline bool HW_x64 = false;
		static inline bool HW_ABM = false;
		static inline bool HW_RDRAND = false;
		static inline bool HW_BMI1 = false;
		static inline bool HW_BMI2 = false;
		static inline bool HW_ADX = false;
		static inline bool HW_PREFETCHWT1 = false;
		// SIMD: 128-bit
		static inline bool HW_SSE = false;
		static inline bool HW_SSE2 = false;
		static inline bool HW_SSE3 = false;
		static inline bool HW_SSSE3 = false;
		static inline bool HW_SSE41 = false;
		static inline bool HW_SSE42 = false;
		static inline bool HW_SSE4a = false;
		static inline bool HW_AES = false;
		static inline bool HW_SHA = false;
		// SIMD: 256-bit
		static inline bool HW_AVX = false;
		static inline bool HW_XOP = false;
		static inline bool HW_FMA3 = false;
		static inline bool HW_FMA4 = false;
		static inline bool HW_AVX2 = false;
		// SIMD: 512-bit
		static inline bool HW_AVX512F = false;    //  AVX512 Foundation
		static inline bool HW_AVX512CD = false;   //  AVX512 Conflict Detection
		static inline bool HW_AVX512PF = false;   //  AVX512 Prefetch
		static inline bool HW_AVX512ER = false;   //  AVX512 Exponential + Reciprocal
		static inline bool HW_AVX512VL = false;   //  AVX512 Vector Length Extensions
		static inline bool HW_AVX512BW = false;   //  AVX512 Byte + Word
		static inline bool HW_AVX512DQ = false;   //  AVX512 Doubleword + Quadword
		static inline bool HW_AVX512IFMA = false; //  AVX512 Integer 52-bit Fused Multiply-Add
		static inline bool HW_AVX512VBMI = false; //  AVX512 Vector Byte Manipulation Instructions
		// constructor
		CPUCaps();
	};
};
