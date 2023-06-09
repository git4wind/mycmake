#include <iostream>
using namespace std;

// abstract class
class AbstractSmile
{
private:
    /* data */
public:
    AbstractSmile(/* args */){};
    virtual ~AbstractSmile(){};
    virtual void transform() = 0;
    virtual void ability() = 0;
};

// sun class
class SheepSmile : public AbstractSmile
{
private:
    /* data */
public:
    SheepSmile(/* args */){};
    ~SheepSmile(){};

    void transform() override
    {
        cout << "变成人兽--绵羊人形态..." << endl;
    }
    void ability() override
    {
        cout << "巨羊角之术..." << endl;
    }
};

class LionSmile : public AbstractSmile
{
public:
    void transform() override
    {
        cout << "变成人兽--狮子人形态..." << endl;
    }

    void ability() override
    {
        cout << "火遁之术..." << endl;
    }
};

class BatSmile : public AbstractSmile
{
public:
    void transform() override
    {
        cout << "变成人兽--蝙蝠人形态..." << endl;
    }

    void ability() override
    {
        cout << "声呐引剑之术万剑归宗..." << endl;
    }
};

// define factory
class AbstractFactory
{
public:
    virtual ~AbstractFactory(){};
    virtual AbstractSmile *createSmile() = 0;
};

class SheepFactory : public AbstractFactory
{
public:
    ~SheepFactory()
    {
        cout << "SheepFactory ~ 被析构了..." << endl;
    }

    AbstractSmile *createSmile() override
    {
        return new SheepSmile;
    }
};

class LionFactory : public AbstractFactory
{
public:
    ~LionFactory()
    {
        cout << "LionFactory  ~ 被析构了..." << endl;
    }

    AbstractSmile *createSmile() override
    {
        return new LionSmile;
    }
};

class BatFactory : public AbstractFactory
{
public:
    ~BatFactory()
    {
        cout << "BatFactory ~ 被析构了..." << endl;
    }

    AbstractSmile *createSmile() override
    {
        return new BatSmile;
    }
};

int main()
{
    AbstractFactory* pFact = new LionFactory;
    if (pFact)
    {
        AbstractSmile* pObj = pFact->createSmile();
        if (pObj)
        {
            pObj->transform();
            pObj->ability();
            delete pObj;
            pObj = nullptr;
        }
        delete pFact;
        pFact = nullptr;
    }
    

    return 0;
}