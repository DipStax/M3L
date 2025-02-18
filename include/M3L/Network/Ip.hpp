#pragma once

#include <string>

#include <winsock2.h>

#include "M3L/Network/meta.hpp"

namespace m3l::net
{
    namespace ip
    {
        struct v4
        {
            using Container = uint32_t;
            static constexpr uint8_t size = 4;
            static constexpr int familly = AF_INET;
        };

        struct v6
        {
            using Container = uint64_t;
            static constexpr uint8_t size = 6;
            static constexpr int familly = AF_INET6;
        };
    }

    template<IsBaseIpFormat T>
    class Ip : public T
    {
        public:
            using RawContainer = typename T::Container;

            Ip() = default;
            template<class _T>
            Ip(const _T &_arg);
            template<class ...Ts>
            Ip(const Ts &&..._args);

            void set(const RawContainer _raw);
            void set(const std::string &_ip);

            template<class ...Ts>
            requires IsByteIpFormat<T, Ts...>
            constexpr void set(const Ts ..._bytes);

            [[nodiscard]] constexpr RawContainer raw() const;
            [[nodiscard]] std::string str() const;

            template<IsBaseIpFormat _T>
            friend std::ostream &operator<<(std::ostream &_os, const Ip<_T> &_ip);

        private:
            T::Container m_raw = 0;
    };
}

#include "M3L/Network/Ip.inl"