/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Project:     Glesly: my GLES-based rendering library
 * Purpose:     C++ wrapper for GL/ES - Main class
 * Author:      György Kövesdi (kgy@teledigit.eu)
 * Licence:     GPL (see file 'COPYING' in the project root for more details)
 * Comments:    
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __GLESLY_SRC_GLESLY_MAIN_H_INCLUDED__
#define __GLESLY_SRC_GLESLY_MAIN_H_INCLUDED__

#include <list>

#include <GLES2/gl2.h>

#include <glesly/backend.h>
#include <glesly/render.h>

SYS_DECLARE_MODULE(DM_GLESLY);

namespace Glesly
{
    class Main
    {
     public:
        Main(TargetPtr & target);
        virtual ~Main();

        void Run(void);
        void Clear(void);

        inline void Finish(void)
        {
            myFinished = true;
        }

        virtual void Initialize(void) =0;
        virtual void NextFrame(void) =0;
        virtual void Cleanup(void) =0;

        virtual void WindowSizeChanged(int w, int h) { }

        inline void AddRender(RenderPtr rp)
        {
            myRenders.push_back(rp);
        }

     protected:
        Glesly::Backend myBackend;

     private:
        SYS_DEFINE_CLASS_NAME("Glesly::Main");

        bool myFinished;

        typedef std::list<RenderPtr> RenderList;
        RenderList myRenders;

    }; // class Main

} // namespace Glesly

#endif /* __GLESLY_SRC_GLESLY_MAIN_H_INCLUDED__ */

/* * * * * * * * * * * * * End - of - File * * * * * * * * * * * * * * */
