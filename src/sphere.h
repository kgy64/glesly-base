/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Project:     
 * Purpose:     
 * Author:      
 * License:     GPL (see file 'COPYING' in the project root for more details)
 * Comments:    
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __SRC_SPHERE_H_INCLUDED__
#define __SRC_SPHERE_H_INCLUDED__

#include <pacalib/pacalib.h>
#include <glesly/surfaced-icosahedron.h>
#include <Debug/Debug.h>

SYS_DECLARE_MODULE(DM_GLESLY);

namespace Glesly
{
    class SphereBitmaps
    {
     protected:
        inline SphereBitmaps(int size, Glesly::PixelFormat format = Glesly::FORMAT_DEFAULT):
            textureTargets { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr },
            myFormat(format)
        {
            if (size) {
                reset(size, format);
            }
        }

        PaCaLib::TargetPtr texture_0;
        PaCaLib::TargetPtr texture_1;
        PaCaLib::TargetPtr texture_2;
        PaCaLib::TargetPtr texture_3;
        PaCaLib::TargetPtr texture_4;
        PaCaLib::TargetPtr texture_5;

        Glesly::Target2D * textureTargets[6];

        Glesly::PixelFormat myFormat;

     public:
        void reset(int size, Glesly::PixelFormat format = Glesly::FORMAT_DEFAULT);
        void reset(const char * const * filenames);

     private:
        SYS_DEFINE_CLASS_NAME("Glesly::SphereBitmaps");

        void reset(PaCaLib::TargetPtr & target, const char * name, int & size);

    }; // class Glesly::SphereBitmaps

    template <int resolution = 0>
    class Sphere: public SphereBitmaps, public Glesly::SurfacedIcosahedron<resolution>
    {
        typedef Glesly::SurfacedIcosahedron<resolution> super;

     protected:
        Sphere(Glesly::Render & render, float radius, int size):
            SphereBitmaps(size),
            super(render, radius)
        {
            SYS_DEBUG_MEMBER(DM_GLESLY);
        }

     public:
        inline static Glesly::ObjectPtr Create(Glesly::Render & render, float radius, int size = 0)
        {
            return (new Sphere(render, radius, size))->ObjectBase::Create();
        }

        virtual ~Sphere()
        {
            SYS_DEBUG_MEMBER(DM_GLESLY);
        }

     private:
        SYS_DEFINE_CLASS_NAME("Glesly::Sphere");

        virtual const Glesly::Target2D * const * getTargets(void) const override
        {
            return textureTargets;
        }

    }; // class Glesly::Sphere

} // namespace Glesly

#endif /* __SRC_SPHERE_H_INCLUDED__ */

/* * * * * * * * * * * * * End - of - File * * * * * * * * * * * * * * */