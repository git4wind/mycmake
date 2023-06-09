#include "Solider.h"
#include <iostream>
using namespace std;

Solider::Solider(std::string name):m_strName(name)
{
}

Solider::~Solider()
{
    if (m_pGun)
    {
        delete m_pGun;
        m_pGun = nullptr;
    }
}

void Solider::addBullet2Gun(int nNum)
{
    m_pGun->addBullet(nNum);
}

void Solider::addGun(Gun *pGun)
{
    if (pGun)
    {
       m_pGun = pGun;
    }
}

bool Solider::fire()
{
    bool bRet = false;
    if(m_pGun)
    {
        bRet = m_pGun->shoot();
    }
    return bRet;        
}
