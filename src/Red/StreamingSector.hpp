#pragma once

#include "Red/Addresses.hpp"
#include "Red/Common.hpp"

namespace Red
{
struct StreamingSectorNodeBuffer
{
    uint8_t unk00[0x28];               // 00
    DynArray<Handle<worldNode>> nodes; // 28
    DynArray<NodeRef> nodeRefs;        // 38
};
}

namespace Raw::StreamingSector
{
using NodeBuffer = Core::OffsetPtr<0x40, Red::StreamingSectorNodeBuffer>;

constexpr auto OnReady = Core::RawFunc<
    /* addr = */ Red::Addresses::StreamingSector_OnReady,
    /* type = */ void (*)(Red::worldStreamingSector* aSector, uint64_t a2)>();
}
