#include <numeric>

#include "M3L/Container/TriggerMap.hpp"

namespace m3l
{
    template<template<class> class T, class ...Ts>
    TriggerMap<T, std::tuple<Ts...>>::TriggerMap(ThreadPool &_tp)
        : m_tup(T<Ts>(_tp)...)
    {
    }

    template<template<class> class T, class ...Ts>
    TriggerMap<T, std::tuple<Ts...>>::TriggerMap(TriggerMap<T, std::tuple<Ts...>> &&_tm) noexcept
        : m_tup(std::move(_tm.m_tup))
    {
    }

    template<template<class> class T, class ...Ts>
    template<class _T>
    requires ContainIn<_T, Ts...>
    constexpr size_t TriggerMap<T, std::tuple<Ts...>>::find() const noexcept
    {
        return tuple_find<_T, Ts...>::value;
    }

    template<template<class> class T, class ...Ts>
    template<class _T>
    requires ContainIn<_T, Ts...>
    constexpr const T<_T> &TriggerMap<T, std::tuple<Ts...>>::at() const noexcept
    {
        return std::get<T<_T>>(m_tup);
    }

    template<template<class> class T, class ...Ts>
    template<class _T>
    requires ContainIn<_T, Ts...>
    constexpr T<_T> &TriggerMap<T, std::tuple<Ts...>>::at() noexcept
    {
        return std::get<T<_T>>(m_tup);
    }
}