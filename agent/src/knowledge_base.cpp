#include "agent/knowledge_base.hpp"

namespace wumpus {

// TODO: implement the inference engine

KnowledgeBase::KnowledgeBase()
{
}

void KnowledgeBase::tell(WumpusWorld &world) const
{
}

void KnowledgeBase::tell(Action action) const
{
}

Action KnowledgeBase::ask(WumpusWorld &world) const
{
    return Action::CLIMB;
}

} // namespace wumpus
