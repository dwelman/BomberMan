#include "systems/TagSystem.hpp"

bool TagSystem::CheckMaskForTag(TAG_MASK_TYPE mask, TAG_MASK_TYPE tag)
{
    return ((mask & tag) == tag);
}
