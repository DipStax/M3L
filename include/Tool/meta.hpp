#pragma once

#include <concepts>
#include <type_traits>

namespace m3l
{   
    template<class T>
    concept NumericType = std::is_arithmetic<T>::value;

    template<class T>
    concept IsUInt = std::unsigned_integral<T>;

    namespace meta
    {
        
        namespace imp
        {
            template<size_t I, class T, class ...Ts>
            struct find_in;
    
            template<size_t I, class T, class _T, class ...Ts>
            struct find_in<I, T, _T, Ts...>
            {
                static constexpr size_t value = std::is_same<T, _T>::value ? I : imp::find_in<I, T, Ts...>::value;
            };
    
            template<size_t I, class T, class _T>
            struct find_in<I, T, _T>
            {
                static constexpr size_t value = std::is_same<T, _T>::value ? I : I + 1;
            };

            template<class ...Ts>
            struct contain_in;

            template<class T, class ...Ts>
            struct contain_in<T, T, Ts...>
            {
                using type = std::true_type;
            };

            template<class T, class _T, class ...Ts>
            struct contain_in<T, _T, Ts...>
            {
                using type = typename imp::contain_in<T, Ts...>::type;
            };

            template<class T>
            struct contain_in<T>
            {
                using type = std::false_type;
            };
        }

        template<class T, class ...Ts>
        using find_in = imp::find_in<0, T, Ts...>;

        template<class T, class ...Ts>
        constexpr size_t find_in_v = find_in<T, Ts...>::value;

        template<class T, class ...Ts>
        using contain_in = typename imp::contain_in<T, Ts...>::type;

        template<class T, class ...Ts>
        constexpr bool contain_in_v = contain_in<T, Ts...>::value;
    }

    template<class T, class ...Ts>
    concept ContainIn = meta::contain_in_v<T, Ts...>;

    #pragma region Operator

    template<class T, class _T>
    concept AssignOp = requires (T r, _T l) {
        r = l;
    };

    template<class T, class _T>
    concept EqOp = requires (T r, _T l) {
        r == l;
    };

    template<class T, class _T>
    concept NEqOp = requires (T r, _T l) {
        r != l;
    };

    template<class T, class _T>
    concept LsOp = requires (T r, _T l) {
        r < l;
    };

    template<class T, class _T>
    concept GtOp = requires (T r, _T l) {
        r > l;
    };

    template<class T, class _T>
    concept LsEqOp = requires (T r, _T l) {
        r <= l;
    };

    template<class T, class _T>
    concept GtEqOp = requires (T r, _T l) {
        r >= l;
    };

    template<class T, class _T>
    concept GlobCompOp = requires (T r, _T l) {
        r <=> l;
    };

    template<class T, class _T>
    concept AddOp = requires (T r, _T l) {
        r + l;
    };

    template<class T, class _T>
    concept SubOp = requires (T r, _T l) {
        r - l;
    };

    template<class T, class _T>
    concept MulOp = requires (T r, _T l) {
        r * l;
    };

    template<class T, class _T>
    concept DivOp = requires (T r, _T l) {
        r / l;
    };

    template<class T, class _T>
    concept ModOp = requires (T r, _T l) {
        r % l;
    };

    template<class T, class _T>
    concept BitAndOp = requires (T r, _T l) {
        r & l;
    };

    template<class T, class _T>
    concept BitOrOp = requires (T r, _T l) {
        r | l;
    };

    template<class T, class _T>
    concept BitXorOp = requires (T r, _T l) {
        r ^ l;
    };

    template<class T, class _T>
    concept LShiftOp = requires (T r, _T l) {
        r << l;
    };

    template<class T, class _T>
    concept RShiftOp = requires (T r, _T l) {
        r >> l;
    };

    template<class T, class _T>
    concept AssignAddOp = requires (T r, _T l) {
        r += l;
    };

    template<class T, class _T>
    concept AssignSubOp = requires (T r, _T l) {
        r -= l;
    };

    template<class T, class _T>
    concept AssignMulOp = requires (T r, _T l) {
        r *= l;
    };

    template<class T, class _T>
    concept AssignDivOp = requires (T r, _T l) {
        r /= l;
    };

    template<class T, class _T>
    concept AssignModOp = requires (T r, _T l) {
        r %= l;
    };

    template<class T, class _T>
    concept AssignBitAndOp = requires (T r, _T l) {
        r &= l;
    };

    template<class T, class _T>
    concept AssignBitOrOp = requires (T r, _T l) {
        r |= l;
    };

    template<class T, class _T>
    concept AssignBitXorOp = requires (T r, _T l) {
        r ^= l;
    };

    template<class T, class _T>
    concept AssignLShiftOp = requires (T r, _T l) {
        r <<= l;
    };

    template<class T, class _T>
    concept AssignRShiftOp = requires (T r, _T l) {
        r >>= l;
    };

    template<class T>
    concept PreIncOp = requires (T r) {
        r++;
    };

    template<class T>
    concept PostIncOp = requires (T r) {
        ++r;
    };

    template<class T>
    concept PreDecOp = requires (T r) {
        r--;
    };

    template<class T>
    concept PostDecOp = requires (T r) {
        --r;
    };

    #pragma endregion
}