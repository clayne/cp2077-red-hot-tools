#pragma once

#include "Core/Foundation/Feature.hpp"
#include "Core/Hooking/HookingAgent.hpp"
#include "Core/Logging/LoggingAgent.hpp"
#include "Red/InkLayer.hpp"
#include "Red/InkLibrary.hpp"
#include "Red/InkSpawner.hpp"
#include "Red/InkSystem.hpp"
#include "Red/InkWidget.hpp"

namespace App
{
struct InkWindowExtendedData
{
    Red::WeakHandle<Red::inkWindow> handle;
    uint64_t hash;
    Red::CName name;
    Red::CName slot;
    Red::WeakHandle<Red::Entity> entity;
};

struct InkLayerExtendedData
{
    Red::WeakHandle<Red::inkLayer> handle;
    uint64_t hash;
    bool isActive;
    bool isInteractive;
    Red::CName inputContext;
    Red::DynArray<InkWindowExtendedData> windows;
};

struct InkWidgetExtendedData
{
    Red::WeakHandle<Red::inkWidget> handle;
    uint64_t hash;
    uint64_t layerHash;
    uint32_t depth;
    bool isInteractive;
};

struct InkWidgetCollectionData
{
    Red::CName layerName;
    Red::WeakHandle<Red::Entity> entity;
    Red::DynArray<InkWidgetExtendedData> widgets;
};

struct InkWidgetSpawnData
{
    Red::CName layerName;
    Red::CName gameControllerName;
    Red::CName inputContext;
    uint64_t libraryPathHash;
    Red::CName libraryItemName;
};

struct InkLibraryItemUserData : Red::inkUserData
{
    uint64_t libraryPathHash;
    Red::CName libraryItemName;
    Red::CName gameControllerName;

    RTTI_IMPL_TYPEINFO(InkLibraryItemUserData);
    RTTI_IMPL_ALLOCATOR();
};

class InkWidgetCollector
    : public Core::Feature
    , public Core::LoggingAgent
    , public Core::HookingAgent
{
public:
    InkWidgetCollector(bool aCompatMode);

    Red::DynArray<InkLayerExtendedData> CollectLayers();
    InkWidgetCollectionData CollectHoveredWidgets();

    void TogglePointerInput(bool aEnabled);
    void TogglePointerInput();
    void EnsurePointerInput();

    InkWidgetSpawnData GetWidgetSpawnInfo(const Red::Handle<Red::inkWidget>& aWidget);

protected:
    void OnBootstrap() override;

    static void OnSpawnRoot(Red::inkWidgetLibraryResource* aLibrary,
                            Red::Handle<Red::inkWidgetLibraryItemInstance>& aInstance);
    static void OnSpawnLocal(Red::inkWidgetLibraryResource* aLibrary,
                             Red::Handle<Red::inkWidgetLibraryItemInstance>& aInstance,
                             Red::CName aItemName);
    static void OnSpawnExternal(Red::inkWidgetLibraryResource* aLibrary,
                                Red::Handle<Red::inkWidgetLibraryItemInstance>& aInstance,
                                Red::ResourcePath aExternalPath,
                                Red::CName aItemName);
    static void OnAsyncSpawnLocal(Red::inkWidgetLibraryResource* aLibrary,
                                  Red::InkSpawningInfo& aSpawningInfo,
                                  Red::CName aItemName,
                                  uint8_t aParam);
    static void OnAsyncSpawnExternal(Red::inkWidgetLibraryResource* aLibrary,
                                     Red::InkSpawningInfo& aSpawningInfo,
                                     Red::ResourcePath aExternalPath,
                                     Red::CName aItemName,
                                     uint8_t aParam);
    static void OnFinishAsyncSpawn(Red::InkSpawningContext& aContext,
                                   Red::Handle<Red::inkWidgetLibraryItemInstance>& aInstance);
    static void OnAttachInstance(Red::inkLayer*,
                                 const Red::Handle<Red::inkWidgetLibraryItemInstance>& aInstance,
                                 const Red::Handle<Red::inkWidgetLibraryResource>& aLibrary);

    static void OnWindowConstruct(Red::inkWindow* aWindow);
    static void OnWindowDestruct(Red::inkWindow* aWindow);
    static void OnWindowToggleInput(Red::inkWindow* aWindow, bool aEnabled);
    static void OnPointerHandlerReset(Red::inkPointerHandler* aHandler, int32_t* aArea);
    static void OnPointerHandlerOverride(Red::inkPointerHandler* aHandler,
                                         const Red::SharedPtr<Red::inkPointerHandler>& aOverride,
                                         int32_t aIndex);
    static void OnWidgetDraw(Red::inkWidget* aWidget, Red::inkWidgetContext& aContext);

    bool CollectHoveredWidgets(Red::DynArray<InkWidgetExtendedData>& aOut,
                               const Red::Vector2& aPointerPosition,
                               const Red::Handle<Red::inkVirtualWindow>& aWindow,
                               const Red::inkHudWidgetSpawnEntry* aHudEntry = nullptr,
                               const Red::Entity* aEntity = nullptr);

    static void AddLibraryItemInstanceData(Red::inkWidgetLibraryResource* aLibrary, Red::CName aItemName,
                                           Red::inkWidgetLibraryItemInstance* aItemInstance);
    static Red::Handle<App::InkLibraryItemUserData> GetLibraryItemInstanceData(const Red::Handle<Red::inkWidget>& aWidget);

    static const Red::SharedPtr<Red::inkPointerHandler>& GetOverriddenPointerHandler(Red::inkWindow* aWindow);
    static const Red::SharedPtr<Red::inkPointerHandler>& GetOverriddenPointerHandler(Red::inkPointerHandler* aHandler);

    static inline Core::Map<Red::inkWindow*, Red::SharedPtr<Red::inkPointerHandler>> s_pointerHandlersByWindow;
    static inline Core::Map<Red::inkPointerHandler*, Red::SharedPtr<Red::inkPointerHandler>> s_pointerHandlersByHandler;
    static inline std::shared_mutex s_pointerHandlerLock;
    static inline bool s_compatMode;
};
}

RTTI_DEFINE_CLASS(App::InkWindowExtendedData, {
    RTTI_PROPERTY(handle);
    RTTI_PROPERTY(hash);
    RTTI_PROPERTY(name);
    RTTI_PROPERTY(slot);
    RTTI_PROPERTY(entity);
});

RTTI_DEFINE_CLASS(App::InkLayerExtendedData, {
    RTTI_PROPERTY(handle);
    RTTI_PROPERTY(hash);
    RTTI_PROPERTY(isActive);
    RTTI_PROPERTY(isInteractive);
    RTTI_PROPERTY(inputContext);
    RTTI_PROPERTY(windows);
});

RTTI_DEFINE_CLASS(App::InkWidgetExtendedData, {
    RTTI_PROPERTY(handle);
    RTTI_PROPERTY(hash);
    RTTI_PROPERTY(layerHash);
    RTTI_PROPERTY(depth);
    RTTI_PROPERTY(isInteractive);
});

RTTI_DEFINE_CLASS(App::InkWidgetCollectionData, {
    RTTI_PROPERTY(layerName);
    RTTI_PROPERTY(entity);
    RTTI_PROPERTY(widgets);
});

RTTI_DEFINE_CLASS(App::InkWidgetSpawnData, {
    RTTI_PROPERTY(layerName);
    RTTI_PROPERTY(gameControllerName);
    RTTI_PROPERTY(inputContext);
    RTTI_PROPERTY(libraryPathHash);
    RTTI_PROPERTY(libraryItemName);
});

RTTI_DEFINE_CLASS(App::InkLibraryItemUserData, {
    RTTI_PARENT(Red::inkUserData);
    RTTI_PROPERTY(libraryPathHash);
    RTTI_PROPERTY(libraryItemName);
    RTTI_PROPERTY(gameControllerName);
});
