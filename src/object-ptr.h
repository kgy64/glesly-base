/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Project:     Glesly: my GLES-based rendering library
 * Purpose:     C++ wrapper for GL/ES - Smart Pointer for Objects
 * Author:      György Kövesdi (kgy@teledigit.eu)
 * Licence:     GPL (see file 'COPYING' in the project root for more details)
 * Comments:    
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __GLESLY_SRC_OBJECT_PTR_H_INCLUDED__
#define __GLESLY_SRC_OBJECT_PTR_H_INCLUDED__

#include <list>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace Glesly
{
    class ObjectBase;

    typedef boost::weak_ptr<ObjectBase> ObjectWeak;

    class ObjectPtr: public boost::shared_ptr<ObjectBase>
    {
     public:
        ObjectPtr(ObjectBase * obj);

        inline ObjectPtr(boost::shared_ptr<ObjectBase> & obj):
            boost::shared_ptr<ObjectBase>(obj)
        {
        }

        inline ObjectPtr & operator=(boost::shared_ptr<ObjectBase> & obj)
        {
            static_cast<boost::shared_ptr<ObjectBase>&>(*this) = obj;
            return *this;
        }

    }; // ObjectPtr

    typedef std::list<ObjectPtr> Objects;

    typedef Objects::iterator ObjectListIterator;

    typedef boost::shared_ptr<Objects> ObjectListPtr;

} // namespace Glesly

#endif /* __GLESLY_SRC_OBJECT_PTR_H_INCLUDED__ */

/* * * * * * * * * * * * * End - of - File * * * * * * * * * * * * * * */
