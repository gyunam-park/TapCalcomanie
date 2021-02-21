#include "StampLabel.hpp"

StampLabel::StampLabel()
{
    m_stampLabel = nullptr;
    m_stampNode = nullptr;
    SetPosition(Vec2(0.0f, 0.0f));
    SetSize(Size(0.0f, 0.0f));
    SetStampData(STAMP_DATA_NULL);
    SetFontSize(STAMP_FONT_SIZE::SIZE_28);
    SetString("");
}

StampLabel::StampLabel(Vec2 _position, Size _size, STAMP_FONT_SIZE _fontSize, const std::string& _string)
{
    m_stampLabel = nullptr;
    m_stampNode = nullptr;
    SetPosition(_position);
    SetSize(_size);
    SetStampData(STAMP_DATA_NULL);
    SetFontSize(_fontSize);
    SetString(_string);
}

StampLabel::~StampLabel()
{

}

StampLabel* StampLabel::create()
{
    StampLabel* stampLabel = new StampLabel();

    if (stampLabel != nullptr && stampLabel->init())
    {
        stampLabel->autorelease();
    }
    else
    {
        if (stampLabel != nullptr)
        {
            delete (stampLabel);
            stampLabel = nullptr;
        }
    }

    return (stampLabel);
}

StampLabel* StampLabel::create(Vec2 _position, Size _size, STAMP_FONT_SIZE _fontSize, const std::string& _string)
{
    StampLabel* stampLabel = new StampLabel(_position, _size, _fontSize, _string);

    if (stampLabel != nullptr && stampLabel->init())
    {
        stampLabel->autorelease();
    }
    else
    {
        if (stampLabel != nullptr)
        {
            delete (stampLabel);
            stampLabel = nullptr;
        }
    }

    return (stampLabel);
}

bool StampLabel::init()
{
    if (!Node::init()) { return (false); }

    /* STAMPED LABEL BACKGROUND */
    m_stampNode = DrawNode::create();
    m_stampData.SetData(
        Vec2(0.0f, 0.0f),
        m_size,
        0,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        Color4B(25, 25, 25, 255));
    m_stampNode->setPosition(m_position);
    this->addChild(m_stampNode);

    /* STAMPED LABEL */
    char str[256] = {0};
    switch (m_fontSize)
    {
    case (STAMP_FONT_SIZE::SIZE_28):
    {
        sprintf(str, "Fonts/NANUM_MYEONGJO_%d.fnt", 28);
        break;
    }
    case (STAMP_FONT_SIZE::SIZE_44):
    {
        sprintf(str, "Fonts/NANUM_MYEONGJO_%d.fnt", 44);
        break;
    }
    }
    std::string fontPath(str);

    m_stampLabel = Label::createWithBMFont(fontPath, m_string);
    m_stampLabel->setPosition(m_position);
    m_stampLabel->setColor(Color3B(245, 245, 245));
    this->addChild(m_stampLabel);

    this->scheduleUpdate();
    this->schedule(CC_SCHEDULE_SELECTOR(StampLabel::UpdateStamp), 0.4f, -1, 0.0f);

    return (true);
}

void StampLabel::update(float delta)
{
    Node::update(delta);
}

void StampLabel::UpdateStamp(float delta)
{
    unsigned int gallableSize = 0;

    switch (m_fontSize)
    {
    case (STAMP_FONT_SIZE::SIZE_28):
    {
        gallableSize = 14;
        break;
    }
    case (STAMP_FONT_SIZE::SIZE_44):
    {
        gallableSize = 22;
        break;
    }
    }

    m_stampData.SetRadius(rand() % gallableSize, rand() % gallableSize, rand() % gallableSize, rand() % gallableSize);

    DrawStampLabel();
}

////////////////////////////////////////////////
//                   SET
////////////////////////////////////////////////

void StampLabel::SetPosition(Vec2 _position)
{
    m_position = _position;
    m_stampData.SetPosition(m_position);
    if (m_stampLabel != nullptr) 
    { 
        m_stampLabel->setPosition(m_position); 
    }
}

void StampLabel::SetSize(Size _size)
{
    m_size = _size;
    m_stampData.SetSize(m_size);
}

void StampLabel::SetStampData(StampData _data)
{
    m_stampData.SetData(_data);
}

void StampLabel::SetStampColor(Color4B _color)
{
    m_stampData.SetColor(_color);
}

void StampLabel::SetStampColor(Color4F _color)
{
    m_stampData.SetColor(_color);
}

void StampLabel::SetFontSize(STAMP_FONT_SIZE _fontSize)
{
    m_fontSize = _fontSize;
}

void StampLabel::SetString(const std::string& _string)
{
    m_string = _string;
    if (m_stampLabel != nullptr)
    {
        m_stampLabel->setString(m_string);
    }
}

void StampLabel::SetFontColor(Color3B _color)
{
    if (m_stampLabel != nullptr)
    {
        m_stampLabel->setColor(_color);
    }
}

void StampLabel::DrawStampLabel()
{
    m_stampData.UpdateData();
    m_stampNode->clear();
    m_stampNode->drawSolidPoly(m_stampData.GetVerticeArray(), m_stampData.GetVertice(), Color4F(m_stampData.GetColor()));
}