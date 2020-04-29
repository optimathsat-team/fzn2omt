// -*- C++ -*-
// 
// Author: Alberto Griggio <giuseppe.spallitta@unitn.it>

#include "../toplevel/cmdline.h"
#include "../msatconfig.h"
#include <iostream>
#include <fstream>

using namespace std;

#ifdef USE_GOOGLE_PROFILER
#  include <google/profiler.h>
#endif

namespace msat {

CmdLine::CmdLine(){
	bv_ = false;
}

CmdLine::CmdLine(bool bv){
	bv_ = bv;
}


CmdLine::~CmdLine()
{
}

const std::string &CmdLine::get_input_file()
{
    return inputfile_;
}

bool CmdLine::fzn_bv_integers(){
	return bv_;
}

bool CmdLine::fzn_bv_all_different(){
	return bv_;
}

void CmdLine::update_config(Configuration *cfg){
}


} // namespace msat
