#pragma once


namespace Tmpl8
{
	// timer
	struct Timer
	{
		Timer() { reset(); }
		//Returns elapsed time in seconds.
		float elapsed() const
		{
			std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - start);
			return static_cast<float>(time_span.count());
		}
		void reset() { start = std::chrono::high_resolution_clock::now(); }
		std::chrono::high_resolution_clock::time_point start;
	};

	// 32-bit surface container
	class Surface
	{
		enum { OWNER = 1 };
	public:
		// constructor / destructor
		Surface() = default;
		Surface(int w, int h, uint* buffer);
		Surface(int w, int h);
		Surface(const char* file);
		~Surface();
		// operations
		void InitCharset();
		void SetChar(int c, const char* c1, const char* c2, const char* c3, const char* c4, const char* c5);
		void Print(const char* t, int x1, int y1, uint c);
		void Clear(uint c);
		void Line(float x1, float y1, float x2, float y2, uint c);
		void Plot(int x, int y, uint c);
		void LoadImage(const char* file);
		void CopyTo(Surface* dst, int x, int y);
		void Box(int x1, int y1, int x2, int y2, uint color);
		void Bar(int x1, int y1, int x2, int y2, uint color);
		// attributes
		uint* pixels = 0;
		int width = 0, height = 0;
		bool ownBuffer = false;
	};

	// basic sprite class
	class Sprite
	{
	public:
		// structors
		Sprite(Surface* a_Surface, unsigned int a_NumFrames);
		~Sprite();
		// methods
		void Draw(Surface* a_Target, int a_X, int a_Y);
		void DrawScaled(int a_X, int a_Y, int a_Width, int a_Height, Surface* a_Target);
		void SetFlags(unsigned int a_Flags) { flags = a_Flags; }
		void SetFrame(unsigned int a_Index) { currentFrame = a_Index; }
		unsigned int GetFlags() const { return flags; }
		int GetWidth() { return width; }
		int GetHeight() { return height; }
		uint* GetBuffer() { return surface->pixels; }
		unsigned int Frames() { return numFrames; }
		Surface* GetSurface() { return surface; }
		void InitializeStartData();
	private:
		// attributes
		int width, height;
		unsigned int numFrames;
		unsigned int currentFrame;
		unsigned int flags;
		unsigned int** start;
		Surface* surface;
	};
	
	// application base class
	class TheApp
	{
	public:
		virtual void Init() = 0;
		virtual void Tick(float deltaTime) = 0;
		virtual void Shutdown() = 0;
		virtual void MouseUp(int button) = 0;
		virtual void MouseDown(int button) = 0;
		virtual void MouseMove(int x, int y) = 0;
		virtual void MouseWheel(float y) = 0;
		virtual void KeyUp(int key) = 0;
		virtual void KeyDown(int key) = 0;
		Surface* screen = 0;
	};

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

// pixel operations
inline uint ScaleColor(const uint c, const uint scale)
{
	const uint rb = (((c & 0xff00ff) * scale) >> 8) & 0x00ff00ff;
	const uint ag = (((c & 0xff00ff00) >> 8) * scale) & 0xff00ff00;
	return rb + ag;
}
inline uint AddBlend(const uint c1, const uint c2)
{
	const uint r1 = (c1 >> 16) & 255, r2 = (c2 >> 16) & 255;
	const uint g1 = (c1 >> 8) & 255, g2 = (c2 >> 8) & 255;
	const uint b1 = c1 & 255, b2 = c2 & 255;
	const uint r = std::min(255u, r1 + r2);
	const uint g = std::min(255u, g1 + g2);
	const uint b = std::min(255u, b1 + b2);
	return (r << 16) + (g << 8) + b;
}
inline uint SubBlend(uint a_Color1, uint a_Color2)
{
	int red = (a_Color1 & 0xff0000) - (a_Color2 & 0xff0000);
	int green = (a_Color1 & 0x00ff00) - (a_Color2 & 0x00ff00);
	int blue = (a_Color1 & 0x0000ff) - (a_Color2 & 0x0000ff);
	if (red < 0) red = 0;
	if (green < 0) green = 0;
	if (blue < 0) blue = 0;
	return (uint)(red + green + blue);
}

// random numbers
uint RandomUInt();
uint RandomUInt(uint& seed);
float RandomFloat();
float RandomFloat(uint& seed);
float Rand(float range);

// Perlin noise
float noise2D(const float x, const float y);

// forward declaration of helper functions
void FatalError(const char* fmt, ...);
bool FileIsNewer(const char* file1, const char* file2);
bool FileExists(const char* f);
bool RemoveFile(const char* f);
std::string TextFileRead(const char* _File);
int LineCount(const std::string& s);
void TextFileWrite(const std::string& text, const char* _File);
