#pragma once

namespace Tmpl8
{
	class Surface;
	// basic sprite class
	class Sprite
	{
	public:
		// constructors
		Sprite(Surface* a_Surface, int a_NumFrames);
		Sprite(const Sprite&) = delete; //You are not allowed to copy this object.
		~Sprite();

		Sprite& operator=(const Sprite&) = delete; //No copying...
		// methods
		void Draw(Surface* a_Target, int a_X, int a_Y);
		void DrawScaled(int a_X, int a_Y, int a_Width, int a_Height, Surface* a_Target);
		void SetFlags(unsigned int a_Flags) { flags = a_Flags; }
		void SetFrame(unsigned int a_Index) { currentFrame = a_Index; }
		unsigned int GetFlags() const { return flags; }
		int GetWidth() { return width; }
		int GetHeight() { return height; }
		uint* GetBuffer();
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
};