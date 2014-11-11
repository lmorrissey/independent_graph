/*
 * pair_hasher.h
 *
 *  Created on: Oct 14, 2014
 *      Author: Laura
 */

#ifndef PAIR_HASHER_H_
#define PAIR_HASHER_H_

#include <utility>
#include <functional>
#include <tuple>

namespace hash_pair {

        template<typename TT>
        struct hash
        {
            size_t operator()(TT const& tt) const
            {
                return std::hash<TT>()(tt);
            }
        };

// Code from boost.
// See Mike Seymour in magic-numbers-in-boosthash-combine:
//     http://stackoverflow.com/questions/4948780
        namespace {
        template<class T>
        inline void hash_combine(std::size_t& seed, T const& v)
        {
            seed ^= hash_pair::hash<T>()(v) + 0x9e3779b9 + (seed << 6)
                    + (seed >> 2);
        }

// Recursive template code derived from Matthieu M.
        template<class Pair, size_t Index = std::tuple_size<Pair>::value - 1>
        struct HashValueImpl
        {
            static void apply(size_t& seed, Pair const& pair)
            {
                HashValueImpl<Pair, Index - 1>::apply(seed, pair);
                hash_combine(seed, std::get < Index > (pair));
            }
        };

        template<class Pair>
        struct HashValueImpl<Pair, 0>
        {
            static void apply(size_t& seed, Pair const& pair)
            {
                hash_combine(seed, std::get < 0 > (pair));
            }
        };
    }

    template<typename ... TT>
    struct hash<std::pair<TT...>>
    {
        size_t operator()(std::pair<TT...> const& tt) const
        {
            size_t seed = 0;
            HashValueImpl<std::pair<TT...> >::apply(seed, tt);
            return seed;
        }
    };
}

#endif /* PAIR_HASHER_H_ */
