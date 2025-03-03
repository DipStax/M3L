#pragma once

#include <memory>

namespace m3l
{
    namespace priv {
        template<class T>
        struct CLNode
        {
            T data;
            std::shared_ptr<CLNode> next = nullptr;
            std::shared_ptr<CLNode> prev = nullptr;
        };
    }

    template<class T>
    class CircleList
    {
        public:
            CircleList() = default;
            ~CircleList();

            [[nodiscard]] size_t size() const;

            void push_back(const T &_data);

            template<class ...Ts>
            void emplace(int32_t _idx, Ts ..._args);
            template<class ...Ts>
            void emplace_back(Ts ..._args);

            void swap(int32_t _idx1, int32_t _idx2);
            void resize(size_t _size, T &_val = T());

            [[nodiscard]] T &at(int32_t _idx);
            [[nodiscard]] const T &at(int32_t _idx) const;

            [[nodiscard]] T &operator[](int32_t _idx);
            [[nodiscard]] const T &operator[](int32_t _idx) const;

            void erase(int32_t _idx);

            void clear();

        private:
            [[nodiscard]] std::shared_ptr<priv::CLNode<T>> iat(int32_t _idx);
            [[nodiscard]] const std::shared_ptr<priv::CLNode<T>> iat(int32_t _idx) const;

            std::shared_ptr<priv::CLNode<T>> m_head = nullptr;
            size_t m_size = 0;
    };
}

#include "M3L/Container/CircleList.inl"