#include "configuration.h"
#include <iostream>
using namespace std;
namespace msat {

Configuration::Configuration(){
    bv_ = false;
}

Configuration::Configuration(bool bv)
{
    bv_ = bv;
}

void Configuration::copy_to(Configuration *dest)
{
    *dest = *this;
}

} // namespace msat
