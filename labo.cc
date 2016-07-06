#include <iostream>
using namespace std;

class Souris
{
  /*****************************************************
    Compléter le code à partir d'ici
  *******************************************************/
	private:
		double poids;
		string couleur;
		int age;
		int esperance_vie;
		bool clonee; 
	public:
		Souris(double weight, string color, int months = 0, int lifeExpectancy = 36, bool isCloned = false):
			poids(weight), couleur(color), age(months), esperance_vie(lifeExpectancy), clonee(isCloned)
		{
			cout << "Une nouvelle souris !"<<endl;
		}
		Souris(Souris const& other):poids(other.poids), couleur(other.couleur),age(other.age)
		{
			esperance_vie = other.esperance_vie*4/5;
			clonee = true;
			cout << "Clonage d'une souris !" <<endl;
		}
		~Souris()
		{
			cout << "Fin d'une souris..." <<endl;
		}
		void afficher()const
		{
			if (clonee)
			{
				cout << "Une souris " << couleur << ", clonee, de " << age << " mois et pesant "<< poids << " grammes" << endl;
			}
			else
			{
				cout << "Une souris " << couleur << " de " << age << " mois et pesant "<< poids << " grammes" << endl;
			}
		}
		void vieillir()
		{
			++age;
			if ((clonee) and (age > (esperance_vie/2)))
			{
				couleur = "verte";
			}
		}
		void evolue()
		{
			while(age < esperance_vie)
			{
				vieillir();
			}
		}	
  /*******************************************
   * Ne rien modifier après cette ligne.
   *******************************************/

}; // fin de la classe Souris

int main()
{
  Souris s1(50.0, "blanche", 2);
  Souris s2(45.0, "grise");
  Souris s3(s2);
  // ... un tableau peut-être...
  s1.afficher();
  s2.afficher();
  s3.afficher();
  s1.evolue();
  s2.evolue();
  s3.evolue();
  s1.afficher();
  s2.afficher();
  s3.afficher();
  return 0;
}
