#pragma once

#include "Vec3.hpp"
#include "components/BaseComponent.hpp"
#include <cstddef>

class Render : public BaseComponent
{
    private:
        Render();

        std::size_t m_meshID;
        std::size_t m_textureID;
        bool active = true;

    public:
        Render(Render const &src);
        Render(std::size_t mesh, std::size_t text, bool act);
        Render(std::size_t mesh, std::size_t text);
        ~Render();

        std::size_t getMeshID()const;
        std::size_t getTextureID()const;
        bool getActive()const;

        void setMeshID(std::size_t ID);
        void setTextureID(std::size_t ID);
        void setActive(bool act);


        Render &operator=(Render const &cp);
};