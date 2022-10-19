// Template, IGAD version 3
// IGAD/NHTV/UU - Jacco Bikker - 2006-2022

#include "precomp.h"
#include "template.h"

#include <glad.h>
#include <GLFW/glfw3.h>

#include "template_gl.h"
#include "game.h"

//// windows.h: disable as much as possible to speed up compilation.
#define NOMINMAX
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#endif
#define NOGDICAPMASKS
// #define NOVIRTUALKEYCODES
#define NOWINMESSAGES
#define NOWINSTYLES
#define NOSYSMETRICS
#define NOMENUS
#define NOICONS
#define NOKEYSTATES
#define NOSYSCOMMANDS
#define NORASTEROPS
#define NOSHOWWINDOW
#define OEMRESOURCE
#define NOATOM
#define NOCLIPBOARD
#define NOCOLOR
#define NOCTLMGR
#define NODRAWTEXT
#define NOKERNEL
#define NONLS
#define NOMEMMGR
#define NOMETAFILE
#define NOMINMAX
#define NOMSG
#define NOOPENFILE
#define NOSCROLL
#define NOSERVICE
#define NOSOUND
#define NOTEXTMETRIC
#define NOWH
#define NOWINOFFSETS
#define NOCOMM
#define NOKANJI
#define NOHELP
#define NOPROFILER
#define NODEFERWINDOWPOS
#define NOMCX
#define NOIME

#ifdef APIENTRY
#undef APIENTRY
#endif
#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#include <GLFW/glfw3native.h>

//Windows leaks defines, so we don't want this anymore...
#undef LoadImage

#define STB_IMAGE_IMPLEMENTATION
#define STBI_NO_PSD
#define STBI_NO_PIC
#define STBI_NO_PNM
#include "surface.h"
#include "timer.h"
#include "lib/stb_image.h"

#pragma comment( linker, "/subsystem:windows /ENTRY:mainCRTStartup" )


namespace Tmpl8::Detail
{
	static void* GLFWWindow = nullptr;

	const char* VertexShaderSource = R"shader(
#version 330
in vec4 p;
in vec2 t;
out vec2 u;
void main()
{
	u=t;gl_Position=p;
})shader";
	const char* FragmentShaderSource = R"shader(
#version 330
uniform sampler2D c;
in vec2 u;
out vec4 f;
void main()
{
	f=/*sqrt*/(texture(c,u));
}
)shader";
};

using namespace Tmpl8;

// Enable usage of dedicated GPUs in notebooks
// Note: this does cause the linker to produce a .lib and .exp file;
// see http://developer.download.nvidia.com/devzone/devcenter/gamegraphics/files/OptimusRenderingPolicies.pdf
#ifdef WIN32
extern "C"
{
	__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}
#endif

extern GLFWwindow* window = nullptr;
static bool hasFocus = true, running = true;
static GLTexture* renderTarget = 0;
static int scrwidth = 0, scrheight = 0;
static TheApp* app = 0;

// provide access to the render target, for OpenCL / OpenGL interop
GLTexture* GetRenderTarget() { return renderTarget; }

// GLFW callbacks
void InitRenderTarget( int w, int h )
{
	// allocate render target and surface
	scrwidth = w, scrheight = h;
	renderTarget = new GLTexture( scrwidth, scrheight, GLTexture::INTTARGET );
}
void ReshapeWindowCallback( GLFWwindow* window, int w, int h )
{
	glViewport( 0, 0, w, h );
}
void KeyEventCallback( GLFWwindow* window, int key, int scancode, int action, int mods )
{
	if (key == GLFW_KEY_ESCAPE) running = false;
	if (action == GLFW_PRESS) { if (app) if (key >= 0) app->KeyDown( key ); }
	else if (action == GLFW_RELEASE) { if (app) if (key >= 0) app->KeyUp( key ); }
}
void CharEventCallback( GLFWwindow* window, uint code ) { /* nothing here yet */ }
void WindowFocusCallback( GLFWwindow* window, int focused ) { hasFocus = (focused == GL_TRUE); }
void MouseButtonCallback( GLFWwindow* window, int button, int action, int mods )
{
	if (action == GLFW_PRESS) { if (app) app->MouseDown( button ); }
	else if (action == GLFW_RELEASE) { if (app) app->MouseUp( button ); }
}
void MouseScrollCallback( GLFWwindow* window, double x, double y )
{
	app->MouseWheel( (float)y );
}
void MousePosCallback( GLFWwindow* window, double x, double y )
{
	if (app) app->MouseMove( (int)x, (int)y );
}
void ErrorCallback( int error, const char* description )
{
	fprintf( stderr, "GLFW Error: %s\n", description );
}

// Application entry point
void main()
{
	// open a window
	if (!glfwInit()) FatalError( "glfwInit failed." );
	glfwSetErrorCallback( ErrorCallback );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 ); // 3.3 is enough for our needs
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
	glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
	glfwWindowHint( GLFW_STENCIL_BITS, GL_FALSE );
	glfwWindowHint( GLFW_RESIZABLE, GL_FALSE /* easier :) */ );
#ifdef FULLSCREEN
	window = glfwCreateWindow( SCRWIDTH, SCRHEIGHT, "Tmpl8-2022", glfwGetPrimaryMonitor(), 0 );
#else
	window = glfwCreateWindow( SCRWIDTH, SCRHEIGHT, "Tmpl8-2022", 0, 0 );
#endif
	if (!window) FatalError( "glfwCreateWindow failed." );
	glfwMakeContextCurrent( window );
	// register callbacks
	glfwSetWindowSizeCallback( window, ReshapeWindowCallback );
	glfwSetKeyCallback( window, KeyEventCallback );
	glfwSetWindowFocusCallback( window, WindowFocusCallback );
	glfwSetMouseButtonCallback( window, MouseButtonCallback );
	glfwSetScrollCallback( window, MouseScrollCallback );
	glfwSetCursorPosCallback( window, MousePosCallback );
	glfwSetCharCallback( window, CharEventCallback );
	// initialize GLAD
	if (!gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress )) FatalError( "gladLoadGLLoader failed." );
	glfwSwapInterval( 0 );
	// prepare OpenGL state
	glDisable( GL_DEPTH_TEST );
	glDisable( GL_CULL_FACE );
	glDisable( GL_BLEND );
	// we want a console window for text output
#ifndef FULLSCREEN
	CONSOLE_SCREEN_BUFFER_INFO coninfo;
	AllocConsole();
	GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &coninfo );
	coninfo.dwSize.X = 1280;
	coninfo.dwSize.Y = 800;
	SetConsoleScreenBufferSize( GetStdHandle( STD_OUTPUT_HANDLE ), coninfo.dwSize );
	FILE* file = nullptr;
	freopen_s( &file, "CON", "w", stdout );
	freopen_s( &file, "CON", "w", stderr );
	SetWindowPos( GetConsoleWindow(), HWND_TOP, 0, 0, 1280, 800, 0 );
	glfwShowWindow( window );
#endif
	// initialize application
	InitRenderTarget( SCRWIDTH, SCRHEIGHT );
	Surface* screen = new Surface( SCRWIDTH, SCRHEIGHT );
	app = new Game();
	app->screen = screen;
	app->Init();
	// done, enter main loop

	// basic shader: apply gamma correction
	std::unique_ptr<Shader> shader = std::make_unique<Shader>(Detail::VertexShaderSource, Detail::FragmentShaderSource, true );

	float deltaTime = 0;
	static int frameNr = 0;
	static Timer timer;
	while (!glfwWindowShouldClose( window ))
	{
		deltaTime = std::min( 0.5f, timer.elapsed() );
		timer.reset();
		app->Tick( deltaTime );
		// send the rendering result to the screen using OpenGL
		if (frameNr++ > 1)
		{
			if (app->screen) renderTarget->CopyFrom( app->screen );
			shader->Bind();
			shader->SetInputTexture( 0, "c", renderTarget );
			DrawQuad();
			shader->Unbind();
			glfwSwapBuffers( window );
			glfwPollEvents();
		}
		if (!running) break;
	}
	// close down
	app->Shutdown();
	shader.reset();
	delete app;

	glfwDestroyWindow( window );
	glfwTerminate();
}

// RNG - Marsaglia's xor32
static uint seed = 0x12345678;
uint RandomUInt()
{
	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;
	return seed;
}
float RandomFloat() { return RandomUInt() * 2.3283064365387e-10f; }
float Rand( float range ) { return RandomFloat() * range; }
// local seed
uint RandomUInt( uint& seed )
{
	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;
	return seed;
}
float RandomFloat( uint& seed ) { return RandomUInt( seed ) * 2.3283064365387e-10f; }

// Perlin noise implementation - https://stackoverflow.com/questions/29711668/perlin-noise-generation
static int numX = 512, numY = 512, numOctaves = 7, primeIndex = 0;
static float persistence = 0.5f;
static int primes[10][3] = {
	{ 995615039, 600173719, 701464987 }, { 831731269, 162318869, 136250887 }, { 174329291, 946737083, 245679977 },
	{ 362489573, 795918041, 350777237 }, { 457025711, 880830799, 909678923 }, { 787070341, 177340217, 593320781 },
	{ 405493717, 291031019, 391950901 }, { 458904767, 676625681, 424452397 }, { 531736441, 939683957, 810651871 },
	{ 997169939, 842027887, 423882827 }
};
static float Noise( const int i, const int x, const int y )
{
	int n = x + y * 57;
	n = (n << 13) ^ n;
	const int a = primes[i][0], b = primes[i][1], c = primes[i][2];
	const int t = (n * (n * n * a + b) + c) & 0x7fffffff;
	return 1.0f - (float)t / 1073741824.0f;
}
static float SmoothedNoise( const int i, const int x, const int y )
{
	const float corners = (Noise( i, x - 1, y - 1 ) + Noise( i, x + 1, y - 1 ) + Noise( i, x - 1, y + 1 ) + Noise( i, x + 1, y + 1 )) / 16;
	const float sides = (Noise( i, x - 1, y ) + Noise( i, x + 1, y ) + Noise( i, x, y - 1 ) + Noise( i, x, y + 1 )) / 8;
	const float center = Noise( i, x, y ) / 4;
	return corners + sides + center;
}
static float Interpolate( const float a, const float b, const float x )
{
	const float ft = x * 3.1415927f, f = (1 - cosf( ft )) * 0.5f;
	return a * (1 - f) + b * f;
}
static float InterpolatedNoise( const int i, const float x, const float y )
{
	const int integer_X = (int)x, integer_Y = (int)y;
	const float fractional_X = x - integer_X, fractional_Y = y - integer_Y;
	const float v1 = SmoothedNoise( i, integer_X, integer_Y );
	const float v2 = SmoothedNoise( i, integer_X + 1, integer_Y );
	const float v3 = SmoothedNoise( i, integer_X, integer_Y + 1 );
	const float v4 = SmoothedNoise( i, integer_X + 1, integer_Y + 1 );
	const float i1 = Interpolate( v1, v2, fractional_X );
	const float i2 = Interpolate( v3, v4, fractional_X );
	return Interpolate( i1, i2, fractional_Y );
}
float noise2D( const float x, const float y )
{
	float total = 0, frequency = (float)(2 << numOctaves), amplitude = 1;
	for (int i = 0; i < numOctaves; ++i)
	{
		frequency /= 2, amplitude *= persistence;
		total += InterpolatedNoise( (primeIndex + i) % 10, x / frequency, y / frequency ) * amplitude;
	}
	return total / frequency;
}

// Helper functions
bool FileIsNewer( const char* file1, const char* file2 )
{
	struct stat f1{};
	struct stat f2{};

	auto ret = stat( file1, &f1 );
	FATALERROR_IF( ret, "File %s not found!", file1 );

	if (stat( file2, &f2 )) return true; // second file does not exist

#ifdef _MSC_VER
	return f1.st_mtime >= f2.st_mtime;
#else
	if (f1.st_mtim.tv_sec >= f2.st_mtim.tv_sec)
		return true;
	return f1.st_mtim.tv_nsec >= f2.st_mtim.tv_nsec;
#endif
}

bool FileExists( const char* f )
{
	std::ifstream s( f );
	return s.good();
}

bool RemoveFile( const char* f )
{
	if (!FileExists( f )) return false;
	return !remove( f );
}

uint FileSize( const std::string& filename )
{
	std::ifstream s( filename );
	return s.good();
}

std::string TextFileRead( const char* _File )
{
	std::ifstream s( _File );
	std::string str( (std::istreambuf_iterator<char>( s )), std::istreambuf_iterator<char>() );
	s.close();
	return str;
}

int LineCount( const std::string& s )
{
	const char* p = s.c_str();
	int lines = 0;
	while (*p) if (*p++ == '\n') lines++;
	return lines;
}

void TextFileWrite( const std::string& text, const char* _File )
{
	std::ofstream s( _File, std::ios::binary );
	int len = (int)text.size();
	s.write( (const char*)&len, sizeof( len ) );
	s.write( text.c_str(), len );
}

void FatalError( const char* fmt, ... )
{
	char t[4096];
	va_list args;
	va_start( args, fmt );
	vsnprintf_s( t, sizeof( t ), fmt, args );
	va_end( args );
#ifdef _MSC_VER
	MessageBox( NULL, t, "Fatal error", MB_OK );
#else
	fprintf( stderr, t );
#endif
	while (1)
	{
		__debugbreak();

		exit(0);
	}
}
// EOF