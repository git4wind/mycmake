#include <iostream>  // 字符串类,cout,cin,endl;
#include <map>  // map<> 容器
#include <list>  // list<> 容器
#include <typeinfo> // typeid(t)获取对象的类型;
#include <functional>  // 可调用对象包装器function<void(int,string)> ,std::bind<funcptr,placeholders::_1,...>
#include <memory>  // 智能指针: std::shared_ptr<>, std::unique_ptr<>,std::weak_ptr<>

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

//lambda
void lambdafunc(int x, int y)
{
    int a = 0;
    int b = 1;
    //lambda []没有捕获参数,则此表达式可转化为函数指针;
    using ptr = void(*)(int);
    ptr ptr1 = [](int x)
    {
        cout << "x: " << x << endl;
    };
    ptr1(10);
    //对于lambda表达式[=,&,...]有参数捕获的,lambda表达式就只能是仿函数类型;
    //使用可调用对象包装器function<> 对lambda表达式进行包装;   //mutable选项可修改仿函数operate()的const属性;
    function<void(int)> ff1 = [=](int y) mutable
    {
        cout << "y: " << y << endl;
    };
    ff1(11);
    //使用可调用对象绑定器bind() 对lambda表达式进行绑定;
    function<void(int)> ff2 = std::bind([=](int z) mutable
    {
        cout << "z: " << z << endl;
    },placeholders::_1 );
    ff2(12);

}
//右值引用的作用和使用
class ReadOnlyValue
{
public:
    ReadOnlyValue():m_pNum(new int(100))
    {
        cout << "construct class : it is. " << endl;
        printf("m_pNum 地址: %p \n" , m_pNum);
    }
    //拷贝构造函数防止浅拷贝;
    ReadOnlyValue(const ReadOnlyValue & a) : m_pNum(new int(*a.m_pNum))
    {
        cout << "copy construct : it is." << endl;
    }
    //右值引用构造函数或者叫移动构造函数,目标(目的): 复用其他对象中的资源(堆内存) ;实现浅拷贝不去使用深拷贝;
    ReadOnlyValue(ReadOnlyValue && a) : m_pNum(a.m_pNum)
    {
        a.m_pNum = nullptr;
        cout << "move construct : 浅拷贝." << endl;
    }

    ~ReadOnlyValue()
    {
        cout << "destruct class : delete new  ptr attr." << endl;
        if(m_pNum)
        {
            delete m_pNum;
            m_pNum = nullptr;
        }
    }
public:
    int * m_pNum = nullptr;

};
//返回将亡值得方式:
ReadOnlyValue getObj()
{
    ReadOnlyValue rightValue;
    return rightValue;
}
ReadOnlyValue getObj1()
{
    return ReadOnlyValue();
}
ReadOnlyValue && getObj2()
{
    return ReadOnlyValue();
}
//std::forward<T >(t)
template<typename T>
void printValue(T& t)
{
    cout << "left-value: " << t << endl;
}

template<typename T>
void printValue(T&& t)
{
    cout << "right-value: " << t << endl;
}
// 泛型编程 T&& 和 auto &&,在这2中场景下 && 被称作未定的引用类型; 未定类型引用的推导, 规则: 右值或者非右值(右值引用,左值,左值引用,常量右值引用,常量左值引用);
// 1, const T&& 表示一个右值引用,不是未定引用类型; 2, 通过右值推导 T&&或者auto&& 得到的是一个右值引用类型; 否则通过非右值推导T&&或者auto&& 得到的是一个左值引用类型;
template<typename T>
void testForward(T && v)
{
    printValue(v);
    printValue(std::move(v));
    printValue(std::forward<T>(v));
    cout << endl;
}
//
struct Sharedptr
{
    shared_ptr<Sharedptr> getPtr()
    {
        return shared_ptr<Sharedptr>(this);
    }
    ~Sharedptr()
    {
        cout << "class Sharedptr is disstruct..." << endl;
    }
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
#if 0
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
#endif
#if 0
    //lambda
    lambdafunc(1,2);
    //左值: loactor value ;可取地址的值; 指存储在内存中、有明确存储地址（可取地址）的数据；
    //右值: read value ; 只读的值; 右值是指可以提供数据值的数据（不可取地址）；
    //左值
    int nNum = 9;
    //左值引用
    int & a = nNum;
    //右值 右值引用:只能通过右值进行初始化;
    int && b = 8;
    //常量左值引用 ; //constexpr 编译阶段会替换表达式,提高运行效率;
    const int & c = nNum;
    const int & f = b;
    //常量右值引用
    const int && d = 6;
    //const int && e = b; //error
    //int && e = b; //error
    const int & g = d;
    const int & h = a;
    //右值引用可以延长某块内存的生命周期;
    // 右值:分纯右值和将亡值;
    // 纯右值:非引用返回的临时变量,运算表达式产生的临时变量,原始字面量和lambda表达式等;
    // 将亡值:与右值引用相关的表达式,比如,T&&类型函数的返回值,std::move的返回值等;
    //下面2个赋值方式都要求右侧的对象一定是临时对象;
    ReadOnlyValue rightValue = getObj(); //getObj()函数返回的是临时对象则会调用 ReadOnlyValue的移动构造函数来保留堆内存,如果返回的不是临时对象则编译器会调用ReadOnlyValue的拷贝构造函数;
    cout << "右值引用赋值方式2:" << endl;
    ReadOnlyValue && rightValue1 = getObj();
    printf("右值引用赋值后的 m_pNum 地址: %p \n", rightValue1.m_pNum);
    //如果没有移动构造函数,使用右值引用初始化的要求会更高一些;
    //要求右侧是一个临时的不能取地址的对象, 如 return ReadOnlyValue();
    cout << "无移动构造函数,右值引用初始化:" << endl;
    ReadOnlyValue && rightValue2 = getObj1();
    printf("没有移动构造函数,右值引用初始化: m_pNum 地址: %p \n", rightValue2.m_pNum);
    //std::move 作用是将左值转化为右值(将亡值),转移资源来减少拷贝;
    ReadOnlyValue && rightValue3 = std::move(rightValue1);
    std::list<string> ls1{"test1", "test2","test3"};
    std::list<string> ls2 = ls1;
    std::list<string> ls3 = std::move(ls2);
    //函数原型:  //template<class T> T&& forward(typename remove_reference<T>::type& t) noexcept;
                //template<class T> T&& forward(typename remove_reference<T>::type&& t) noexcept;
    //std::forward<T >(t) 完美转发,按参数的原来的类型转发到另一个函数;
    //forward<T>(t)返回类型: 当T为左值引用类型时,t将被转换为T类型的左值;否则T为其他情况,t都被转换为T类型的右值;
    testForward(520);
    int num = 1314;
    testForward(num);
    testForward(forward<int>(num));
    testForward(forward<int&>(num));
    testForward(forward<int&&>(num));
#endif
    //#include <memory> 智能指针; //通过构造函数初始化;
    std::shared_ptr<int> ptr1(new int(3));
    cout << "ptr1 use_count: " << ptr1.use_count() << endl;
    //通过移动构造和拷贝构造函数初始化;
    shared_ptr<int> ptr2 = std::move(ptr1);
    cout << "ptr1 use_count: " << ptr1.use_count() << endl;
    cout << "ptr2 use_count: " << ptr2.use_count() << endl;
    shared_ptr<int> ptr3 = ptr2;
    cout << "ptr2 use_count: " << ptr2.use_count() << endl;
    cout << "ptr3 use_count: " << ptr3.use_count() << endl;
    //通过 std::make_shared 初始化;
    shared_ptr<int> ptr4 = std::make_shared<int>(5);
    //通过reset()初始化;
    ptr4.reset();
    cout << "ptr4 use_count: " << ptr4.use_count() << endl;
    ptr3.reset(new int(9));
    cout << "ptr3 use_count: " << ptr3.use_count() << endl;
    cout << "ptr2 use_count: " << ptr2.use_count() << endl;
    //获取原始指针;
    int* ptr = ptr3.get(); //ptr3作为智能指针对象操作用. ;
    *ptr = 8;
    *ptr3 = 10; //ptr3作为指针指向内存的类型时用-> ;
    //指定智能指针shared_ptr<T> 删除器函数;
    shared_ptr<int> ptr5(new int(6),[](int* pt){
        if(pt)
        {
            delete pt;
            pt = nullptr;
            cout << "智能指针的删除器函数被调用..." << endl;
        }
    });
    // 智能指针管理内存是数组类型时必须指定删除器了;
    shared_ptr<int> ptr6(new int[3],[](int* pt){
        if (pt)
        {
            delete[] pt;
            pt = nullptr;
            cout << "智能指针的删除器函数被调用..." << endl;
        }
    });
    shared_ptr<int> ptr7(new int[4], std::default_delete<int[]>() );
    //unique_ptr<T> 1,通过构造函数初始化;
    unique_ptr<int> ptr8(new int(8));
    // 通过移动构造函数初始化;
    unique_ptr<int> ptr9 = std::move(ptr8);
    // 通过reset()初始化;
    ptr9.reset(new int(9));
    //获取原始指针;
    int* ptr10 = ptr9.get();
    *ptr10 = 10;
    *ptr9 = 90;
    //unique<T> 指定删除器;
    using ptrFunc = void(*)(int *); //无参数时可以看作是函数指针;
    unique_ptr<int, ptrFunc> ptr11(new int(11), [](int* pt){
        if (pt)
        {
            delete pt;
            pt = nullptr;
            cout << "unique_ptr delete memory..." << endl;
        }
        
    });
    //有参数时,lambda表达式就是仿函数,必须使用可调用对象包装器function<void(int *)>对仿函数(lambda表达式)进行包装;
    unique_ptr<int, function<void(int *)>> ptr12(new int(12), [=](int *pt){
        if (pt)
        {
            delete pt;
            pt = nullptr;
            cout << "unique_ptr delete memory with lambda..." << endl;
        }
    });
    unique_ptr<int[]> ptr13(new int[3]);
    shared_ptr<int[]> ptr14(new int[2]);
    //weak_ptr<T> 初始化;
    shared_ptr<int> sp(new int(1));
    weak_ptr<int> wp1;  //空对象,未被实例化;
    weak_ptr<int> wp2(wp1); //空对象,未被实例化;
    weak_ptr<int> wp3(sp);
    weak_ptr<int> wp4 = sp;
    weak_ptr<int> wp5 = wp3;
    // lock():获取管理所监测资源的 shared_ptr<T> 对象;
    shared_ptr<int> sp1, sp2;
    weak_ptr<int> wp;
    sp1 = make_shared<int>(521);
    wp = sp1;
    sp2 = wp.lock();
    cout << "weak_ptr<int> use_count: " << wp.use_count() << endl;
    // reset() 清空对象,使其不监测任何资源(内存);
    sp1.reset();
    cout << "weak_ptr<int> use_count: " << wp.use_count() << endl;
    sp1 = wp.lock();
    cout << "weak_ptr<int> use_count: " << wp.use_count() << endl;
    // expired() 判断观测的资源是否已经被释放;
    cout << "1.weak_ptr<int> wp " << (wp.expired()? "is" : "is not") << " expired." << endl;
    wp.reset();
    cout << "2.weak_ptr<int> wp " << (wp.expired()? "is" : "is not") << " expired." << endl;
    cout << "shared_ptr<int> use_count: " << sp1.use_count() << endl;
    cout << "*sp1: " << *sp1 << endl;
    cout << "*sp2: " << *sp2 << endl;
    /** shared_ptr<T> 使用的注意事项:
     * 1.不能使用同一个原始地址初始化多个共享智能指针
     * 2.函数不能返回管理了this的共享智能指针对象.this 也是相当于原始地址;
     * 3.共享智能指针不能循环引用
    */
   Sharedptr * pst = new Sharedptr;
   shared_ptr<Sharedptr> stt1(pst);
   //shared_ptr<Sharedptr> stt2(pst); //error
   shared_ptr<Sharedptr> stt2 = stt1;


    return 0;
}