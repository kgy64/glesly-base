/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Project:     Glesly: my GLES-based rendering library
 * Purpose:     Interface for bitmap targets
 * Author:      György Kövesdi (kgy@teledigit.eu)
 * Licence:     GPL (see file 'COPYING' in the project root for more details)
 * Comments:    
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __GLESLY_SRC_TARGET_BASE_H_INCLUDED__
#define __GLESLY_SRC_TARGET_BASE_H_INCLUDED__

#include <glesly/format.h>
#include <Debug/Debug.h>

SYS_DECLARE_MODULE(DM_GLESLY);

namespace Glesly
{
    class Target2D
    {
     protected:
        inline Target2D(void)
        {
            SYS_DEBUG_MEMBER(DM_GLESLY);
        }

     public:
        virtual ~Target2D()
        {
            SYS_DEBUG_MEMBER(DM_GLESLY);
        }

        virtual Target2D & operator=(const Target2D & other);

        virtual int GetWidth(void) const =0;
        virtual int GetHeight(void) const =0;
        virtual const void * GetPixelData(void) const =0;
        virtual Glesly::PixelFormat GetPixelFormat(void) const =0;

     private:
        SYS_DEFINE_CLASS_NAME("Glesly::Target2D");

    }; // class Glesly::Target2D

} // namespace Glesly

#endif /* __GLESLY_SRC_TARGET_BASE_H_INCLUDED__ */

/* * * * * * * * * * * * * End - of - File * * * * * * * * * * * * * * */
