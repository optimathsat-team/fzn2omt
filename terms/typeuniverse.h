// -*- C++ -*-
//
// Author: Giuseppe Spallitta <giuseppe.spallitta@unitn.it>

#ifndef MSAT_TYPEUNIVERSE_H_INCLUDED
#define MSAT_TYPEUNIVERSE_H_INCLUDED

#include <string>
#include <vector>
#include <ostream>
#include <unordered_map>
#include <unordered_set>
#include "../utils/exception.h"

namespace msat {

/**
 * The class representing data types
 */
class DataType {
private:
    friend class TypeUniverse;

    

public:

    DataType(size_t id=0, const std::string &name=""): id_(id), name_(name) {}
    
    bool is_simple() const { 
        return id_ != 0; 
    }

    size_t get_arity() const { 
        return types_.size(); 
    }

    const DataType *get_component(size_t idx) const;

    const std::string &get_name() const;

    size_t hash() const;
    
private:
    size_t id_;
    std::string name_;
    std::vector<const DataType *> types_;
};

/**
 * A type universe manages a set of types, providing functions for creating,
 * accessing and querying types
 */
class TypeUniverse {
public:
    MSAT_DECLARE_EXCEPTION(error)
    
    TypeUniverse();
    ///< Constructor

    ~TypeUniverse();
    ///< Destructor

    bool is_subtype(const DataType *s, const DataType *m) const;
    ///< \return true if \a s is a subtype of \a m

private:

    struct DataType_eq {
        bool operator()(const DataType *t1, const DataType *t2) const
        {
            return t1 == t2;
        }
    };
    
    struct DataType_hash {
        size_t operator()(const DataType *tp) const
        {
            return tp->hash();
        }
    };
    
    typedef std::unordered_set<DataType *, DataType_hash, DataType_eq> TypeStore;
    typedef std::unordered_map<const DataType *, const DataType *> SubtypeMap;

    TypeStore store_;
    SubtypeMap subtypes_; 
    size_t next_id_;
    DataType application_; 
    std::unordered_set<const DataType *> removed_; 
};


} // namespace msat

#endif // MSAT_TYPEUNIVERSE_H_INCLUDED
