#include <iostream>
#include <new>
#include <malloc.h>
#include <cstdlib>
#include <cstring>
#define field_size 4
#define game_start 140
#define game_exit 141
#define moved 142
#define dir_unknown 149
#define dir_left 150
#define dir_right 151
#define dir_up 152
#define dir_down 153
#define move_left 154
#define move_right 155
#define move_up 156
#define move_down 157
#define move_impossible 158
#define move_win 160
#define cannot_undo 161
int gamefield[field_size*field_size];
int moves[1000];
int turns_count=0;
int free_tile_pos;
int COUNT=0;
int get_free_pos(int gamefield[]);
int move_tile_left(int gamefield[]);
int move_tile_right(int gamefield[]);
int move_tile_up(int gamefield[]);
int move_tile_down(int gamefield[]);
void copy_position(int source[],int dest[]) {
	for(int i=0; i<(field_size*field_size); i++) {
		dest[i]=source[i];
	}
}
void set_default(int gamefield[]) {
	for(int i=0; i<(field_size*field_size); i++) {
		gamefield[i]=(i+1);
	}
}
void set_position(int position[]) {
	for(int i=0; i<(field_size*field_size); i++) {
		gamefield[i]=position[i];
	}
}
void shuffle(int gamefield[],int times) {
	int c=times;
	int r;
	while(c>0) {
		r=rand()%4+1;
		if(r==1) {
			if(move_tile_left(gamefield)==moved)
			c--;}
		if(r==2) {
			if(move_tile_right(gamefield)==moved)
			c--;}
		if(r==3) {
			if(move_tile_up(gamefield)==moved) c--;}
		if(r==4) {
			if(move_tile_down(gamefield)==moved) c--;}
    }
}
///
int youwin(int gamefield[]) {
	int i=0;
	while(i<(field_size*field_size)) {
		if(gamefield[i-1]>gamefield[i])return 0;
		i++;
	}
	return move_win;
}
int move_tile(int gamefield[],int type) {
get_free_pos(gamefield);
	if(type==dir_left) {
		if (move_tile_left(gamefield)==moved) turns_count++;
	}
	if(type==dir_right) {
		if(move_tile_right(gamefield)==moved) turns_count++;
	}
	if(type==dir_up) {
		if(move_tile_up(gamefield)==moved) turns_count++;
	}
	if(type==dir_down) {
		if(move_tile_down(gamefield)==moved) turns_count++;
	}
	get_free_pos(gamefield);
	return 1;
}
int move_tile_left(int gamefield[]) {
	int temp;
	if((free_tile_pos)%field_size==0)
		return move_impossible;
	if((free_tile_pos)%field_size!=0) {
		temp=gamefield[free_tile_pos-1];
		gamefield[free_tile_pos-1]=gamefield[free_tile_pos];
		gamefield[free_tile_pos]=temp;
		free_tile_pos--;
		return moved;
	}
}
void print_field(int gamefield[]) {
	std::cout<<"Turn "<<turns_count<<" Board :"<<std::endl;
	for(int i=0; i<(field_size*field_size); i++) {
		if(gamefield[i]!=(field_size*field_size)) {
			std::cout<<gamefield[i]<<" ";
		} else {
			std::cout<<"x ";
		}
		if(gamefield[i]<10||gamefield[i]==(field_size*field_size)) std::cout<<" ";
		if ((i%field_size)==(field_size-1)) std::cout<<std::endl;
	}
}
int get_free_pos(int gamefield[]) {
	for(int i=0; i<(field_size*field_size); i++) {
		if(gamefield[i]==(field_size*field_size)) {
			free_tile_pos=i;return i;
			break;
		}
	}
}
int move_tile_right(int gamefield[]) {
	int temp;
	if((free_tile_pos)%field_size==(field_size-1))//Åñëè ïóñòàÿ ÿ÷åéêà óïèðàåòñÿ â ëåâóþ ñòåíêó
		return move_impossible;//Òî õîä âëåâî íåâîçìîæåí
	if((free_tile_pos)%field_size!=(field_size-1)) {
		temp=gamefield[free_tile_pos+1];
		gamefield[free_tile_pos+1]=gamefield[free_tile_pos];
		gamefield[free_tile_pos]=temp;
		free_tile_pos++;
		return moved;
	}
}
int undo_move(int type){if(turns_count==0)return cannot_undo;
	if(type==dir_left){
		if(move_tile_right(gamefield)==moved)
			{
			turns_count--;
			return moved;}
			if(move_tile_right(gamefield)==move_impossible)
			return move_impossible;
	}
	if(type==dir_right){
		if(move_tile_left(gamefield)==moved)
			{
			turns_count--;
			return moved;}
			if(move_tile_left(gamefield)==move_impossible)
			return move_impossible;
	}
	if(type==dir_up){
		if(move_tile_down(gamefield)==moved)
			{
			turns_count--;
			return moved;}
			if(move_tile_down(gamefield)==move_impossible)
			return move_impossible;
	}
	if(type==dir_down){
		if(move_tile_up(gamefield)==moved)
			{
			turns_count--;
			return moved;}
			if(move_tile_up(gamefield)==move_impossible)
			return move_impossible;
	}
	
}
int move_tile_down(int gamefield[]) {
	int temp;
	if((free_tile_pos)>(field_size*(field_size-1)))
		return move_impossible;
	if((free_tile_pos)<(field_size*(field_size-1))) {
		temp=gamefield[free_tile_pos+field_size];
		gamefield[free_tile_pos+field_size]=gamefield[free_tile_pos];
		gamefield[free_tile_pos]=temp;
		free_tile_pos+=field_size;
		return moved;
	}
}
int addtoarr(int type){
	moves[turns_count]=type;
	return 1;
}
int move_tile_up(int gamefield[]) {
	int temp;
	if((free_tile_pos)<field_size)
		return move_impossible;
	if((free_tile_pos)>(field_size-1)) {
		temp=gamefield[free_tile_pos-field_size];
		gamefield[free_tile_pos-field_size]=gamefield[free_tile_pos];
		gamefield[free_tile_pos]=temp;
		free_tile_pos-=field_size;
		return moved;
	}
}
int main(void) { int hardness;
set_default(gamefield);
get_free_pos(gamefield);
std::cout<<"Enter number of shuffles "<<std::endl;
std::cin>>hardness;
	shuffle(gamefield,hardness);
	get_free_pos(gamefield);
	print_field(gamefield);
	while (youwin(gamefield)!=move_win) {
		bool q=0;
		char command;
		std::cin>>command;
		if(command=='a') {
			moves[turns_count]=dir_left;
			move_tile(gamefield,dir_left);
			print_field(gamefield);
			q=1;
		}
		if(command=='w') {
			moves[turns_count]=dir_up;
			move_tile(gamefield,dir_up);
			print_field(gamefield);
			q=1;
		}
		if(command=='d') {
			moves[turns_count]=dir_right;
			move_tile(gamefield,dir_right);
			print_field(gamefield);
			q=1;
		}
		if(command=='s') {
			moves[turns_count]=dir_down;
			move_tile(gamefield,dir_down);
			print_field(gamefield);
			q=1;
		}
		if(command=='u') {
			q=1;
			if(undo_move(moves[turns_count-1])==moved)
					print_field(gamefield);
					if(undo_move(moves[turns_count-1]==cannot_undo)){
						std::cout<<"cannot undo as it is first turn"<<std::endl;
					}
				 else std::cout<<moves[turns_count]; print_field(gamefield);
		}
		if(!q) print_field(gamefield);
	}
	std::cout<<"You win!"<<std::endl;
	return 0;
}
