#pragma once
#include <string>
#include "Gun.h"

class Solider
{
private:
    std::string m_strName;
    Gun* m_pGun = nullptr;
public:
    Solider(std::string name);
    ~Solider();

    void addBullet2Gun(int nNum);
    void addGun(Gun *pGun);
    bool fire();
};

