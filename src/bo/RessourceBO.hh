#ifndef RESSOURCEBO_HH
#define RESSOURCEBO_HH

class RessourceBO {
    public:
        RessourceBO(int id_p, bool isTransient_p, int loadCost_p);
        int getId() const;
        bool isTransient() const;
        int getLoadCost() const;

    private:
        int id_m;
        bool isTransient_m;
        int loadCost_m;
};

#endif
