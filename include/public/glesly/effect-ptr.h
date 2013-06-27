/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Project:     Glesly: my GLES-based rendering library
 * Purpose:     Specific smart pointers for layer transition classes
 * Author:      György Kövesdi (kgy@teledigit.eu)
 * Licence:     GPL (see file 'COPYING' in the project root for more details)
 * Comments:    
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __GLESLY_INCLUDE_PUBLIC_GLESLY_EFFECT_PTR_H_INCLUDED__
#define __GLESLY_INCLUDE_PUBLIC_GLESLY_EFFECT_PTR_H_INCLUDED__

#include <boost/shared_ptr.hpp>
#include <stack>

namespace Glesly
{
    class LayerChangeEffectBase;

    typedef boost::shared_ptr<LayerChangeEffectBase> LayerEffectPtr;

    typedef std::stack<LayerEffectPtr> ObjectLayerStack;

    class LayerEffectCreatorBase;

    typedef boost::shared_ptr<LayerEffectCreatorBase> LayerCreatorPtr;

}; // namespace Glesly

#endif /* __GLESLY_INCLUDE_PUBLIC_GLESLY_EFFECT_PTR_H_INCLUDED__ */

/* * * * * * * * * * * * * End - of - File * * * * * * * * * * * * * * */
