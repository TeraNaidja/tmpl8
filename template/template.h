#pragma once


namespace Tmpl8
{
	class Surface;

	// application base class
	class TheApp
	{
	public:
		virtual ~TheApp() = default;

		virtual void Init() = 0;
		virtual void Tick(float deltaTime) = 0;
		virtual void Shutdown() = 0;
		virtual void MouseUp(int button) = 0;
		virtual void MouseDown(int button) = 0;
		virtual void MouseMove(int x, int y) = 0;
		virtual void MouseWheel(float y) = 0;
		virtual void KeyUp(int key) = 0;
		virtual void KeyDown(int key) = 0;
		Surface* screen = nullptr;
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
[[noreturn]] void FatalError(const char* fmt, ...);
bool FileIsNewer(const char* file1, const char* file2);
bool FileExists(const char* f);
bool RemoveFile(const char* f);
std::string TextFileRead(const char* _File);
int LineCount(const std::string& s);
void TextFileWrite(const std::string& text, const char* _File);
