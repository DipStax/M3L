#include "M3L/Rendering/Model.hpp"

namespace m3l
{
    Model::Model(Object3D &_obj, Texture &_txtr)
        : m_obj(&_obj), m_txtr(&_txtr)
    {
    }

    void Model::setObject(Object3D &_obj)
    {
        m_obj = &_obj;
    }

    void Model::setTexture(Texture &_txtr)
    {
        m_txtr = &_txtr;
    }

    void Model::displayEdge(bool _enable, bool _withtxtr)
    {
        m_edge = _enable;
        m_withtxtr = _withtxtr;
    }

    void Model::draw(RenderTarget3D &_target, RenderState3D _state) const
    {
        _state.transform *= getTransform();

        if (!m_edge || m_withtxtr) {
            _state.texture = m_txtr;
            _target.draw(*m_obj, _state);
        }
        if (m_edge) {
            _state.texture = nullptr;
            _state.vertexOnly = true;
            _target.draw(*m_obj, _state);
        }
    }
}