/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Project:     
 * Purpose:     
 * Author:      
 * License:     GPL (see file 'COPYING' in the project root for more details)
 * Comments:    
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "sphere.h"

#include <glesly/read-tga.h>

using namespace Glesly;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                                       *
 *     class Glesly::SphereBitmaps:                                                      *
 *                                                                                       *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void SphereBitmaps::reset(int size, Glesly::PixelFormat format)
{
 SYS_DEBUG_MEMBER(DM_GLESLY);

 if (myFormat == Glesly::FORMAT_DEFAULT) {
    myFormat = format;
 }

 if (myFormat == Glesly::FORMAT_DEFAULT) {
    myFormat = Glesly::FORMAT_RGB_565;
 }

 if (!texture_0 || texture_0->GetPixelFormat() != myFormat || texture_0->GetWidth() != size || texture_0->GetHeight() != size) {
    texture_0 = PaCaLib::Target::Create(size, size, myFormat);
 }
 if (!texture_1 || texture_1->GetPixelFormat() != myFormat || texture_1->GetWidth() != size || texture_1->GetHeight() != size) {
    texture_1 = PaCaLib::Target::Create(size, size, myFormat);
 }
 if (!texture_2 || texture_2->GetPixelFormat() != myFormat || texture_2->GetWidth() != size || texture_2->GetHeight() != size) {
    texture_2 = PaCaLib::Target::Create(size, size, myFormat);
 }
 if (!texture_3 || texture_3->GetPixelFormat() != myFormat || texture_3->GetWidth() != size || texture_3->GetHeight() != size) {
    texture_3 = PaCaLib::Target::Create(size, size, myFormat);
 }
 if (!texture_4 || texture_4->GetPixelFormat() != myFormat || texture_4->GetWidth() != size || texture_4->GetHeight() != size) {
    texture_4 = PaCaLib::Target::Create(size, size, myFormat);
 }
 if (!texture_5 || texture_5->GetPixelFormat() != myFormat || texture_5->GetWidth() != size || texture_5->GetHeight() != size) {
    texture_5 = PaCaLib::Target::Create(size, size, myFormat);
 }

 textureTargets[0] = &*texture_0;
 textureTargets[1] = &*texture_1;
 textureTargets[2] = &*texture_2;
 textureTargets[3] = &*texture_3;
 textureTargets[4] = &*texture_4;
 textureTargets[5] = &*texture_5;
}

void SphereBitmaps::reset(const char * const * filenames)
{
 SYS_DEBUG_MEMBER(DM_GLESLY);

 if (!filenames) {
    return;
 }

 int size = 0;

 reset(texture_0, filenames[0], size);
 reset(texture_1, filenames[1], size);
 reset(texture_2, filenames[2], size);
 reset(texture_3, filenames[3], size);
 reset(texture_4, filenames[4], size);
 reset(texture_5, filenames[5], size);

 textureTargets[0] = &*texture_0;
 textureTargets[1] = &*texture_1;
 textureTargets[2] = &*texture_2;
 textureTargets[3] = &*texture_3;
 textureTargets[4] = &*texture_4;
 textureTargets[5] = &*texture_5;
}

void SphereBitmaps::reset(PaCaLib::TargetPtr & target, const char * name, int & size)
{
 SYS_DEBUG_MEMBER(DM_GLESLY);

 if (!name) {
    return;
 }

 Glesly::ReadTGA tga(name);

 if (!size) {
    size = tga.GetWidth();
 }

 ASSERT(tga.GetWidth() == size && tga.GetHeight() == size, "got a texture ('" << name << "') with wrong size: " << tga.GetWidth() << "x" << tga.GetHeight() << ", instead of " << size << "x" << size);

 if (myFormat == Glesly::FORMAT_DEFAULT) {
    myFormat = tga.GetPixelFormat();
 } else {
    ASSERT(tga.GetPixelFormat() == myFormat, "got a texture ('" << name << "') with wrong format " << tga.GetPixelFormat() << ", instead of " << myFormat);
 }

 if (!target || target->GetPixelFormat() != myFormat) {
    target = PaCaLib::Target::Create(size, size, myFormat);
 }

 *target = tga;
}

/* * * * * * * * * * * * * End - of - File * * * * * * * * * * * * * * */