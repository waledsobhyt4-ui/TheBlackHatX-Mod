#include <Geode/Geode.hpp>
using namespace geode::prelude;

$on_mod(Loaded) {
    log::info("TheBlackHatX Mod loaded!");
    FLAlertLayer::create(
        "TheBlackHatX",
        "The mod was loaded successfully!",
        "OK"
    )->show();
}
