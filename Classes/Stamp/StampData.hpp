#ifndef __STAMP_DATA_HPP__
#define __STAMP_DATA_HPP__

#include "cocos2d.h"
#include "RadiusData.hpp"

USING_NS_CC;

class StampData
{
private: /* CONSTANTS */
    const float     RADIUS_NONE = 0.0f;
    const float     RADIAN      = (3.141592f / 180.0f);
    const Color4F   COLOR_NONE  = Color4F::WHITE;

private: /* MEMBER VARIABLE */
    Vec2            m_position;         // GALLOBJECT_POSITION
    Size            m_size;             // GALLOBJECT_SIZE
    RadiusData      m_radiusData;       // RADIUS_DATA
    unsigned int    m_edge;             // EDGE_VALUE
    unsigned int    m_vertice;          // VERTICE_VALUE
    Vec2*           m_verticeArray;     // VERTICE_ARRAY
    Color4F         m_color;            // GALLOBJECT_COLOR
    Vec2            START_POINT;        // START_POINT

public:
    StampData();
    StampData(Vec2 _position, Size _size, unsigned int _edge, RadiusData _data, Color4B _color);
    StampData(Vec2 _position, Size _size, unsigned int _edge, RadiusData _data, Color4F _color);
    StampData(Vec2 _position, Size _size, unsigned int _edge, float _topLeft, float _topRight, float _bottomLeft, float _bottomRight, Color4B _color);
    StampData(Vec2 _position, Size _size, unsigned int _edge, float _topLeft, float _topRight, float _bottomLeft, float _bottomRight, Color4F _color);
    ~StampData();

public: /* SET */
    void            SetData(StampData _data);
    void            SetData(Vec2 _position, Size _size, unsigned int _edge, RadiusData _data, Color4B _color);
    void            SetData(Vec2 _position, Size _size, unsigned int _edge, RadiusData _data, Color4F _color);
    void            SetData(Vec2 _position, Size _size, unsigned int _edge, float _topLeft, float _topRight, float _bottomLeft, float _bottomRight, Color4B _color);
    void            SetData(Vec2 _position, Size _size, unsigned int _edge, float _topLeft, float _topRight, float _bottomLeft, float _bottomRight, Color4F _color);
    void            SetPosition(Vec2 _position);
    void            SetSize(Size _size);
    void            SetRadius(RadiusData _data);
    void            SetRadius(float _topLeft, float _topRight, float _bottomLeft, float _bottomRight);
    void            SetRadius(float _all);
    void            SetEdge(unsigned int _edge);
private:
    /* USER SHOULD NOT APPROACH GENERATOR FUNCTION */
    void            SetVertice();
    void            SetVerticeArray();
    /* USER SHOULD NOT APPROACH GENERATOR FUNCTION */
public:
    void            SetColor(Color4B _color);
    void            SetColor(Color4F _color);

public: /* GET */
    Vec2            GetPosition();
    Size            GetSize();
    unsigned int    GetEdge();
    RadiusData      GetRadius();
    unsigned int    GetVertice();
    Vec2*           GetVerticeArray();
    Color4F         GetColor();

public: /* UPDATE */
    void            UpdateData();
};

static StampData STAMP_DATA_NULL  = StampData(Vec2(0.0f, 0.0f), Size(0.0f,0.0f), 0, RadiusData(0.0f), Color4B(0,0,0,0));

#endif