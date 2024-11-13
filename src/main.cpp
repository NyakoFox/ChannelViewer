/**
 * Include the Geode headers.
 */
#include <Geode/Geode.hpp>
/**
 * Required to modify the MenuLayer class
 */
#include <Geode/modify/GJBaseGameLayer.hpp>
#include <Geode/modify/UILayer.hpp>

/**
 * Brings cocos2d and all Geode namespaces 
 * to the current scope.
 */
using namespace geode::prelude;

/**
 * `$modify` lets you extend and modify GD's 
 * classes; to hook a function in Geode, 
 * simply $modify the class and write a new 
 * function definition with the signature of 
 * the one you want to hook.
 */
class $modify(GJBaseGameLayer) {
    void update(float dt) {
        GJBaseGameLayer::update(dt);

        if (!Mod::get()->getSettingValue<bool>("channelviewer-enabled"))
        {
            return;
        }

        // Grab UI Layer
        auto uiLayer = this->getChildByID("UILayer");
        if (uiLayer) {
            // Grab the text label
            CCLabelBMFont* text = (CCLabelBMFont*) uiLayer->getChildByID("channelid");
            if (text) {
                // Set the text to the channel ID
                text->setString(("Channel: " + std::to_string(this->m_gameState.m_currentChannel)).c_str());
            }
        }
    }
};

class $modify(UILayer) {
    struct Fields {
        CCLabelBMFont* text = nullptr;
    };

    bool init(GJBaseGameLayer* layer) {
        if (!UILayer::init(layer)) return false;

        auto director = CCDirector::sharedDirector();
        float screenTop = director->getScreenTop();

        m_fields->text = CCLabelBMFont::create("", "bigFont.fnt");

        m_fields->text->setID("channelid");
        m_fields->text->setScale(0.4f);
        m_fields->text->setPosition(5, (int)(screenTop - 2));
        m_fields->text->setAnchorPoint({ 0, 1 });
        m_fields->text->setColor({ 255, 255, 255 });
        m_fields->text->setOpacity(64);
        m_fields->text->setZOrder(999);

        this->addChild(m_fields->text);
        this->updateLayout();

        this->scheduleUpdate();

        return true;
    }
};
