#ifndef __STAMP_LABEL_HPP__
#define __STAMP_LABEL_HPP__

#include "cocos2d.h"
#include "StampData.hpp"

USING_NS_CC;

class StampLabel : public Node
{
public:
    enum class STAMP_FONT_SIZE {
        SIZE_28 = 0,
        SIZE_44
    };

private:
    Label*                  m_stampLabel;
    DrawNode*               m_stampNode;
    StampData               m_stampData;
    STAMP_FONT_SIZE         m_fontSize;
    Size                    m_size;
    Vec2                    m_position;
    std::string             m_string;

public:
    StampLabel();
    StampLabel(Vec2 _position, Size _size, STAMP_FONT_SIZE _fontSize, const std::string& _string);
    virtual ~StampLabel();

    static StampLabel* create();
    static StampLabel* create(Vec2 _position, Size _size, STAMP_FONT_SIZE _fontSize, const std::string& _string);

    virtual bool init() override;
    virtual void update(float delta) override;

public: /* CUSTOM SCHEDULE */
    void UpdateStamp(float delta);

public: /* SET */
    void SetPosition(Vec2 _position);
    void SetSize(Size _size);
    void SetStampData(StampData _data);
    void SetStampColor(Color4B _color);
    void SetStampColor(Color4F _color);
    void SetFontSize(STAMP_FONT_SIZE _fontSize);
    void SetString(const std::string& _string);
    void SetFontColor(Color3B _color);

public: /* DRAW */
    void DrawStampLabel();
};

#endif