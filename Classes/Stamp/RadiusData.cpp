#include "RadiusData.hpp"

RadiusData::RadiusData()
{
    m_topLeft       = 0.0f;
    m_topRight      = 0.0f;
    m_bottomLeft    = 0.0f;
    m_bottomRight   = 0.0f;
}

RadiusData::RadiusData(float _topLeft, float _topRight, float _bottomLeft, float _bottomRight)
{
    SetData(_topLeft, _topRight, _bottomLeft, _bottomRight);
}

RadiusData::RadiusData(float _radius)
{
    SetData(_radius);
}

RadiusData::~RadiusData()
{
    
}

////////////////////////////////////////////////
//                   SET
////////////////////////////////////////////////

void RadiusData::SetData(RadiusData _data)
{
    SetData(_data.GetTopLeft(), _data.GetTopRight(), _data.GetBottomLeft(), _data.GetBottomRight());
}

void RadiusData::SetData(float _topLeft, float _topRight, float _bottomLeft, float _bottomRight)
{
    SetTopLeft(_topLeft);
    SetTopRight(_topRight);
    SetBottomLeft(_bottomLeft);
    SetBottomRight(_bottomRight);
}

void RadiusData::SetData(float _radius)
{
    SetData(_radius, _radius, _radius, _radius);
}

void RadiusData::SetTopLeft(float _radius)
{
    m_topLeft = _radius;
}

void RadiusData::SetTopRight(float _radius)
{
    m_topRight = _radius;
}

void RadiusData::SetBottomLeft(float _radius)
{
    m_bottomLeft = _radius;
}

void RadiusData::SetBottomRight(float _radius)
{
    m_bottomRight = _radius;
}

////////////////////////////////////////////////
//                   GET
////////////////////////////////////////////////

float RadiusData::GetTopLeft()
{
    return (m_topLeft);
}

float RadiusData::GetTopRight()
{
    return (m_topRight);
}

float RadiusData::GetBottomLeft()
{
    return (m_bottomLeft);
}

float RadiusData::GetBottomRight()
{
    return (m_bottomRight);
}