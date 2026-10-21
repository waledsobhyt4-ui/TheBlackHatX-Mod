##include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <Geode/modify/GJBaseGameLayer.hpp>
#include <Geode/binding/PlayerObject.hpp>

using namespace geode::prelude;

// ==================== SETTINGS HELPERS ====================
bool isNoclip() {
    return Mod::get()->getSettingValue<bool>("noclip");
}

bool isInfinityJump() {
    return Mod::get()->getSettingValue<bool>("infinity-jump");
}

bool isBot() {
    return Mod::get()->getSettingValue<bool>("bot");
}

int getBotInterval() {
    return Mod::get()->getSettingValue<int64_t>("bot-interval");
}

bool showIndicators() {
    return Mod::get()->getSettingValue<bool>("show-indicators");
}

// ==================== STATUS INDICATOR ====================
static const int INDICATOR_TAG = 884422;

void updateIndicators(CCNode* layer) {
    if (!layer || !showIndicators()) return;

    auto existing = layer->getChildByTag(INDICATOR_TAG);
    if (existing) existing->removeFromParent();

    auto label = CCLabelBMFont::create("", "bigFont.fnt");
    label->setAnchorPoint({1.f, 1.f});
    label->setScale(0.35f);
    label->setPosition({
        CCDirector::get()->getWinSize().width - 8.f,
        CCDirector::get()->getWinSize().height - 8.f
    });
    label->setZOrder(99999);
    label->setTag(INDICATOR_TAG);

    std::string text;
    if (isNoclip()) text += "NC ";
    if (isInfinityJump()) text += "IJ ";
    if (isBot()) text += "BOT ";
    if (text.empty()) text = "OFF";

    label->setString(text.c_str());
    label->setColor(text == "OFF" ? ccc3(255, 80, 80) : ccc3(80, 255, 120));
    layer->addChild(label);
}

// ==================== NOCLIP ====================
class $modify(TBHX_PlayLayer, PlayLayer) {
    void destroyPlayer(PlayerObject* player, GameObject* obj) {
        if (isNoclip()) {
            // Skip death completely
            return;
        }
        PlayLayer::destroyPlayer(player, obj);
    }

    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects))
            return false;

        updateIndicators(this);
        return true;
    }

    void resetLevel() {
        PlayLayer::resetLevel();
        updateIndicators(this);
    }
};

// ==================== INFINITY JUMP ====================
class $modify(TBHX_PlayerObject, PlayerObject) {
    // Force the player to be able to jump even in air
    void pushButton(PlayerButton btn) {
        if (isInfinityJump() && btn == PlayerButton::Jump) {
            // Temporarily force on ground so jump works
            bool wasOnGround = m_isOnGround;
            m_isOnGround = true;
            PlayerObject::pushButton(btn);
            m_isOnGround = wasOnGround;
            return;
        }
        PlayerObject::pushButton(btn);
    }
};

// ==================== SIMPLE BOT (Auto Jump) ====================
class $modify(TBHX_GJBaseGameLayer, GJBaseGameLayer) {
    struct Fields {
        float m_botTimer = 0.f;
        bool m_botHolding = false;
    };

    void update(float dt) {
        GJBaseGameLayer::update(dt);

        if (!isBot()) {
            m_fields->m_botTimer = 0.f;
            if (m_fields->m_botHolding) {
                // Release if we were holding
                this->handleButton(false, 1, true); // Jump button, player 1
                m_fields->m_botHolding = false;
            }
            return;
        }

        // Simple spam click bot
        float interval = getBotInterval() / 1000.f; // ms → seconds
        m_fields->m_botTimer += dt;

        if (m_fields->m_botTimer >= interval) {
            m_fields->m_botTimer = 0.f;

            if (m_fields->m_botHolding) {
                // Release
                this->handleButton(false, 1, true);
                m_fields->m_botHolding = false;
            } else {
                // Press
                this->handleButton(true, 1, true);
                m_fields->m_botHolding = true;
            }
        }
    }
};

// ==================== LOAD LOG ====================
$on_mod(Loaded) {
    log::info("waledsobhyt4-ui by WaledSobhYT loaded!");
    log::info("Noclip / Infinity Jump / Bot ready");
}

