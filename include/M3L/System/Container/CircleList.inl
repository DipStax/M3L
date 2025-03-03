#include "M3L/Container/CircleList.hpp"

namespace m3l
{
    template<class T>
    CircleList<T>::~CircleList()
    {
        clear();
    }

    template<class T>
    size_t CircleList<T>::size() const
    {
        return m_size;
    }

    template<class T>
    void CircleList<T>::push_back(const T &_data)
    {
        std::shared_ptr<priv::CLNode<T>> node = nullptr;

        if (m_head) {
            node = std::make_shared<priv::CLNode<T>>(_data);
            node->next = m_head;
            node->prev = m_head->prev;
            m_head->prev->next = node;
            m_head->prev = node;
        } else {
            m_head = std::make_shared<priv::CLNode<T>>(_data);
            m_head->next = m_head;
            m_head->prev = m_head;
        }
        m_size++;
    }

    template<class T>
    template<class ...Ts>
    void CircleList<T>::emplace(int32_t _idx, Ts ..._args)
    {
        std::shared_ptr<priv::CLNode<T>> ptr = nullptr;
        std::shared_ptr<priv::CLNode<T>> node = nullptr;

        if (_idx == 0) {
            push_back(T(std::forward<Ts>(_args)...));
            m_head = m_head->prev;
        } else {
            node = std::make_shared<priv::CLNode<T>>(T(std::forward<Ts>(_args)...));
            ptr = at(_idx);
            node->next = ptr;
            node->prev = ptr->prev;
            ptr->prev->next = node;
            ptr->prev = node;
        }
    }

    template<class T>
    template<class ...Ts>
    void CircleList<T>::emplace_back(Ts ..._args)
    {
        emplace(m_size, std::forward<Ts>(_args)...);
    }

    template<class T>
    void CircleList<T>::swap(int32_t _idx1, int32_t _idx2)
    {
        std::swap(iat(_idx1)->data, iat(_idx2)->data);
    }

    template<class T>
    void CircleList<T>::resize(size_t _size, T &_val)
    {
        if (_size > m_size) {
            for (size_t it = 0; it < _size - m_size; it++)
                push_back(_val);
        } else {
            while(m_size != _size)
                erase(m_size - 1);
        }
    }

    template<class T>
    T &CircleList<T>::at(int32_t _idx)
    {
        return iat(_idx)->data;
    }

    template<class T>
    const T &CircleList<T>::at(int32_t _idx) const
    {
        return iat(_idx)->data;
    }

    template<class T>
    T &CircleList<T>::operator[](int32_t _idx)
    {
        return iat(_idx)->data;
    }

    template<class T>
    const T &CircleList<T>::operator[](int32_t _idx) const
    {
        return iat(_idx)->data;
    }

    template<class T>
    void CircleList<T>::erase(int32_t _idx)
    {
        std::shared_ptr<priv::CLNode<T>> ptr = m_head;

        if (m_size == 0)
            return;
        if (_idx == 0) {
            if (m_size > 1) {
                m_head->next->prev = m_head->prev;
                m_head->prev->next = m_head->next;
                m_head = m_head->next;
            } else if (m_size == 1) {
                m_head = nullptr;
            }
        } else {
            ptr = iat(_idx);
            ptr->next->prev = ptr->prev;
            ptr->prev->next = ptr->next;
        }
        ptr->next = nullptr;
        ptr->prev = nullptr;
        ptr.reset();
        m_size--;
    }

    template<class T>
    void CircleList<T>::clear()
    {
        while (m_size)
            erase(0);
    }

    template<class T>
    std::shared_ptr<priv::CLNode<T>> CircleList<T>::iat(int32_t _idx)
    {
        std::shared_ptr<priv::CLNode<T>> ptr = m_head;

        if (_idx > 0)
            for (int32_t it = 0; it < _idx; it++, ptr = ptr->next) {}
        else
            for (int32_t it = 0; it > _idx; it--, ptr = ptr->prev) {}
        return ptr;
    }

    template<class T>
    const std::shared_ptr<priv::CLNode<T>> CircleList<T>::iat(int32_t _idx) const
    {
        std::shared_ptr<priv::CLNode<T>> ptr = m_head;

        if (_idx > 0)
            for (int32_t it = 0; it < _idx; it++, ptr = ptr->next) {}
        else
            for (int32_t it = 0; it > _idx; it--, ptr = ptr->prev) {}
        return ptr;
    }
}