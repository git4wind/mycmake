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
enum class Type : char
{
    Sheep,
    Lion,
    Bat
};

class SmileFactory
{
public:
    AbstractSmile *createSmile(Type type)
    {
        AbstractSmile *ptr = nullptr;
        switch (type)
        {
        case Type::Sheep:
            ptr = new SheepSmile;
            break;
        case Type::Lion:
            ptr = new LionSmile;
            break;
        case Type::Bat:
            ptr = new BatSmile;
            break;
        default:
            break;
        }
        return ptr;
    }
};

int main()
{
    SmileFactory fact;
    AbstractSmile* obj = fact.createSmile(Type::Bat);
    if (obj)
    {
        obj->transform();
        obj->ability();
        delete obj;
    }
    
    return 0;
}