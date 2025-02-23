#include <fstream>

#include "M3L/Rendering/Object3D.hpp"
#include "M3L/Rendering/Target/RenderTarget3D.hpp"
#include "Tool/Splitter.hpp"

namespace m3l
{
    Object3D::Object3D()
    {
        Init();
    }

    void Object3D::load(const std::string &_path)
    {
        std::ifstream file;
        std::string line;
        std::pair<std::string, std::string> pair;

        file.open(_path);
        while (std::getline(file, line)) {
            pair = split::noSpace(line, ' ');
            if (m_fnParsing.contains(pair.first)) {
                try {
                    (this->*(m_fnParsing[pair.first]))(line);
                } catch (std::exception &_excp) {
                    throw std::runtime_error("[Object3D](" + _path + "): Internal error: " + _excp.what() + " | '" + line + "'");
                }
            }
            else if (!line.empty() && line.at(0) == '#') {
                fnComment("");
            } else if (!line.empty()) {
                throw std::runtime_error("[Object3D](" + _path + "): Unknow flag: '" + line + "'");
            }
        }
        // add polyTri resolution
    }

    void Object3D::setTexture(Texture &_txtr)
    {
        m_txtr = &_txtr;
    }

    void Object3D::draw(RenderTarget3D &_target, RenderState3D _state) const
    {
        _state.texture = m_txtr;

        for (const auto& _f : m_f)
            _target.draw(_f.data(), _f.size(), _state);
    }

    void Object3D::Init()
    {
        static bool init = false;

        if (init)
            return;
        init = true;
        m_fnParsing["f"] = &Object3D::fnLoadF;
        m_fnParsing["v"] = &Object3D::fnLoadV;
        m_fnParsing["vn"] = &Object3D::fnLoadVn;
        m_fnParsing["vp"] = &Object3D::fnLoadVp;
        m_fnParsing["vt"] = &Object3D::fnLoadVt;
        m_fnParsing["#"] = &Object3D::fnComment;
    }

    void Object3D::fnLoadF(const std::string &_line)
    {
        std::vector<std::string> multi = split::multiple(_line, ' ', true);
        std::vector<std::string> param;
        std::vector<Vertex3D> f;

        multi.erase(multi.begin());
        if (multi.size() < 3)
            throw std::runtime_error("Not enough parameters");
        for (auto &_pt : multi) {
            Vertex3D vtx;

            param = split::multiple(_pt, '/', false);
            if (param.size() < 1 || param.size() > 3)
                throw std::runtime_error("not enough value in the parameters");
            vtx.pos = m_v[std::stoll(param.at(0)) - 1];
            if (param.size() > 1) {
                if (!param.at(1).empty())
                    vtx.txtrPos = m_vt[std::stoll(param.at(1)) - 1].as2();
                // if (param.size() > 2)
                // handling normalized vector ?
            }
            f.push_back(vtx);
        }
        m_f.push_back(f);
    }

    void Object3D::fnLoadV(const std::string &_line)
    {
        std::pair<std::string, std::string> pair = split::noSpace(_line, '#');
        std::vector<std::string> multi = split::multiple(pair.first, ' ', true);

        m_v.push_back({ std::stof(multi.at(1)), std::stof(multi.at(2)), std::stof(multi.at(3)) });
    }

    void Object3D::fnLoadVn(const std::string &_line)
    {
        std::pair<std::string, std::string> pair = split::noSpace(_line, '#');
        std::vector<std::string> multi = split::multiple(_line, ' ', true);

        m_vn.push_back({ std::stof(multi.at(1)), std::stof(multi.at(2)), std::stof(multi.at(3)) });
    }

    void Object3D::fnLoadVt(const std::string &_line)
    {
        std::pair<std::string, std::string> pair = split::noSpace(_line, '#');
        std::vector<std::string> multi = split::multiple(_line, ' ', true);
        Vector3<float> vec;

        multi.erase(multi.begin());
        vec.x = std::stof(multi.at(0));
        vec.y = (multi.size() > 1) ? std::stof(multi.at(1)) : 0;
        vec.z = (multi.size() > 2) ? std::stof(multi.at(2)) : 0;
        if (vec.y < 0 || vec.y > 1 || vec.z < 0 || vec.z > 1)
            throw std::runtime_error("Optional parameter doesn't fit");
        m_vt.push_back(vec);
    }

    void Object3D::fnLoadVp(const std::string &_line)
    {
        std::pair<std::string, std::string> pair = split::noSpace(_line, '#');
        std::vector<std::string> multi = split::multiple(_line, ' ', true);
        Vector3<float> vec;

        vec.x = std::stof(multi.at(1));
        vec.y = (multi.size() > 1) ? 0 : std::stof(multi.at(2));
        vec.z = (multi.size() > 2) ? 0 : std::stof(multi.at(2));
        m_v.push_back(vec);
    }

    void Object3D::fnComment(const std::string &_line)
    {
        std::ignore = _line;
    }
}