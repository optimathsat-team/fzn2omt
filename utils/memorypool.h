// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
//
// Pools for fast dynamic allocation
// 
// Author: Alberto Griggio <griggio@fbk.eu>,
// following examples from Chapter 19 of Bjarne Stroustroup's book "The C++
// Programming Language"
// 
//

#ifndef MSAT_MEMORYPOOL_H_INCLUDED
#define MSAT_MEMORYPOOL_H_INCLUDED

#include <memory>
#include <limits>
#include <stdlib.h>
#include <assert.h>
#include "../msatconfig.h"
#include "../utils/xmalloc.h"

#ifdef MSAT_MSVC
#  pragma warning(disable: 4200) // disable MSVC warning about zero-length array
#endif

namespace msat {

// some template metaprogramming fun... :-) These are for aligned memory
// allocation
template<size_t pow2>
struct shift_amount {
    static const size_t value = shift_amount<(pow2 >> 1)>::value + 1;
};
template<>
struct shift_amount<1> {
    static const size_t value = 0;
};

template<size_t n, size_t x=1>
struct nearest_pow2 {
    static const size_t value = (x < n ? nearest_pow2<n, (x << 1)>::value : x);
};
template<size_t n>
struct nearest_pow2<n, static_cast<size_t>(1) << (sizeof(size_t)*8-1)> {
    static const size_t value = static_cast<size_t>(1) << (sizeof(size_t)*8-1);
};


template <size_t Sz, bool aligned=false>
class MemoryPool {
    struct Link { Link *next_; };

    struct align {
        static const size_t base_ =
            (Sz >= sizeof(Link) ? Sz : sizeof(Link));
        static const size_t value_ =
            aligned ? nearest_pow2<base_>::value : base_;
    };
    
    struct Chunk {
        Chunk *next_;
        char data_[0];

        static Chunk *alloc(size_t sz)
        {
            void *mem = xmalloc<char>(sizeof(Chunk) + (align::value_ * sz));
            Chunk *ret = new (mem) Chunk;
            ret->next_ = NULL;
            return ret;
        }

        static void free(Chunk *c) { xfree(c); }
    };

public:
    MemoryPool(size_t chunk_elems, float grow_factor=1.0,
               size_t max_chunk_elems=0):
        chunk_size_(chunk_elems), grow_factor_(grow_factor),
        max_chunk_size_(max_chunk_elems)
    {
        all_chunks_ = NULL;
        pool_head_ = NULL;
    }
    
    ~MemoryPool()
    {
        Chunk *n = all_chunks_;
        while (n) {
            Chunk *tmp = n;
            n = n->next_;
            Chunk::free(tmp);
        }
    }

    char *allocate()
    {
        if (pool_head_ == NULL) {
            pool_head_ = grow_pool();
        }
        Link *p = pool_head_;
        pool_head_ = p->next_;
        p->~Link();
        return reinterpret_cast<char *>(p);
    }

    void deallocate(char *p)
    {
        assert(p != NULL);
        Link *block = new (p) Link;
        block->next_ = pool_head_;
        pool_head_ = block;
    }

private:
    Link *grow_pool()
    {
        Chunk *n = Chunk::alloc(chunk_size_);
        n->next_ = all_chunks_;
        all_chunks_ = n;

        char *start = n->data_;
        char *last = &start[(chunk_size_-1) * align::value_];

        Link *ret = new (start) Link;

        chunk_size_ = size_t(chunk_size_ * grow_factor_);
        if (max_chunk_size_ && chunk_size_ > max_chunk_size_) {
            chunk_size_ = max_chunk_size_;
        }

        Link *cur = ret;
        for (char *p = start; p < last; p += align::value_) {
            Link *next = new (p + align::value_) Link;
            cur->next_ = next;
            cur = next;
        }
        assert(static_cast<void *>(cur) == static_cast<void *>(last));
        cur->next_ = NULL;

        return ret;
    }
        
    size_t chunk_size_;
    ///< the number of elements in each chunk

    const float grow_factor_;
    ///< the growing factor for chunk_size_

    const size_t max_chunk_size_;
    ///< the maximum size of chunks (0: unlimited)
    
    Chunk *all_chunks_;
    ///< the list of allocated chunks
    
    Link *pool_head_;
    ///< head of the pool of elements

    /* Forbid their use */
    MemoryPool(const MemoryPool &);
    const MemoryPool &operator=(const MemoryPool &);
};


// a pool for objects of type T
template<class T, bool aligned=false>
class ObjectPool {
public:
    ObjectPool(size_t chunk_size=1024, float grow_factor=1.0,
               size_t max_chunk_size=0):
        p_(chunk_size, grow_factor, max_chunk_size) {}
    
    T *alloc()
    {
        char *mem = p_.allocate();
        return new (mem) T();
    }

    template <class Arg>
    T *alloc(Arg a)
    {
        char *mem = p_.allocate();
        return new (mem) T(a);
    }
    
    void free(T *elem)
    {
        elem->~T();
        p_.deallocate(reinterpret_cast<char *>(elem));
    }

private:
    MemoryPool<sizeof(T), aligned> p_;

    ObjectPool(const ObjectPool &);
    const ObjectPool &operator=(const ObjectPool &);
};


} // namespace msat

#endif // MSAT_MEMORYPOOL_H_INCLUDED
