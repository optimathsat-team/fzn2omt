#include "configuration.h"
#include <iostream>
using namespace std;
namespace msat {

Configuration::Configuration(){
    bv_ = false;
    language_config_ = 0;
}

Configuration::Configuration(bool bv)
{
    bv_ = bv;
    language_config_ = 0;
}

Configuration::Configuration(bool bv, int language)
{
    bv_ = bv;
    language_config_ = language;
}

void Configuration::copy_to(Configuration *dest)
{
    *dest = *this;
}

} // namespace msat
