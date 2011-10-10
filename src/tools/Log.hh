#ifndef LOG_HH
#define LOG_HH
#include <iostream>
#include <string>
#include <vector>
#include <boost/static_assert.hpp>

#define USELESS 0 /*LOG(USELESS) << "C'est toto qui va a la plage, et..." */
#define DEBUG 1   /*LOG(DEBUG)   << "Je viens d'initialiser ma structure interne" */
#define INFO 2    /*LOG(INFO)    << "Fin de la phase d'init" */
#define WARNING 3 /*LOG(WARNING) << "Je passe l'eponge sur tes entrees mal formatees, mais fait attention coco" */
#define ERREUR 4  /*LOG(ERREUR)  << "Le turbo propulseur a rendu l'ame, impossible de continuer" */
#define WTF 5     /*LOG(WTF)     << "What a Terrible Failure..." */

/*****************************
 * Ci dessus : la definition des niveaux de log.
 *
 * Ci dessous : rien d'interessant. Vraiment.
 * Ce qui suit n'a d'interet que si vous souhaitez modifier le loggueur,
 * mais si vous souhaitez juste savoir comment l'utiliser, concentrez vous sur ce qui precede
 *****************************/

class LogHelper {
    public:
        static std::vector<std::string> buildLogLvl();
        static std::vector<std::string> vLogStrLvl_g;

        /**
         * Etant donne un path, extrait le nom du fichier
         */
        static std::string extractFilename(const std::string& path_p);
};


#ifndef MIN_LOG_LVL
/* Il est possible de definir le level de log par defaut :
 * - via le script configure
 * - via une macro dans un .cc
 * 
 * Si on est malgre ca dans le cas ou aucun lvl par defaut n'est defini, on en fourni un par defaut
 */
#define MIN_LOG_LVL WARNING
#endif

#define LOGINIT(log_lvl) BOOST_STATIC_ASSERT(0 <= log_lvl && log_lvl <= WTF); \
    if ( MIN_LOG_LVL > (log_lvl) ); \
    else std::clog << "[" << LogHelper::vLogStrLvl_g[(log_lvl)] << " - "

#define LOGENDMSG << LogHelper::extractFilename(__FILE__) << ":" <<  __LINE__<< "] "

#define LOG(log_lvl) \
    LOGINIT(log_lvl) \
    LOGENDMSG

#define LOG_M(log_lvl, msg) \
    LOGINIT(log_lvl) \
    << msg << " - " \
    LOGENDMSG




#endif
