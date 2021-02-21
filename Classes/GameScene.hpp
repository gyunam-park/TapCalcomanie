#ifndef __GAME_SCENE_HPP__
#define __GAME_SCENE_HPP__

#include "cocos2d.h"
#include "Constants.hpp"
#include "Stamp/StampLabel.hpp"

USING_NS_CC;

class GameScene : public Scene
{
private: /* DIFFICULTY */
    GAME_DIFFICULTY                 m_difficulty;

private: /* GAME STATE */
    enum class GAME_STATE {
        INIT = 0,
        BEGIN,
        TAPPED,
        COMPARE,
        RESULT,
        RESTART
    };
    GAME_STATE                      m_gameState;

private: /* STAMP */
    std::list<StampData>            m_stampDataList;
    unsigned int                    m_totalIndex;
    unsigned int                    m_targetIndex;
    unsigned int                    m_currentIndex;

private: /* TARGET */
    DrawNode*                       m_targetDrawNode;

private: /* CURRENT */
    DrawNode*                       m_currentDrawNode;

private: /* RESULT */
    StampLabel*                     m_resultStampLabel;
    Color4F                         m_resultColor;
    StampLabel*                     m_restartStampLabel;
    StampLabel*                     m_backHomeStampLabel;

private: /* TOUCH */
    float                           m_touchDelta;
    long                            m_preTime;
    long                            m_postTime;
    bool                            m_isDoubleTap;

private: /* DELAY */
    float                           m_delayDelta;

public:
    GameScene();
    GameScene(GAME_DIFFICULTY _difficulty);
    virtual ~GameScene();

    static GameScene* createScene();
    static GameScene* createScene(GAME_DIFFICULTY _difficulty);
    static GameScene* create();
    static GameScene* create(GAME_DIFFICULTY _difficulty);

    virtual bool init() override;
    virtual void update(float delta) override;
    virtual void onEnter() override;
    virtual void onExit() override;

public: /* TOOUCH EVENT */
    bool onTouchBegan(Touch* _touch, Event* _event);
    void CheckTab(float delta);
    long GetCurrentDeltaTime();

public: /* CUSTOM SCHEDULE */
    void IncreaseCurrentIndex(float delta);
    void PopFrontStamp(float delta);

public: /* STAMP*/
    void GenerateStampDataList();
    void DrawTargetCanvas();
    void DrawCurrentCanvas();

public: /* COMPARE */
    void CompareIndex();
};

#endif