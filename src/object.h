/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Project:     Glesly: my GLES-based rendering library
 * Purpose:     Generic OpenGL object classes
 * Author:      György Kövesdi (kgy@teledigit.eu)
 * Licence:     GPL (see file 'COPYING' in the project root for more details)
 * Comments:    
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __GLESLY_SRC_OBJECT_H_INCLUDED__
#define __GLESLY_SRC_OBJECT_H_INCLUDED__

#include <glesly/render.h>
#include <glesly/texture.h>
#include <glesly/shader-ptr.h>
#include <glesly/object-ptr.h>
#include <glesly/math/matrix.h>
#include <glesly/shader-uniforms.h>
#include <glesly/shader-attribs.h>

namespace Glesly
{
    class Object: public Glesly::Shaders::VarManager
    {
        class UniformList;
        class VBOAttribBase;

        friend class UniformList;
        friend class VBOAttribBase;
        friend ObjectPtr;

     public:
        inline GLint GetUniformLocation(const char * name) const
        {
            return GetProgram().GetUniformLocation(name);
        }

        virtual GLint GetUniformLocationSafe(const char * name) const
        {
            return GetProgram().GetUniformLocationSafe(name);
        }

        inline GLint GetAttribLocation(const char * name) const
        {
            return GetProgram().GetAttribLocation(name);
        }

        inline GLint GetAttribLocationSafe(const char * name) const
        {
            return GetProgram().GetAttribLocationSafe(name);
        }

        /// Removes this class from the parent
        /*! 
         *  \warning Do not call it from destructor, it is not necessary and leads to creash! */
        inline void Destroy(void)
        {
            GetProgram().Remove(myIter);
        }

     protected:
        Object(Render & renderer);
        virtual ~Object();

        ObjectWeak mySelf;

        inline void Register(void)
        {
            ObjectPtr me = mySelf.lock();
            myIter = GetProgram().Add(me);
        }

        void DrawArrays(GLenum mode, GLint first, GLsizei count);
        void DrawElements(GLenum mode, GLsizei count);

        inline Render & GetProgram(void)
        {
            return myProgram;
        }

        inline const Render & GetProgram(void) const
        {
            return myProgram;
        }

     public:
        void NextFrame(void);

        Glesly::Transformation & GetProjection(void)
        {
            return myProjection;
        }

     private:
        SYS_DEFINE_CLASS_NAME("Glesly::Object");

        Render::Objects::iterator myIter;

        virtual void Frame(void) { };

        Render & myProgram;

        /// The object's Projection Matrix
        Glesly::Transformation myProjection;

        Glesly::Shaders::UniformMatrix_ref<float, 4> p_matrix;

    }; // class Object

} // namespace Glesly

#endif /* __GLESLY_SRC_OBJECT_H_INCLUDED__ */

/* * * * * * * * * * * * * End - of - File * * * * * * * * * * * * * * */
