#ifdef _WINDOWS
#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>
#endif

#include <stdio.h>
#define GL_GLEXT_PROTOTYPES 1
#include "GL/gl.h"
#include "GL/glext.h"
#include "SDL.h"

typedef WINGDIAPI const GLubyte * (APIENTRYP PFNGLGETINTEGERVPROC) (GLenum pname, GLint *params);
typedef WINGDIAPI const GLubyte * (APIENTRYP PFNGLGETSTRINGPROC) (GLenum name);

int main(int argc, char **argv)
{
    GLint val = 0;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_LoadLibrary(NULL);
    SDL_SetVideoMode(640, 480, 0, SDL_OPENGL);

    PFNGLGETSTRINGPROC pglGetString = (PFNGLGETSTRINGPROC) SDL_GL_GetProcAddress("glGetString");
    PFNGLGETINTEGERVPROC pglGetIntegerv = (PFNGLGETINTEGERVPROC) SDL_GL_GetProcAddress("glGetIntegerv");
    PFNGLGETPROGRAMIVARBPROC pglGetProgramivARB = (PFNGLGETPROGRAMIVARBPROC) SDL_GL_GetProcAddress("glGetProgramivARB");

    printf("Basic strings...\n\n");

    #define getval(x) printf(#x ": %s\n", pglGetString(x))

    getval(GL_RENDERER);
    getval(GL_VERSION);
    getval(GL_VENDOR);

    #undef getval

    printf("\nExtensions...\n\n");

    const GLubyte *ext = pglGetString(GL_EXTENSIONS);
    while (*ext)
    {
        fputc((*ext == ' ') ? '\n' : ((int) *ext), stdout);
        ext++;
    } // while

    ext--;
    if (*ext != ' ')
        printf("\n");

    printf("\nARB1 values...\n\n");

    if (pglGetProgramivARB == NULL)
        printf("  (unsupported.)\n");
    else
    {
        #define getval(x) \
            val = -1; \
            pglGetProgramivARB(GL_VERTEX_PROGRAM_ARB, x, &val); \
            printf(#x ": %d\n", (int) val);

        getval(GL_MAX_PROGRAM_INSTRUCTIONS_ARB);
        getval(GL_MAX_PROGRAM_NATIVE_INSTRUCTIONS_ARB);
        getval(GL_MAX_PROGRAM_TEMPORARIES_ARB);
        getval(GL_MAX_PROGRAM_NATIVE_TEMPORARIES_ARB);
        getval(GL_MAX_PROGRAM_PARAMETERS_ARB);
        getval(GL_MAX_PROGRAM_NATIVE_PARAMETERS_ARB);
        getval(GL_MAX_PROGRAM_ATTRIBS_ARB);
        getval(GL_MAX_PROGRAM_NATIVE_ATTRIBS_ARB);
        getval(GL_MAX_PROGRAM_ADDRESS_REGISTERS_ARB);
        getval(GL_MAX_PROGRAM_NATIVE_ADDRESS_REGISTERS_ARB);
        getval(GL_MAX_PROGRAM_LOCAL_PARAMETERS_ARB);
        getval(GL_MAX_PROGRAM_ENV_PARAMETERS_ARB);
        getval(GL_MAX_PROGRAM_PARAMETERS_ARB);

        #undef getval
    } // else

    printf("\nGLSL values...\n\n");

    #define getval(x) \
        val = -1; \
        pglGetIntegerv(x, &val); \
        printf(#x ": %d\n", (int) val);

    getval(GL_MAX_VERTEX_UNIFORM_COMPONENTS_ARB);
    getval(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS_ARB);
    getval(GL_MAX_VERTEX_UNIFORM_COMPONENTS_ARB);
	getval(GL_MAX_VARYING_FLOATS_ARB);
	getval(GL_MAX_VERTEX_ATTRIBS_ARB);
	getval(GL_MAX_TEXTURE_IMAGE_UNITS_ARB);
	getval(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS_ARB);
	getval(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS_ARB);
	getval(GL_MAX_TEXTURE_COORDS_ARB);

    #undef getval

    SDL_Quit();
    printf("\n");

    return 0;
}


