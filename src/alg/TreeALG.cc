#include "TreeALG.hh"

TreeALG::TreeALG()
:currentNode_m(0)
{
}

TreeALG::~TreeALG()
{
}

void TreeALG::setCurrentNodeToRoot()
{
}

bool TreeALG::hasCurrentNodeChildren()
{
    return false;
}

TreeALG::ChildrenInfoPool TreeALG::getChildrenOfCurrentNode()
{
    return ChildrenInfoPool();
}

NodeContentALG * TreeALG::setCurrentNodeToChild(int)
{
    return 0;
}

NodeContentALG * TreeALG::getCurrentNodeInformation()
{
}

void TreeALG::addChildrenToCurrentNode(DecisionALG *)
{
}
