#ifndef TREEALG_HH
#define TREEALG_HH

#include "DecisionALG.hh"

#include <vector>
#include <list>
#include <string>
#include <sstream>

/** Structure contenant l'information utile du noeud d'un point de vue
    recherche de solution. Quelque soit la structure de l'arbre, on en
    aura toujours besoin.
*/

struct NodeContentALG
{
    uint32_t nbSimu_m;
    float sumEval_m;
    DecisionALG * pDecision_m;

    NodeContentALG() : nbSimu_m(0), sumEval_m(0.0), pDecision_m(0) {}
    NodeContentALG(DecisionALG * pDecision_p) :
        nbSimu_m(0), sumEval_m(0.0), pDecision_m(pDecision_p)
    {}

    ~NodeContentALG()
    {
        // faudrait deleter là, mais si on delete, faut faire une copie pour le
        // move du vector...
        //delete pDecision_m;
    }

    // du coup on fait un clear manuel lors de la destruction d'un Node
    void clear() {delete pDecision_m; pDecision_m = 0; nbSimu_m = 0; sumEval_m = 0;}

    std::string toString() const
    {
        std::stringstream ss_l;
        ss_l << sumEval_m / nbSimu_m << "," << nbSimu_m;
        return ss_l.str();
    }
};

/** Classe servant d'interface pour l'arbre au sein de la MCTS.
 * Cette classe necessite en parametre template une classe implementant
 * un arbre. Il est conseille que cet arbre depende lui meme (template ou pas)
 * de la structure NodeContentALG ci dessus.
 * On utilise un iterateur pour gerer le deplacement dans l'arbre.
 */

template <typename TreeImpl>
class TreeALG
{
public:
    TreeALG();
    ~TreeALG();

    typedef typename TreeImpl::iterator iterator;
    typedef std::vector<iterator> ChildrenPool;

    // renvoie un iterateur sur la racine
    iterator root();

    // renvoie vrai si un iterateur a des fils
    bool hasChildren(iterator const &);

    // renvoie la liste des fils d'un iterateur
    ChildrenPool children(iterator const &);

    // detruit le noeud de l'iterateur qui devient donc invalide
    void deleteNode(iterator &);

    // renvoie un iterateur sur le noeud courant?
    iterator addChildren(iterator &, NodeContentALG &);

    std::string toString(int = -1);
    std::string toString(int, iterator const &);

private:
    TreeImpl impl_m;
};

#endif
