#pragma once
#include <string>

class Gun
{
public:
    Gun(std::string strType) : m_strType(strType) {}
    ~Gun() {}
    void addBullet(int nNum);
    bool shoot();

private:
    int m_nBulletCount = 0;
    std::string m_strType;
};
