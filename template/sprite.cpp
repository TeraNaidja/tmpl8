#include "precomp.h"
#include "sprite.h"

#include "surface.h"


Tmpl8::Sprite::Sprite(Surface* a_Surface, int a_NumFrames) :
	width(a_Surface->width / a_NumFrames),
	height(a_Surface->height),
	numFrames(a_NumFrames),
	currentFrame(0),
	flags(0),
	start(new unsigned int* [a_NumFrames]),
	surface(a_Surface)
{
	assert(a_NumFrames > 0);
	InitializeStartData();
}

Tmpl8::Sprite::~Sprite()
{
	delete surface;
	for (unsigned int i = 0; i < numFrames; i++) delete start[i];
	delete start;
}

void Tmpl8::Sprite::Draw(Surface* a_Target, int a_X, int a_Y)
{
	if ((a_X < -width) || (a_X > (a_Target->width + width))) return;
	if ((a_Y < -height) || (a_Y > (a_Target->height + height))) return;
	int x1 = a_X, x2 = a_X + width;
	int y1 = a_Y, y2 = a_Y + height;
	uint* src = GetBuffer() + static_cast<size_t>(currentFrame * width);
	if (x1 < 0)
	{
		src += -x1;
		x1 = 0;
	}
	if (x2 > a_Target->width) x2 = a_Target->width;
	if (y1 < 0)
	{
		src += static_cast<size_t>(-y1 * width * numFrames);
		y1 = 0;
	}
	if (y2 > a_Target->height) y2 = a_Target->height;
	uint* dest = a_Target->pixels;
	int xs;
	const int dpitch = a_Target->width;
	if ((x2 > x1) && (y2 > y1))
	{
		unsigned int addr = y1 * dpitch + x1;
		const int w = x2 - x1;
		const int h = y2 - y1;
		for (int y = 0; y < h; y++)
		{
			const int line = y + (y1 - a_Y);
			const int lsx = start[currentFrame][line] + a_X;
			xs = (lsx > x1) ? lsx - x1 : 0;
			for (int x = xs; x < w; x++)
			{
				const uint c1 = *(src + x);
				if (c1 & 0xffffff) *(dest + addr + x) = c1;
			}
			addr += dpitch;
			src += static_cast<size_t>(width * numFrames);
		}
	}
}

void Tmpl8::Sprite::DrawScaled(int a_X, int a_Y, int a_Width, int a_Height, Tmpl8::Surface* a_Target)
{
	if ((a_Width == 0) || (a_Height == 0)) return;
	for (int x = 0; x < a_Width; x++) for (int y = 0; y < a_Height; y++)
	{
		int u = (int)((float)x * ((float)width / (float)a_Width));
		int v = (int)((float)y * ((float)height / (float)a_Height));
		uint color = GetBuffer()[u + v * width * numFrames];
		if (color & 0xffffff) a_Target->pixels[a_X + x + ((a_Y + y) * a_Target->width)] = color;
	}
}

void Tmpl8::Sprite::InitializeStartData()
{
	for (unsigned int f = 0; f < numFrames; ++f)
	{
		start[f] = new unsigned int[height];
		for (int y = 0; y < height; ++y)
		{
			start[f][y] = width;
			uint* addr = GetBuffer() + static_cast<size_t>(f * width + y * width * numFrames);
			for (int x = 0; x < width; ++x) if (addr[x])
			{
				start[f][y] = x;
				break;
			}
		}
	}
}


uint* Tmpl8::Sprite::GetBuffer()
{
	return surface->pixels;
}
