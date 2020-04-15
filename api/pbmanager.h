// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
// Author: Patrick Trentin <patrick.trentin@unitn.it>
//
// This file is part of OptiMathSAT.

#ifndef PBMANAGER_H_INCLUDED
#define PBMANAGER_H_INCLUDED

#include "../api/optenvironment.h"
#include "../api/circuit.h"

namespace msat { namespace opt {

typedef std::pair<Term, Term> SoftClause;
typedef std::vector<SoftClause> SoftClauseStack;
typedef SoftClauseStack::iterator softclauses_iterator;
typedef SoftClauseStack::reverse_iterator softclauses_reverse_iterator;

class PBManager{
public:
    PBManager(TermManager *mgr,OptEnvironment *env_, Term id);
    ///< constructor

    ~PBManager();
    ///< destructor

    Circuit* new_circuit(Term weight);
    void do_push_soft_clause(const SoftClause &c);
    bool is_zero_weight(Term w);
    bool is_positive_weight(Term w);
    bool is_negative_weight(Term w);
    bool do_assert_soft_formula(Term c, Term w, Term &b_i, Term &nb_i, Term &w_i, Term &enc);
    void assert_soft_formula(Term c, Term w);
    bool has_pending_push(Term &cs);
    

    inline softclauses_iterator begin()
                { return stack_.begin(); };
    inline softclauses_iterator end()
                { return stack_.end(); };
    inline softclauses_reverse_iterator rbegin()
                { return stack_.rbegin(); };
    inline softclauses_reverse_iterator rend()
                { return stack_.rend(); };

    Term zero_;
protected:
    Term tid_;
private:
    typedef std::vector<Circuit*> CircuitList;
    typedef std::map<Term, CircuitList> CircuitsMap;

    CircuitsMap map_;
    Term pbsum_;
    TermList pbsums_;
    TermManager *mgr_;
    OptEnvironment *env_;
    Term lower_;
    Term upper_;
    SoftClauseStack stack_;
};

} // namespace opt
} // namespace msat

#endif // OPTENVIRONMENT_H_INCLUDED

