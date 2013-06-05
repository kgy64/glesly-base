/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Project:     Glesly: my GLES-based rendering library
 * Purpose:     Class to execute one OpenGL program with Objects
 * Author:      György Kövesdi (kgy@teledigit.eu)
 * Licence:     GPL (see file 'COPYING' in the project root for more details)
 * Comments:    
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <glesly/object.h>

#include "render.h"

using namespace Glesly;

Render::Render()
{
 SYS_DEBUG_MEMBER(DM_GLESLY);
}

Render::~Render()
{
 SYS_DEBUG_MEMBER(DM_GLESLY);
}

void Render::NextFrame(void)
{
 SYS_DEBUG_MEMBER(DM_GLESLY);

 Frame();

 for (Objects::iterator i = myObjects.begin(); i != myObjects.end(); ++i) {
    (*i)->UseProgram();
    (*i)->ActivateVariables();
    (*i)->BufferVariables();
    (*i)->Frame();
    (*i)->UnbufferVariables();
    SYS_DEBUG(DL_INFO3, " - glUseProgram(0);");
    glUseProgram(0);
 }
}

/* * * * * * * * * * * * * End - of - File * * * * * * * * * * * * * * */
