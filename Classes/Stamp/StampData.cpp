#include "StampData.hpp"

StampData::StampData()
{
    START_POINT = Vec2::ZERO;
    SetPosition(Vec2::ZERO);
    SetSize(Size::ZERO);
    SetEdge(0);
    SetRadius(RADIUS_NONE);
    SetVertice();
    SetVerticeArray();
    SetColor(COLOR_NONE);
}

StampData::StampData(Vec2 _position, Size _size, unsigned int _edge, RadiusData _data, Color4B _color)
{
    START_POINT = Vec2::ZERO;
    SetPosition(_position);
    SetSize(_size);
    SetEdge(_edge);
    SetRadius(_data);
    SetColor(_color);
}

StampData::StampData(Vec2 _position, Size _size, unsigned int _edge, RadiusData _data, Color4F _color)
{
    START_POINT = Vec2::ZERO;
    SetPosition(_position);
    SetSize(_size);
    SetEdge(_edge);
    SetRadius(_data);
    SetColor(_color);
}

StampData::StampData(Vec2 _position, Size _size, unsigned int _edge, float _topLeft, float _topRight, float _bottomLeft, float _bottomRight, Color4B _color)
{
    START_POINT = Vec2::ZERO;
    SetPosition(_position);
    SetSize(_size);
    SetEdge(_edge);
    SetRadius(_topLeft, _topRight, _bottomLeft, _bottomRight);
    SetVertice();
    SetVerticeArray();
    SetColor(_color);
}

StampData::StampData(Vec2 _position, Size _size, unsigned int _edge, float _topLeft, float _topRight, float _bottomLeft, float _bottomRight, Color4F _color)
{
    START_POINT = Vec2::ZERO;
    SetPosition(_position);
    SetSize(_size);
    SetEdge(_edge);
    SetRadius(_topLeft, _topRight, _bottomLeft, _bottomRight);
    SetVertice();
    SetVerticeArray();
    SetColor(_color);
}

StampData::~StampData()
{
    
}

////////////////////////////////////////////////
//                   SET
////////////////////////////////////////////////

void StampData::SetData(StampData _data)
{
    SetPosition(_data.GetPosition());
    SetSize(_data.GetSize());
    SetEdge(_data.GetEdge());
    SetRadius(_data.GetRadius());
    SetVertice();
    SetVerticeArray();
    SetColor(_data.GetColor());
}

void StampData::SetData(Vec2 _position, Size _size, unsigned int _edge, RadiusData _data, Color4B _color)
{
    SetPosition(_position);
    SetSize(_size);
    SetEdge(_edge);
    SetRadius(_data);
    SetVertice();
    SetVerticeArray();
    SetColor(_color);
}

void StampData::SetData(Vec2 _position, Size _size, unsigned int _edge, RadiusData _data, Color4F _color)
{
    SetPosition(_position);
    SetSize(_size);
    SetEdge(_edge);
    SetRadius(_data);
    SetVertice();
    SetVerticeArray();
    SetColor(_color);
}

void StampData::SetData(Vec2 _position, Size _size, unsigned int _edge, float _topLeft, float _topRight, float _bottomLeft, float _bottomRight, Color4B _color)
{
    SetPosition(_position);
    SetSize(_size);
    SetEdge(_edge);
    SetRadius(_topLeft, _topRight, _bottomLeft, _bottomRight);
    SetVertice();
    SetVerticeArray();
    SetColor(_color);
}

void StampData::SetData(Vec2 _position, Size _size, unsigned int _edge, float _topLeft, float _topRight, float _bottomLeft, float _bottomRight, Color4F _color)
{
    SetPosition(_position);
    SetSize(_size);
    SetEdge(_edge);
    SetRadius(_topLeft, _topRight, _bottomLeft, _bottomRight);
    SetVertice();
    SetVerticeArray();
    SetColor(_color);
}

void StampData::SetPosition(Vec2 _position)
{
    m_position = _position;
}

void StampData::SetSize(Size _size)
{
    m_size = _size;
}

void StampData::SetEdge(unsigned int _edge)
{
    m_edge = _edge;
}

void StampData::SetRadius(RadiusData _data)
{
    float radiusMax = 0.0f;

    if (m_size.width < m_size.height)               { radiusMax = m_size.width * 0.5f; }
    else                                            { radiusMax = m_size.height * 0.5f; }

    if (_data.GetTopLeft() < RADIUS_NONE)           { m_radiusData.SetTopLeft(RADIUS_NONE);                 }
    else if (_data.GetTopLeft() > radiusMax)        { m_radiusData.SetTopLeft(radiusMax);                   }
    else                                            { m_radiusData.SetTopLeft(_data.GetTopLeft());          }

    if (_data.GetTopRight() < RADIUS_NONE)          { m_radiusData.SetTopRight(RADIUS_NONE);                }
    else if (_data.GetTopRight() > radiusMax)       { m_radiusData.SetTopRight(radiusMax);                  }
    else                                            { m_radiusData.SetTopRight(_data.GetTopRight());        }

    if  (_data.GetBottomLeft() < RADIUS_NONE)       { m_radiusData.SetBottomLeft(RADIUS_NONE);              }
    else if (_data.GetBottomLeft() > radiusMax)     { m_radiusData.SetBottomLeft(radiusMax);                }
    else                                            { m_radiusData.SetBottomLeft(_data.GetBottomLeft());    }

    if (_data.GetBottomRight() < RADIUS_NONE)       { m_radiusData.SetBottomRight(RADIUS_NONE);             }
    else if (_data.GetBottomRight() > radiusMax)    { m_radiusData.SetBottomRight(radiusMax);               }
    else                                            { m_radiusData.SetBottomRight(_data.GetBottomRight());  }
}

void StampData::SetRadius(float _topLeft, float _topRight, float _bottomLeft, float _bottomRight)
{
    float radiusMax = 0.0f;

    if (m_size.width < m_size.height)   { radiusMax = m_size.width * 0.5f;              }
    else                                { radiusMax = m_size.height * 0.5f;             }

    if (_topLeft < RADIUS_NONE)         { m_radiusData.SetTopLeft(RADIUS_NONE);         }
    else if (_topLeft > radiusMax)      { m_radiusData.SetTopLeft(radiusMax);           }
    else                                { m_radiusData.SetTopLeft(_topLeft);            }

    if (_topRight < RADIUS_NONE)        { m_radiusData.SetTopRight(RADIUS_NONE);        }
    else if (_topRight > radiusMax)     { m_radiusData.SetTopRight(radiusMax);          }
    else                                { m_radiusData.SetTopRight(_topRight);          }

    if (_bottomLeft < RADIUS_NONE)      { m_radiusData.SetBottomLeft(RADIUS_NONE);      }
    else if (_bottomLeft > radiusMax)   { m_radiusData.SetBottomLeft(radiusMax);        }
    else                                { m_radiusData.SetBottomLeft(_bottomLeft);      }

    if (_bottomRight < RADIUS_NONE)     { m_radiusData.SetBottomRight(RADIUS_NONE);     }
    else if (_bottomRight > radiusMax)  { m_radiusData.SetBottomRight(radiusMax);       }
    else                                { m_radiusData.SetBottomRight(_bottomRight);    }
}

void StampData::SetRadius(float _all)
{
    float radiusMax = 0.0f;

    if (m_size.width < m_size.height)   { radiusMax = m_size.width * 0.5f;      }
    else                                { radiusMax = m_size.height * 0.5f;     }

    if (_all < RADIUS_NONE)             { m_radiusData.SetData(RADIUS_NONE);    }
    else if (_all > radiusMax)          { m_radiusData.SetData(radiusMax);      }
    else                                { m_radiusData.SetData(_all);           }
}

void StampData::SetVertice()
{
    unsigned int activateRadius = 0;

    if (m_radiusData.GetTopLeft() != RADIUS_NONE)       { activateRadius++; }
    if (m_radiusData.GetTopRight() != RADIUS_NONE)      { activateRadius++; }
    if (m_radiusData.GetBottomLeft() != RADIUS_NONE)    { activateRadius++; }
    if (m_radiusData.GetBottomRight() != RADIUS_NONE)   { activateRadius++; }

    if (activateRadius == 0)
    { 
        m_vertice = (1 + 1 + 4); 
    }
    else
    {
        m_vertice = (1 + 1 + 4 + activateRadius + (m_edge * activateRadius));
    }
}

void StampData::SetVerticeArray()
{
    /* INITIALIZE VERTEX VARIABLE */
    unsigned int vertexIndex    = 0;
    m_verticeArray              = new Vec2[m_vertice];

    /* GET SIZE */
    float width                 = m_size.width * 0.5f;
    float height                = m_size.height * 0.5f;

    /* INITIALIZE START & END POINT */
    START_POINT                 = m_position;
    Vec2 END_POINT              = Vec2(0.0f, 0.0f);

    /* GET RADIUS */
    float topLeft               = m_radiusData.GetTopLeft();
    float topRight              = m_radiusData.GetTopRight();
    float bottomLeft            = m_radiusData.GetBottomLeft();
    float bottomRight           = m_radiusData.GetBottomRight();

    /* BASICALLY STAMP HAVE AT LEAST ONE WORN EDGE */
    if (m_edge == 0)
    {
        m_verticeArray[vertexIndex] = START_POINT;
        /* TOP RIGHT*/
        if (topRight > 0.0f)
        {

            m_verticeArray[++vertexIndex] = END_POINT = m_position + Vec2(width, -height + bottomRight);
            m_verticeArray[++vertexIndex] = m_position + Vec2(width, height - topRight);
            m_verticeArray[++vertexIndex] = m_position + Vec2(width - topRight, height);
        }
        else
        {
            m_verticeArray[++vertexIndex] = END_POINT = m_position + Vec2(width, -height + bottomRight);
            m_verticeArray[++vertexIndex] = m_position + Vec2(width, height);
        }

        /* TOP LEFT */
        if (topLeft > 0.0f)
        {
            m_verticeArray[++vertexIndex] = m_position + Vec2(-width + topLeft, height);
            m_verticeArray[++vertexIndex] = m_position + Vec2(-width, height - topLeft);
        }
        else
        {
            m_verticeArray[++vertexIndex] = m_position + Vec2(-width, height);
        }

        /* BOTTOM LEFT */
        if (bottomLeft > 0.0f)
        {
            m_verticeArray[++vertexIndex] = m_position + Vec2(-width, -height + bottomLeft);
            m_verticeArray[++vertexIndex] = m_position + Vec2(-width + bottomLeft, -height);
        }
        else
        {
            m_verticeArray[++vertexIndex] = m_position + Vec2(-width, -height);
        }

        /* BOTTOM RIGHT */
        if (bottomRight > 0.0f)
        {
            m_verticeArray[++vertexIndex] = m_position + Vec2(width - bottomRight, -height);
            m_verticeArray[++vertexIndex] = END_POINT;
        }
        else
        {
            m_verticeArray[++vertexIndex] = END_POINT;
        }
    }
    /* GENERATE VERTICES POINTS FOLLOWING WORN EDGE */
    else
    {
        m_verticeArray[vertexIndex] = START_POINT;

        /* TOP RIGHT */
        if (topRight > 0.0f)
        {
            m_verticeArray[++vertexIndex] = END_POINT = m_position + Vec2(width, -height + bottomRight);
            m_verticeArray[++vertexIndex] = m_position + Vec2(width, height - topRight);
            for (int i = 1; i <= m_edge; i++)
            {
                m_verticeArray[++vertexIndex] = m_position + Vec2(width - topRight + topRight * cos((90.0f / (m_edge + 1) * i * RADIAN)),
                    height - topRight + topRight * sin((90.0f / (m_edge + 1) * i * RADIAN)));
            }
            m_verticeArray[++vertexIndex] = m_position + Vec2(width - topRight, height);
        }
        else
        {
            m_verticeArray[++vertexIndex] = END_POINT = m_position + Vec2(width, -height + bottomRight);
            m_verticeArray[++vertexIndex] = m_position + Vec2(width, height);
        }

        /* TOP LEFT */
        if (topLeft > 0.0f)
        {
            m_verticeArray[++vertexIndex] = m_position + Vec2(-width + topLeft, height);
            for (int i = 1; i <= m_edge; i++)
            {
                m_verticeArray[++vertexIndex] = m_position + Vec2(-width + topLeft - topLeft * sin((90.0f / (m_edge + 1) * i * RADIAN)),
                    height - topLeft + topLeft * cos((90.0f / (m_edge + 1) * i * RADIAN)));
            }
            m_verticeArray[++vertexIndex] = m_position + Vec2(-width, height - topLeft);
        }
        else
        {
            m_verticeArray[++vertexIndex] = m_position + Vec2(-width, height);
        }

        /* BOTTOM LEFT */
        if (bottomLeft > 0.0f)
        {
            m_verticeArray[++vertexIndex] = m_position + Vec2(-width, -height + bottomLeft);
            for (int i = 1; i <= m_edge; i++)
            {
                m_verticeArray[++vertexIndex] = m_position + Vec2(-width + bottomLeft - bottomLeft * cos((90.0f / (m_edge + 1) * i * RADIAN)),
                    -height + bottomLeft - bottomLeft * sin((90.0f / (m_edge + 1) * i * RADIAN)));
            }
            m_verticeArray[++vertexIndex] = m_position + Vec2(-width + bottomLeft, -height);
        }
        else
        {
            m_verticeArray[++vertexIndex] = m_position + Vec2(-width, -height);
        }

        /* BOTTOM RIGHT */
        if (bottomRight > 0.0f)
        {
            m_verticeArray[++vertexIndex] = m_position + Vec2(width - bottomRight, -height);
            for (int i = 1; i <= m_edge; i++)
            {
                m_verticeArray[++vertexIndex] = m_position + Vec2(width - bottomRight + bottomRight * sin((90.0f / (m_edge + 1) * i * RADIAN)),
                    -height + bottomRight - bottomRight * cos((90.0f / (m_edge + 1) * i * RADIAN)));
            }
            m_verticeArray[++vertexIndex] = END_POINT;
        }
        else
        {
            m_verticeArray[++vertexIndex] = END_POINT;
        }
    }
}

void StampData::SetColor(Color4B _color)
{
    m_color = Color4F(_color);
}

void StampData::SetColor(Color4F _color)
{
    m_color = _color;
}

////////////////////////////////////////////////
//                   GET
////////////////////////////////////////////////

Vec2 StampData::GetPosition()
{
    return (m_position);
}

Size StampData::GetSize()
{
    return (m_size);
}

unsigned int StampData::GetEdge()
{
    return (m_edge);
}

RadiusData StampData::GetRadius()
{
    return (m_radiusData);
}

unsigned int StampData::GetVertice()
{
    return (m_vertice);
}

Vec2* StampData::GetVerticeArray()
{
    return (m_verticeArray);
}

Color4F StampData::GetColor()
{
    return (m_color);
}

////////////////////////////////////////////////
//                 UPDATE
////////////////////////////////////////////////

void StampData::UpdateData()
{
    SetVertice();
    SetVerticeArray();
}