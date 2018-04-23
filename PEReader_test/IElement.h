#pragma once
#include "IVisitor.h"

namespace pe_parse
{
    struct IElement
    {
        virtual ~IElement() = default;

        virtual void Accept(IVisitor&) = 0;
    };
}