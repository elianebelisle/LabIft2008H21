/**
 * \file Graphe.h
 * \brief Classe définissant le type abstrait Graphe.
 * \author Jean-Francis Roy
 * \version 0.1
 * \date Août 2016
 *
 * Définition de la classe Graphe et de ses fonctions membres.
 * Implémentation dans des listes d'adjacence.
 */

#ifndef _GRAPHE_H
#define _GRAPHE_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <list>
#include <queue>
#include <stack>

namespace labGrapheAlgorithmes {
/**
 * \class Graphe
 *
 * \brief Classe générique représentant un graphe
 *
 *  La classe gère un graphe générique. L'implémentation
 *  se fait par des listes d'adjacence. Les numéros de
 *  sommets débutent à 0. Le type T correspond aux noms
 *  des sommets, qui peuvent être optionnellement intégrés.
 *
 */
template<typename T>
class Graphe {
public:
	Graphe(size_t = 10);
	~Graphe();

	void nommer(unsigned int, const T &);
	void ajouterArc(unsigned int, unsigned int);
	void enleverArc(unsigned int, unsigned int);

	T reqNom(unsigned int) const;
	bool arcExiste(unsigned int, unsigned int) const;
	size_t reqNbSommets() const;

	void affiche() const;
	std::vector<unsigned int> listerSommetsAdjacents(unsigned int) const;

	unsigned int ordreEntreeSommet(unsigned int) const;
	unsigned int ordreSortieSommet(unsigned int) const;

	// Fonctions supplémentaires du laboratoire GrapheAlgorithmes
	std::vector<unsigned int> parcoursProfondeur(unsigned int) const;
	std::vector<unsigned int> parcoursLargeur(unsigned int) const;
	bool estConnexe() const;
	std::vector<unsigned int> triTopologique() const;

private:

	size_t m_nbSommets; /*!< le nombre de sommets */
	std::vector<T> m_noms; /*!< les noms des sommets */

	// Chaque sommet a sa liste d'adjacences, dont les valeurs correspondent au numéro
	// du sommet pointé par l'arc.
	std::vector<std::list<unsigned int> > m_listesAdj; /*!< les listes d'adjacence */

	// Méthodes privées
	void verifieInvariant() const;
    bool canVisitEveryNeighbors() const;
    Graphe <T> createNonOrientedGraph() const;
    std::vector<unsigned int> getInputOrderForAllVertex() const;

    std::queue<unsigned int> getSources(std::vector<unsigned int> inputOrders) const;

    template<typename C>
    std::vector<unsigned int> getPath(unsigned int debut, C &) const;
    unsigned int getNextElement(const std::queue<unsigned int> &queue) const;
    unsigned int getNextElement(const std::stack<unsigned int> &stack) const;
    template<typename C>
    void addUnmarkedNeighborToContainer(C &container, std::vector<bool> &marks, T elementToTreat) const;
    template<typename C>
    void treatNextElement(C &container, std::vector<bool> &marks, std::vector<unsigned int> &inDepthPath) const;
};

} //Fin du namespace

#include "Graphe.hpp"

#endif
