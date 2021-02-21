#ifndef __HOME_SCENE_HPP__
#define __HOME_SCENE_HPP__

#include "cocos2d.h"
#include "Constants.hpp"
#include "Stamp/StampLabel.hpp"

USING_NS_CC;

class HomeScene : public Scene
{
private: /* TITLE */
    StampLabel*             m_titleStampLabel;

private: /* DIFFICULTY */
    GAME_DIFFICULTY         m_difficulty;
    unsigned int            m_totalIndex;
    unsigned int            m_targetIndex;
    StampLabel*             m_difficultyStampLabel;

private: /* PREVIEW CANVAS */
    std::list<StampData>    m_stampDataList;
    DrawNode*               m_previewDrawNode;

private: /* MANUAL */
    StampLabel*             m_tapStampLabel;
    StampLabel*             m_doubleTapStampLabel;

private: /* TOUCH */
    float                   m_touchDelta;
    long                    m_preTime;
    long                    m_postTime;
    bool                    m_isDoubleTap;

public:
    HomeScene();
    virtual ~HomeScene();

    static HomeScene* createScene();
    static HomeScene* create();

    virtual bool init() override;
    virtual void onEnter() override;
    virtual void onExit() override;

public: /* TOOUCH EVENT */
    bool onTouchBegan(Touch* _touch, Event* _event);
    void CheckTab(float delta);
    long GetCurrentDeltaTime();

public: /* DIFFICULTY */
    void ChangeDifficulty(float delta);
    void GenerateStampDataList();
    void DrawPreviewCanvas();
    void ChangePreview(float delta);
};

#endif