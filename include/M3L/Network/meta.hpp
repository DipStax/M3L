#pragma once

#include "Tool/PreProcessing.hpp"

#define WIN_SOCKET SOCKET

namespace m3l
{
    namespace meta
    {
        namespace imp
        {
            template<template<typename ...> class T, class _T>
            struct is_base_of_template
            {
                template<class ...Ts>
                static constexpr std::true_type  test(const T<Ts...> *);
                static constexpr std::false_type test(...);
                using type = decltype(test(std::declval<_T*>()));
            };

            template<template<typename, auto...> class T, class _T>
            struct is_base_of_template_nttp
            {
                template<class __T, auto ...Ts>
                static constexpr std::true_type  test(const T<__T, Ts...>*);
                static constexpr std::false_type test(...);
                using type = decltype(test(std::declval<_T*>()));
            };
        }

        template<template<typename ...> class T, class _T>
        using is_base_of_template = typename imp::is_base_of_template<T, _T>::type;

        template<template<typename, auto...> class T, class _T>
        constexpr bool is_base_of_template_v = is_base_of_template<T, _T>::value;

        template<template<typename, auto...> class T, class _T>
        using is_base_of_template_nttp = typename imp::is_base_of_template_nttp<T, _T>::type;

        template<template<typename, auto...> class T, class _T>
        constexpr bool is_base_of_template_nttp_v = is_base_of_template_nttp<T, _T>::value;
    }

    namespace net
    {
        /// -----------------------------------
        /// Ip
        /// -----------------------------------

        namespace ip
        {
            struct v4;
            struct v6;
        }

        template<class T>
        concept IsBaseIpFormat = IsUInt<typename T::Container> && requires {
                { T::size } -> std::same_as<const uint8_t &>;
                { T::familly } -> std::same_as<const int &>;
            } && sizeof(typename T::Container) >= T::size;

        template<class T>
        concept IsBaseIp = (std::same_as<T, m3l::net::ip::v4> || std::same_as<T, m3l::net::ip::v6>);

        template<class T, class ...Ts>
        concept IsByteIpFormat = IsBaseIpFormat<T> && (sizeof...(Ts) == T::size && (std::is_same_v<Ts, uint8_t> && ...));

        template<IsBaseIpFormat T>
        class Ip;

        template<class T>
        concept IsIpFormat = m3l::meta::is_base_of_template_v<m3l::net::Ip, T>;

        /// -----------------------------------
        /// Socket
        /// -----------------------------------

        enum Protocol;

        template<IsBaseIp T, Protocol _T>
        class BasicSocket;

        template<class T>
        concept IsBaseSocket = m3l::meta::is_base_of_template_nttp_v<m3l::net::BasicSocket, T>;
    }
}