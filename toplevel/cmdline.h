// -*- C++ -*-
//
// Author: Giuseppe Spallitta <giuseppe.spallitta@unitn.it>


#ifndef MSAT_CMDLINE_H_INCLUDED
#define MSAT_CMDLINE_H_INCLUDED

#include "../utils/exception.h"
#include "../configuration.h"
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
// EDIT (p.t.): added methods to support flatzinc interface
#include "../msatconfig.h"
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

namespace msat {

class CmdLine{
public:
    MSAT_DECLARE_EXCEPTION(error)
    
    CmdLine();
    CmdLine(bool bv);
    ~CmdLine();

    const std::string &get_input_file();

    void update_config(Configuration *cfg);

    bool fzn_all_solutions();
    bool fzn_max_solutions();
    bool fzn_bv_integers();
    bool fzn_bv_all_different();
private:
    std::string inputfile_;
    Configuration config_;
    bool bv_;

};

inline bool fzn_all_solutions(){
	return false;
}

inline bool fzn_max_solutions(){
	return false;
}

} // namespace msat

#endif // MSAT_CMDLINE_H_INCLUDED
