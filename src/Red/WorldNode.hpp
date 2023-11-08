#pragma once

namespace Raw::WorldNodeInstance
{
using Node = Core::OffsetPtr<0x60, Red::Handle<Red::worldNode>>;
}

namespace Raw::WorldNodeRegistry
{
constexpr auto FindNode = Core::RawVFunc<
    /* addr = */ 0x190,
    /* type = */ void (Red::worldNodeInstanceRegistry::*)(Red::Handle<Red::worldINodeInstance>& aOut, uint64_t aNodeID)>();
}
