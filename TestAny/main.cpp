#include "../TezcatFramework/include/TezcatFramework.h"

using namespace tezcat;

using F = void(*)(const std::string&, int);
using F1 = std::function<double(std::string, int, float)>;
using Func = std::function<void(const std::string&, int)>;

F1 f1 = [](std::string msg, int a, float b)
    {
        TEZ_CONSOLE_WRITE(msg);
        return a + b;
    };

void test(const std::string& data, int i)
{
    TEZ_CONSOLE_WRITE_LINE(data << i);
}

class PP
{
public:
    PP() : p(100) {}
    PP(const PP& other) : name("copy constructor invoke")
    {
        TEZ_CONSOLE_WRITE_LINE(name);
    }

    PP(PP&& other) noexcept : name("move constructor invoke")
    {
        TEZ_CONSOLE_WRITE_LINE(name);
    }

    ~PP()
    {
        TEZ_CONSOLE_WRITE_LINE("deconstructor invoke");
    }

    void test(const std::string& data, int i)
    {
        std::string str("TypeInfo : [");
        std::cout << str << typeid(PP).name() << "]" << data << i << std::endl;
    }

    int p = 0;
    std::string name;
};

struct BB
{
    BB()
    {
        TEZ_CONSOLE_WRITE_LINE("constructor invoke");
    }

    BB(const BB& other)
    {
        TEZ_CONSOLE_WRITE_LINE("copy constructor invoke");
    }

    ~BB()
    {
        TEZ_CONSOLE_WRITE_LINE("deconstructor invoke");
    }
};

BB getBB()
{
    return BB();
}

void display1()
{
    int i = 10;
    float f = 3.3333f;

    TezAny a = std::string("hello_world");
    TEZ_CONSOLE_WRITE_LINE(a.cast<std::string>());

    PP c;
    a = std::move(c);
    TEZ_CONSOLE_WRITE_LINE(a.cast<PP>().p);

    a = 10;
    TEZ_CONSOLE_WRITE_LINE(a.cast<int>());

    a = &test;
    a.cast<F>()("Function Pointer Invoke!!", 30);

    a = f1;
    TEZ_CONSOLE_WRITE_LINE(a.cast<F1>()("std::function invoke!! ", 5, 3.5f));

    PP p;
    a = Func(std::bind(&PP::test, &p, std::placeholders::_1, std::placeholders::_2));
    a.cast<Func>()(" std::function Invoke!!", 40);
}

void display2()
{
    std::vector<TezAny> arrays;
    arrays.resize(8);

    arrays[0] = std::string("hohohohohoho");
    arrays[1] = 10;
    arrays[2] = 20.0f;
    arrays[3] = 30.0;
    arrays[4] = PP();
    arrays[5] = &test;
    arrays[6] = f1;
    arrays[7] = false;

    for (auto& a : arrays)
    {
        TEZ_CONSOLE_WRITE_LINE(a.toString());
    }
}

int main()
{
    display1();
    display2();

    TEZ_PAUSE;
    return 0;
}
