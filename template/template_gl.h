#pragma once

class mat4;
namespace Tmpl8
{
	class Surface;

	// OpenGL texture wrapper
	class GLTexture
	{
	public:
		enum { DEFAULT = 0, FLOAT = 1, INTTARGET = 2 };
		// constructor / destructor
		GLTexture(uint width, uint height, uint type = DEFAULT);
		~GLTexture();
		// methods
		void Bind(const uint slot = 0);
		void CopyFrom(Surface* src);
		void CopyTo(Surface* dst);
	public:
		// public data members
		unsigned int ID = 0; //GLUint
		uint width = 0, height = 0;
	};

	// template function access
	GLTexture* GetRenderTarget();

	// shader wrapper
	class Shader
	{
	public:
		// constructor / destructor
		Shader(const char* vfile, const char* pfile, bool fromString);
		~Shader();
		// methods
		void Init(const char* vfile, const char* pfile);
		void Compile(const char* vtext, const char* ftext);
		void Bind();
		void SetInputTexture(uint slot, const char* name, GLTexture* texture);
		void SetInputMatrix(const char* name, const mat4& matrix);
		void SetFloat(const char* name, const float v);
		void SetInt(const char* name, const int v);
		void SetUInt(const char* name, const uint v);
		void Unbind();
	private:
		// data members
		uint vertex = 0;	// vertex shader identifier
		uint pixel = 0;		// fragment shader identifier
		uint ID = 0;		// shader program identifier
	};
	
	// forward declarations of helper functions
	void _CheckGL(const char* f, int l);
	uint CreateVBO(const float* data, const uint size);
	void BindVBO(const uint idx, const uint N, const uint id);
	void CheckShader(uint shader, const char* vshader, const char* fshader);
	void CheckProgram(uint id, const char* vshader, const char* fshader);
	void DrawQuad();

#define CheckGL() { _CheckGL( __FILE__, __LINE__ ); }
};
