#include "components/Tag.hpp"

Tag::Tag() : BaseComponent(TAG)
{

}

Tag::Tag(TAG_MASK_TYPE tagMask) : Tag()
{
    m_tagMask = tagMask;
}

Tag::Tag(Tag const &t) : Tag()
{
    *this = t;
}

Tag &Tag::operator=(Tag const &t)
{
    m_tagMask = t.m_tagMask;
    return (*this);
}

Tag::~Tag()
{

}

TAG_MASK_TYPE Tag::GetTagMask() const
{
    return (m_tagMask);
}

void Tag::SetTagMask(TAG_MASK_TYPE tagMask)
{
    m_tagMask = tagMask;
}
