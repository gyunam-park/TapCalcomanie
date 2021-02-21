#include "GameScene.hpp"
#include "HomeScene.hpp"

GameScene::GameScene()
{
    /* DIFFICULTY */
    m_difficulty = GAME_DIFFICULTY::EASY;

    /* GAME STATE */
    m_gameState = GAME_STATE::INIT;

    /* RESULT */
    m_resultStampLabel = nullptr;
    m_restartStampLabel = nullptr;
    m_backHomeStampLabel = nullptr;
    m_resultColor = DISABLE_COLOR_4F;

    /* TOUCH */
    m_touchDelta = 0.0f;
    m_preTime = 0;
    m_postTime = 0;
    m_isDoubleTap = false;

    /* INDEX */
    m_totalIndex = 0;
    switch (m_difficulty)
    {
    case (GAME_DIFFICULTY::EASY):
    {
        m_totalIndex = EASY_MAX;
        break;
    }
    case (GAME_DIFFICULTY::MEDIUM):
    {
        m_totalIndex = MEDIUM_MAX;
        break;
    }
    case (GAME_DIFFICULTY::HARD):
    {
        m_totalIndex = HARD_MAX;
        break;
    }
    }
    m_targetIndex = 0;
    m_currentIndex = 0;

    /* CANVAS */
    m_targetDrawNode = nullptr;
    m_currentDrawNode = nullptr;

    /* RESTART DELTA */
    m_delayDelta = 0.0f;
}

GameScene::GameScene(GAME_DIFFICULTY _difficulty)
{
    /* DIFFICULTY */
    m_difficulty = _difficulty;

    /* GAME STATE */
    m_gameState = GAME_STATE::INIT;

    /* RESULT */
    m_resultStampLabel = nullptr;
    m_restartStampLabel = nullptr;
    m_backHomeStampLabel = nullptr;
    m_resultColor = DISABLE_COLOR_4F;

    /* TOUCH */
    m_touchDelta = 0.0f;
    m_preTime = 0;
    m_postTime = 0;
    m_isDoubleTap = false;

    /* CANVAS */
    m_targetDrawNode = nullptr;
    m_currentDrawNode = nullptr;

    /* RESTART DELTA */
    m_delayDelta = 0.0f;

    /* INDEX */
    m_totalIndex = 0;
    switch (m_difficulty)
    {
    case (GAME_DIFFICULTY::EASY):
    {
        m_totalIndex = EASY_MAX;
        break;
    }
    case (GAME_DIFFICULTY::MEDIUM):
    {
        m_totalIndex = MEDIUM_MAX;
        break;
    }
    case (GAME_DIFFICULTY::HARD):
    {
        m_totalIndex = HARD_MAX;
        break;
    }
    }
    m_targetIndex = 0;
    m_currentIndex = 0;
}

GameScene::~GameScene()
{

}

GameScene* GameScene::createScene()
{
    GameScene* gameScene = create();
    return (gameScene);
}

GameScene* GameScene::createScene(GAME_DIFFICULTY _difficulty)
{
    GameScene* gameScene = create(_difficulty);
    return (gameScene);
}

GameScene* GameScene::create()
{
    GameScene* gameScene = new GameScene();

    if (gameScene != nullptr && gameScene->init())
    {
        gameScene->autorelease();
    }
    else
    {
        if (gameScene != nullptr)
        {
            delete (gameScene);
            gameScene = nullptr;
        }
    }

    return (gameScene);
}

GameScene* GameScene::create(GAME_DIFFICULTY _difficulty)
{
    GameScene* gameScene = new GameScene(_difficulty);

    if (gameScene != nullptr && gameScene->init())
    {
        gameScene->autorelease();
    }
    else
    {
        if (gameScene != nullptr)
        {
            delete (gameScene);
            gameScene = nullptr;
        }
    }

    return (gameScene);
}

bool GameScene::init()
{
    if (!Scene::init()) { return (false); }

    /* SET RANDOM SEED */
    srand(static_cast<unsigned int>(time(nullptr)));

    /* CENTER POSITION */
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 originPoint = Director::getInstance()->getVisibleOrigin();
    Vec2 centerPoint = Vec2(originPoint.x + visibleSize.width * 0.5f, originPoint.y + visibleSize.height * 0.5f);

    /* GENERATE STAMPS */
    GenerateStampDataList();

    /* BACKGROUND */
    Layer* backgroundLayer = Layer::create();
    this->addChild(backgroundLayer);

    DrawNode* backgroundDrawNode = DrawNode::create();
    StampData backgroundData = StampData(
        centerPoint,
        visibleSize,
        0,
        RadiusData(0.0f),
        WHITE_COLOR_4B);
    backgroundData.UpdateData();
    backgroundDrawNode->drawSolidPoly(backgroundData.GetVerticeArray(), backgroundData.GetVertice(), Color4F(backgroundData.GetColor()));
    backgroundLayer->addChild(backgroundDrawNode);

    /* MAIN LAYER */
    Layer* mainLayer = Layer::create();
    this->addChild(mainLayer);

    /* TARGET */
    m_targetDrawNode = DrawNode::create();
    m_targetDrawNode->setPosition(Vec2(originPoint.x + visibleSize.width * 0.5f, originPoint.y + visibleSize.height * 0.75f));
    mainLayer->addChild(m_targetDrawNode);

    /* SET TARGET GENERATOR RANGE */
    switch (m_difficulty)
    {
    case (GAME_DIFFICULTY::EASY):
    {
        m_targetIndex = rand() % (EASY_MAX - EASY_MIN) + EASY_MIN;
        break;
    }
    case (GAME_DIFFICULTY::MEDIUM):
    {
        m_targetIndex = rand() % (MEDIUM_MAX - MEDIUM_MIN) + MEDIUM_MIN;
        break;
    }
    case (GAME_DIFFICULTY::HARD):
    {
        m_targetIndex = rand() % (HARD_MAX - HARD_MIN) + HARD_MIN;
        break;
    }
    }

    /* DRAW TARGET CANVAS */
    DrawTargetCanvas();

    /* CURRENT */
    m_currentDrawNode = DrawNode::create();
    m_currentDrawNode->setPosition(Vec2(originPoint.x + visibleSize.width * 0.5f, originPoint.y + visibleSize.height * 0.25f));
    mainLayer->addChild(m_currentDrawNode);

    /* RESULT LAYER */
    Layer* resultLayer = Layer::create();
    this->addChild(resultLayer);

    /* RESULT STAMP LABEL */
    m_resultStampLabel = StampLabel::create(
        centerPoint,
        Size(400.0f, 36.0f),
        StampLabel::STAMP_FONT_SIZE::SIZE_44,
        "");
    m_resultStampLabel->SetStampColor(DISABLE_COLOR_4B);
    m_resultStampLabel->SetFontColor(WHITE_COLOR_3B);
    resultLayer->addChild(m_resultStampLabel);

    /* RESTART STAMP LABEL */
    m_restartStampLabel = StampLabel::create(
        Vec2(originPoint.x + visibleSize.width * 0.5f, originPoint.y + visibleSize.height * 0.575f),
        Size(320.0f, 36.0f),
        StampLabel::STAMP_FONT_SIZE::SIZE_28,
        "1 TAP                 RESTART"
    );
    m_restartStampLabel->SetStampColor(BLACK_COLOR_4B);
    resultLayer->addChild(m_restartStampLabel);
    m_restartStampLabel->setVisible(false);

    /* BACK HOME STAMP LABEL */
    m_backHomeStampLabel = StampLabel::create(
        Vec2(originPoint.x + visibleSize.width * 0.5f, originPoint.y + visibleSize.height * 0.425f),
        Size(320.0f, 36.0f),
        StampLabel::STAMP_FONT_SIZE::SIZE_28,
        "2 TAP    BACK TO HOME"
    );
    m_backHomeStampLabel->SetStampColor(BLACK_COLOR_4B);
    resultLayer->addChild(m_backHomeStampLabel);
    m_backHomeStampLabel->setVisible(false);

    /* INITIALIZE GAME STATE */
    m_gameState = GAME_STATE::BEGIN;

    /* SCHEDULE */
    this->scheduleUpdate();

    /* SET SCHEDULE TIME BY DIFFICULTY */
    float increaseTime = 0.0f;
    switch (m_difficulty)
    {
    case (GAME_DIFFICULTY::EASY):
    {
        increaseTime = EASY_STAMP_TIME;
        break;
    }
    case (GAME_DIFFICULTY::MEDIUM):
    {
        increaseTime = MEDIUM_STAMP_TIME;
        break;
    }
    case (GAME_DIFFICULTY::HARD):
    {
        increaseTime = HARD_STAMP_TIME;
        break;
    }
    }

    this->schedule(CC_SCHEDULE_SELECTOR(GameScene::IncreaseCurrentIndex), increaseTime, -1, 0.0f);
    this->schedule(CC_SCHEDULE_SELECTOR(GameScene::PopFrontStamp), 0.20f, -1, 0.0f);

    return (true);
}

void GameScene::update(float delta)
{
    Scene::update(delta);

    CompareIndex();

    /* DELAY & RESET */
    if (m_gameState == GAME_STATE::RESTART)
    {
        /* DELAY */
        if (m_delayDelta > 0.4f)
        {
            m_delayDelta = 0.0f;
            GameScene* gameScene = GameScene::createScene(m_difficulty);
            Director::getInstance()->replaceScene(gameScene);
        }
        m_delayDelta += delta;
    }
}

void GameScene::onEnter()
{
    Scene::onEnter();

    /* ADD TOUCH EVENT */
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void GameScene::onExit()
{
    Scene::onExit();

    /* REMOVE EVENTS */
    _eventDispatcher->removeAllEventListeners();
}

bool GameScene::onTouchBegan(Touch* _touch, Event* _event)
{
    auto touchPoint = _touch->getLocation();

    m_isDoubleTap = false;
    m_postTime = GetCurrentDeltaTime();

    if ((m_postTime - m_preTime < 400) && (m_postTime - m_preTime > 50)) {
        m_isDoubleTap = true;
    }

    this->scheduleOnce(CC_SCHEDULE_SELECTOR(GameScene::CheckTab), 0.15f);

    m_preTime = GetCurrentDeltaTime();

    return (true);
}

long GameScene::GetCurrentDeltaTime()
{
    struct timeval now;
    gettimeofday(&now, NULL);
    return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

void GameScene::CheckTab(float delta)
{
    /* SINGLE TAP */
    if (m_isDoubleTap == false)
    {
        if (m_gameState == GAME_STATE::BEGIN)
        {
            m_gameState = GAME_STATE::TAPPED;
        }
        else if (m_gameState == GAME_STATE::RESULT)
        {
            m_gameState = GAME_STATE::RESTART;
        }
    }
    /* DOUBLE TAP */
    else
    {
        HomeScene* homeScene = HomeScene::create();
        Director::getInstance()->replaceScene(homeScene);
    }
}

void GameScene::PopFrontStamp(float delta)
{
    if (m_gameState == GAME_STATE::COMPARE)
    {
        if (m_targetIndex == 0 || m_currentIndex == 0) { m_gameState = GAME_STATE::RESULT; }
        if (m_currentIndex > 0 && m_targetIndex > 0)
        {
            m_stampDataList.pop_front();
            m_currentIndex--;
            m_targetIndex--;

            DrawTargetCanvas();
            DrawCurrentCanvas();
        }
    }
}

void GameScene::IncreaseCurrentIndex(float delta)
{
    if (m_currentIndex == m_stampDataList.size() || m_gameState == GAME_STATE::TAPPED)
    {
        m_gameState = GAME_STATE::COMPARE;
        return;
    }
    if (m_gameState != GAME_STATE::BEGIN) { return; }

    m_currentIndex++;

    DrawCurrentCanvas();
}

void GameScene::GenerateStampDataList()
{
    for (int i = 0; i < m_totalIndex; i++)
    {
        Size size = Size(16.0f * ((rand() % 6) + 1), 16.0f * ((rand() % 5) + 1));
        float radius = (size.width < size.height) ? size.width * 0.5f : size.height * 0.5f;
        int directionX = (rand() % 2) ? 1 : -1;
        int directionY = (rand() % 2) ? 1 : -1;
        float posX = (rand() % static_cast<int>(CANVAS_SIZE * 0.5f + 1));
        float posY = (rand() % static_cast<int>(CANVAS_SIZE * 0.5f + 1));
        Vec2 pos = Vec2(posX * directionX, posY * directionY);

        m_stampDataList.push_back(StampData(
            pos,
            size,
            rand() % 4,
            rand() % (int)(radius), rand() % (int)(radius), rand() % (int)(radius), rand() % (int)(radius),
            Color4B(25 + (rand() % 231), 25 + (rand() % 231), 25 + (rand() % 231), 255)));
    }
}

void GameScene::DrawTargetCanvas()
{
    auto target_it = m_stampDataList.begin();
    for (int i = 0; i < m_targetIndex; i++) { target_it++; }
    m_targetDrawNode->clear();
    for (auto it = m_stampDataList.begin(); it != target_it; it++)
    {
        m_targetDrawNode->drawSolidPoly((*it).GetVerticeArray(), (*it).GetVertice(), Color4F((*it).GetColor()));
    }
}

void GameScene::DrawCurrentCanvas()
{
    m_currentDrawNode->clear();
    auto current_it = m_stampDataList.begin();
    for (int i = 0; i < m_currentIndex; i++) { current_it++; }
    for (auto it = m_stampDataList.begin(); it != current_it; it++)
    {
        m_currentDrawNode->drawSolidPoly((*it).GetVerticeArray(), (*it).GetVertice(), Color4F((*it).GetColor()));
        m_resultColor = Color4F((*it).GetColor());
    }
}

void GameScene::CompareIndex()
{
    if (m_gameState == GAME_STATE::RESULT)
    {
        char resultBuffer[256];
        if (m_currentIndex == m_targetIndex)
        {
            sprintf(resultBuffer, "TAPCALCOMANIE");
            m_resultStampLabel->SetSize(Size(430, 44));
        }
        else
        {
            sprintf(resultBuffer, "FAILED");
            m_resultStampLabel->SetSize(Size(200, 44));
        }
        m_resultStampLabel->SetString(resultBuffer);

        if (m_resultColor.r > 200.f / 255.0f && m_resultColor.g > 200.f / 255.0f && m_resultColor.b > 200.f / 255.0f)
        {
            m_resultStampLabel->SetFontColor(BLACK_COLOR_3B);
        }

        if (m_resultColor == DISABLE_COLOR_4F)
        {
            m_resultColor = Color4F(BLACK_COLOR_4B);
        }
        m_resultStampLabel->SetStampColor(m_resultColor);
        m_resultStampLabel->DrawStampLabel();

        m_restartStampLabel->setVisible(true);
        m_backHomeStampLabel->setVisible(true);
    }
}