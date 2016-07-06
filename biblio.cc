#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*******************************************
 * Completez le programme a partir d'ici.
 *******************************************/
class Auteur
{
	private:
		string Name;
		bool Prix;
	public:
		Auteur(string name, bool hasPrix = false):Name(name), Prix(hasPrix)
		{}
		string getNom()const {return Name;}
		bool getPrix()const {return Prix;}
};

class Oeuvre
{
	private:
		string titre;
		Auteur& author;
		string langue;
	public:
		Oeuvre(string title, Auteur& writer, string language)
			:titre(title), author(writer), langue(language)
			{}
		string getTitre()const {return titre;}
		string getLangue()const {return langue;}
		Auteur const& getAuteur()const {return author;}
		Oeuvre(Oeuvre const& other) = delete;
		void affiche()const
		{
			cout << titre << ", " << author.getNom() << ", en " << langue << endl;
		}
		~Oeuvre()
		{
			cout << "L'oeuvre \"" << titre << ", " << author.getNom() << ", en " << langue << "\" n'est plus disponible." << endl;
		}
};

class Exemplaire
{
	private:
		Oeuvre& copie;
	public:
		Exemplaire(Oeuvre& book):copie(book)
		{	
			cout << "Nouvel exemplaire de : " << copie.getTitre() << ", "<< copie.getAuteur().getNom() << ", en " << copie.getLangue() << endl;
		}
		Oeuvre& getOeuvre()const{return copie;}
		
		Exemplaire(Exemplaire const& other):copie(other.getOeuvre())
		{
			cout << "Copie d'un exemplaire de : " << copie.getTitre() <<", "<<copie.getAuteur().getNom() <<", en "<<copie.getLangue()<<endl;
		}
		
		void affiche()const
		{
			cout << "Exemplaire de : "<< copie.getTitre() << ", "<< copie.getAuteur().getNom() << ", en " << copie.getLangue();
		}
		
		~Exemplaire()
		{
			cout << "Un exemplaire de \""<< copie.getTitre() << ", "<< copie.getAuteur().getNom() << ", en " << copie.getLangue()<< "\" a été jeté !"<<endl;
		}
};

class Bibliotheque 
{
	private:
		string Nom;
		vector<Exemplaire *> Books;
		
	public:
		Bibliotheque(string name):Nom(name)
		{
			cout<< "La bibliothèque "<<Nom<<" est ouverte !"<<endl;
		}
		
		string getNom()const {return Nom;}
		
		void stocker( Oeuvre& work, int NumCopy = 1)
		{
			for( int count = 0; count < NumCopy; count++)
			{
				Books.push_back(new Exemplaire(work));
			}
		}
		
		void lister_exemplaires( string language = "")
		{
			if (language == "")
			{
				 for(vector<Exemplaire*>::iterator it = Books.begin() ; it != Books.end(); ++it)
				 {
					  (**it).affiche();
					  cout<<endl;
				 }
			}else
			{
				 for(vector<Exemplaire*>::iterator it = Books.begin() ; it != Books.end(); ++it)
				 {
					  if ( (**it).getOeuvre().getLangue() == language )
					  {
						  (**it).affiche();
						  cout<<endl;
					  }
				 }				
			}
		}
		
		int compter_exemplaires(Oeuvre const& sample)
		{
			int counter = 0;
			for(vector<Exemplaire*>::iterator it = Books.begin() ; it != Books.end(); ++it)
			{
			  if ( ( (**it).getOeuvre().getTitre() == sample.getTitre() )
				and ((**it).getOeuvre().getLangue() == sample.getLangue())
				and  (**it).getOeuvre().getAuteur().getNom() == sample.getAuteur().getNom() )
			  {
				counter++;
			  }
			}
			return counter;			
		}
		
		void afficher_auteurs( bool hasPrix = false)const
		{	
			if (hasPrix)
			{
				for(vector<Exemplaire*>::const_iterator it = Books.begin() ; it != Books.end(); ++it)
				{
					if ( (**it).getOeuvre().getAuteur().getPrix() )
					{
						cout<<(**it).getOeuvre().getAuteur().getNom()<<endl;
					}
				}	
			}
			else
			{		
				for(vector<Exemplaire*>::const_iterator it = Books.begin() ; it != Books.end(); ++it)
				{
					cout<<(**it).getOeuvre().getAuteur().getNom()<<endl;
				}
			}			
		}
		
		~Bibliotheque()
		{
			cout << "La bibliothèque "<< Nom << " ferme ses portes," <<endl;
			cout << "et détruit ses exemplaires :"<<endl;
			
			for(vector<Exemplaire*>::const_iterator it = Books.begin() ; it != Books.end(); ++it)
			{
				delete *it;
			}
		}
		
};

/*******************************************
 * Ne rien modifier apres cette ligne.
 *******************************************/

int main()
{
  Auteur a1("Victor Hugo"),
         a2("Alexandre Dumas"),
         a3("Raymond Queneau", true);

  Oeuvre o1("Les Misérables"           , a1, "français" ),
         o2("L'Homme qui rit"          , a1, "français" ),
         o3("Le Comte de Monte-Cristo" , a2, "français" ),
         o4("Zazie dans le métro"      , a3, "français" ),
         o5("The Count of Monte-Cristo", a2, "anglais" );

  Bibliotheque biblio("municipale");
  biblio.stocker(o1, 2);
  biblio.stocker(o2);
  biblio.stocker(o3, 3);
  biblio.stocker(o4);
  biblio.stocker(o5);

  cout << "La bibliothèque " << biblio.getNom()
       << " offre les exemplaires suivants :" << endl;
  biblio.lister_exemplaires();

  const string langue("anglais");
  cout << " Les exemplaires en "<< langue << " sont :" << endl;
  biblio.lister_exemplaires(langue);

  cout << " Les auteurs à succès sont :" << endl;
  biblio.afficher_auteurs(true);

  cout << " Il y a " << biblio.compter_exemplaires(o3) << " exemplaires de "
       << o3.getTitre() << endl;

  return 0;
}
