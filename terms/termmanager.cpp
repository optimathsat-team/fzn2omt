// -*- C++ -*-
//
// Author: Giuseppe Spallitta <giuseppe.spallitta@unitn.it>

#include "../terms/termmanager.h"
#include <assert.h>
#include <algorithm>
#include <stdlib.h>
using namespace std;

std::unordered_map<std::string, int> term2index;
std::unordered_set<std::string> unique_set_term;

namespace msat {

TermManager::TermManager()
{
    universe_ = new TypeUniverse();
    sig_ = new Signature(universe_);
    next_term_id_ = 1;
    smtlib_index_ = 10;
    next_simple_type_id_ = 1;
    next_variable_idx_ = 1;
    initialize_standard_signature();
}


TermManager::~TermManager()
{
   // Nothing to do
}

void TermManager::declare_var_print(const Symbol *expr){
    std::string name(expr->get_name());
    if(name.rfind(".pvt_fzn",0) == 0){
        std::replace(name.begin(), name.end(), ':', '_');
        if(unique_set_term.find(name) == unique_set_term.end()){
            unique_set_term.insert(name);
            std::cout<<"(declare-const "<<name<<" "<<expr->get_type()->get_name()<<")"<<std::endl; 
        }
    }else{
       std::cout<<"(declare-const "<<name<<" "<<expr->get_type()->get_name()<<")"<<std::endl; 
    }
}

bool TermManager::Term_eq::operator()(Term t1, Term t2) const
{
    const Symbol *s1 = t1->get_symbol();
    const Symbol *s2 = t2->get_symbol();

    if (s1 == s2) {
        return true;
    }
    return false;
}


size_t TermManager::Term_hash::operator()(Term t) const
{
    return t->get_symbol()->get_id();
}

const DataType *TermManager::make_simple_type(const std::string &name)
{
    DataType *dt = new DataType(next_simple_type_id_, name);
    next_simple_type_id_+=1;
    type_store_.insert(dt);
    return dt;
}

void TermManager::initialize_standard_signature()
{    
    boolean_ = make_simple_type("Bool");
    rational_ = make_simple_type("Real");
    integer_ = make_simple_type("Int");

    true_ = add_interpreted_symbol("true", boolean_);
    false_ = add_interpreted_symbol("false", boolean_);
    eq_rat_ = add_interpreted_symbol("=", rational_);
    eq_int_ = add_interpreted_symbol("=", integer_);
    leq_rat_ = add_interpreted_symbol("<=", rational_);
    leq_int_ = add_interpreted_symbol("<=", integer_);

    and_ = add_interpreted_symbol("and", boolean_ );
    or_ = add_interpreted_symbol("or", boolean_);
    iff_ = add_interpreted_symbol("=", boolean_);
    not_ = add_interpreted_symbol("not", boolean_);

    true_term_ = make_term(true_);
    false_term_ = make_term(false_);

    times_rat_ = add_interpreted_symbol("*", rational_);
    times_int_ = add_interpreted_symbol("*", integer_);
    plus_rat_ = add_interpreted_symbol("+", rational_);
    plus_int_ = add_interpreted_symbol("+", integer_);
    divide_ = add_interpreted_symbol("/", rational_);
}

const Symbol *TermManager::make_symbol(const std::string &name,
                                       const DataType *tp)
{
    if (name.size() == 0) {
        throw "Symbol name cannot be empty";
    }
    if (name[0] == '`') {
        throw ("Symbol cannot start with the \"`\" character");
    }
   
    const Symbol *ret = sig_->add_symbol(name, tp);
    return ret;

}


const Symbol *TermManager::make_unique_symbol(const std::string &prefix,
                                              const DataType *tp)
{
    Symbol *ret = NULL;
    
    std::string buf = "";
    buf.append(prefix);
    std::string int_buf;

    for (int i = 0; sig_->get_symbol(buf); ++i) {
        buf.append(" ");
        buf.append(std::to_string(i));
    }

    assert(!sig_->get_symbol(buf));

    return make_symbol(buf, tp);
}

const Symbol *TermManager::make_term_ite_symbol(const DataType *argtype)
{
    Symbol *ret = NULL;
    return ret;
}


bool TermManager::is_subtype(const DataType *subtp,
                             const DataType *supertp) const
{
    return universe_->is_subtype(subtp, supertp);                 
}

bool TermManager::is_constant(const Symbol *s) const
{
    return false;
}


bool TermManager::is_variable(const Symbol *s) const
{
    return false;
}

//-----------------------------------------------------------------------------
// Term creation
//-----------------------------------------------------------------------------

inline
Term TermManager::make_bin(const Symbol *symb,
                                  Term t1, Term t2,
                                  const char *where)
{
    Term ret = NULL;
    return ret;
}


Term TermManager::make_and(Term t1, Term t2)
{
    std::vector<Term> children;
    children.push_back(t1);
    children.push_back(t2);
    return make_term(and_, children);
}


Term TermManager::make_or(Term t1, Term t2)
{
   std::vector<Term> children;
    children.push_back(t1);
    children.push_back(t2);
    return make_term(or_, children);
}


Term TermManager::make_not(Term t)
{
    std::vector<Term> children;
    children.push_back(t);
    return make_term(not_, children);
}


Term TermManager::make_iff(Term t1, Term t2)
{
    std::vector<Term> children;
    children.push_back(t1);
    children.push_back(t2);
    return make_term(iff_, children);
}


Term TermManager::make_constant(const Symbol *symb)
{
    declare_var_print(symb);
    return make_term(symb);
}

Term TermManager::make_number(const Number &num)
{
    std::string snum = num.to_str();
    std::vector<Term> children;
    const DataType *tp = (snum.find('/') != std::string::npos) ?
            rational_ : integer_;
    if(tp == rational_){
        Number a1 = QNumber::from_str(snum.substr(0,snum.find('/')));
        Number b1 = QNumber::from_str(snum.substr(snum.find('/')+1,snum.length()));
        Term a = make_number(a1);
        Term b = make_number(b1);
        return make_divide(a,b);
    }
    else{
        const Symbol *s  = sig_->add_symbol(snum, tp);
        return make_term(s, children);
    }
}


Term TermManager::make_equal(Term t1, Term t2)
{
    Term ret = NULL;
    std::vector<Term> children;
    children.push_back(t1);
    children.push_back(t2);
    const Symbol *eq = NULL;
    const DataType *tp1 = t1->get_type(), *tp2 = t2->get_type();
    if(is_number(t1->get_symbol()) && is_number(t2->get_symbol())){
        std::string t1_name(t1->get_symbol()->to_str());
        std::string t2_name(t2->get_symbol()->to_str());
        if(atof(t1_name.c_str())==atof(t2_name.c_str()))
            return true_term_;
        else
            return false_term_;
    }else{
        if(tp1 == get_integer_type() && tp1 == tp2){
            eq = eq_int_;
        }
        else{
            eq = eq_rat_;
        } 
    }
    return make_term(eq, children);
}


Term TermManager::make_term_ite(Term c, Term t,
                                       Term e)
{
    Term ret = NULL;

    return ret;
}

Term TermManager::make_leq(Term t1, Term t2)
{
    std::vector<Term> children;
    children.push_back(t1);
    children.push_back(t2);
    const DataType *tp1 = t1->get_type(), *tp2 = t2->get_type();
    const Symbol *leq = NULL;
    if(is_number(t1->get_symbol()) && is_number(t2->get_symbol())){
        std::string t1_name(t1->get_symbol()->to_str());
        std::string t2_name(t2->get_symbol()->to_str());
        if(tp1 == get_integer_type() && tp1 == tp2){
            if(atoi(t1_name.c_str())<=atoi(t2_name.c_str()))
                return true_term_;
            else
                return false_term_;
        } 
    }  
    leq = leq_rat_;
    return make_term(leq, children);

}


Term TermManager::make_plus(Term t1, Term t2)
{
    Term ret = NULL;
    std::vector<Term> children;
    children.push_back(t1);
    children.push_back(t2);
    const DataType *tp1 = t1->get_type(), *tp2 = t2->get_type();
    if(is_number(t1->get_symbol()) && is_number(t2->get_symbol())){
        std::string t1_name(t1->get_symbol()->to_str());
        std::string t2_name(t2->get_symbol()->to_str());
        if(tp1 == get_integer_type() && tp1 == tp2)
            ret = make_number(atoi(t1_name.c_str()) + atoi(t2_name.c_str()));
        else
            ret = make_term(plus_rat_, children);  
    }else{
        ret =  make_term(plus_rat_, children);   
    }
    return ret;
}


Term TermManager::make_times(Term t1, Term t2)
{
    Term ret = NULL;
    std::vector<Term> children;
    children.push_back(t1);
    children.push_back(t2);

    const DataType *tp1 = t1->get_type(), *tp2 = t2->get_type();
    if(is_number(t1->get_symbol()) && is_number(t2->get_symbol())){
        std::string t1_name(t1->get_symbol()->to_str());
        std::string t2_name(t2->get_symbol()->to_str());
        if(tp1 == get_integer_type() && tp1 == tp2)
            ret = make_number(atoi(t1_name.c_str()) * atoi(t2_name.c_str()));
        else{ 
            ret = make_term(times_rat_, children); 
        }
    }else{
        ret =  make_term(times_rat_, children);   
    }
    return ret;
}


Term TermManager::make_divide(Term t1, Term t2)
{
    Term ret = NULL;
    std::vector<Term> children;
    children.push_back(t1);
    children.push_back(t2);
    ret =  make_term(divide_, children);
    return ret;
}


Term TermManager::make_floor(Term t)
{
    Term ret = NULL;
    return ret;
}

void TermManager::typecheck(Term term, const DataType *tp,
                            const char *where) const
{

}

Term TermManager::make_term(const Symbol *symb, std::vector<Term> children)
{
    Term_ *ret = new Term_(0, symb);
    for(int i=0; i<children.size(); i++){
        ret->add_child(children[i]);
    }
    ret->id_ = next_term_id_;
    next_term_id_+=1;
    return ret;
}

} // namespace msat
