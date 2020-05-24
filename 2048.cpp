#include <iostream>
#include <cstdlib>
int Score=0;
int turns=0;
enum reply {
    nothing,movel,mover,moveu,moved,unknown,EXIT,undo,next,failed_to_move,gameover,failed_to_load,win
};
enum direction {
    left,right,up,down
};
typedef struct position {
	short int pos[4][4];
	short int score;
	short int turn;
	bool exists;
} position;
void init(short int field[4][4]) {
	for(int i=0; i<4; i++) {
		for(int j=0; j<4; j++) {
			field[i][j]=0;
		}
	}
	field[rand()%4][rand()%4]=2;
	field[rand()%4][rand()%4]=2;
}
void move_check(short int field[4][4],bool movable[4][4][4]) {
	for(int i=0; i<4; i++) {
		for(int j=0; j<4; j++) {
			if((j==0)||((field[i][j]==0))) movable[left][i][j]=0;
			else if((j>0)&&(field[i][j]!=0)) movable[left][i][j]=1;
			if((j==3)||(field[i][j]==0)) movable[right][i][j]=0;
			else if ((j<3)&&(field[i][j]!=0))movable[right][i][j]=1;
			if ((i==0)||(field[i][j]==0)) movable[up][i][j]=0;
			else if ((i>0)&&(field[i][j]!=0))movable[up][i][j]=1;
			if((i==3)||(field[i][j]==0)) movable[down][i][j]=0;
			else if((i<3)&&(field[i][j]!=0))
				movable[down][i][j]=1;
		}
	}

}
bool move_l(short int field[4][4],bool movable[4][4][4]) {
	int c=0;
	for(int i=0; i<4; i++) {
		short int k;
		for(int j=0; j<4; j++) {
			if(movable[left][i][j]&&(field[i][j]!=0)&&(field[i][j-1]==0)) {
				c++;
				k=field[i][j];
				field[i][j-1]=k;
				field[i][j]=0;
			}
			if((j>0)&&(field[i][j]!=0)&&(field[i][j]==field[i][j-1])) {
				k=field[i][j];
				Score+=field[i][j];
				field[i][j-1]*=2;
				field[i][j]=0;
				c++;
			}
		}
	}

	if(c==0)return 0;
	else return 1;
}
bool move_u(short int field[4][4],bool movable[4][4][4]) {
	int c=0;
	for(int i=0; i<4; i++) {
		short int k;
		for(int j=0; j<4; j++) {
			if(movable[up][i][j]&&(field[i][j]!=0)&&(field[i-1][j]==0)) {
				c++;
				k=field[i][j];
				field[i-1][j]=k;
				field[i][j]=0;
			}
			if((i>0)&&(field[i][j]!=0)&&(field[i][j]==field[i-1][j])) {
				k=field[i][j];
				Score+=field[i-1][j];
				field[i-1][j]*=2;
				field[i][j]=0;
				c++;
			}
		}
	}

	if(c==0)return 0;
	else return 1;
}
bool move_d(short int field[4][4],bool movable[4][4][4]) {
	int c=0;
	for(int i=0; i<4; i++) {
		short int k;
		for(int j=0; j<4; j++) {
			if(movable[down][i][j]&&(field[i][j]!=0)&&(field[i+1][j]==0)) {
				c++;
				k=field[i][j];
				field[i+1][j]=k;
				field[i][j]=0;
			}
			if((i<3)&&(field[i][j]!=0)&&(field[i][j]==field[i+1][j])) {
				k=field[i][j];
				Score+=field[i][j];
				field[i+1][j]*=2;
				field[i][j]=0;
				c++;
			}
		}

	}

	if(c==0)return 0;
	else return 1;
}
bool move_r(short int field[4][4],bool movable[4][4][4]) {
	int c=0;
	for(int i=0; i<4; i++) {
		short int k;
		for(int j=0; j<4; j++) {
			if(movable[right][i][j]&&(field[i][j]!=0)&&(field[i][j+1]==0)) {
				k=field[i][j];
				field[i][j+1]=k;
				field[i][j]=0;
				c++;
			}
			if((j<3)&&(field[i][j]!=0)&&(field[i][j]==field[i][j+1])) {
				k=field[i][j];
				Score+=field[i][j];
				field[i][j+1]*=2;
				field[i][j]=0;
				c++;
			}

		}
	}

	if(c==0)return 0;
	else return 1;
}
bool setrand2(short int field[4][4],bool arr[4][4]) {
	int r1=rand()%4;
	int r2=rand()%4;
	for(int i=0; i<4; i++) {
		for(int j=0; j<4; j++) {
			if (field[i][j]>0) arr[i][j]=1;
			else arr[i][j]=0;
		}
	}
	int util=1;
	for(int i=0; i<4; i++) {
		for(int j=0; j<4; j++) {
			util*=arr[i][j];
		}
	}
	if(util==1) return 0;
	while(field[r1][r2]!=0) {
		r1=rand()%4;
		r2=rand()%4;

	}
	field[r1][r2]=2;
	return 1;
}
bool loadpos(position POS[1000],short int field[4][4],int num) {
	for(int i=0; i<4; i++) {
		for(int j=0; j<4; j++) {
			field[i][j]=POS[num].pos[i][j];
		}
	}
	return true;
}
void printfield(short int field[4][4]) {
	std::cout<<std::endl;
	std::cout<<"Score:"<<Score<<"Turns:"<<turns<<std::endl;
	for(int i=0; i<4; i++) {
		std::cout<<""<<std::endl;
		std::cout<<""<<std::endl;
		for(int j=0; j<4; j++) {

			std::cout<<" "<<field[i][j];
			if(field[i][j]<10&&field[i][j]>-1)std::cout<<"    ";
			if((field[i][j]<100)&&(field[i][j]>10))std::cout<<"   ";
			if((field[i][j]<1000)&&(field[i][j]>100))std::cout<<"  ";
			if((field[i][j]<10000)&&(field[i][j]>1000))std::cout<<" ";
		}
	}
	std::cout<<std::endl;
}
reply controls(position POS[1000],short int field[4][4],bool movable[4][4][4],char _keyhit) {
	bool flag=true;
	if(_keyhit=='x') {
		return EXIT;
	}
	if(_keyhit=='u') {
		if(turns>0) {
			loadpos(POS,field,turns-1);
			turns--;
		}
		return undo;
	}
	if(_keyhit=='n') {
		if(POS[turns+1].exists) {
			loadpos(POS,field,turns+1);
			turns++;
			return next;
		} else return failed_to_load;

	}
	if(_keyhit=='w') {
		bool mvd=false;
		flag=move_u(field,movable);
		mvd=flag;
		move_check(field,movable);
		while(flag) {
			flag=move_u(field,movable);
			move_check(field,movable);
		}
		if(mvd)return moveu;
		else return failed_to_move;
	}
	if(_keyhit=='s') {
		bool mvd=false;
		flag=move_d(field,movable);
		mvd=flag;
		move_check(field,movable);
		while(flag) {
			flag=move_d(field,movable);
			move_check(field,movable);
		}
		if(mvd)return moved;
		else return failed_to_move;
	}
	if(_keyhit=='a') {
		bool mvd=false;
		flag=move_l(field,movable);
		mvd=flag;
		move_check(field,movable);
		while(flag) {
			flag=move_l(field,movable);
			move_check(field,movable);
		}
		if(mvd)return movel;
		else return failed_to_move;
	}
	if(_keyhit=='d') {
		bool mvd=false;
		flag=move_r(field,movable);
		mvd=flag;
		move_check(field,movable);
		while(flag) {
			flag=move_r(field,movable);
			move_check(field,movable);
		}
		if(mvd)return mover;
		else return failed_to_move;
	}
	return nothing;
}

bool writepos(position POS[1000],int score,int num,short int field[4][4]) {
	if(POS==NULL)return false;
	for(int i=0; i<4; i++) {
		for(int j=0; j<4; j++) {
			POS[num].pos[i][j]=field[i][j];
		}
	}
	POS[num].turn=num;
	POS[num].score=score;
	POS[num].exists=true;
	return true;
}
bool tile_exists(short int field[4][4],short int k) {
	for(int i=0; i<4; i++) {
		for(int j=0; j<4; j++) {
			if(field[i][j]==k)return 1;

		}
	}
	return 0;
}
bool trymove(short int field[4][4],bool movable[4][4][4]) {
	bool tryy[8];
	for(int i=0; i<4; i++) {
		short int k;
		for(int j=0; j<4; j++) {
			if (movable[up][i][j]&&(field[i][j]!=0)&&(field[i-1][j]==0))return true;
			if((i>0)&&(field[i][j]!=0)&&(field[i][j]==field[i-1][j]))return true;
			if(movable[down][i][j]&&(field[i][j]!=0)&&(field[i+1][j]==0))return true;
			if((i<3)&&(field[i][j]!=0)&&(field[i][j]==field[i+1][j]))return true;
			if(movable[left][i][j]&&(field[i][j]!=0)&&(field[i][j-1]==0)) return true;
			if((j>0)&&(field[i][j]!=0)&&(field[i][j]==field[i][j-1])) return true;
			if(movable[right][i][j]&&(field[i][j]!=0)&&(field[i][j+1]==0))return true;
			if((j<3)&&(field[i][j]!=0)&&(field[i][j]==field[i][j+1]))return true;
		}
	}
	return false;
}
int main() {
	char KEY;
	position POS[1000];
	short int field[4][4];
	bool isempty[4][4];
	bool movable[4][4][4];
	init(field);
	writepos(POS,Score,turns,field);
	move_check(field,movable);
	reply current=nothing;
	while((current!=gameover)&&(current!=EXIT)&&(current!=win)) {
		if(tile_exists(field,2048)){
		current=win;
		printfield(field);continue;}
		move_check(field,movable);
		printfield(field);
		std::cin>>KEY;
		current=controls(POS,field,movable,KEY);
		if((current==movel)||(current==mover)||(current==moved)||(current==moveu)) {
			turns++;
			writepos(POS,Score,turns,field);
		}
		move_check(field,movable);
		if((current!=next)&&(current!=undo)&&(current!=failed_to_load))setrand2(field,isempty);
		move_check(field,movable);
		if(!trymove(field,movable)) {
			current=gameover;
		}
		
	}
	if(current==gameover)std::cout<<"Game Over";
	if(current==win)std::cout<<"You win!";
	if(current==EXIT)std::cout<<"Player exited";
	system("pause");

}
