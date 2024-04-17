#pragma once

#include "Red/InkSpawner.hpp"

namespace Raw::InkWidgetLibrary
{
constexpr auto AsyncSpawnFromExternal = Core::RawFunc<
    /* addr = */ Red::AddressLib::InkWidgetLibrary_AsyncSpawnFromExternal,
    /* type = */ bool (*)(
        Red::inkWidgetLibraryResource* aLibrary,
        Red::InkSpawningInfo& aSpawningInfo,
        Red::ResourcePath aExternalPath,
        Red::CName aItemName,
        uint8_t aParam)>();

constexpr auto AsyncSpawnFromLocal = Core::RawFunc<
    /* addr = */ Red::AddressLib::InkWidgetLibrary_AsyncSpawnFromLocal,
    /* type = */ bool (*)(
        Red::inkWidgetLibraryResource* aLibrary,
        Red::InkSpawningInfo& aSpawningInfo,
        Red::CName aItemName,
        uint8_t aParam)>();

constexpr auto SpawnFromExternal = Core::RawFunc<
    /* addr = */ Red::AddressLib::InkWidgetLibrary_SpawnFromExternal,
    /* type = */ uintptr_t (*)(
        Red::inkWidgetLibraryResource* aLibrary,
        Red::Handle<Red::inkWidgetLibraryItemInstance>& aInstance,
        Red::ResourcePath aExternalPath,
        Red::CName aItemName)>();

constexpr auto SpawnFromLocal = Core::RawFunc<
    /* addr = */ Red::AddressLib::InkWidgetLibrary_SpawnFromLocal,
    /* type = */ uintptr_t (*)(
        Red::inkWidgetLibraryResource* aLibrary,
        Red::Handle<Red::inkWidgetLibraryItemInstance>& aInstance,
        Red::CName aItemName)>();

constexpr auto SpawnRoot = Core::RawFunc<
    /* addr = */ Red::AddressLib::InkWidgetLibrary_SpawnRoot,
    /* type = */ uintptr_t (*)(
        Red::inkWidgetLibraryResource* aLibrary,
        Red::Handle<Red::inkWidgetLibraryItemInstance>& aInstance)>();
}
