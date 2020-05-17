#include "configuration.h"
#include <iostream>
using namespace std;
namespace msat {

Configuration::Configuration(){
    bv_ = false;
    language_ = 0;
}

Configuration::Configuration(bool bv)
{
    bv_ = bv;
    language_ = 0;
}

Configuration::Configuration(bool bv, int language)
{
    bv_ = bv;
    language_ = language;
}

void Configuration::copy_to(Configuration *dest)
{
    *dest = *this;
}

} // namespace msat
