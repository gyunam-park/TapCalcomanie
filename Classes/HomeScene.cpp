#include "HomeScene.hpp"
#include "GameScene.hpp"

HomeScene::HomeScene()
{
    /* TITILE */
    m_titleStampLabel = nullptr;

    /* PREVIEW */
    m_previewDrawNode = nullptr;

    /* DIFFICULTY */
    m_difficultyStampLabel = nullptr;
    m_difficulty = GAME_DIFFICULTY::EASY;
    
    /* STAMP LABEL */
    m_tapStampLabel = nullptr;
    m_doubleTapStampLabel = nullptr;

    /* INDEX */
    m_totalIndex = EASY_MAX;
    m_targetIndex = 0;
    
    /* TOUCH */
    m_touchDelta = 0.0f;
    m_preTime = 0;
    m_postTime = 0;
    m_isDoubleTap = false;
}

HomeScene::~HomeScene()
{

}

HomeScene* HomeScene::createScene()
{
    HomeScene* homeScene = create();
    return (homeScene);
}

HomeScene* HomeScene::create()
{
    HomeScene* homeScene = new HomeScene();

    if (homeScene != nullptr && homeScene->init())
    {
        homeScene->autorelease();
    }
    else
    {
        if (homeScene != nullptr)
        {
            delete (homeScene);
            homeScene = nullptr;
        }
    }

    return (homeScene);
}

bool HomeScene::init()
{
    if (!Scene::init()) { return (false); }

    /* SET RANDOM SEED */
    srand(static_cast<unsigned int>(time(nullptr)));

    /* CENTER POSITION */
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 originPoint = Director::getInstance()->getVisibleOrigin();
    Vec2 centerPoint = Vec2(originPoint.x + visibleSize.width * 0.5f, originPoint.y + visibleSize.height * 0.5f);

    /* BACKGROUND LAYER */
    Layer* backgroundLayer = Layer::create();
    this->addChild(backgroundLayer);

    /* BACKGROUND STAMP */
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

    /* PREVIEW CANVAS */
    m_previewDrawNode = DrawNode::create();
    m_previewDrawNode->setPosition(Vec2(originPoint.x + visibleSize.width * 0.5f, originPoint.y + visibleSize.height * 0.6f));
    mainLayer->addChild(m_previewDrawNode);

    /* TITLE  */
    m_titleStampLabel = StampLabel::create(
        Vec2(originPoint.x + visibleSize.width * 0.5f, originPoint.y + visibleSize.height * 0.8f),
        Size(400.0f, 44.0f),
        StampLabel::STAMP_FONT_SIZE::SIZE_44,
        "TAPCALCOMANIE");
    m_titleStampLabel->SetStampColor(BLACK_COLOR_4B);
    mainLayer->addChild(m_titleStampLabel);

    /* DIFFICULTY */
    m_difficultyStampLabel = StampLabel::create(
        Vec2(originPoint.x + visibleSize.width * 0.5f, originPoint.y + visibleSize.height * 0.35f),
        Size(120.0f, 44.0f),
        StampLabel::STAMP_FONT_SIZE::SIZE_28,
        "EASY");
    m_difficultyStampLabel->SetStampColor(EASY_COLOR);
    mainLayer->addChild(m_difficultyStampLabel);

    /* TAP */
    m_tapStampLabel = StampLabel::create(
        Vec2(originPoint.x + visibleSize.width * 0.5f, originPoint.y + visibleSize.height * 0.2f),
        Size(400.0f, 36.0f),
        StampLabel::STAMP_FONT_SIZE::SIZE_28,
        "1 TAP                             START");
    m_tapStampLabel->SetStampColor(BLACK_COLOR_4B);
    mainLayer->addChild(m_tapStampLabel);

    /* DOUBLE TAP */
    m_doubleTapStampLabel = StampLabel::create(
        Vec2(originPoint.x + visibleSize.width * 0.5f, originPoint.y + visibleSize.height * 0.15f),
        Size(400.0f, 36.0f),
        StampLabel::STAMP_FONT_SIZE::SIZE_28,
        "2 TAP   CHANGE DIFFICULTY");
    m_doubleTapStampLabel->SetStampColor(BLACK_COLOR_4B);
    mainLayer->addChild(m_doubleTapStampLabel);

    /* GENERATE START LIST */
    GenerateStampDataList();

    /* SCHEDULE */
    this->scheduleUpdate();
    this->schedule(CC_SCHEDULE_SELECTOR(HomeScene::ChangePreview), 0.4f, -1, 0.0f);

    return (true);
}

void HomeScene::onEnter()
{
    Scene::onEnter();

    /* ADD TOUCH EVENT */
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(HomeScene::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void HomeScene::onExit()
{
    Scene::onExit();

    /* REMOVE EVENTS */
    _eventDispatcher->removeAllEventListeners();
}

bool HomeScene::onTouchBegan(Touch* _touch, Event* _event)
{
    auto touchPoint = _touch->getLocation();

    m_isDoubleTap = false;
    m_postTime = GetCurrentDeltaTime();

    if ((m_postTime - m_preTime < 400) && (m_postTime - m_preTime > 50)) {
        m_isDoubleTap = true;
    }

    this->scheduleOnce(CC_SCHEDULE_SELECTOR(HomeScene::CheckTab), 0.25f);

    m_preTime = GetCurrentDeltaTime();

    return (true);
}

long HomeScene::GetCurrentDeltaTime()
{
    struct timeval current;
    gettimeofday(&current, NULL);

    long deltaTime = 0;
    deltaTime = (current.tv_sec * 1000) + (current.tv_usec / 1000);

    return (deltaTime);
}

void HomeScene::CheckTab(float delta)
{
    if (m_isDoubleTap == false) 
    {
        GameScene* gameScene = GameScene::create(m_difficulty);
        Director::getInstance()->replaceScene(gameScene);
    }
    else
    {
        this->scheduleOnce(CC_SCHEDULE_SELECTOR(HomeScene::ChangeDifficulty), 0.0f);
    }
}

void HomeScene::ChangeDifficulty(float delta)
{
    unsigned int difficulty = static_cast<unsigned int>(m_difficulty);

    difficulty++;
    if (difficulty > static_cast<unsigned int>(GAME_DIFFICULTY::HARD))
    {
        difficulty = 0;
    }
    m_difficulty = static_cast<GAME_DIFFICULTY>(difficulty);

    switch (m_difficulty)
    {
    case (GAME_DIFFICULTY::EASY):
    {
        m_totalIndex = EASY_MAX;

        m_difficultyStampLabel->SetString("EASY");
        m_difficultyStampLabel->SetStampColor(EASY_COLOR);
        m_difficultyStampLabel->SetSize(Size(120.0f, 36.0f));
        break;
    }
    case (GAME_DIFFICULTY::MEDIUM):
    {
        m_totalIndex = MEDIUM_MAX;

        m_difficultyStampLabel->SetString("MEDIUM");
        m_difficultyStampLabel->SetStampColor(MEDIUM_COLOR);
        m_difficultyStampLabel->SetSize(Size(170.0f, 36.0f));
        break;
    }
    case (GAME_DIFFICULTY::HARD):
    {
        m_totalIndex = HARD_MAX;

        m_difficultyStampLabel->SetString("HARD");
        m_difficultyStampLabel->SetStampColor(HARD_COLOR);
        m_difficultyStampLabel->SetSize(Size(120.0f, 36.0f));
        break;
    }
    }

    m_difficultyStampLabel->DrawStampLabel();
}

void HomeScene::GenerateStampDataList()
{
    m_stampDataList.clear();

    unsigned int min_range = 0;
    switch (m_difficulty)
    {
    case (GAME_DIFFICULTY::EASY):
    {
        min_range = EASY_MIN;
        break;
    }
    case (GAME_DIFFICULTY::MEDIUM):
    {
        min_range = MEDIUM_MIN;
        break;
    }
    case (GAME_DIFFICULTY::HARD):
    {
        min_range = HARD_MIN;
        break;
    }
    }

    m_targetIndex = rand() % (m_totalIndex - min_range) + min_range;
    for (int i = 0; i < m_targetIndex; i++)
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

void HomeScene::DrawPreviewCanvas()
{
    auto target_it = m_stampDataList.begin();
    for (int i = 0; i < m_targetIndex; i++) { target_it++; }
    m_previewDrawNode->clear();
    for (auto it = m_stampDataList.begin(); it != target_it; it++)
    {
        m_previewDrawNode->drawSolidPoly((*it).GetVerticeArray(), (*it).GetVertice(), Color4F((*it).GetColor()));
    }
}

void HomeScene::ChangePreview(float delta)
{
    GenerateStampDataList();
    DrawPreviewCanvas();
}
