
#include <GFSDK_SSAO.h>
#include <glad/glad.h>

#undef glActiveTexture
#undef glAttachShader
#undef glBindBuffer
#undef glBindBufferBase
#undef glBindFramebuffer
#undef glBindFragDataLocation
#undef glBindTexture
#undef glBindVertexArray
#undef glBlendColor
#undef glBlendEquationSeparate
#undef glBlendFuncSeparate
#undef glBufferData
#undef glBufferSubData
#undef glColorMaski
#undef glCompileShader
#undef glCreateShader
#undef glCreateProgram
#undef glDeleteBuffers
#undef glDeleteFramebuffers
#undef glDeleteProgram
#undef glDeleteShader
#undef glDeleteTextures
#undef glDeleteVertexArrays
#undef glDisable
#undef glDrawBuffers
#undef glEnable
#undef glDrawArrays
#undef glFramebufferTexture
#undef glFramebufferTexture2D
#undef glFramebufferTextureLayer
#undef glGenBuffers
#undef glGenFramebuffers
#undef glGenTextures
#undef glGenVertexArrays
#undef glGetError
#undef glGetBooleani_v
#undef glGetFloatv
#undef glGetIntegerv
#undef glGetIntegeri_v
#undef glGetProgramiv
#undef glGetProgramInfoLog
#undef glGetShaderiv
#undef glGetShaderInfoLog
#undef glGetString
#undef glGetUniformBlockIndex
#undef glGetUniformLocation
#undef glGetTexLevelParameteriv
#undef glIsEnabled
#undef glIsEnabledi
#undef glLinkProgram
#undef glPolygonOffset
#undef glShaderSource
#undef glTexImage2D
#undef glTexImage3D
#undef glTexParameteri
#undef glTexParameterfv
#undef glUniform1i
#undef glUniformBlockBinding
#undef glUseProgram
#undef glViewport


void GFSDK_SSAO_STDCALL NVglShaderSource(GLuint shader, GLsizei count, const GLchar* const* strings, const GLint* lengths)
{
	GLchar ** m_strings = new GLchar *[count];
	for (int i = 0; i < count; ++ i)
	{
		size_t const length = (lengths ? lengths[i] : strlen(strings[i]));
		m_strings[i] = new GLchar[length + 1]();
		memcpy(m_strings[i], strings[i], length * sizeof(GLchar));
	}
	glad_glShaderSource(shader, count, (const GLchar **) m_strings, lengths);
}

GFSDK_SSAO_GLFunctions ionGetNVGLFunctions()
{
	GFSDK_SSAO_GLFunctions functions;

	functions.glActiveTexture = glad_glActiveTexture;
	functions.glAttachShader = glad_glAttachShader;
	functions.glBindBuffer = glad_glBindBuffer;
	functions.glBindBufferBase = glad_glBindBufferBase;
	functions.glBindFramebuffer = glad_glBindFramebuffer;
	functions.glBindFragDataLocation = glad_glBindFragDataLocation;
	functions.glBindTexture = glad_glBindTexture;
	functions.glBindVertexArray = glad_glBindVertexArray;
	functions.glBlendColor = glad_glBlendColor;
	functions.glBlendEquationSeparate = glad_glBlendEquationSeparate;
	functions.glBlendFuncSeparate = glad_glBlendFuncSeparate;
	functions.glBufferData = glad_glBufferData;
	functions.glBufferSubData = glad_glBufferSubData;
	functions.glColorMaski = glad_glColorMaski;
	functions.glCompileShader = glad_glCompileShader;
	functions.glCreateShader = glad_glCreateShader;
	functions.glCreateProgram = glad_glCreateProgram;
	functions.glDeleteBuffers = glad_glDeleteBuffers;
	functions.glDeleteFramebuffers = glad_glDeleteFramebuffers;
	functions.glDeleteProgram = glad_glDeleteProgram;
	functions.glDeleteShader = glad_glDeleteShader;
	functions.glDeleteTextures = glad_glDeleteTextures;
	functions.glDeleteVertexArrays = glad_glDeleteVertexArrays;
	functions.glDisable = glad_glDisable;
	functions.glDrawBuffers = glad_glDrawBuffers;
	functions.glEnable = glad_glEnable;
	functions.glDrawArrays = glad_glDrawArrays;
	functions.glFramebufferTexture = glad_glFramebufferTexture;
	functions.glFramebufferTexture2D = glad_glFramebufferTexture2D;
	functions.glFramebufferTextureLayer = glad_glFramebufferTextureLayer;
	functions.glGenBuffers = glad_glGenBuffers;
	functions.glGenFramebuffers = glad_glGenFramebuffers;
	functions.glGenTextures = glad_glGenTextures;
	functions.glGenVertexArrays = glad_glGenVertexArrays;
	functions.glGetError = glad_glGetError;
	functions.glGetBooleani_v = glad_glGetBooleani_v;
	functions.glGetFloatv = glad_glGetFloatv;
	functions.glGetIntegerv = glad_glGetIntegerv;
	functions.glGetIntegeri_v = glad_glGetIntegeri_v;
	functions.glGetProgramiv = glad_glGetProgramiv;
	functions.glGetProgramInfoLog = glad_glGetProgramInfoLog;
	functions.glGetShaderiv = glad_glGetShaderiv;
	functions.glGetShaderInfoLog = glad_glGetShaderInfoLog;
	functions.glGetString = glad_glGetString;
	functions.glGetUniformBlockIndex = glad_glGetUniformBlockIndex;
	functions.glGetUniformLocation = glad_glGetUniformLocation;
	functions.glGetTexLevelParameteriv = glad_glGetTexLevelParameteriv;
	functions.glIsEnabled = glad_glIsEnabled;
	functions.glIsEnabledi = glad_glIsEnabledi;
	functions.glLinkProgram = glad_glLinkProgram;
	functions.glPolygonOffset = glad_glPolygonOffset;
	functions.glShaderSource = NVglShaderSource;
	functions.glTexImage2D = glad_glTexImage2D;
	functions.glTexImage3D = glad_glTexImage3D;
	functions.glTexParameteri = glad_glTexParameteri;
	functions.glTexParameterfv = glad_glTexParameterfv;
	functions.glUniform1i = glad_glUniform1i;
	functions.glUniformBlockBinding = glad_glUniformBlockBinding;
	functions.glUseProgram = glad_glUseProgram;
	functions.glViewport = glad_glViewport;

	return functions;
}
