/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Project:     Glesly: my GLES-based rendering library
 * Purpose:     Class to execute one OpenGL program with Objects
 * Author:      György Kövesdi (kgy@teledigit.eu)
 * Licence:     GPL (see file 'COPYING' in the project root for more details)
 * Comments:    
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __GLESLY_SRC_RENDER_H_INCLUDED__
#define __GLESLY_SRC_RENDER_H_INCLUDED__

#include <list>

#include <glesly/camera.h>
#include <glesly/program.h>
#include <glesly/object-list.h>
#include <glesly/render-ptr.h>
#include <glesly/shader-uniforms.h>

namespace Glesly
{
    /// An OpenGL program with Objects
    class Render: public Glesly::Program, public Glesly::ObjectListBase
    {
     public:
        virtual ~Render();

        inline Glesly::CameraMatrix & GetCamera(void)
        {
            return myCamera;
        }

        void NextFrame(void);

        virtual void MouseClickRaw(int x, int y, int index, int count);
        virtual void Initialize(void) { }
        virtual void Cleanup(void) { }

     protected:
        Render(void);

        virtual void ConvertMouseCoordinates(float & x, float & y) { }

     private:
        SYS_DEFINE_CLASS_NAME("Glesly::Render");

        virtual void Frame(void) { }

        Glesly::CameraMatrix myCamera;

        Shaders::UniformMatrix_ref<float, 4> myCameraMatrix;

    }; // class Render

}; // namespace Glesly

#define USE_VERTEX_SHADER(name) Attach(Shader::Create(GL_VERTEX_SHADER, Glesly::Shaders::name))
#define USE_FRAGMENT_SHADER(name) Attach(Shader::Create(GL_FRAGMENT_SHADER, Glesly::Shaders::name))

#endif /* __GLESLY_SRC_RENDER_H_INCLUDED__ */

/* * * * * * * * * * * * * End - of - File * * * * * * * * * * * * * * */
