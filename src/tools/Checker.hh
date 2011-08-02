#ifndef CHECKER_HH
#define CHECKER_HH

class ContextALG;
class ContextBO;
class MachineBO;
class RessourceBO;

/**
 * Fonctions s'appuyant sur la classe #Checker, permettant de s'evitant la creation d'instances temporaires
 */
bool check(ContextALG const * pContextALG_p);
bool check(ContextBO const * pContextBO_p);

class Checker {
    public:
        Checker(ContextALG const * pContextALG_p);

        /**
         * Constructeur sans argument pour simplifier l'utilisation de cette classe.
         * Necessite un appel a #setContextALG
         */
        Checker();

        void setContextALG(ContextALG const * pContextALG_p);

        bool isValid();

        /**
         * Calcule le score en supposant que l'instance est valide.
         * Dans le cas contrainte, le comportement est indetermine
         */
        int computeScore();

        /**
         * Methodes permettant de ne checker que quelques contraintes
         */
        bool checkCapaIncludingTransient();
        bool checkConflict();
        bool checkSpread();
        bool checkDependances();
        
        /**
         * Methodes permettant de ne calculer que certains couts
         */
        int computeLoadCost();
        int computeLoadCost(int idxRess_p);
        int computeLoadCost(int idxRess_p, int idxMachine_p);

        int computeBalanceCost();
        int computeBalanceCost(int idxMachine_p);
        int computeBalanceCost(int idxMachine_p, int idxBalanceCost_p);

        int computePMC();
        int computeSMC();
        int computeMMC();

    private:
        bool checkCapaIncludingTransient(RessourceBO const * pRess_p);

        /**
         * Le const permet surtout a la classe cliente de s'assurer qu'on ne pourri
         * pas son contexte. Ceci dit, si le client peut eventuellement la modifier
         * donc attention : il n'est pas possible de cacher quoique se soit !
         */
        ContextALG const * pContextALG_m;

};

#endif
