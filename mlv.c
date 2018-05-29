#include <MLV/MLV_all.h>
#include <time.h>
#include <stdio.h>

int Passage[30][30];

// On défini un nouveau type qu'on nomme "Coordonnees" qui permet de définir des coordonnées 
typedef  struct{
	int x; // Coorodonée de l'axe des abscisses
	int y; // Coorodonée de l'axe des ordonnéees
} Coordonnees;

// Cette fonction permet d'ouvrir une fenêtre et d'afficher un cadrillage sur celle-ci
// Elle prend comme argument le nombre de carré à dessiner (Nb) et leur dimmension en pixel (dim)
void AffCadrillage(int dim, int Nb){
	
	MLV_create_window( "beginner - 2 - shapes", "shapes", (dim+1)*Nb, (dim+1)*Nb); // Ouvre une fenêtre de dimension (dim+1)*Nb
	/*int i; //On utilisera "i" pour se déplacer dans le fenêtre
	
	// On parcours la fenêtre en incrémentant "i" de la dimension d'une case 
	//(+1 car on ne compte pas les lignes dans la dimension de la case) jusqu'au bord de la fenêtre
	for(i=0; i<((dim+1)*Nb); i=i+dim+1){ 
		MLV_draw_line(0, i, (dim+1)*Nb, i, MLV_COLOR_BLUE ); // On dessine une ligne verticale d'ordonnées i
		MLV_draw_line(i, 0, i, (dim+1)*Nb, MLV_COLOR_BLUE ); // On dessine une ligne horizontale d'abscisse i
	}*/
	MLV_actualise_window(); // On actualise la fenêtre
}

void RectangleBlanc(Coordonnees point, int dim){
	int i=0, j=0;
	i = point.x/dim * (dim+1) +1;
	j = point.y/dim * (dim+1) +1;
	MLV_draw_filled_rectangle(i, j, dim, dim, MLV_COLOR_WHITE);
	MLV_actualise_window(); // On actualise la fenêtre
}

void RectangleRouge(Coordonnees point, int dim){
	int i=0, j=0;
	i = point.x/dim * (dim+1) +1;
	j = point.y/dim * (dim+1) +1;
	MLV_draw_filled_rectangle(i, j, dim, dim, MLV_COLOR_RED);
	MLV_actualise_window(); // On actualise la fenêtre
	MLV_wait_milliseconds(50); // On attend 300 milliseconde
}

void RectangleVert(Coordonnees point, int dim){
	int i=0, j=0;
	i = point.x/dim * (dim+1) +1;
	j = point.y/dim * (dim+1) +1;
	MLV_draw_filled_rectangle(i, j, dim, dim, MLV_COLOR_GREEN);
	MLV_actualise_window(); // On actualise la fenêtre
	MLV_wait_milliseconds(0); // On attend 300 milliseconde
}

void RectangleRose(Coordonnees point, int dim){
	int i=0, j=0;
	i = point.x/dim * (dim+1) +1;
	j = point.y/dim * (dim+1) +1;
	MLV_draw_filled_rectangle(i, j, dim, dim, MLV_COLOR_PINK);
	MLV_actualise_window(); // On actualise la fenêtre
}

void EffMur(int d, Coordonnees point, int dim){
	int i, j;
	i = point.x/dim * (dim+1) +1;
	j = point.y/dim * (dim+1) +1;
	
	// Haut
	if(d == 3){
		MLV_draw_line(i,j-1,i+dim-1,j-1, MLV_COLOR_WHITE);
	}
	// Bas
	else if(d == 2){
		MLV_draw_line(i,j+dim,i+dim-1,j+dim, MLV_COLOR_WHITE);
	}
	// Gauche
	else if(d == 1) {
		MLV_draw_line(i-1,j,i-1,j+dim-1, MLV_COLOR_WHITE);
	}
	// Droite
	else if(d == 0) {
		MLV_draw_line(i+dim,j,i+dim,j+dim-1, MLV_COLOR_WHITE);
	}
}

int VerifCase(int Direction[], int Nb, int i, int j){
	int h = 0, a = 0;
	
	//Droite
	if(i == (Nb-1)) Direction[0] = 0;
	else{
		if(Passage[i+1][j]) Direction[0] = 0;
		else Direction[0] = 1;
	}
	
	//Gauche
	if(i == 0) Direction[1] = 0;
	else{
		if(Passage[i-1][j]) Direction[1] = 0;
		else Direction[1] = 1;
	}
	
	//Bas
	if(j == (Nb-1)) Direction[2] = 0;
	else{
		if(Passage[i][j+1]) Direction[2] = 0;
		else Direction[2] = 1;
	}
	
	//Haut
	if(j == 0) Direction[3] = 0;
	else{
		if(Passage[i][j-1]) Direction[3] = 0;
		else Direction[3] = 1;
	}
	
	for(; a<4; a++){
		h = h + Direction[a];
	}
	
	return h;
}

int DessinerChemin(int dim, int Nb, Coordonnees point){
	int Direction[4];
	int i=point.x/dim, j=point.y/dim, h, d;
	Passage[i][j]=1;
	
	h = VerifCase(Direction, Nb, i, j);
	
	if(h == 0){
		RectangleRose(point, dim);
		return 0;
	}
	
	do{
		d = (((double)rand())/RAND_MAX) * 4;
	}while(Direction[d] == 0);
	
	RectangleRouge(point, dim);
	RectangleBlanc(point, dim);
	EffMur(d, point, dim);
	Direction[d] = 0;
	// Haut
	if(d == 3)point.y = point.y-dim;
	// Bas
	else if(d == 2) point.y = point.y+dim;
	// Gauche
	else if(d == 1) point.x = point.x-dim;
	// Droite
	else if(d == 0) point.x = point.x+dim;
	DessinerChemin(dim, Nb, point);
	RectangleRouge(point, dim);
	
	h = VerifCase(Direction, Nb, i, j);
	if(h == 0){
		RectangleBlanc(point, dim);
		return 0;
	}
	
	do{
		d = (((double)rand())/RAND_MAX) * 4;
	}while(Direction[d] == 0);
	
	EffMur(d, point, dim);
	RectangleBlanc(point, dim);
	Direction[d] = 0;
	// Haut
	if(d == 3) point.y = point.y-dim;
	// Bas
	else if(d == 2) point.y = point.y+dim;
	// Gauche
	else if(d == 1) point.x = point.x-dim;
	// Droite
	else if(d == 0) point.x = point.x+dim;
	DessinerChemin(dim, Nb, point);
	RectangleRouge(point, dim);
	
	h = VerifCase(Direction, Nb, i, j);
	if(h == 0){
		RectangleBlanc(point, dim);
		return 0;
	}
		
	do{
		d = (((double)rand())/RAND_MAX) * 4;
	}while(Direction[d] == 0);
	
	RectangleBlanc(point, dim);
	EffMur(d, point, dim);
	Direction[d] = 0;
	// Haut
	if(d == 3) point.y = point.y-dim;
	// Bas
	else if(d == 2) point.y = point.y+dim;
	// Gauche
	else if(d == 1) point.x = point.x-dim;
	// Droite
	else if(d == 0) point.x = point.x+dim;
	DessinerChemin(dim, Nb, point);
	RectangleRouge(point, dim);
	
	RectangleBlanc(point, dim);
	return 0;	
}

int Victoire(Coordonnees point, Coordonnees sortie, int dim){
	int i,j,k,l;
	i = point.x/dim * (dim+1) +1;
	j = point.y/dim * (dim+1) +1;
	k = sortie.x/dim * (dim+1) +1;
	l = sortie.y/dim * (dim+1) +1;
	
	if(i == k && j == l) return 1;
	return 0;
}

int main(int argc, char **argv){
	int dim = 20, Nb = 30, i=0, j=0;
	Coordonnees point, sortie;
	MLV_Event event_type=MLV_NONE;
	MLV_Keyboard_button touche;
	point.x = 1;
	point.y = 1;
	sortie.x = dim*(Nb-1);
	sortie.y = dim*(Nb-1);
	srand(time(NULL));
	
	for(;i<=dim;i++){
		for(;j<=dim; j++){
			Passage[i][j]=0;
		}
	}
	
	AffCadrillage(dim, Nb);// Ouvre la fenêtre et d'affiche le cadrillage.
	MLV_actualise_window();// Actualise la fenêtre
	DessinerChemin(dim, Nb, point);
	RectangleRouge(point, dim);
	RectangleVert(sortie, dim);
	
	while( event_type!=MLV_KEY || touche != MLV_KEYBOARD_ESCAPE ){
		event_type = MLV_wait_keyboard_or_mouse( &touche, NULL, NULL, NULL, NULL);
		if(touche == MLV_KEYBOARD_UP){
			if(point.y != 0){
				RectangleBlanc(point, dim);
				point.y = point.y-dim;
			}
			RectangleRouge(point, dim);
		}
		else if(touche == MLV_KEYBOARD_DOWN){
			if(point.y != (dim*Nb)-dim){
				RectangleBlanc(point, dim);
				point.y = point.y+dim;
			}
			RectangleRouge(point, dim);
		}
		else if(touche == MLV_KEYBOARD_LEFT){
			if(point.x != 0){
				RectangleBlanc(point, dim);
				point.x = point.x-dim;
			}
			RectangleRouge(point, dim);
		}
		else if(touche == MLV_KEYBOARD_RIGHT){
			if(point.x != (dim*Nb)-dim){
				RectangleBlanc(point, dim);
				point.x = point.x+dim;
			}
			RectangleRouge(point, dim);
		}
		MLV_actualise_window();
		
		if(Victoire(point, sortie, dim)) break;
	}

	// Fermer la fenêtre
	MLV_free_window();
	printf("C'est gagné !! :)");
	return 0;
}

