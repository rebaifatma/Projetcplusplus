#ifndef BOURSE_H_INCLUDED
#define BOURSE_H_INCLUDED
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <bits/stdc++.h>
#include <set>
#include<map>
#include<iterator>



using namespace std;

class Date {
    private:
        int jour;
        int mois;
        int annee;

    public:
        Date(){};

        Date(int j, int m, int a) {
            jour = j;
            mois = m;
            annee = a;
            /*if (!Est_valide()) {
                std::cerr << "Erreur : date non valide" << std::endl;
                exit(1);
            }*/
        }
        void getjour(){cout<<jour;}

        bool Est_valide() const {

            if (mois < 1 || mois >= 12) {
                return false;
            }
            if (jour < 1 || jour > 31) {
                return false;
            }
            if ((mois == 4 || mois == 6 || mois == 9 || mois == 11) && jour > 30) {
                return false;
            }
            if (mois == 2) {
                if (jour > 29) {
                    return false;
                }
                if (jour == 29 && (annee % 4 != 0 || (annee % 100 == 0 && annee % 400 != 0))) {
                    return false;
                }
            }
            return true;
        }

        Date operator++(int)  {
            int jdm;
            if (mois == 2) {
                if (annee % 4 == 0 ) {
                    jdm=28;
                } else {
                    jdm=29;
                }
            } else if (mois == 4 || mois == 6 || mois == 9 || mois == 11) {
                jdm=30;
            } else {
                jdm=31;
            }
            if (jour < jdm) {
                jour=jour+1;
            } else {
                jour = 1;
                mois++;
                if (mois > 12) {
                    mois = 1;
                    annee++;
                }
            }
            return *this;
        }
         bool operator==(const Date& autre) const {
            return (autre.annee == annee && autre.mois == mois && autre.jour == jour) ;

        }
        bool operator < (const Date& autre) const {return (annee < autre.annee)||(autre.annee&&mois < autre.mois )||(annee == autre.annee&&mois==autre.mois &&jour < autre.jour);}

        bool operator>(const Date& autre) const {return (annee > autre.annee)||(autre.annee&&mois >autre.mois )||(annee == autre.annee&&mois==autre.mois &&jour > autre.jour);}
        bool operator <= (const Date& autre) const {return(*(this)==autre)||(*this<autre);}

        friend ostream& operator<<(ostream& flux, const Date& D) {
            flux << setfill('0') << setw(2) << D.jour << "/" << setw(2) << D.mois << "/" << D.annee;
            return flux;
        }

        friend istream& operator>>(istream& input,  Date& date) {
            char separator;
            input >> date.jour >> separator >> date.mois >> separator >> date.annee;
            if (separator != '/') {
                 input.setstate(std::ios::failbit);
            }
            return input;
        }
};


class PrixJournalier {
    private:
        Date date;
        string nomAction;
        float prix;
    public:
        PrixJournalier(){}
        PrixJournalier(Date date, string nomAction, float prix) : date(date), nomAction(nomAction), prix(prix) {}
        friend bool operator <(PrixJournalier pj1,PrixJournalier pj2 ){
        if (pj1.getDate() < pj2.getDate()) {
            return true;
        } else if (  pj2.getDate()<pj1.getDate()) {
            return false;
        } else { // Si les dates sont égales, on trie par symbole
            return pj1.getNomAction()< pj2.getNomAction();
        }
    }

     bool operator==(const PrixJournalier& other) const {return( (date== other.date)&&(nomAction==other.nomAction)&&(prix==other.prix)) ;}
     friend istream& operator >> (istream& input , PrixJournalier& pj)  {

        string nomAction;
        string prix;
        string j,m,a;
        getline(input,j,'/');
        getline(input,m,'/');
        getline(input,a,';');
        getline(input,nomAction,';');
        getline(input,prix,'\n');
        pj.date=Date( atoi(j.c_str()),atoi(m.c_str()),atoi(a.c_str()));
        pj.nomAction=nomAction;
        pj.prix= atof(prix.c_str());
        return input;


    }
    friend ostream& operator<<(ostream& flux, const PrixJournalier& D) {
            flux <<D.nomAction <<"   " <<  D.date<<"   " << D.prix;
            return flux;
        }

    Date getDate() const { return date; }
    string getNomAction() const {return nomAction;}
    float getPrix() const { return prix; }
};

class PersistancePrixJournaliers{
    public:
        static vector<PrixJournalier> lirePrixJournaliersDUnFichier(string chemin){
             vector<PrixJournalier> historique;
             ifstream f(chemin);
             int nbLignes= 0;
             string entete;
             if(f.is_open()){
                  f>>entete;
                 while(!f.eof()){
                     PrixJournalier pj;
                     f>>(pj);
                     historique.push_back(pj);
                     nbLignes++;
                }
             }
            return historique;
       }
};
class Titre{

   private:
       string nomAction;
       int qte;
   public:
       Titre(string n,int q=0){
       nomAction=n;
       qte=q;
       }
       string getNomAction() const { return nomAction;}
       int getQte() const { return qte;}
       void ajouterQte(int qteaj){
           qte= qte+qteaj;
       }
       void  diminuerQte (int qter){
           qte= qte-qter;
       }

};

enum TypeTransaction { Vente, Achat, Rien };
class Transaction {
    private:
        string nomAction;
        int qte;
        TypeTransaction Tx;
    public:
        Transaction(){};
        Transaction(string NomAction,int qte,TypeTransaction tx ):nomAction(NomAction),qte(qte),Tx(tx){};
        string getNomAction() const { return nomAction;}
        int getQte() const { return qte;}
        TypeTransaction  gettx()  const {return Tx;}
       /* void setNomAction(string nom)  {  nomAction=nom;}
        void  setQte(int q)  {  qte=q;}
        void  settx(TypeTransaction t)  {Tx=t;}*/
};
class Portefeuille{
   private:
       vector<Titre> actions;
       float valeurTotale;
   public:
     Portefeuille(float budget,vector<Titre> actions):actions(actions),valeurTotale(budget){}
     float getValeurTotale()const {return valeurTotale;}
     vector<Titre> getActions() const { return actions;}
     void acheterAction(string NomAction, int qtea,float prix){
           int i;
           for( i=0;i< static_cast<int>(actions.size());i++){
               if (actions[i].getNomAction()==NomAction){
                     actions[i].ajouterQte(qtea);
                     break;
               }
          }
          if(i==static_cast<int>(actions.size())){
             Titre T (NomAction,qtea);
             actions.push_back(T);
          }
          valeurTotale-= qtea*prix;
    }
    void vendre(string nomAction,int qte,float prix){
           valeurTotale+=qte*prix;
           int i ;
           for(i=0;i<static_cast<int>(actions.size());i++){
               if (nomAction== actions[i].getNomAction()){
                actions[i].diminuerQte(qte);
                break;
               }
          }
          if(actions[i].getQte()==0){
                actions.erase(actions.begin() + i);
          }

   }
};


class Bourse{
  protected:
     Date dateActuelle;
   public:
       void setDate (Date d){dateActuelle=d;}
       Date getaDateBourse(){return dateActuelle;}
       void incrementerDate(){dateActuelle++;}
       Bourse(Date dateActuelle):dateActuelle(dateActuelle){};
       virtual vector <string>  getActionsDisponiblesToDay()const=0;
       virtual vector <PrixJournalier> getPrixJournaliersToday () const =0;
       virtual vector<PrixJournalier> getPrixJournalierTodayParPrix(float prix)const =0;
       virtual vector<string> getActionsDisponiblesTodeyParPrix(float prix) const =0;
       virtual float getLeDernierePrix(string nomAction) const =0;
       virtual float getprixJournalierParnNom(string nom) const =0;
       virtual ~Bourse(){};



};


class BourseVector : public Bourse {
    private:
        vector<PrixJournalier> historique;
    public:
     BourseVector(Date d,vector<PrixJournalier> h):Bourse(d), historique(h) {}
     vector <PrixJournalier> getPrixJournaliersToday() const  {
            vector<PrixJournalier>vect;
            auto it = historique.begin();
            while (it != historique.end() && it->getDate() <= dateActuelle) {
               if (it->getDate() == dateActuelle) {
                   vect.push_back(*it);
               }
               ++it;
            }
            return vect;

      }

      vector<string> getActionsDisponiblesToDay() const  {
            vector<string> vect;
            auto it = historique.begin();
            while (it != historique.end() && it->getDate() <= dateActuelle) {
               if (it->getDate() == dateActuelle) {
                    vect.push_back(it->getNomAction());
               }
               ++it;
           }
          return vect;

      }

     vector<PrixJournalier> getPrixJournalierTodayParPrix(float prix) const {
           vector<PrixJournalier>vect;
            auto it = historique.begin();
            while ((it != historique.end())&&(it->getDate()<=dateActuelle)) {
                 if ( (it->getPrix()< prix)&&( it->getDate()==dateActuelle)) {
                       vect.push_back(*it);
                 }
                 it++;
            }

           return vect;
       }
       vector<string > getActionsDisponiblesTodeyParPrix(float prix) const {
           vector<string>vect;
            auto it = historique.begin();
            while (it != historique.end() && it->getDate() <= dateActuelle) {

                   if ((it->getDate() == dateActuelle)&& (it->getPrix()<=prix)) {
                       vect.push_back(it->getNomAction());
                   }
                  ++it;
            }
           return vect;
       }
       float getLeDernierePrix(string nomAction) const{
           float prix =0;

           for(auto it:historique )  {

               if(it.getNomAction()==nomAction&&it.getDate()<=dateActuelle ){
                        prix= it.getPrix();
                }
              else if(it.getDate()>dateActuelle){
                break;
              }

           }
           return prix;
       }
       float getprixJournalierParnNom(string nom) const {
            for(int i=0;i<static_cast<int>(historique.size());i++){
                if(historique[i].getNomAction()==nom && historique[i].getDate() == dateActuelle){
                        return  historique[i].getPrix();

                }

            }
       }





};
class BourseSet : public Bourse {
    private:
        set<PrixJournalier> historique;

    public:
        BourseSet(Date d,vector<PrixJournalier> h):Bourse(d) {
            for(auto it :h){
                    historique.insert(it);
            }
        }
        vector <PrixJournalier> getPrixJournaliersToday() const  {
            vector<PrixJournalier> vect;
            auto it = historique.lower_bound(PrixJournalier(dateActuelle, "", 0));
            while (it != historique.end() && it->getDate() == dateActuelle ) {
                    vect.push_back(*it);
                    ++it;
            }

            return vect;

        }
        vector <string>  getActionsDisponiblesToDay()const {
                vector<string> vect;
                auto it = historique.lower_bound(PrixJournalier(dateActuelle, "", 0));

                 while (it != historique.end() && it->getDate() == dateActuelle ) {
                    cout<<"oui";
                    vect.push_back(it->getNomAction());

                    ++it;
                }
                return vect;
        }
        vector<PrixJournalier> getPrixJournalierTodayParPrix(float prix)const{
            vector<PrixJournalier> vect;
            auto it = historique.lower_bound(PrixJournalier(dateActuelle, "", prix));

            while (it != historique.end() && it->getDate() == dateActuelle ) {
                if(it->getPrix()<= prix){
                    vect.push_back(*it);
                }
                ++it;
             }
            return vect;
        }
        vector<string> getActionsDisponiblesTodeyParPrix(float prix) const {
            vector<std::string> vect;
            auto it = historique.lower_bound(PrixJournalier(dateActuelle, "", prix));

            while (it != historique.end() && it->getDate() == dateActuelle ) {
                if(it->getPrix()<= prix){
                    vect.push_back(it->getNomAction());
                }
                ++it;
             }
            return vect;
        }
        float getLeDernierePrix(string nomAction) const{
            float prix;
            auto it = historique.upper_bound(PrixJournalier(dateActuelle, nomAction, 0));
            while (it != historique.begin()) {
                --it;
                if (it->getNomAction() == nomAction) {
                    prix = it->getPrix();
                    break;
                }
           }
           return prix;
       }
       float getprixJournalierParnNom(string nom) const {
             auto it = historique.lower_bound(PrixJournalier(dateActuelle, nom, 0.0));
             while (it != historique.end() && it->getNomAction() == nom ) {
                if( it->getDate() == dateActuelle)
                   return it->getPrix();
                else
                    ++it;
             }

       }
};
class BourseMultiMap : public Bourse {
    private:
        multimap<Date ,PrixJournalier> historique;

    public:

         BourseMultiMap(Date dateActuelle, vector<PrixJournalier> h): Bourse(dateActuelle){
             for ( PrixJournalier prixJournalier : h) {
                   historique.insert(make_pair(prixJournalier.getDate(), prixJournalier));

             }
           }
        vector<string> getActionsDisponiblesToDay() const {
           vector<string> vect;
           auto it = historique.find(dateActuelle);
           while( it->first==dateActuelle) {
                 vect.push_back(it->second.getNomAction());
                 it++;
           }

           return vect;
        }

        vector<PrixJournalier>getPrixJournaliersToday() const {

            vector<PrixJournalier> vect;
            auto it = historique.find(dateActuelle);

             while( it->first==dateActuelle) {
               vect.push_back(it->second);
               it++;

            }

            return vect;
        }


        vector<PrixJournalier> getPrixJournalierTodayParPrix(float prix) const  {
           vector<PrixJournalier> prixJournaliersParPrix;
           auto it = historique.find(dateActuelle);
           while( it->first==dateActuelle) {
             if ( it->second.getPrix() <= prix) {
                 prixJournaliersParPrix.push_back(it->second);
             }
             it++;
           }

          return prixJournaliersParPrix;
        }

        vector<string> getActionsDisponiblesTodeyParPrix(float prix) const  {
            vector<string> actionsDisponiblesParPrix;

            auto it = historique.find(dateActuelle);
            while( it->first==dateActuelle) {
               if ( it->second.getPrix() <= prix) {
                actionsDisponiblesParPrix.push_back(it->second.getNomAction());
               }
               it++;
            }

        return actionsDisponiblesParPrix;
       }

       float getLeDernierePrix(string nomAction) const  {

           auto it =historique.upper_bound( dateActuelle);
            while (it != historique.begin()) {
                 --it;
                if (it->second.getNomAction()==nomAction ) {
                      return it->second.getPrix();
                }
            }
       }
       float getprixJournalierParnNom(string nomAction) const  {
           auto range = historique.equal_range(dateActuelle);
           auto it = range.second;
            while (it != range.first) {
                 --it;
                if (it->second.getNomAction()==nomAction ) {
                      return it->second.getPrix();
                }
            }
       }



};
class Trader {
public:
    Trader(){};
    virtual Transaction choisirTransaction(const Bourse &b, const Portefeuille &pf)=0;
    virtual ~Trader(){} ;
};

class TraderAletoireVerifie : public Trader {
    public:
     TraderAletoireVerifie():Trader(){};
     Transaction choisirTransaction(const Bourse &b, const Portefeuille &pf) override{
         TypeTransaction tx;
         vector<Titre>actions=pf.getActions();
         if (actions.empty() && pf.getValeurTotale()==0){
                Transaction Tx(" ",0,Rien );
                return Tx;

          }
         else if (pf.getValeurTotale()==0) {

                vector<PrixJournalier> prixJournalierDisponibleToday;
                prixJournalierDisponibleToday=b.getPrixJournaliersToday();
                if(!prixJournalierDisponibleToday.empty()){
                    vector<PrixJournalier>prixJournalierAvendre;
                    for(int i=0;i<static_cast<int>(pf.getActions().size());i++){
                        for(int j=0;j<static_cast<int>(prixJournalierDisponibleToday.size());j++) {
                               if(prixJournalierDisponibleToday[j].getNomAction()==pf.getActions()[i].getNomAction()){
                                    prixJournalierAvendre.push_back(prixJournalierDisponibleToday[j]);

                                }
                        }
                    }
                    if(!prixJournalierAvendre.empty()){
                        int i=rand()%prixJournalierAvendre.size();
                        int qte=0;
                        int k=0;//tw nahih just le test
                        for( k=0;k<pf.getActions().size();k++){
                            if(pf.getActions()[k].getNomAction()==prixJournalierAvendre[i].getNomAction()){
                               qte=1+rand()%pf.getActions()[k].getQte();

                                break;
                            }
                        }

                        Transaction Tx(prixJournalierAvendre[i].getNomAction(),qte,Vente );
                        return Tx;
                    }
                    else{
                        Transaction Tx(" ",0,Rien );

                         return Tx;
                    }
            }
         }

        else if(actions.empty()){

                vector<PrixJournalier>  prixJournalierDisponibleTodayParPrix;
                prixJournalierDisponibleTodayParPrix=b.getPrixJournalierTodayParPrix(pf.getValeurTotale());
                if(prixJournalierDisponibleTodayParPrix.empty()){
                        Transaction Tx(" ",0,Rien );

                        return Tx;
                }
                else{
                    int n=prixJournalierDisponibleTodayParPrix.size();
                    int i=rand()%n;
                    int m =pf.getValeurTotale()/prixJournalierDisponibleTodayParPrix[i].getPrix();

                    int qteachete=1+(rand()%m);

                    Transaction Tx (prixJournalierDisponibleTodayParPrix[i].getNomAction(),qteachete,Achat);
                    return Tx;


                }
            }

        else{
                int x= rand()%3;
                if(x==0){
                   tx=Achat;
                }
                else if(x==1){
                 tx=Vente;

                }
                else{
                    tx=Rien;
                }
                if(tx==Achat){
                        vector<PrixJournalier> prixJournalierDisponibleTodayParPrix;
                        prixJournalierDisponibleTodayParPrix=b.getPrixJournalierTodayParPrix(pf.getValeurTotale());

                        if(prixJournalierDisponibleTodayParPrix.size()!=0){

                           int n=prixJournalierDisponibleTodayParPrix.size();
                           int i=rand()%n;

                           int m=pf.getValeurTotale()/prixJournalierDisponibleTodayParPrix[i].getPrix();

                           int qteachete=1+(rand()%m);

                           Transaction Tx (prixJournalierDisponibleTodayParPrix[i].getNomAction(),qteachete,Achat);

                           return Tx;
                           }
                        else{
                                int i=rand()%2;
                                if(i==0){

                                   Transaction Tx(" ",0,Rien );
                                   return Tx;
                                }
                                else{
                                  tx=Vente;
                                  vector<PrixJournalier> prixJournalierDisponibleToday;
                                  prixJournalierDisponibleToday = b.getPrixJournaliersToday();

                                  if(! prixJournalierDisponibleToday.empty()){
                                       vector<PrixJournalier>prixJournalierAvendre;
                                       for(int i=0;i<static_cast<int>(actions.size());i++){
                                         for(int j=0;j<static_cast<int>(prixJournalierDisponibleToday.size());j++) {
                                             if(prixJournalierDisponibleToday[j].getNomAction()==actions[i].getNomAction()){
                                                 prixJournalierAvendre.push_back(prixJournalierDisponibleToday[j]);
                                             }
                                         }
                                       }
                                       if(!prixJournalierAvendre.empty()){

                                          int n=prixJournalierAvendre.size();

                                          int i=rand()% n;

                                          int qte=0;

                                          int k=0;

                                          for(k=0;k<static_cast<int>(pf.getActions().size());k++){

                                             if(actions[k].getNomAction()==prixJournalierAvendre[i].getNomAction() ){
                                                 qte=1+(rand()%actions[k].getQte());
                                                 break;
                                             }
                                          }


                                          Transaction Tx(prixJournalierAvendre[k].getNomAction(),qte,Vente );
                                          return Tx;

                                       }
                                  }
                                  else{

                                    Transaction Tx(" ",0,Rien );
                                    return Tx;

                                  }

                                }

                       }
                }
                else if (tx==Vente){
                        vector<PrixJournalier> prixJournalierDisponibleToday;
                        prixJournalierDisponibleToday=b.getPrixJournaliersToday();
                        if(!prixJournalierDisponibleToday.empty()){
                               vector<PrixJournalier>prixJournalierAvendre;
                               for(int i=0;i<static_cast<int>(actions.size());i++){
                                    for(int j=0;j<static_cast<int>(prixJournalierDisponibleToday.size());j++) {
                                        if(prixJournalierDisponibleToday[j].getNomAction()==actions[i].getNomAction()){
                                             prixJournalierAvendre.push_back(prixJournalierDisponibleToday[j]);
                                        }
                                    }
                                }
                               if(prixJournalierAvendre.size()!=0){
                                    int n= prixJournalierAvendre.size();
                                    int i=rand()%n;

                                    int j=0;
                                    for( j=0;j<static_cast<int>(actions.size());j++){
                                      if(actions[j].getNomAction()==prixJournalierAvendre[i].getNomAction() ){
                                            int qte=1+(rand()%actions[j].getQte());


                                              Transaction Tx(actions[j].getNomAction(),qte,Vente );
                                              return Tx;



                                      }


                                    }



                               }
                              else{

                                   int i=rand()%2;
                                   if(i==0){
                                       Transaction Tx(" ",0,Rien );
                                    }
                                    else{
                                        tx=Achat;
                                         vector<PrixJournalier> prixJournalierDisponibleTodayParPrix;
                                         prixJournalierDisponibleTodayParPrix=b.getPrixJournalierTodayParPrix(pf.getValeurTotale());
                                         if(prixJournalierDisponibleTodayParPrix.empty()){
                                             Transaction Tx(" ",0,Rien );
                                             return Tx;

                                         }

                                         else{
                                              int i=rand()%prixJournalierDisponibleTodayParPrix.size();
                                              int m =pf.getValeurTotale()/prixJournalierDisponibleTodayParPrix[i].getPrix();
                                              int qteachete=1+(rand()%m);
                                              Transaction Tx (prixJournalierDisponibleTodayParPrix[i].getNomAction(),qteachete,Achat);
                                              return Tx;
                                        }

                                   }
                              }
                        }
                }
                else{
                      Transaction Tx(" ",0,Rien );

                      return Tx;
                }

        }


}

};
class TraderAletoire : public Trader {
  public:
      TraderAletoire(): Trader(){};
      Transaction  choisirTransaction(const Bourse &b, const Portefeuille &pf)override{

        vector<Titre>actions=pf.getActions();
        bool test=false;
        while(test==false){
            int tx= rand()%3;
            if (tx==1){ //les diago mt3 if welse mriglin
                    vector<PrixJournalier> prixJournalierDisponibleToday;
                    prixJournalierDisponibleToday=b.getPrixJournaliersToday();
                    vector<PrixJournalier>prixJournalierAvendre;
                    if(prixJournalierDisponibleToday.size()!=0){
                         for(int i=0;i<actions.size();i++){
                            for(int j=0;j<prixJournalierDisponibleToday.size();j++) {
                                        if(prixJournalierDisponibleToday[j].getNomAction()==actions[i].getNomAction()){
                                           prixJournalierAvendre.push_back(prixJournalierDisponibleToday[j]);
                             }           }
                         }

                         if(prixJournalierAvendre.size()!=0){
                         int i=rand()%prixJournalierAvendre.size();
                         int j;
                         for( j=0;j<static_cast<int>(actions.size());j++){
                                      if(actions[j].getNomAction()==prixJournalierAvendre[i].getNomAction() )
                                         break;
                                         int qte=1+rand()%actions[j].getQte();
                                         Transaction Tx (prixJournalierAvendre[i].getNomAction(),qte,Vente);
                                         test=true;
                                         return Tx;
                                     }
                        }

                    }
            }
            else if(tx==2){
                         vector<PrixJournalier> prixJournalierDisponibleTodayParPrix;
                         prixJournalierDisponibleTodayParPrix=b.getPrixJournalierTodayParPrix(pf.getValeurTotale());
                         if(prixJournalierDisponibleTodayParPrix.size()!=0){
                             int i=rand()%prixJournalierDisponibleTodayParPrix.size();
                             int qteachete=1+rand()%int(pf.getValeurTotale()/prixJournalierDisponibleTodayParPrix[i].getPrix());test=true;
                             Transaction Tx(prixJournalierDisponibleTodayParPrix[i].getNomAction(),qteachete,Achat);
                             return Tx;
                         }
                    }
             else{
                            test=true;
                            Transaction Tx(" ",0,Rien );

                            return Tx;
            }
        }


      }
};
class TraderAletoireIntelgent: public Trader {
  public:
     TraderAletoireIntelgent():Trader(){};
     Transaction  choisirTransaction(const Bourse &b, const Portefeuille &pf)override{
        vector<Titre>actions=pf.getActions();
        bool test=false;
        while(test==false){
            TypeTransaction tx= static_cast<TypeTransaction>(rand()%3);
            if (tx==Vente){ //nBI3 a8la wahda
                        vector<PrixJournalier> prixJournalierDisponibleToday;
                        prixJournalierDisponibleToday=b.getPrixJournaliersToday();
                        if(!prixJournalierDisponibleToday.empty()){
                               vector<PrixJournalier>prixJournalierAvendre;
                               for(int i=0;i<static_cast<int>(actions.size());i++){
                                    for(int j=0;j<static_cast<int>(prixJournalierDisponibleToday.size());j++) {
                                        if(prixJournalierDisponibleToday[j].getNomAction()==actions[i].getNomAction()){
                                        prixJournalierAvendre.push_back(prixJournalierDisponibleToday[j]);
                                       }
                                    }
                                }
                               if(!prixJournalierAvendre.empty()){
                                    float p=prixJournalierAvendre[0].getPrix();
                                    int j=0;
                                    for(int i=0;i<static_cast<int>(prixJournalierAvendre.size());i++){
                                        if(prixJournalierAvendre[i].getPrix()>p)
                                        {
                                           p=prixJournalierAvendre[i].getPrix();
                                           j=i;
                                        }

                                    }

                                    for( int k=0;k<static_cast<int>(actions.size());k++){
                                      if(actions[k].getNomAction()==prixJournalierAvendre[j].getNomAction() ){
                                        int qte=1+rand()%actions[k].getQte();
                                        Transaction Tx(prixJournalierAvendre[j].getNomAction(),qte,Vente );
                                        test=true;
                                        return Tx;
                                      }
                                    }
                               }
                        }
            }
            else if(tx==Achat){
                    //ken prix arkhes wahda nbi3
                    vector<PrixJournalier> prixJournalierDisponibleTodayParPrix;
                    prixJournalierDisponibleTodayParPrix=b.getPrixJournalierTodayParPrix(pf.getValeurTotale());
                    if(!prixJournalierDisponibleTodayParPrix.empty()){
                           float p=prixJournalierDisponibleTodayParPrix[0].getPrix();
                           int j=0;
                           for(int i=0;i<0;i++){
                                if(prixJournalierDisponibleTodayParPrix[i].getPrix()<p)
                                {
                                  p=prixJournalierDisponibleTodayParPrix[i].getPrix();
                                  j=i;
                                }
                           }
                           int qteachete=1+rand()%int(pf.getValeurTotale()/prixJournalierDisponibleTodayParPrix[j].getPrix());
                           Transaction Tx (prixJournalierDisponibleTodayParPrix[j].getNomAction(),qteachete,Achat);
                           test=true;

                           return Tx;
                    }
             }
             else{
                    Transaction Tx(" ",0,Rien );
                    test=true;

                    return Tx;
             }
        }
     }
};
/*class TraderAletoireIntelgent: public Trader {
  public:
     TraderAletoireIntelgent():Trader(){};
     Transaction  choisirTransaction(const Bourse &b, const Portefeuille &pf)override{
        vector<Titre>actions=pf.getActions();
        bool test=false;
        while(test==false){
            TypeTransaction tx= static_cast<TypeTransaction>(rand()%3);
            if (tx==Vente){ //nBI3 a8la wahda
                        vector<PrixJournalier> prixJournalierDisponibleToday;
                        prixJournalierDisponibleToday=b.getPrixJournaliersToday();
                        if(!prixJournalierDisponibleToday.empty()){
                               vector<PrixJournalier>prixJournalierAvendre;
                               for(int i=0;i<static_cast<int>(actions.size());i++){
                                    for(int j=0;j<static_cast<int>(prixJournalierDisponibleToday.size());j++) {
                                        if(prixJournalierDisponibleToday[j].getNomAction()==actions[i].getNomAction()){
                                        prixJournalierAvendre.push_back(prixJournalierDisponibleToday[j]);
                                       }
                                    }
                                }
                               if(!prixJournalierAvendre.empty()){
                                    float p=prixJournalierAvendre[0].getPrix();
                                    int j=0;
                                    for(int i=0;i<static_cast<int>(prixJournalierAvendre.size());i++){
                                        if(prixJournalierAvendre[i].getPrix()>p)
                                        {
                                           p=prixJournalierAvendre[i].getPrix();
                                           j=i;
                                        }

                                    }

                                    for( int k=0;k<static_cast<int>(actions.size());k++){
                                      if(actions[k].getNomAction()==prixJournalierAvendre[j].getNomAction() ){
                                        int qte=1+rand()%actions[k].getQte();
                                        Transaction Tx(prixJournalierAvendre[j].getNomAction(),qte,Vente );
                                        test=true;
                                        return Tx;
                                    }

                               }
                        }
             }
             else if(tx==Achat){
                    //ken prix arkhes wahda nbi3


                    vector<PrixJournalier> prixJournalierDisponibleTodayParPrix;
                    prixJournalierDisponibleTodayParPrix=b.getPrixJournalierTodayParPrix(pf.getValeurTotale());
                    if(!prixJournalierDisponibleTodayParPrix.empty()){
                           float p=prixJournalierDisponibleTodayParPrix[0].getPrix();
                           int j=0;
                           for(int i=0;i<0;i++){
                                if(prixJournalierDisponibleTodayParPrix[i].getPrix()<p)
                                {
                                  p=prixJournalierDisponibleTodayParPrix[i].getPrix();
                                  j=i;
                                }

                           }
                           int qteachete=1+rand()%int(pf.getValeurTotale()/prixJournalierDisponibleTodayParPrix[j].getPrix());
                           Transaction Tx (prixJournalierDisponibleTodayParPrix[j].getNomAction(),qteachete,Achat);
                           test=true;
                           cout<<"oui";
                           return Tx;

                    }



             }
             else{
                    Transaction Tx(" ",0,Rien );
                    test=true;
                    cout<<"oui";
                    return Tx;


             }
        }

      }
};*/


class Simulation{
   private:
       Date dateDebut;
       Date dateFin;
       Date dateCourant;
       float budget;
   public:
    Simulation() {
        dateDebut = Date();
        dateFin = Date();
        dateCourant = Date();
        budget = 0.0;
    }

    static map<string,long> executer(Bourse& bourse, Trader& trader, Date debut, Date fin, float soldeInitial) {
        map<string, long> stats;
        if(debut>bourse.getaDateBourse()){
            bourse.setDate(debut);
        }


        vector<Titre> actions;
        Portefeuille P(soldeInitial, actions);
        long compteurVente=0;
        long compteurAchat=0;
        int nbTransactions = 0;
        auto start = chrono::high_resolution_clock::now();
        while (bourse.getaDateBourse() <= fin) {
                Transaction Tx = trader.choisirTransaction(bourse, P);
                if( nbTransactions == 100){
                     nbTransactions == 0;



                     bourse.incrementerDate();
                }

                else if(Tx.gettx() == Vente){
                        cout<<"vente"<<endl;

                       P.vendre(Tx.getNomAction(),Tx.getQte(),bourse.getprixJournalierParnNom(Tx.getNomAction()));

                        nbTransactions++;
                        compteurVente++;
              }
              else if (Tx.gettx()== Rien ) {


                   nbTransactions = 0;

                   bourse.incrementerDate();
                   cout<<"rien"<<endl;
                   cout<<"date"<<bourse.getaDateBourse()<<endl;
              }


              else if(Tx.gettx()==Achat){
                     cout<<"achat"<<endl;


                        P.acheterAction(Tx.getNomAction(), Tx.getQte(),bourse.getprixJournalierParnNom(Tx.getNomAction()));
                        nbTransactions++;
                        compteurAchat++;

              }


        }

        for (auto p:P.getActions()) {

             P.vendre(p.getNomAction(),p.getQte(), bourse.getLeDernierePrix(p.getNomAction()));
        }
        auto stop = chrono::high_resolution_clock::now();

        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
        stats.insert(make_pair("tempsExecutionSimulationParµs", duration.count()));
        stats.insert(make_pair("soldeFinaleDeTrader", P.getValeurTotale()));
        stats.insert(make_pair("nombreDeVente", compteurVente));
        stats.insert(make_pair("nombreDeAchat", compteurAchat));
        if(P.getValeurTotale()-soldeInitial<0){
            stats.insert(make_pair("Gain", P.getValeurTotale()-soldeInitial-1));
        }
        else{
            stats.insert(make_pair("Gain", P.getValeurTotale()-soldeInitial));
        }


    return stats;
}





};





#endif // BOURSE_H_INCLUDED
