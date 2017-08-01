#pragma once

#include "Vec3.hpp"
#include "components/BaseComponent.hpp"
#include <cstddef>

class Render : public BaseComponent
{
private:
    std::size_t m_meshID;
    std::size_t m_textureID;
    bool        m_active;

    Render();
public:
    Render(std::size_t meshID, std::size_t textureID, bool active);
    Render(std::size_t meshID, std::size_t textureID);
    Render(Render const &src);
    ~Render();

    Render &operator=(Render const &cp);

    std::size_t GetMeshID() const;
    std::size_t GetTextureID() const;
    bool        GetActive() const;
    void        SetMeshID(std::size_t ID);
    void        SetTextureID(std::size_t ID);
    void        SetActive(bool act);
};