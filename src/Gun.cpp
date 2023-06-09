#include "Gun.h"
#include <iostream>
using namespace std;

void Gun::addBullet(int nNum)
{
    this->m_nBulletCount = nNum;
}

bool Gun::shoot()
{
    if (m_nBulletCount <= 0)
    {
        cout << "There is no bullets !" << endl;
        return false;
    }
    m_nBulletCount -= 1;
    cout << "Shoot successfully !" << endl;
    return true;
}
