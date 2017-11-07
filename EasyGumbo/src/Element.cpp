#include "Element.h"

#include <cassert>

using EasyGumbo::Element;

Element::Element(GumboNode& element) noexcept :
    _node(element)
{
    assert(GUMBO_NODE_ELEMENT == _node.type);
}

EasyGumbo::Vector<GumboNode*> Element::Children() const noexcept
{
    return EasyGumbo::Vector<GumboNode*>(_node.v.element.children);
}

const GumboSourcePosition& Element::Start() const noexcept
{
    return _node.v.element.start_pos;
}

const GumboSourcePosition& Element::End() const noexcept
{
    return _node.v.element.end_pos;
}

const GumboAttribute* Element::Attribute(const char* name) const noexcept
{
    return gumbo_get_attribute(&_node.v.element.attributes, name);
}
