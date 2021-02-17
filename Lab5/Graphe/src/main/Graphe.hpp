#include <iostream>
#include <algorithm>
#include "ContratException.h"


namespace labGrapheAlgorithmes {


/**
 * \brief Constructeur du graphe
 * \param[in] le nombre de sommets à initialiser dans le graphe
 */
template <typename T>
Graphe<T>::Graphe(size_t p_nbSommets) : m_nbSommets(p_nbSommets) {
	m_noms.resize(m_nbSommets);
	m_listesAdj.resize(m_nbSommets);
}

/**
 * \brief Destructeur du graphe
 *
 * Aucune mémoire à libérer manuellement: tous les attributs de la classe ont un type
 * qui gère sa propre mémoire. C'est pour cette raison que nous n'avons pas besoin non
 * plus de constructeur de copie ou de surcharge de l'opérateur =.
 */
template <typename T>
Graphe<T>::~Graphe() {
}


/**
 * \brief Attribue une étiquette à un sommet
 *
 * Appose un nom au sommet dont le numéro est reçu en paramètre. Le type de ce nom
 * est générique.
 *
 * \param[in] p_sommet Le numéro du sommet à nommer
 * \param[in] p_nom Le nom à attribuer
 * \pre Le numéro correspond à un sommet valide
 * \post Le sommet est maintenant nommé à l'aide du nom reçu
 *
 */
template <typename T>
void Graphe<T>::nommer(unsigned int p_sommet, const T & p_nom) {
	PRECONDITION(p_sommet < m_nbSommets);

	// On valide la position du sommet.
	if (p_sommet >= m_nbSommets) {
		throw std::logic_error("nommer: numéro de sommet invalide.");
	}

	m_noms[p_sommet] = p_nom;
	INVARIANTS();
}


/**
 * \brief Ajoute un arc entre deux sommets
 *
 * Ajoute un arc entre les deux sommets reçus en paramètre.
 *
 * \param[in] p_source Le numéro du sommet source de l'arc
 * \param[in] p_cible Le numéro du sommet cible de l'arc
 * \pre Le numéro du sommet source correspond à un sommet valide
 * \pre Le numéro du sommet cible correspond à un sommet valide
 * \pre Il n'y a pas déjà d'arc du sommet source vers le sommet cible
 * \post Il y a maintenant un arc du sommet source vers le sommet cible
 *
 */
template <typename T>
void Graphe<T>::ajouterArc(unsigned int p_source, unsigned int p_cible) {
	PRECONDITION(p_source < m_nbSommets);
	PRECONDITION(p_cible < m_nbSommets);
	PRECONDITION(!arcExiste(p_source, p_cible));

	// On valide la position du sommet source.
	if (p_source >= m_nbSommets) {
		throw std::logic_error("nommer: numéro de sommet source invalide.");
	}

	// On valide la position du sommet cible.
	if (p_cible >= m_nbSommets) {
		throw std::logic_error("nommer: numéro de sommet cible invalide.");
	}

	// On valide que l'arc n'existe pas déjà.
	if (arcExiste(p_source, p_cible)) {
		throw std::logic_error("ajouterArc: l'arc existe déjà");
	}

	// On ajoute un nouvel arc à la liste d'adjacence correspondant au sommet source.
	// Notons que la position de l'ajout n'a pas d'importance: il n'y a pas de notion
	// d'ordre au niveau des arcs sortants d'un sommet.
	m_listesAdj[p_source].push_back(p_cible);

	POSTCONDITION(arcExiste(p_source, p_cible));
	INVARIANTS();
}


/**
 * \brief Retire un arc entre deux sommets
 *
 * Retire l'arc entre les deux sommets reçus en paramètre.
 *
 * \param[in] p_source Le numéro du sommet source de l'arc
 * \param[in] p_cible Le numéro du sommet cible de l'arc
 * \pre Le numéro du sommet source correspond à un sommet valide
 * \pre Le numéro du sommet cible correspond à un sommet valide
 * \pre Il existe un arc du sommet source vers le sommet cible
 * \post Il n'y a plus d'arc du sommet source vers le sommet cible
 *
 */
template <typename T>
void Graphe<T>::enleverArc(unsigned int p_source, unsigned int p_cible) {
	PRECONDITION(arcExiste(p_source, p_cible));

	// On recherche l'arc dans la liste d'adjacence du sommet source.
	std::list<unsigned int> & liste = m_listesAdj[p_source];
	std::list<unsigned int>::iterator it = std::find(liste.begin(), liste.end(), p_cible);

	// Si la recherche a échoué, l'itérateur résultant pointera vers la fin de la liste.
	if (it == liste.end()) {
		throw std::logic_error("enlever: l'arc est inexistant");
	}

	liste.erase(it);

	POSTCONDITION(!arcExiste(p_source, p_cible));
	INVARIANTS();
}


/**
 * \brief Obtient le nom d'un sommet
 *
 * Retourne le nom (de type générique) du sommet dont le numéro est reçu
 * en paramètre.
 *
 * \param[in] p_sommet Le numéro du sommet
 * \return Le nom du sommet
 * \pre Le numéro du sommet correspond à un sommet valide
 * \post Le graphe est inchangé
 *
 */
template <typename T>
T Graphe<T>::reqNom(unsigned int p_sommet) const {
	PRECONDITION(p_sommet < m_nbSommets);

	// On valide la position du sommet.
	if (p_sommet >= m_nbSommets) {
		throw std::logic_error("reqNom: numéro de sommet invalide.");
	}

	return m_noms[p_sommet];
}


/**
 * \brief Vérifie s'il y a un arc entre deux sommets
 *
 * \param[in] p_source Le numéro du sommet source de l'arc
 * \param[in] p_cible Le numéro du sommet cible de l'arc
 * \return true s'il y a un arc du sommet source vers le sommet cible, et false autrement
 * \pre Le numéro du sommet source correspond à un sommet valide
 * \pre Le numéro du sommet cible correspond à un sommet valide
 * \post Le graphe est inchangé
 *
 */
template <typename T>
bool Graphe<T>::arcExiste(unsigned int p_source, unsigned int p_cible) const {
	PRECONDITION(p_source < m_nbSommets);
	PRECONDITION(p_cible < m_nbSommets);

	// On valide la position du sommet source.
	if (p_source >= m_nbSommets) {
		throw std::logic_error("arcExiste: numéro de sommet source invalide.");
	}

	// On valide la position du sommet cible.
	if (p_cible >= m_nbSommets) {
		throw std::logic_error("arcExiste: numéro de sommet cible invalide.");
	}

	// On recherche l'arc dans la liste d'adjacence du sommet source.
	std::list<unsigned int> liste = m_listesAdj[p_source];
	std::list<unsigned int>::iterator it = std::find(liste.begin(), liste.end(), p_cible);

	// Si la recherche a échoué, l'itérateur résultant pointera vers la fin de la liste.
	return it != liste.end();
}


/**
 * \brief Obtient le nombre de sommets dans le graphe
 *
 * \return Le nombre de sommets dans le graphe
 * \post Le graphe est inchangé
 *
 */
template <typename T>
size_t Graphe<T>::reqNbSommets() const {
	return m_nbSommets;
}


/**
 * \brief Affiche le contenu du graphe
 *
 * \post Le graphe est inchangé
 *
 */
template <typename T>
void Graphe<T>::affiche() const {

	for (unsigned int i = 0; i < m_nbSommets; ++i) {
		std::cout << "Sommet " << i << ": ";

		for (std::list<unsigned int>::const_iterator it = m_listesAdj[i].begin(); it != m_listesAdj[i].end(); ++it) {
			std::cout << i << "->" << *it << ", ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

}


/**
 * \brief Liste les sommets adjacents à un sommet dans le graphe
 *
 * Retourne un vecteur de numéros de sommets qui sont reliés par un arc au sommet reçu en argument.
 *
 * \param[in] p_sommet Le numéro du sommet
 * \return Un vecteur contenant les numéros des sommets adjacents
 * \pre Le numéro du sommet correspond à un sommet valide
 * \post Le graphe est inchangé
 *
 */
template <typename T>
std::vector<unsigned int> Graphe<T>::listerSommetsAdjacents(unsigned int p_sommet) const {
	PRECONDITION(p_sommet < m_nbSommets);

	// On valide la position du sommet.
	if (p_sommet >= m_nbSommets) {
		throw std::logic_error("listerSommetsAdjacents: numéro de sommet invalide.");
	}

	// On parcourt la liste de sommets adjacents et on les ajoute dans un vecteur, qu'on retourne.
	std::vector<unsigned int> v;
	for (std::list<unsigned int>::const_iterator it = m_listesAdj[p_sommet].begin(); it != m_listesAdj[p_sommet].end(); ++it) {
		v.push_back(*it);
	}

	return v;
}


/**
 * \brief Retourne l'ordre d'entrée d'un sommet
 *
 * Retourne le nombre d'arcs entrants dans le sommet reçu en argument.
 *
 * \param[in] p_sommet Le numéro du sommet
 * \return L'ordre d'entrée du sommet
 * \pre Le numéro du sommet correspond à un sommet valide
 * \post Le graphe est inchangé
 *
 */
template <typename T>
unsigned int Graphe<T>::ordreEntreeSommet(unsigned int p_sommet) const {
	PRECONDITION(p_sommet < m_nbSommets);

	// On valide la position du sommet.
	if (p_sommet >= m_nbSommets) {
		throw std::logic_error("listerSommetsAdjacents: numéro de sommet invalide.");
	}

	// On parcourt tous les arcs et on compte les arcs entrants.
	unsigned int cpt = 0;

	for (unsigned int i = 0; i < m_nbSommets; ++i) {
		for (std::list<unsigned int>::const_iterator it = m_listesAdj[i].begin(); it != m_listesAdj[i].end(); ++it) {
			if (*it == p_sommet) {
				cpt++;
			}
		}
	}

	return cpt;
}


/**
 * \brief Retourne l'ordre de sortie d'un sommet
 *
 * Retourne le nombre d'arcs sortants du sommet reçu en argument.
 *
 * \param[in] p_sommet Le numéro du sommet
 * \return L'ordre de sortie du sommet
 * \pre Le numéro du sommet correspond à un sommet valide
 * \post Le graphe est inchangé
 *
 */
template <typename T>
unsigned int Graphe<T>::ordreSortieSommet(unsigned int p_sommet) const {
	PRECONDITION(p_sommet < m_nbSommets);

	// On valide la position du sommet.
	if (p_sommet >= m_nbSommets) {
		throw std::logic_error("listerSommetsAdjacents: numéro de sommet invalide.");
	}

	// On retourne le nombre d'arcs sortants du sommet.
	return m_listesAdj[p_sommet].size();
}


template <typename T>
void Graphe<T>::verifieInvariant() const {
	INVARIANT(m_noms.size() == m_nbSommets);
	INVARIANT(m_listesAdj.size() == m_nbSommets);
}

// Algorithmes

/**
 * \brief Effectue un parcours en profondeur du graphe
 *
 * Retourne le résultat du parcours en profondeur du graphe. Dans notre solution,
 * pour éviter de dupliquer du code, nous utilisons des fonctions utilitaires pour
 * utiliser la même fonction générique de parcours acceptant les deux types de conteneurs
 * (pile ou file) nécessaires. Notez que vous pouviez dupliquer le code dans votre solution,
 * car la nôtre est moins évidente à imaginer et implémenter.
 *
 * \param[in] p_debut Le numéro du sommet de départ
 * \return Le vecteur contenant le résultat du parcours
 * \pre Le numéro du sommet correspond à un sommet valide
 * \post Le graphe est inchangé
 *
 */
template <typename T>
std::vector<unsigned int> Graphe<T>::parcoursProfondeur(unsigned int p_debut) const {
}

/**
 * \brief Effectue un parcours en largeur du graphe
 *
 * Retourne le résultat du parcours en largeur du graphe. Dans notre solution,
 * pour éviter de dupliquer du code, nous utilisons des fonctions utilitaires pour
 * utiliser la même fonction générique de parcours acceptant les deux types de conteneurs
 * (pile ou file) nécessaires. Notez que vous pouviez dupliquer le code dans votre solution,
 * car la nôtre est moins évidente à imaginer et implémenter.
 *
 * \param[in] p_debut Le numéro du sommet de départ
 * \return Le vecteur contenant le résultat du parcours
 * \pre Le numéro du sommet correspond à un sommet valide
 * \post Le graphe est inchangé
 *
 */
template <typename T>
std::vector<unsigned int> Graphe<T>::parcoursLargeur(unsigned int p_debut) const {
}

template <typename T>
bool Graphe<T>::estConnexe() const {
}

template <typename T>
std::vector<unsigned int> Graphe<T>::triTopologique() const {
}

} //Fin du namespace
