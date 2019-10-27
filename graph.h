#ifndef GRAPH_H
#define GRAPH_H
#include <list>
#include <vector>
#include <algorithm>

using namespace std;
template<class G>
class CNode
{
	public:
    typedef class G::Edge Edge;//typename because is a dependent scope
	typedef typename G::n_ N;
	//typedef class G::Node N;
	N value;
	list<Edge*> EdgeNod;
	
	CNode(N date){
		this->value=date;
	}
	
	void RemEdgeN(CNode <G> *tmp){
		//lista de aristas del nodo inicio
        for (typename list<Edge*>::iterator it= EdgeNod.begin(); it != EdgeNod.end(); it++){
			//lista de aristas del nodo fin
			for (typename list<Edge*>::iterator itt= tmp->EdgeNod.begin(); itt != tmp->EdgeNod.end(); itt++){	
				if(*it == *itt){
					 EdgeNod.remove(*it);
					 tmp->EdgeNod.remove(*itt);
					 
					 delete *it;
					return;
				}
			}	
		}
    }
	
	void RemEdges(){
        Edge *tmp;
        while(!EdgeNod.empty()){
            tmp = EdgeNod.front();
            ((tmp->enodo[0])->EdgeNod).remove(tmp);
            ((tmp->enodo[1])->EdgeNod).remove(tmp);
            delete tmp;
        }
    }
    
    double b(){
        double tmp_b, b_edge;
        b_edge = EdgeNod[0]->value;
        for(typename list<Edge*>::iterator it=EdgeNod.begin(); it!=EdgeNod.end(); ++it) {
            tmp_b = (*it)->value;
            b_edge = min(b_edge, tmp_b);
        }
        return b_edge;
    }
	~CNode(){};
};

template<class G>
class CEdge
{
	public:
	typedef typename G::Node Node;
	typedef typename G::e_ E;
	//typedef typename G::Edge E;
	E value;
	Node *enodo[2]; //Node extremos
	bool mdir; //0[bidireccional] 1[unidireccional]
	CEdge(E date, bool dir){
		this->value=date;
		this->mdir=dir;
		enodo[0]=enodo[1]=nullptr;
	}
	~CEdge(){};
};

//template<class T, class C>
template<class N, class E>
class CGraph
{
	public:
	typedef CGraph<N,E>  self;
	typedef CNode<self>  Node;
	typedef CEdge<self>  Edge;
	typedef N n_;
	typedef E e_;
	vector<Node*> mnodes;
	
	bool findN(N, unsigned&);
	bool InsNode(N);
	bool InsEdge(Node *&,Node *&,E ,bool);
	bool RemNode(N);
	bool RemEdge(N, N);
	void printGraph();
	virtual ~CGraph(){ 
        unsigned int t = mnodes.size(), i;
        for(i=0; i<t; i++)  delete mnodes[i];
    }
};

template<class N, class E>
//para no repetir código
bool CGraph<N,E>::findN(N d, unsigned &id){
	for(id=0;id < mnodes.size();id++){
		if(mnodes[id]->value==d)  return 1;
	}			
	return 0;
}
	
template<class N, class E>	
bool CGraph<N,E>::InsNode(N date){
	Node* new_node= new Node(date);
	mnodes.push_back(new_node);
	//prob necesitamos ya ir calculando cant de node?
	return 1;	
}

template<class N, class E>
bool CGraph<N,E>::InsEdge(Node *&a, Node *&b, E dato, bool dir){			
	Edge* new_edge= new Edge(dato,dir);
	a->EdgeNod.push_back(new_edge);
	b->EdgeNod.push_back(new_edge);
	new_edge->enodo[0]= a; 	new_edge->enodo[1]= b;
	//prob necesitamos ya ir calculando cant de edges
	return 1;
}

template<class N, class E>
bool CGraph<N,E>::RemEdge(N a, N b){
		unsigned ia, ib;
		if(!(findN(a,ia) and findN(b,ib))) {cout<<"no hay nodos[extremos]"<<endl; return 0;}
		mnodes[ia]->RemEdgeN(mnodes[ib]);
		return 1;
}

template<class N, class E>	
bool CGraph<N,E>::RemNode(N date){
	unsigned idate;
	if(!findN(date,idate)) return 0;
		
	mnodes[idate]->RemEdges();
	delete mnodes[idate];
	mnodes->erase(mnodes.begin()+idate);
	//mnodes.erase(mnodes.begin()+idate);
	return 1;
}

template<class N, class E>	
void CGraph<N,E>::printGraph(){
	for(int i=0; i<mnodes.size(); i++) {//ingreso al vector de nodos del grafo
		Node *temp_node = mnodes[i]; // cada nodo
		cout<<temp_node->value;// etiqueta-valor de cada nodo

		for (typename list<Edge*>::iterator it= temp_node->EdgeNod.begin(); it != temp_node->EdgeNod.end(); ++it){
	     	//recorrer la lista de punteros a aristas del nodo
			if(temp_node->value != (*it)->enodo[1]->value){
				cout<<" ---> "<< (*it)->value<<"("<<((*it)->enodo[1])->value<<")";
				cout<<endl;
			}
		}
		cout<<"\n";
	}
}

#endif //GRAPH_H
