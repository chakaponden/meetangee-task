#include "DFSIterator.h"

#include <cassert>

using EasyGumbo::DFSIterator;

DFSIterator::DFSIterator(const DFSIterator& value) noexcept :
    _nodeStart(value._nodeStart),
    _nodeCurrent(value._nodeCurrent)
{
}

DFSIterator::DFSIterator(GumboNode* node) noexcept :
    _nodeStart(node),
    _nodeCurrent(node)
{
}

bool DFSIterator::GotoFirstChildren() noexcept
{
    assert(_nodeCurrent != nullptr);

    switch (_nodeCurrent->type)
    {
        case GUMBO_NODE_ELEMENT:
            return GotoChildren(_nodeCurrent->v.element.children, 0);
        case GUMBO_NODE_DOCUMENT:
            return GotoChildren(_nodeCurrent->v.document.children, 0);
        default:
            return false;
    }
}

bool DFSIterator::GotoChildren(const GumboVector& vector, size_t index) noexcept
{
    assert(_nodeCurrent != nullptr);

    if ((vector.length) != 0 && (index < vector.length))
    {
        _nodeCurrent = static_cast<GumboNode*>(vector.data[index]);
        return true;
    }
    return false;
}

bool DFSIterator::GotoAdj() noexcept
{
    if (_nodeCurrent == _nodeStart || _nodeCurrent == nullptr)
    {
        return false;
    }

    const GumboNode* parent = _nodeCurrent->parent;
    const size_t nextIndex = _nodeCurrent->index_within_parent + 1;

    switch (parent->type)
    {
        case GUMBO_NODE_ELEMENT:
            return GotoChildren(parent->v.element.children, nextIndex);
        case GUMBO_NODE_DOCUMENT:
            return GotoChildren(parent->v.document.children, nextIndex);
        default:
            return false;
    }
}

DFSIterator DFSIterator::FromCurrent() const noexcept
{
    return DFSIterator(_nodeCurrent);
}

bool DFSIterator::operator!=(const DFSIterator& obj) const noexcept
{
    return (_nodeCurrent != obj._nodeCurrent);
}

bool DFSIterator::operator==(const DFSIterator& obj) const noexcept
{
    return (_nodeCurrent == obj._nodeCurrent);
}

DFSIterator &DFSIterator::operator++() noexcept
{
    if(_nodeCurrent == nullptr)
    {
        return *this;
    }

    if(!GotoFirstChildren())
    {
        // goto neighboring tree node
        while(!GotoAdj())
        {
            // if unsuccessful - goto up of tree
            // maybe somewhere branch there
            _nodeCurrent = _nodeCurrent->parent;
            if(_nodeCurrent == _nodeStart)
            {
                // finish pass in depth
                _nodeCurrent = nullptr;
                break;
            }
        }
    }
    return *this;
}

DFSIterator DFSIterator::operator++(int) noexcept
{
    DFSIterator tmp(*this);
    operator++();
    return tmp;
}

GumboNode* DFSIterator::operator->() noexcept
{
    return _nodeCurrent;
}

GumboNode& DFSIterator::operator*() noexcept
{
    return *_nodeCurrent;
}
