#include <iostream>
#include "Bourse.h"
#include <cstdlib>
#include <ctime>
using namespace std;

int main(){

    while(1){
    int choix;
    srand(time(NULL));

    vector<PrixJournalier>historique=PersistancePrixJournaliers::lirePrixJournaliersDUnFichier("prices_simple (1).csv");
    Simulation sim;
    TraderAletoire trad;
    time_t t=time(NULL);
    tm tm=*localtime(&t);
    cout<<"\n***************************************************************************************************************"<<endl;
    cout<<"*"<<"                                                                                                             "<<"*"<<endl;
    cout<<"*"<<tm.tm_hour<<":"<<tm.tm_min<<":"<<tm.tm_sec<<"                      Menu                                                    "<<tm.tm_mday<<"/"<<tm.tm_mon+1<<"/"<<tm.tm_year+1900<<"*"<<endl;
    cout<<"*"<<"                                                                                                             "<<"*"<<endl;
    cout<<"\n***************************************************************************************************************"<<endl;
    cout<<"1)Creer une simulation"<<endl;
    cout<<"2)voir les prix journaliers disponible aujourdhui"<<endl;
    cout<<"3)voir les prix journaliers disponible aujourdhui par prix"<<endl;
    cout<<"4)voir le dernier prix d'une action"<<endl;
    cout<<"5) Quitter"<<endl;
    cin>>choix;
    switch(choix){
            case 1:{
                      Date dateDebutSimulation;
                      do{

                                cout<<"Donner la date de debut de simulation"<<endl;
                                 cin>>dateDebutSimulation;
                      }while(!dateDebutSimulation.Est_valide());
                       Date dateFinSimulation;
                      do{

                                cout<<"Donner la date de FIN  de simulation"<<endl;
                                cin>>dateFinSimulation;
                      }while(!dateFinSimulation.Est_valide());
                      int i=0;
                      do{
                                 cout<<"***selectionner le type de bourse             ***"<<endl;
                                 cout<<"*     1) Bourse Set                             *"<<endl;
                                 cout<<"*     2) Bourse Vector                          *"<<endl;
                                 cout<<"*     3) Bourse multimap                        *"<<endl;
                                 cout<<"*************************************************"<<endl;
                                 cin>>i;
                      }while(i<0 || i>3);
                      switch(i){
                              case 1:{
                                   BourseSet b(dateDebutSimulation,historique);
                                   float montantDeDepart;
                                   do{
                                         cout<<"Donner le montant de départ"<<endl;
                                         cin>>montantDeDepart;
                                    }while(montantDeDepart<=0);
                                    int n;
                                    do{

                                        cout<<"***Choisissez le trader pour cette simulation****"<<endl;
                                        cout<<"*     1) Trader Aletoire                        *"<<endl;
                                        cout<<"*     2) Trader Aletoire Verifie                *"<<endl;
                                        cout<<"*     3) Trader Aletoire Intelgent              *"<<endl;
                                        cout<<"*************************************************"<<endl;
                                        cin>>n;
                                    }while (n < 1 || n > 3);
                                    switch(n){
                                            case 1:{

                                                  TraderAletoire trader;
                                                  Simulation sim;
                                                  srand(time(NULL));
                                                  map<string,long> stats=sim.executer(b,trader,dateDebutSimulation,dateFinSimulation,montantDeDepart);
                                                  for(auto it:stats){
                                                            cout<<it.first<<"\t"<<it.second<<endl;
                                                     }

                                                break;
                                             }
                                             case 2:{
                                                    TraderAletoireVerifie trader;
                                                    Simulation sim;
                                                    srand(time(NULL));
                                                    map<string,long> stats=sim.executer(b,trader,dateDebutSimulation,dateFinSimulation,montantDeDepart);
                                                    for(auto it:stats){
                                                            cout<<it.first<<"\t"<<it.second<<endl;
                                                     }

                                                   break;
                                              }
                                              case 3:{
                                                    TraderAletoireIntelgent trader;
                                                     Simulation sim;
                                                     srand(time(NULL));
                                                     map<string,long> stats=sim.executer(b,trader,dateDebutSimulation,dateFinSimulation,montantDeDepart);
                                                     for(auto it:stats){
                                                            cout<<it.first<<"\t"<<it.second<<endl;
                                                     }

                                                     break;
                                             }
                                     }
                                     break;

                               }
                               case 2:{
                                    BourseVector b(dateDebutSimulation,historique);
                                    float montantDeDepart;
                                    do{
                                        cout<<"Donner le montant de départ"<<endl;
                                        cin>>montantDeDepart;
                                    }while(montantDeDepart<=0);
                                    int n;
                                    do{

                                            cout<<"***Choisissez le trader pour cette simulation****"<<endl;
                                            cout<<"*     1) Trader Aletoire                        *"<<endl;
                                            cout<<"*     2) Trader Aletoire Verifie                *"<<endl;
                                            cout<<"*     3) Trader Aletoire Intelgent              *"<<endl;
                                            cout<<"*************************************************"<<endl;
                                            cin>>n;
                                    }while (n < 1 || n > 3);
                                    switch(n){
                                            case 1:{
                                                    TraderAletoire trader;
                                                    Simulation sim;
                                                    srand(time(NULL));
                                                     map<string,long> stats=sim.executer(b,trader,dateDebutSimulation,dateFinSimulation,montantDeDepart);
                                                     for(auto it:stats){
                                                            cout<<it.first<<"\t"<<it.second<<endl;
                                                     }


                                                    break;
                                            }
                                            case 2:{
                                                    TraderAletoireVerifie trader;
                                                    Simulation sim;
                                                    srand(time(NULL));
                                                     map<string,long> stats=sim.executer(b,trader,dateDebutSimulation,dateFinSimulation,montantDeDepart);
                                                     for(auto it:stats){
                                                            cout<<it.first<<"\t"<<it.second<<endl;
                                                     }
                                                        break;
                                            }
                                            case 3:{
                                                        TraderAletoireIntelgent trader;
                                                        Simulation sim;
                                                        srand(time(NULL));
                                                        map<string,long> stats=sim.executer(b,trader,dateDebutSimulation,dateFinSimulation,montantDeDepart);
                                                         for(auto it:stats){
                                                            cout<<it.first<<"\t"<<it.second<<endl;
                                                         }
                                                            break;
                                            }

                                       }
                                       break;
                               }
                               case 3:{
                                       BourseMultiMap b(dateDebutSimulation,historique);
                                       float montantDeDepart;
                                       do{
                                                cout<<"Donner le montant de départ"<<endl;
                                                cin>>montantDeDepart;
                                        }while(montantDeDepart<=0);
                                        int n;
                                        do{

                                                cout<<"***Choisissez le trader pour cette simulation****"<<endl;
                                                cout<<"*     1) Trader Aletoire                        *"<<endl;
                                                cout<<"*     2) Trader Aletoire Verifie                *"<<endl;
                                                cout<<"*     3) Trader Aletoire Intelgent              *"<<endl;
                                                cout<<"*************************************************"<<endl;
                                                cin>>n;
                                        }while (n < 1 || n > 3);
                                        switch(n){
                                                case 1:{
                                                        TraderAletoire trader;
                                                        sim.executer(b,trader,dateDebutSimulation,dateFinSimulation,montantDeDepart);

                                                    break;
                                                }
                                                case 2:{
                                                            TraderAletoireVerifie trader;
                                                            sim.executer(b,trader,dateDebutSimulation,dateFinSimulation,montantDeDepart);

                                                    break;
                                                }
                                                case 3:{
                                                            TraderAletoireIntelgent trader;
                                                            sim.executer(b,trader,dateDebutSimulation,dateFinSimulation,montantDeDepart);

                                                        break;
                                                }
                                        }
                                break;
                               }
                      }





                       break;
             }


            case 2:{
                    int i=0;
                    do{
                        cout<<"***sélectionner le type de bourse pour la recherche            ***"<<endl;
                        cout<<"*     1) Bourse Set                                              *"<<endl;
                        cout<<"*     2) Bourse Vector                                           *"<<endl;
                        cout<<"*     3) Bourse multimap                                         *"<<endl;
                        cout<<"******************************************************************"<<endl;
                    }while(i<0 || i>3);
                    switch(i){
                            case 1:{
                                  Date dateActuelle;
                                  do{

                                      cout<<"Donner la date de debut de simulation"<<endl;
                                     cin>>dateActuelle;
                                   }while(! dateActuelle.Est_valide());
                                    BourseSet b(dateActuelle,historique);
                                    cout<<"les prix jouranliers disponible aujourdhui "<<endl;
                                    for(auto pj:b.getPrixJournaliersToday()){
                                        cout<<pj<<endl;
                                    }
                                 break;
                            }
                            case 2:{
                                   Date dateActuelle;
                                   do{

                                      cout<<"Donner la date de debut de simulation"<<endl;
                                      cin>>dateActuelle;
                                   }while(! dateActuelle.Est_valide());
                                    BourseVector b(dateActuelle,historique);
                                    cout<<"les prix jouranliers disponible aujourdhui "<<endl;
                                    for(auto pj:b.getPrixJournaliersToday()){
                                        cout<<pj<<endl;
                                    }
                                 break;
                            }
                            case 3:{
                                    Date dateActuelle;
                                    do{

                                      cout<<"Donner la date de debut de simulation"<<endl;
                                      cin>>dateActuelle;
                                     }while(! dateActuelle.Est_valide());
                                    BourseVector b(dateActuelle,historique);
                                    cout<<"les prix jouranliers disponible aujourdhui "<<endl;
                                    for(auto pj:b.getPrixJournaliersToday()){
                                            cout<<pj<<endl;
                                    }
                                    break;
                            }
                    }
                    break;
            }
            case 3:{
                    int i=0;
                    do{
                        cout<<"***sélectionner le type de bourse pour la recherche            ***"<<endl;
                        cout<<"*     1) Bourse Set                                              *"<<endl;
                        cout<<"*     2) Bourse Vector                                           *"<<endl;
                        cout<<"*     3) Bourse multimap                                         *"<<endl;
                        cout<<"******************************************************************"<<endl;
                    }while(i<0 || i>3);
                    switch(i){
                            case 1: {
                                Date dateActuelle;
                                   do{

                                      cout<<"Donner la date de debut de simulation"<<endl;
                                      cin>>dateActuelle;
                                   }while(! dateActuelle.Est_valide());
                                BourseMultiMap b(dateActuelle,historique);
                                double p;
                                do{
                                    cout<<"Donner le prix de l'action à rechercher dans la bourse"<<endl;
                                    cin>>p;
                                }while(p<=0);
                                cout<<"les prix jouranliers disponible aujourdhui par votre prix "<< p<<endl;
                                for(auto pj:b.getPrixJournalierTodayParPrix(p)){
                                        cout<<pj<<endl;
                                }
                                break;
                             }
                             case 2:{
                                 Date dateActuelle;
                                   do{

                                      cout<<"Donner la date de debut de simulation"<<endl;
                                      cin>>dateActuelle;
                                   }while(! dateActuelle.Est_valide());
                                BourseVector b(dateActuelle,historique);
                                double p;
                                do{
                                    cout<<"Donner le prix de l'action à rechercher dans la bourse"<<endl;
                                    cin>>p;
                                }while(p<=0);
                                cout<<"les prix jouranliers disponible aujourdhui par votre prix "<< p<<endl;
                                for(auto pj:b.getPrixJournalierTodayParPrix(p)){
                                cout<<pj<<endl;
                               }
                              break;

                             }
                             case 3:{
                                   Date dateActuelle;
                                      do{

                                        cout<<"Donner la date de debut de simulation"<<endl;
                                        cin>>dateActuelle;
                                    }while(! dateActuelle.Est_valide());
                                    BourseMultiMap b(dateActuelle,historique);
                                    double p;
                                    do{
                                            cout<<"Donner le prix de l'action à rechercher dans la bourse"<<endl;
                                            cin>>p;
                                    }while(p<=0);
                                    cout<<"les prix jouranliers disponible aujourdhui par votre prix "<< p<<endl;
                                    for(auto pj:b.getPrixJournalierTodayParPrix(p)){
                                            cout<<pj<<endl;
                                    }
                                    break;
                          }
                     }
                     break;
                }
                 case 4:{
                            int i=0;
                            do{
                                    cout<<"***sélectionner le type de bourse pour la recherche            ***"<<endl;
                                    cout<<"*     1) Bourse Set                                              *"<<endl;
                                    cout<<"*     2) Bourse Vector                                           *"<<endl;
                                    cout<<"*     3) Bourse multimap                                         *"<<endl;
                                    cout<<"******************************************************************"<<endl;
                            }while(i<0 || i>3);
                            switch(i){
                            case 1:{
                                    Date dateActuelle;
                                    do{

                                      cout<<"Donner la date de debut de simulation"<<endl;
                                      cin>>dateActuelle;
                                    }while(! dateActuelle.Est_valide());
                                    BourseSet b(dateActuelle,historique);
                                    string nomAction;
                                    cout<<"taper le nom d'action"<<endl;
                                    cin>>nomAction;

                                    float p=b.getLeDernierePrix(nomAction);
                                    if(p==0){
                                            cout<<"cette action n'existe pas dans la bourse"<<endl;
                                    }
                                    else{
                                        cout<<"Le Dernier Prix de  "<<nomAction<<"\t"<<p<<endl;
                                     }
                                break;
                             }
                            case 2:{
                                       Date dateActuelle;
                                       do{

                                           cout<<"Donner la date de debut de simulation"<<endl;
                                          cin>>dateActuelle;
                                        }while(! dateActuelle.Est_valide());
                                        BourseVector b(dateActuelle,historique);
                                        string nomAction;
                                        cout<<"taper le nom d'action"<<endl;
                                        cin>>nomAction;

                                        float p=b.getLeDernierePrix(nomAction);
                                        if(p==0){
                                            cout<<"cette action n'existe pas dans la bourse"<<endl;
                                         }
                                        else{
                                            cout<<"Le Dernier Prix de  "<<nomAction<<"\t"<<p<<endl;
                                         }
                                         break;
                            }
                            case 3:{
                                       Date dateActuelle;
                                       do{

                                           cout<<"Donner la date de debut de simulation"<<endl;
                                           cin>>dateActuelle;
                                        }while(! dateActuelle.Est_valide());
                                        BourseVector b(dateActuelle,historique);
                                        string nomAction;
                                        cout<<"taper le nom d'action"<<endl;
                                        cin>>nomAction;

                                        float p=b.getLeDernierePrix(nomAction);
                                        if(p==0){
                                            cout<<"cette action n'existe pas dans la bourse"<<endl;
                                        }
                                        else{
                                            cout<<"Le Dernier Prix de  "<<nomAction<<"\t"<<p<<endl;
                                        }
                                        break;
                        }
                        break;
                        }
                 }



                       case 5:{
                           exit(0);

                            break;
                        }
                      default:{
                              cout<<"choix invalide"<<endl;
                              break;
                      }

    }}
      return 0;
}

