#ifdef USE_GECODE

#include "CPSpaceALG.hh"
#include "alg/ContextALG.hh"
#include "tools/Checker.hh"
#include "tools/Log.hh"

#include <gecode/search.hh>

using namespace Gecode;

CPSpaceALG::CPSpaceALG() : pGecodeSpace_m(0)
{
}

CPSpaceALG::CPSpaceALG(const CPSpaceALG &that) :
    SpaceALG(that), pGecodeSpace_m(0)
{
    copy(that);
}

CPSpaceALG::~CPSpaceALG()
{
    delete pGecodeSpace_m;
}

CPSpaceALG &CPSpaceALG::operator=(const CPSpaceALG &that)
{
    if (this != &that) {
        SpaceALG::operator=(that);
        copy(that);
    }

    return *this;
}

void CPSpaceALG::copy(const CPSpaceALG &that)
{
    delete pGecodeSpace_m;
    pGecodeSpace_m = 0;

    if (that.pGecodeSpace_m->status() != SS_FAILED) {
        pGecodeSpace_m = static_cast<GecodeSpace*>(that.pGecodeSpace_m->clone(false));
    }
}

SpaceALG * CPSpaceALG::clone()
{
    return new CPSpaceALG(*this);
}

bool CPSpaceALG::isSolution() const
{
    return pGecodeSpace_m == 0 || pGecodeSpace_m->status() == SS_SOLVED;
}

CPSpaceALG::DecisionsPool CPSpaceALG::generateDecisions() const
{
    if (!pGecodeSpace_m)
        return DecisionsPool();
    else
        return pGecodeSpace_m->generateDecisions();
}

void CPSpaceALG::addDecision(DecisionALG *pDecision_p)
{
    assert(dynamic_cast<const CPDecisionALG*>(pDecision_p));

    if (pGecodeSpace_m) {
        const CPDecisionALG *pCPD_l = static_cast<const CPDecisionALG*>(pDecision_p);
        pGecodeSpace_m->addDecision(pCPD_l);
    }
}

void CPSpaceALG::setpContext(ContextALG *pContext_p)
{
    SpaceALG::setpContext(pContext_p);
    delete pGecodeSpace_m;
    pGecodeSpace_m = new GecodeSpace(pContext_p->getContextBO());
}

double CPSpaceALG::evaluate() const
{
    double res_l = 0.;

    // si on a pas de Gecode, le pb est FAILED
    if (! pGecodeSpace_m)
        return res_l;

    // Montecarlo: on demande une solution à Gecode
    Search::FailStop stop_l(1000);
    Search::Options options_l;
    options_l.stop = &stop_l;
    //options_l.c_d = 1000;
    DFS<GecodeSpace> search_l(pGecodeSpace_m, options_l);
    GecodeSpace *pSol_l = search_l.next();

    // Gecode a pas trouvé de solution réalisable
    if (! pSol_l) {
        if (search_l.stopped()){
            LOG(INFO) << "Search stopped." << endl;
        }
        return res_l;
    }

    // on récupère la solution
    std::vector<int> sol_l = pSol_l->solution();
    delete pSol_l;

    // Quand Gecode intégrera toutes les contraintes, on aura plus besoin de
    // checker
    Checker checker_l(pContext_m->getContextBO(), sol_l);
    if (checker_l.isValid()){
        uint64_t intEval_l = checker_l.computeScore();
        res_l = (double) origEval_m / ((double) origEval_m + intEval_l);
        if (pContext_m->checkRapideAndMajBestSol(sol_l, intEval_l)) {
            LOG(INFO) << "Better solution: " << intEval_l
                      << ", eval = " << res_l << endl;
        }
    }

    return res_l;
}

#endif //USE_GECODE
