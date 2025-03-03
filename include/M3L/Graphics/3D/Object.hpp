#pragma once

#include <istream>
#include <map>
#include <string>
#include <vector>
#include <memory>

#include "M3L/System/Maths/Point3.hpp"
#include "M3L/Graphics/3D/IDrawable.hpp"
#include "M3L/Graphics/Vertex.hpp"

namespace m3l
{
    class M3L_API Object3D : public IDrawable3D
    {
        public:
            Object3D();
            ~Object3D() = default;

            void load(const std::string &_path);

        protected:
            void draw(RenderTarget3D &_target, RenderState3D _state) const;

        private:
            using FnParsing = void (Object3D::*)(const std::string &);

            static void Init();
            static inline std::map<std::string, FnParsing> m_fnParsing;

            // https://en.wikipedia.org/wiki/Wavefront_.obj_file
            void fnLoadF(const std::string &_file);
            void fnLoadV(const std::string &_file);
            void fnLoadVn(const std::string &_file);
            void fnLoadVp(const std::string &_file);
            void fnLoadVt(const std::string &_file);
            void fnComment(const std::string &_file);

        private:
            std::vector<m3l::Vector3<float>> m_v;
            std::vector<m3l::Vector3<float>> m_vn;
            std::vector<m3l::Vector3<float>> m_vt;
            std::vector<m3l::Vector3<float>> m_vp;
            std::vector<std::vector<Vertex3D>> m_f;
    };
}