#include <Geode/Geode.hpp>
#include <Geode/modify/GameOptionsLayer.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(GameOptionsLayer) {
    this->setID("GameOptionsLayer");
}

struct GameOptionsLayerIDs : Modify<GameOptionsLayerIDs, GameOptionsLayer> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("GameOptionsLayer::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set GameOptionsLayer::init hook priority, node IDs may not work properly");
        }
    }

    #ifdef GEODE_IS_WINDOWS
    void setupOptions() { // not 100% if hooking setupOptions is ok but its only thing not inlined.
        log::info("Providing IDs for GameOptionsLayer");
        NodeIDs::get()->provide(this);
        GameOptionsLayer::setupOptions();
    }
    #else
    bool init(GJBaseGameLayer* baseGameLayer) {
        if (!GameOptionsLayer::init(baseGameLayer)) return false;
        NodeIDs::get()->provide(this);
        return true;
    }
    #endif
};