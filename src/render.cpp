/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Project:     Glesly: my GLES-based rendering library
 * Purpose:     Class to execute one OpenGL program with Objects
 * Author:      György Kövesdi (kgy@teledigit.eu)
 * Licence:     GPL (see file 'COPYING' in the project root for more details)
 * Comments:    
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <GLES2/gl2.h>

#include <glesly/object.h>

#include "render.h"

using namespace Glesly;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                                       *
 *       Class Render:                                                                   *
 *                                                                                       *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

Render::Render(Glesly::CameraMatrix & camera, float aspect):
    myScreenAspect(aspect),
    myCameraMatrix(*this, "camera_matrix", camera)
{
 SYS_DEBUG_MEMBER(DM_GLESLY);
}

Render::~Render()
{
 SYS_DEBUG_MEMBER(DM_GLESLY);
}

void Render::Cleanup(void)
{
 SYS_DEBUG_MEMBER(DM_GLESLY);

 GetObjectList().Cleanup();
}

void Render::NextFrame(const SYS::TimeDelay & frame_start_time)
{
 SYS_DEBUG_MEMBER(DM_GLESLY);

 BeforeFrame();

 UseProgram();

 ActivateVariables();

 Frame(frame_start_time);

 ObjectListPtr p = GetObjectListPtr(); // The pointer is copied here to solve thread safety

 if (p.get()) {
    for (ObjectListIterator i = p->begin(); i != p->end(); ++i) {
        (*i)->NextFrame(frame_start_time);
    }
 }

 UnuseProgram();

 AfterFrame();
}

void Render::MouseClickRaw(int x, int y, int index, int count)
{
 SYS_DEBUG_MEMBER(DM_GLESLY);

 if (IsInputBlocked()) {
    return;
 }

 float horiz = x;
 float vert = y;

 try {
    ConvertMouseCoordinates(horiz, vert);
 } catch(::EX::Assert & ex) {
    DEBUG_OUT("Cannot calculate mouse position because " << ex.what());
    return;
 }

 SYS_DEBUG(DL_INFO2, "Mouse button #" << index << " click #" << count << ", at " << x << "x" << y << " -> " << horiz << "x" << vert);

 ObjectListPtr p = GetObjectListPtr(); // The pointer is copied here to solve thread safety

 if (p) {
    SYS_DEBUG(DL_INFO2, "Having " << p->size() << " objects");
    for (ObjectListIterator i = p->begin(); i != p->end(); ++i) {
       if ((*i)->MouseClick(horiz, vert, index, count)) {
           break;
       }
    }
 }
}

void Render::KeyboardClick(UTF8::WChar key)
{
 SYS_DEBUG_MEMBER(DM_GLESLY);

 if (IsInputBlocked()) {
    return;
 }

 ObjectListPtr p = GetObjectListPtr(); // The pointer is copied here to solve thread safety

 if (p.get()) {
    SYS_DEBUG(DL_INFO2, "Having " << p->size() << " objects");
    for (ObjectListIterator i = p->begin(); i != p->end(); ++i) {
       (*i)->KeyboardClick(key);
    }
 }
}

int Render::GetCallbackTimeLimit(void) const
{
 return 30; // TODO: be configurable!
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                                       *
 *       Class Render3D:                                                                 *
 *                                                                                       *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

Render3D::Render3D(RenderInfo & renderInfo):
    Render(renderInfo.myCamera),
    myRenderInfo(renderInfo),
    myT1Matrix(*this, "t0_matrix", renderInfo.myTransform[0]),
    myT2Matrix(*this, "t1_matrix", renderInfo.myTransform[1]),
    myT3Matrix(*this, "t2_matrix", renderInfo.myTransform[2]),
    myT4Matrix(*this, "t3_matrix", renderInfo.myTransform[3])
{
 SYS_DEBUG_MEMBER(DM_GLESLY);
}

Render3D::~Render3D()
{
 SYS_DEBUG_MEMBER(DM_GLESLY);
}

/* * * * * * * * * * * * * End - of - File * * * * * * * * * * * * * * */
