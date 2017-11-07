#include "HasAttribute.h"

using EasyGumbo::HasAttribute;

HasAttribute::HasAttribute(const std::string& type,
                           const std::string& value) noexcept :
    _type(type),
    _value(value)
{
}

bool HasAttribute::operator()(const GumboNode& node) const noexcept
{
    if (node.type != GUMBO_NODE_ELEMENT)
    {
        return false;
    }

    const GumboVector* vec = &node.v.element.attributes;
    auto attribute = gumbo_get_attribute(vec, _type.c_str());
    if(attribute != nullptr)
    {
        if(_value.empty())
        {
            return true;
        }
        else
        {
            return _value == attribute->value;
        }
    }
    return false;
}
