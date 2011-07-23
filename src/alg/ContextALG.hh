#ifndef CONTEXTALG_HH
#define CONTEXTALG_HH

class ContextBO;

/** Brouillon d'un contexte alg qui enveloppe le contexte bo
*/

class ContextALG
{
    public:
    	ContextALG();
    	~ContextALG();

    	ContextBO * getpContextBo() const;
    	void setpContextBo(ContextBO *);

    private:
    	ContextBO * pContextBo_m;
};

#endif
