#ifndef GLDEBUG_H
#define GLDEBUG_H

//#include "Debug.h"
#include "DebugPrint.h"
#include <GL/glew.h>
#include <string>
#include <sstream>
using namespace std;

class GLDebug
{
public:
	static GLenum CheckGLError( const char* filename,const char* funcname,int line )
	{
		GLenum errorCode;
		int lim=1;
		while( ( errorCode = glGetError() ) != GL_NO_ERROR && lim>0)
		{
			lim--;
			const char* errorString = GLErrorString(errorCode);

			if( errorString != NULL )
			{
				stringstream ss;
				string s;
				if( errorCode == GL_OUT_OF_MEMORY )
				{
					ss << "OpenGL Error: " << errorString;
					s = ss.str();
					//throw EngineException(s,filename,funcname,line);
				}
				else
				{
					stringstream ss;
					ss << "OpenGL Error: [" << errorString << "] ( in: " << filename << ", " << funcname << ", line " << line << " )\n";
					s = ss.str();
					const char * cs = s.c_str();
					
					
					DEBUGPRINT((s.c_str()));
					
					// HACK: DebugPrint crashes! Therefore hard-coded! // works now? (check above) voodoo
					/*#ifdef _WIN32
						#include <Windows.h>
						OutputDebugStringA( cs );
					#else
						#include <iostream>
						std::cout<<msg;
					#endif*/
				}
			}
		}
		return errorCode;
	}
	static const char* GLErrorString(GLenum code)
	{
		switch (code)
		{
		case GL_NO_ERROR:
			return "GL_NO_ERROR: No error has been recorded. The value of this symbolic constant is guaranteed to be 0.";
		case GL_INVALID_ENUM:
			return "GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument. The offending function is ignored, having no side effect other than to set the error flag.";
		case GL_INVALID_VALUE:
			return "GL_INVALID_VALUE: A numeric argument is out of range. The offending function is ignored, having no side effect other than to set the error flag.";
		case GL_INVALID_OPERATION:
			return "GL_INVALID_OPERATION: The specified operation is not allowed in the current state. The offending function is ignored, having no side effect other than to set the error flag.";
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			return "GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not complete. The offending command is ignored and has no other side effect than to set the error flag.";
		case GL_OUT_OF_MEMORY:
			return "GL_OUT_OF_MEMORY: There is not enough memory left to execute the function. The state of OpenGL is undefined, except for the state of the error flags, after this error is recorded.";
		case GL_STACK_OVERFLOW:
			return "GL_STACK_OVERFLOW: This function would cause a stack overflow. The offending function is ignored, having no side effect other than to set the error flag.";
		case GL_STACK_UNDERFLOW:
			return "GL_STACK_UNDERFLOW: This function would cause a stack underflow. The offending function is ignored, having no side effect other than to set the error flag.";
		default:
			return "Default: Unknown error";
		}
	}
};

#if defined(DEBUG) || defined(_DEBUG)
#define GLErrCheck() GLDebug::CheckGLError(__FILE__,__FUNCTION__,__LINE__)
#else
#define GLErrCheck() ((void*)0)
#endif

#endif //GLDEBUG_H