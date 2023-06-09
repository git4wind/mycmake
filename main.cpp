
#include <memory>

#include "Gun.h"
#include "Solider.h"


using namespace std;

void test()
{
    // std::shared_ptr<Gun> pGun = std::make_shared<Gun>("AK47");
    Solider sanduo("ldl");
    sanduo.addGun(new Gun("AK47"));
    sanduo.addBullet2Gun(20);
    sanduo.fire();
}

int main()
{
#if 0
    test();
#endif
#if 1

#endif


    return 0;
}