#include "Gumbo.h"

using EasyGumbo::Gumbo;

Gumbo::Gumbo(const char* buffer) noexcept
{
    auto output = gumbo_parse(buffer);
    _output = std::shared_ptr<GumboOutput>(output, [](GumboOutput* obj)
    {
        gumbo_destroy_output(&kGumboDefaultOptions, obj);
    });
}

Gumbo::operator bool() const noexcept
{
    return _output != nullptr;
}

GumboOutput* Gumbo::Output() const noexcept
{
    return _output.get();
}

EasyGumbo::DFSIterator Gumbo::Begin() noexcept
{
    return EasyGumbo::DFSIterator(_output->document);
}

EasyGumbo::DFSIterator Gumbo::End() noexcept
{
    return EasyGumbo::DFSIterator();
}
