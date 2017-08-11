#pragma once

#include "components/BaseComponent.hpp"

enum TagType
{
    PLAYER_TAG = 1,
    ENEMY_TAG = 2,
    BOMB_TAG = 4,
    WALL_TAG = 8,
    INDESTRUCTIBLE_TAG = 16,
    POWERUP_TAG = 32,
    DAMAGE_PLAYER_TAG = 64,
    DAMAGE_ENEMY_TAG = 128,
    DAMAGE_WALL_TAG = 256
};

#define TAG_MASK_TYPE short

class Tag : public BaseComponent
{
private:
    TAG_MASK_TYPE   m_tagMask;

    Tag();
public:
    Tag(TAG_MASK_TYPE tagMask);
    Tag(Tag const &t);

    ~Tag();

    Tag   &operator=(Tag const &t);

    TAG_MASK_TYPE   GetTagMask() const;
    void            SetTagMask(TAG_MASK_TYPE tagMask);
};