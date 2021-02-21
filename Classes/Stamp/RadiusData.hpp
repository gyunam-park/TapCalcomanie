#ifndef __RADIUS_DATA_HPP__
#define __RADIUS_DATA_HPP__

class RadiusData {
private:
    float m_topLeft;          // RADIUS_TOP_LEFT
    float m_topRight;         // RADIUS_TOP_RIGHT
    float m_bottomLeft;       // RADIUS_BOTTOM_LEFT
    float m_bottomRight;      // RADIUS_BOTTOM_RIGHT
public:
    RadiusData();
    RadiusData(float _topLeft, float _topRight, float _bottomLeft, float _bottomRight);
    RadiusData(float _radius);
    ~RadiusData();

public: /* SET */
    void SetData(RadiusData _data);
    void SetData(float _topLeft, float _topRight, float _bottomLeft, float _bottomRight);
    void SetData(float _radius);
    void SetTopLeft(float _radius);
    void SetTopRight(float _radius);
    void SetBottomLeft(float _radius);
    void SetBottomRight(float _radius);

public: /* GET */
    float GetTopLeft();
    float GetTopRight();
    float GetBottomLeft();
    float GetBottomRight();
};

#endif