// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
// Author: Patrick Trentin <patrick.trentin@unitn.it>
//
// This file is part of OptiMathSAT.

#ifndef OBJECTIVE_H_INCLUDED
#define OBJECTIVE_H_INCLUDED

#include "../terms/term.h"
#include<string>
#include<vector>
#include<map>

namespace msat {

namespace opt {

class Objective {
public:
    typedef enum {
        MINIMIZE,
        MAXIMIZE,
    } goal;

    Objective(Term obj,
              Objective::goal g,
              bool strict,
              Term cvar,
              Term cvar_proxy,
              Term bounds_proxy,
              Term incr_proxy,
              Term ass_constr,
              bool bounded_decl);
    virtual ~Objective();

    inline const DataType* get_type() const
                { return obj_->get_type(); };

    inline Term get_obj_function() const
                { return obj_; };
    inline goal get_goal() const
                { return goal_; };
    inline bool has_strict_bound() const
                { return strict_bound_; };
    inline Term get_obj_var() const
                { return cvar_; };
    inline Term get_cost_var_proxy() const
                { return cvar_proxy_; };
    inline Term get_bounds_proxy() const
                { return bounds_proxy_; };
    inline Term get_incr_proxy() const
                { return incr_proxy_; };
    inline Term get_assertion_constraints() const
                { return ass_constr_; };
    inline bool bounded_declaration() const
                { return bounded_decl_; };

private:
    Term obj_;
    ///< objective function
    const Objective::goal goal_;
    ///< desired optimization direction for this objective
    const bool strict_bound_;
    ///< true iff the initial bound opposite to optimization
    ///< direction is to be interpreted as strict. This
    ///< is needed because FlatZinc has non-strict bounds.
    Term cvar_;
    ///< variable associated with objective function
    ///< TODO(PT): can it be removed? see objectivefactory.cpp
    Term cvar_proxy_;
    ///< asserting this binds 'cvar_' to 'obj_'
    Term bounds_proxy_;
    ///< asserting this applies any initial bound
    ///< to 'cvar_'
    Term incr_proxy_;
    ///< asserting this implies bounds_proxy_, plus any
    ///< additional bound placed on cvar_ by the optimization
    ///< search algorithm along the search
    Term ass_constr_;
    ///< set of constraints which must always be asserted when
    ///< the objective is pushed on stack, independently of
    ///< the optimization combination approach.
    const bool bounded_decl_;
    ///< true iff the objective function was declared with
    ///< some bound. This flag does not take into account
    ///< any bound inferred by OptiMathSAT, and it is used
    ///< by an heuristic to allow for early termination
    ///< when a given objective(+bounds!) is UNSAT.

}; /*** Objective ***/

typedef std::vector<Objective *> ObjectiveList;
typedef std::map<const std::string, Objective *> ObjectiveMap;
typedef ObjectiveList::iterator objective_iterator;
typedef ObjectiveList::reverse_iterator objective_reverse_iterator;

} /*** namespace msat::opt ***/
} /*** namespace msat ***/

#endif
