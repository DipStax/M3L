#include "M3L/Network/Ip.hpp"
#include "Tool/Splitter.hpp"

#include <ranges>
#include <algorithm>

namespace m3l::net
{
    template<IsBaseIpFormat T>
    template<class _T>
    Ip<T>::Ip(const _T &_arg)
    {
        set(_arg);
    }

    template<IsBaseIpFormat T>
    template<class ...Ts>
    Ip<T>::Ip(const Ts &&..._args)
    {
        set(std::forward<Ts>(_args)...);
    }

    template<IsBaseIpFormat T>
    void Ip<T>::set(const RawContainer _raw)
    {
        m_raw = _raw;
    }

    template<IsBaseIpFormat T>
    void Ip<T>::set(const std::string &_ip)
    {
        uint8_t shift = 0;

        std::vector<std::string> res = split::multiple(_ip, '.');
        for (std::string _val : res)
            this->m_raw |= static_cast<RawContainer>(std::stoi(_val)) << (shift++ * 8);
    }

    template<IsBaseIpFormat T>
    template<class ...Ts>
    requires IsByteIpFormat<T, Ts...>
    constexpr void Ip<T>::set(const Ts ..._bytes)
    {
        uint8_t shift = 0;

        ((m_raw |= (static_cast<RawContainer>(_bytes) << (shift++ * 8))), ...);
    }

    template<IsBaseIpFormat T>
    constexpr Ip<T>::RawContainer Ip<T>::raw() const
    {
        return m_raw;
    }

    template<IsBaseIpFormat T>
    std::string Ip<T>::str() const
    {
        // todo formatings
        return {};
    }
}