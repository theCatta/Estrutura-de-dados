#include <iostream>
using namespace std;

#define MAX 5

struct No
{
	float dado;
	No *prox;
};

struct PilhaGrupo{
	No *topo;
};

struct Pilha{
	No *topo;
	int qtd;
	PilhaGrupo *pilhaPar;
	PilhaGrupo *pilhaImpar;
	float elementos[MAX];
};

Pilha* init(PilhaGrupo *pp, PilhaGrupo *pi){
	Pilha *p = new Pilha;
	p->qtd = 0;
	p->topo = NULL;
	p->pilhaPar = pp;
	p->pilhaImpar = pi; 
	return p;
}

PilhaGrupo* innit(){
	PilhaGrupo *p = new PilhaGrupo;
	p->topo = NULL;
	
	return p;
}

int push(Pilha *p, float v){
	int podeEmpilhar = (p->qtd < MAX);
	if(podeEmpilhar){
		int numPar = ((int)v % 2 == 0);
		if(numPar){
			No *no = new No;
			no->dado = v;
			no->prox = p->pilhaPar->topo;
			p->pilhaPar->topo = no;
			p->qtd++;
			
			//p->pilhaPar->elementos[p->qtd++] = v;
		} else {
			No *no = new No;
			no->dado = v;
			no->prox = p->pilhaImpar->topo;
			p->pilhaImpar->topo = no;
			p->qtd++;
		}
	}
	
	return podeEmpilhar;
}

int isEmpty(Pilha *p){
	return (p->qtd == 0);
}

int count(Pilha *p){
	int k = 0;
	No *noPar, *noImpar;
	noPar = p->pilhaPar->topo;
	noImpar = p->pilhaImpar->topo;
	while(noPar != NULL){
		k++;
		noPar = noPar->prox;
	}
	
	while(noImpar != NULL){
		k++;
		noImpar = noImpar->prox;
	}
	
	return k;
}

float pop(Pilha *p){
	float ret;
	int podeDesempilhar = (count(p) != 0);
	if(podeDesempilhar){
		if(p->pilhaPar->topo > p->pilhaImpar->topo){
			No *no = p->pilhaPar->topo;
			ret = no->dado;
			p->pilhaPar->topo = p->pilhaPar->topo->prox;
			free(no);
		} else{
			No *no = p->pilhaImpar->topo;
			ret = no->dado;
			p->pilhaImpar->topo = p->pilhaImpar->topo->prox;
			free(no);
		}
	} else {
		ret = NULL;
	} 
	
	return ret;
}


int main(int argc, char** argv)
{
	PilhaGrupo *pilhaPar;
	pilhaPar = innit();
	PilhaGrupo *pilhaimpar;
	pilhaimpar = innit();
	Pilha *pilhaFloat;
	pilhaFloat = init(pilhaPar, pilhaimpar);
	
	int i = 0;
	int numAnterior, num;
	
	while(i < MAX){
		cin >> num;
		
		if(i == 0){
			push(pilhaFloat, num);
			numAnterior = num;
			i++;
		} else if(num > numAnterior){
			push(pilhaFloat, num);
			numAnterior = num;
			i++;
		} else {
			cout << "Menor que número anterior" << endl;
		}
	}
	
	pop(pilhaFloat);
	
	
	cout << "Vazio? " <<(isEmpty(pilhaFloat)? "sim" : "nao" << endl);
	cout << "Count: " << count(pilhaFloat);
	
	return 0;
}