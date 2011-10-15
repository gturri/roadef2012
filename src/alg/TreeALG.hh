#ifndef TREEALG_HH
#define TREEALG_HH

#include <vector>
#include <list>
#include <string>
#include <sstream>

/** Structure contenant l'information utile du noeud d'un point de vue
    recherche de solution. Quelque soit la structure de l'arbre, on en
    aura toujours besoin.
*/

class DecisionALG;

struct NodeContentALG
{
    int numberOfSimulations_m;
    double sumOfEvaluations_m;
    DecisionALG * pDecision_m;

    NodeContentALG() :
        numberOfSimulations_m(0),
        sumOfEvaluations_m(0.0),
        pDecision_m(0)
    {}

    NodeContentALG(DecisionALG * pDecision_p) :
        numberOfSimulations_m(0),
        sumOfEvaluations_m(0.0),
        pDecision_m(pDecision_p)
    {}

    std::string toString() const
    {
        std::stringstream ss_l;
        ss_l << sumOfEvaluations_m / numberOfSimulations_m
             << "(" << numberOfSimulations_m << ")";
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
    iterator getRootNode();

    // renvoie vrai si un iterateur a des fils
    bool hasChildren(iterator const &);

    // renvoie la liste des fils d'un iterateur
    ChildrenPool getChildren(iterator const &);

    // detruit le noeud de l'iterateur qui devient donc invalide
    void deleteNode(iterator const &);

    // renvoie un iterateur sur le noeud courant?
    iterator addChildren(iterator const &, NodeContentALG &);

    std::string toString(const std::string & = "");
    std::string toString(const std::string &, iterator const &);

private:
    TreeImpl impl_m;
};

#endif
