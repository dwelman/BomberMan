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
    DAMAGE_WALL_TAG = 256,
    MOVING_ENTITY_TAG = 512,
    LEVEL_EXIT_TAG = 1024,
    EXPLOSION_TAG = 2048,
	LEVEL_EXIT_OPEN_TAG = 5096
};

#define TAG_MASK_TYPE int

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