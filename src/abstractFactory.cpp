#include <iostream>
#include <map>
#include <list>
#include <typeinfo>
#include <functional>

using namespace std;

// 船体
class ShipBody
{
public:
    virtual string getBody() = 0;
    virtual ~ShipBody(){};
};

class WoodBody : public ShipBody
{
public:
    string getBody() override
    {
        return string("使用<木材>制作船体...");
    }
};
class IronBody : public ShipBody
{
public:
    string getBody() override
    {
        return string("使用<钢铁>制作船体...");
    }
};
class MetaBody : public ShipBody
{
public:
    string getBody() override
    {
        return string("使用<合成金属>制作船体...");
    }
};
// 引擎
class Engine
{
public:
    virtual string getEngine() = 0;
    virtual ~Engine(){};
};
class Human : public Engine
{
    string getEngine() override
    {
        return string("船的动力方式是<手划>...");
    }
};
class Diesel : public Engine
{
    string getEngine() override
    {
        return string("船的动力方式是<内燃机>...");
    }
};
class Nuclear : public Engine
{
    string getEngine() override
    {
        return string("船的动力方式是<核反应堆>...");
    }
};

// 武器
class Weapon
{
public:
    virtual string getWeapon() = 0;
    virtual ~Weapon(){};
};
class Gun : public Weapon
{
    string getWeapon() override
    {
        return string("船上防卫武器系统是<枪>...");
    }
};
class Cannon : public Weapon
{
    string getWeapon() override
    {
        return string("船上防卫武器系统是<炮>...");
    }
};
class Laser : public Weapon
{
    string getWeapon() override
    {
        return string("船上防卫武器系统是<激光>...");
    }
};

// 攒一条船
class Ship
{
public:
    Ship(ShipBody *pBody, Engine *pEngine, Weapon *pWeapon) : m_pBody(pBody), m_pEngine(pEngine), m_pWeapon(pWeapon){};
    ~Ship()
    {
        if (m_pBody)
        {
            delete m_pBody;
            m_pBody = nullptr;
        }
        if (m_pEngine)
        {
            delete m_pEngine;
            m_pEngine = nullptr;
        }
        if (m_pWeapon)
        {
            delete m_pWeapon;
            m_pWeapon = nullptr;
        }
    }
    string getProperty()
    {
        string info = m_pBody->getBody() + m_pEngine->getEngine() + m_pWeapon->getWeapon();
        return info;
    }

private:
    ShipBody *m_pBody = nullptr;
    Engine *m_pEngine = nullptr;
    Weapon *m_pWeapon = nullptr;
};

// 抽象造船工厂
class AbstractFactory
{
public:
    virtual Ship *createShip() = 0;
    virtual ~AbstractFactory(){};
};

class BasicFactory : public AbstractFactory
{
public:
    Ship *createShip() override
    {
        Ship *pShip = new Ship(new WoodBody, new Human, new Gun);
        cout << "基础款的船已经建造完成..." << endl;
        return pShip;
    }
};
class StandardFactory : public AbstractFactory
{
public:
    Ship *createShip() override
    {
        Ship *pShip = new Ship(new IronBody, new Diesel, new Cannon);
        cout << "标准款的船已经建造完成..." << endl;
        return pShip;
    }
};
class UltimateFactory : public AbstractFactory
{
public:
    Ship *createShip() override
    {
        Ship *pShip = new Ship(new MetaBody, new Nuclear, new Laser);
        cout << "旗舰款的船已经建造完成..." << endl;
        return pShip;
    }
};

#if 1
class T1
{
public:
    static int get()
    {
        return 100;
    }
};
class T2
{
public:
    static string get()
    {
        return string("hello world!");
    }
};
template <class T>
void func()
{
    auto ret = T::get();
    cout << "auto: function template: " << ret << endl;
}

template <typename T>
class Container
{
public:
    void printList(T t)
    {
        if (typeid(t) == typeid(std::list<int>))
        {
            for (m_it = t.begin(); m_it != t.end(); m_it++)
            {
                cout << typeid(t).name() << " value: " << *m_it << endl;
            }
            for (auto &it : t)
            {
                cout << "auto & for: value: " << it << endl;
            }
        }
    }
    void printMap(T t)
    {
        if (typeid(t) == typeid(std::map<int, int>) || typeid(t) == typeid(std::map<int, string>))
        {
            for (m_it = t.begin(); m_it != t.end(); m_it++)
            {
                cout << typeid(t).name() << " key: " << m_it->first << ", value: " << m_it->second << endl;
            }
            for (auto &it : t)
            {
                // it.first += 10;  //set and map: must be !! const !! 关联型容器在基于范围的for(c++11);
                cout << "set and map: must be !! const !! auto & for: key: " << it.first << ", value: " << it.second << endl;
            }
        }
    }

private:
    decltype(T().begin()) m_it;
};
// 返回值类型后置;
template <typename T, typename U>
auto add(T t, U u) -> decltype(t + u)
{
    return t + u * 2;
}
// func ptr
int mytest(int a, string b)
{
    cout << "a: " << a << ", b: " << b << endl;
    return 0;
}
typedef int (*func1)(int, string);
using func2 = int (*)(int, string);
//
template <typename T>
struct MyMap
{
    typedef map<int, T> mapType;
};

template <typename T>
using MMap = map<int, T>;

// 委托构造和继承构造
class Base
{
public:
    Base(int i) : m_i(i) {}
    Base(int i, double j) : m_i(i), m_j(j) {}
    Base(int i, double j, string k) : m_i(i), m_j(j), m_k(k) {}

    virtual void test() {}

    void func(int i)
    {
        cout << "base class: i = " << i << endl;
    }
    void func(int i, string str) // 类多态: 重载函数;
    {
        cout << "base class: i= " << i << ", str= " << str << endl;
    }

public:
    int m_i;
    double m_j;
    string m_k;
};

class Child : public Base
{
public:
    using Base::Base; // 继承构造: 直接使用父类的所有同名Base构造函数;
    using Base::func; // 恢复被子类覆盖而隐藏的所有同名fun函数;

    void test() {} // 类多态:子类 重写 父类的(纯)虚函数;

    void func() // 子类func函数 覆盖 了父类的所有同名func函数;父类所有同名fun函数都将被隐藏,无法调用除非在子类中使用using base::func;
    {
        cout << "child class: i am luffy !!!" << endl;
    }
};
// 可调用对象和绑定器;
using funcptr = void (*)(int, string);

class Test
{
public:
    // 重载()
    void operator()(string msg)
    {
        cout << "仿函数: " << msg << endl;
    }
    // 将类对象转换为函数指针;
    operator funcptr()
    {
        return world;
    }
    void hello(int a, string s)
    {
        cout << "h,number: " << a << ", name: " << s << endl;
    }
    static void world(int a, string s)
    {
        cout << "w,number: " << a << ", name: " << s << endl;
    }

public:
    int m_id = 0;
    string m_str;
};
void print(int a, string s)
{
    cout << "a: " << a << ", s: " << s << endl;
}
class A
{
public:
    A(const function<void(int, string)> &f) : callback(f)
    {
    }
    void notify(int id, string name)
    {
        callback(id, name);
    }

private:
    function<void(int, string)> callback;
};

void testFunc(int x, int y, const std::function<void(int, int)>& f )
{
    if (x % 2)
    {
        f(x,y);
    }
}
void output_add(int x, int y)
{
    cout << "x: " << x << " ,y: " << y << ", x+y: " << x+y <<endl;
}
class Test2
{
public:
    void output(int x, int y)
    {
        cout << "x1: " << x << " ,y1: " << y << endl;
    }

public:
    int m_num = 100;
};

#endif

int main()
{
#if 0
    // 下单造旗舰款的船;
    AbstractFactory *pFact = new UltimateFactory;
    if (pFact)
    {
        Ship *pShip = pFact->createShip();
        if (pShip)
        {
            cout << pShip->getProperty() << endl;
            delete pShip;
            pShip = nullptr;
        }
        delete pFact;
        pFact = nullptr;
    }
    //
    map<int, string> mp = {make_pair(1, "ace"), make_pair(2, "bob")};
    mp.insert(make_pair(3, "che"));
    auto it = mp.begin();
    for (; it != mp.end(); it++)
    {
        cout << "key:" << it->first << "  value:" << it->second << endl;
    }
    //
    func<T1>();
    func<T2>();
    // decltype(表达式)编译期间推导出类型,根据已知类型推导; 与auto区别:变量定义时必须初始化才能用auto;
    int a = 100;
    decltype(a) b = 99;
    decltype(a + b) c = 88;
    decltype(c + 3.14) d = 5.55;
    list<int> ls{1, 2, 3, 4, 5};
    Container<list<int>> cc;
    cc.printList(ls);
    auto dd = add<int, double>(5, 6.6);
    cout << "auto decltype: " << dd << endl;
    for(auto & it : ls)
    {
        cout << "atuo & for: " << it << endl;
    }

    //
    func1 f1 = mytest;
    func2 f2 = mytest;
    f1(100, "hello");
    f2(100, "hello");
    (*f1)(100, "hello");
    //
    MyMap<int>::mapType mm1;
    mm1.insert(make_pair(1, 1));
    mm1.insert(make_pair(2, 2));
    Container<MyMap<int>::mapType> c1;
    c1.printMap(mm1);
    MMap<string> mm2;
    mm2.insert(make_pair(1, "mm2"));
    mm2.insert(make_pair(2, "mm2"));
    Container<MMap<string>> c2;
    c2.printMap(mm2);
    //
    Child ch(520,13.14, "i love u");
    cout << "int: " << ch.m_i << ",double: " << ch.m_j << ",string= " << ch.m_k << endl;
    ch.func();
    ch.func(100,"hello");
#endif
    Test t;
    t("我是仿函数");
    Test tt;
    tt(100, "testname");
    // 类的函数指针
    funcptr f = Test::world;
    using fptr = void (Test::*)(int, string);
    fptr f1 = &Test::hello;
    // 类的成员指针(变量)
    using ptr1 = int Test::*;
    ptr1 pt = &Test::m_id;
    Test ttt; // 可调用对象的定义和调用;
    (ttt.*f1)(22, "ice");
    ttt.*pt = 100;
    cout << "m_id: " << ttt.m_id << endl;

    // 可调用对象包装器; std::function<>
    // 1,包装普通函数;
    function<void(int, string)> f11 = print;
    // 2,包装类的静态函数;
    function<void(int, string)> f12 = Test::world;
    // 3,包装仿函数;
    Test ta;
    function<void(string)> f13 = ta;
    // 4,包装可转换为函数指针的对象;
    Test tb;
    function<void(int, string)> f14 = tb;
    // 调用
    f11(1, "aaa");
    f12(2, "bbb");
    f13("ccc");
    f14(3, "ddd");
    A aa(print);
    aa.notify(1,"ace");
    A ab(Test::world);
    ab.notify(2,"abc");
    A ac(tb);
    ac.notify(3,"ddd");

    //可调用对象绑定器; std::bind()返回的是一个仿函数,可将返回值直接赋值给std::function<>
    std::bind(print, placeholders::_1, placeholders::_2)(11,"11");
    std::bind(print, placeholders::_1, "22")(22);
    std::bind(print, 33, "33")();
    //
    for (int i = 0; i < 10; i++)
    {
        auto f = std::bind(output_add, i +100, i+200);
        testFunc(i, i, f);
        auto f1 = std::bind(output_add, placeholders::_1, placeholders::_2);
        testFunc(i,i,f1);
    }
    Test2 ts2;
    auto f2 = std::bind(&Test2::output, &ts2, placeholders::_1,placeholders::_2);
    f2(100,200);
    auto f3 = std::bind(&Test2::m_num, &ts2);
    f3() = 666;
    cout << "f3(): " << f3() << endl;
    //可调用对象包装器来包装仿函数(std::bind绑定器返回的就是仿函数);
    function<void(int, int)> f22 = std::bind(&Test2::output, &ts2, placeholders::_1,placeholders::_2);
    f22(200,100);
    function<int &()> f33 = std::bind(&Test2::m_num, &ts2);
    f33() = 888;
    cout << "f33(): " << f33() << endl;


    return 0;
}