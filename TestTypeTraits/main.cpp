#include "../TezcatFramework/include/TezConfig.h"



template<typename T>
struct is_int_helper : public std::false_type
{

};

template<>
struct is_int_helper<int> : public std::true_type
{

};

template<typename T>
struct is_int : public is_int_helper<std::remove_cv_t<T>>
{

};

int main()
{
    TEZ_CONSOLE_WRITE_LINE(is_int<int>::value);
    TEZ_CONSOLE_WRITE_LINE(is_int<float>::value);


    return 0;
}
