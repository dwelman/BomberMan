#pragma once

//A bit mask is used to quickly identify what components an entity has without costly checking
enum ComponentMask
{
    POSITION = 1,
    COLLISION = 2,
    RENDER = 4,
    MOVEMENT = 8
};

class BaseComponent
{
private:
    ComponentMask m_type;

    BaseComponent();
public:
    BaseComponent(ComponentMask mask);
    BaseComponent(BaseComponent const &c);
    ~BaseComponent();

    BaseComponent   &operator=(BaseComponent const &c);
    ComponentMask   GetComponentType() const;
    void            SetComponentType(ComponentMask mask);
};