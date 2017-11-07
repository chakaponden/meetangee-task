#include "Tag.h"

using EasyGumbo::Tag;

Tag::Tag(GumboTag tag) noexcept :
    _tag(tag)
{
}

bool Tag::operator()(const GumboNode& node) const noexcept
{
    if (node.type != GUMBO_NODE_ELEMENT)
    {
        return false;
    }
    return node.v.element.tag == _tag;
}
