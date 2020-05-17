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

TermManager::TermManager(bool bv_enc)
{
    universe_ = new TypeUniverse();
    sig_ = new Signature(universe_);
    next_term_id_ = 1;
    smtlib_index_ = 10;
    next_simple_type_id_ = 1;
    next_variable_idx_ = 1;
    initialize_standard_signature();
    bv_enc_ = bv_enc;
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
            if(is_bv_enc() && expr->get_type()->get_name() == "Int")
                std::cout<<"(declare-const "<<name<<" "<<"(_ BitVec 25)"<<")"<<std::endl; 
            else 
                std::cout<<"(declare-const "<<name<<" "<<expr->get_type()->get_name()<<")"<<std::endl; 
        }
    }else{
       if(is_bv_enc() && expr->get_type()->get_name() == "Int" && name.rfind(".pb_",0) != 0)
            std::cout<<"(declare-const "<<name<<" "<<"(_ BitVec 25)"<<")"<<std::endl; 
        else 
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
    bv_typeclass_ = make_simple_type("BV");

    true_ = add_interpreted_symbol("true", boolean_);
    false_ = add_interpreted_symbol("false", boolean_);
    eq_rat_ = add_interpreted_symbol("=", rational_);
    eq_int_ = add_interpreted_symbol("=", integer_);
    leq_rat_ = add_interpreted_symbol("<=", rational_);
    leq_int_ = add_interpreted_symbol("<=", integer_);
    bv_ = add_interpreted_symbol("to_bv",bv_typeclass_);

    and_ = add_interpreted_symbol("and", boolean_ );
    or_ = add_interpreted_symbol("or", boolean_);
    iff_ = add_interpreted_symbol("=", boolean_);
    not_ = add_interpreted_symbol("not", boolean_);

    true_term_ = make_term(true_);
    false_term_ = make_term(false_);
    bv_term_ = make_term(bv_);

    times_rat_ = add_interpreted_symbol("*", rational_);
    times_int_ = add_interpreted_symbol("*", integer_);
    plus_rat_ = add_interpreted_symbol("+", rational_);
    plus_int_ = add_interpreted_symbol("+", integer_);
    divide_ = add_interpreted_symbol("/", rational_);
    minus_ = add_interpreted_symbol("-", integer_);

    to_int_ = add_interpreted_symbol("to_int", integer_);
    bvneg_ = add_interpreted_symbol("bvneg", bv_typeclass_);
    bvsub_ = add_interpreted_symbol("bvsub", bv_typeclass_);
    bvmul_ = add_interpreted_symbol("bvmul", bv_typeclass_);
    bvadd_ = add_interpreted_symbol("bvadd", bv_typeclass_);
    bvsle_ = add_interpreted_symbol("bvsle", bv_typeclass_);
    bvule_ = add_interpreted_symbol("bvule", bv_typeclass_);
    bvcomp_ = add_interpreted_symbol("bvcomp", bv_typeclass_);
    bvudiv_ = add_interpreted_symbol("bvudiv", bv_typeclass_);
    bvsdiv_ = add_interpreted_symbol("bvsdiv", bv_typeclass_);
    bvconcat_ = add_interpreted_symbol("concat", bv_typeclass_);
    bvslt_ = add_interpreted_symbol("bvslt", bv_typeclass_);
    bvslt_ = add_interpreted_symbol("bvult", bv_typeclass_);
    bv_sign_extend_ = add_interpreted_symbol("(_ sign_extend 1)", bv_typeclass_);
    sbv_to_int_ = add_interpreted_symbol("sbv_to_int", integer_);

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

Term TermManager::make_negative(Term t)
{
    std::vector<Term> children;
    children.push_back(t);
    return make_term(minus_, children);
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
    if(snum[0] == '-'){
        Number non_negative = QNumber::from_str(snum.substr(1,snum.length()));
        Term x = make_number(non_negative);
        return make_negative(x);
    }
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
    Number a;
    const DataType *tp1 = t1->get_type(), *tp2 = t2->get_type();
    if(is_number(t1->get_symbol(),&a) && is_number(t2->get_symbol(),&a)){
        std::string t1_name(t1->get_symbol()->to_str());
        std::string t2_name(t2->get_symbol()->to_str());

        if(atof(t1_name.c_str())==atof(t2_name.c_str()))
            return true_term_;
        else
            return false_term_;
    }else{
        if(tp1 == get_rational_type() || tp2 == get_rational_type()){
            eq = eq_rat_;
        }
        else{
            eq = eq_int_;
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
    Number n;
    if(is_number(t1->get_symbol(),&n) && is_number(t2->get_symbol(),&n)){
        std::string t1_name(t1->get_symbol()->to_str());
        std::string t2_name(t2->get_symbol()->to_str());
        if(tp1 == get_integer_type() && tp1 == tp2){
            if(atoi(t1_name.c_str())<=atoi(t2_name.c_str()))
                return true_term_;
            else
                return false_term_;
        } 
    } 
    if(tp1 == get_rational_type() || tp2 == get_rational_type()){
        leq = leq_rat_;
    }else if(!is_bv_enc()){
        leq = leq_int_;
    }else{
        leq = bvsle_;
    }
    return make_term(leq, children);

}


Term TermManager::make_plus(Term t1, Term t2)
{
    Term ret = NULL;
    std::vector<Term> children;
    children.push_back(t1);
    children.push_back(t2);
    Number a;
    const DataType *tp1 = t1->get_type(), *tp2 = t2->get_type();
    if(is_number(t1->get_symbol(), &a) && is_number(t2->get_symbol(), &a)){
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
    Number a;
    const DataType *tp1 = t1->get_type(), *tp2 = t2->get_type();
    if(is_number(t1->get_symbol(), &a) && is_number(t2->get_symbol(), &a)){
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
    return t;
}

void TermManager::typecheck(Term term, const DataType *tp,
                            const char *where) const
{
    // Do nothing
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

//ADDITION FOR BV

Term TermManager::make_bv_number(const Number &num, size_t width)
{
    std::vector<Term> children;
    const Symbol *s2  = sig_->add_symbol(num.to_str(), integer_);
    return make_term(s2,children);
}

const Symbol *TermManager::make_int_from_sbv_symbol(size_t width)
{
    return NULL;
}


const Symbol *TermManager::make_int_from_ubv_symbol(size_t width)
{
    return NULL;
}

Term TermManager::make_int_from_sbv(Term t){
    std::vector<Term> children;
    children.push_back(t);
    if(t->to_str().compare("-") == 0){
        std::string number = "-" + t->get_child(0)->to_str();
        const Symbol *s = make_symbol(number, t->get_type());
        return make_term(s);
    }
    std::string name2 = std::to_string(atoi(t->to_str().c_str()));
    if(name2.compare(t->to_str()) != 0){
        return make_term(sbv_to_int_, children);
    }
    return t;
}

Term TermManager::make_int_from_ubv(Term t){
    return NULL;
}

Term TermManager::make_bv_sle(Term t1, Term t2){
    std::vector<Term> children;
    children.push_back(t1);
    children.push_back(t2);
    return make_term(bvsle_,children);
}

Term TermManager::make_bv_ule(Term t1, Term t2){
    std::vector<Term> children;
    children.push_back(t1);
    children.push_back(t2);
    return make_term(bvule_,children);
}

Term TermManager::make_bv_slt(Term t1, Term t2){
    std::vector<Term> children;
    children.push_back(t1);
    children.push_back(t2);
    return make_term(bvslt_,children);
}

Term TermManager::make_bv_mul(Term t1, Term t2)
{
    std::vector<Term> children;
    children.push_back(t1);
    children.push_back(t2);
    return make_term(bvmul_, children);
}

Term TermManager::make_bv_add(Term t1, Term t2)
{
    std::vector<Term> children;
    children.push_back(t1);
    children.push_back(t2);
    return make_term(bvadd_, children);
}

Term TermManager::make_bv_neg(Term t)
{
    std::vector<Term> children;
    children.push_back(t);
    return make_term(bvneg_, children);
}

Term TermManager::make_bv_sub(Term t1, Term t2)
{
    std::vector<Term> children;
    children.push_back(t1);
    children.push_back(t2);
    return make_term(bvsub_, children);
}

Term TermManager::make_bv_ult(Term t1, Term t2)
{
    std::vector<Term> children;
    children.push_back(t1);
    children.push_back(t2);
    return make_term(bvult_, children);
}

Term TermManager::make_bv_udiv(Term t1, Term t2)
{
    std::vector<Term> children;
    children.push_back(t1);
    children.push_back(t2);
    return make_term(bvudiv_, children);
}

Term TermManager::make_bv_sdiv(Term t1, Term t2)
{
    std::vector<Term> children;
    children.push_back(t1);
    children.push_back(t2);
    return make_term(bvsdiv_, children);
}

Term TermManager::make_bv_comp(Term t1, Term t2)
{
    std::vector<Term> children;
    children.push_back(t1);
    children.push_back(t2);
    return make_term(bvcomp_, children);
}

Term TermManager::make_bv_sign_extend(size_t i, Term t){
    std::vector<Term> children;
    children.push_back(t);
    std::string name = "(_ sign_extend " + std::to_string(i) + ")";
    const Symbol *s2  = sig_->add_symbol(name, bv_typeclass_);
    return make_term(s2, children);

}

Term TermManager::make_bv_concat(Term t1, Term t2)
{
    std::vector<Term> children;
    children.push_back(t1);
    children.push_back(t2);
    return make_term(bvconcat_, children);
}


Term TermManager::make_bv_extract(size_t i, size_t j, Term t)
{
    std::vector<Term> children;
    children.push_back(t);
    size_t a = i-j +1;
    std::string name = "(_ extract " + std::to_string(a) + " " + std::to_string(0) + ")";
    const Symbol *s2  = sig_->add_symbol(name, bv_typeclass_);
    return make_term(s2, children);
}

size_t TermManager::get_width_from_type(const DataType *tp) const
{
    return NULL;
}

const DataType *TermManager::get_bv_type(size_t width)
{
    return NULL;
}

Term TermManager::make_int_to_bv(size_t width, Term t)
{
    std::vector<Term> children;
    children.push_back(t);
    Term t1 = make_term(to_int_,children);
    children.clear();
    std::string name = "(_ to_bv 25)";
    const Symbol *s2  = sig_->add_symbol(name, bv_typeclass_);
    children.push_back(t1);
    return make_term(s2,children);
    
}

} // namespace msat
