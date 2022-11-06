#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int ERROR_STATE= 100;
const int MAX=258;
typedef int state;
typedef unsigned char* attri;
typedef unsigned char* token;
unsigned char *x;
unsigned int i=0;
int table[258][258];
int d=0;
struct ds
{
	attri ds_tt[100];
	token ds_token[100];
}list;


unsigned char readchar(unsigned char* x, unsigned int i);
attri attribute(state s);
int  nostar_end_state(state s);
int  star_end_state(state s);
void  catchar_in_token (unsigned char c, token tk);
void create_table(int table[][258]);
token  search_token (unsigned  int *i, attri  tt);
void  lexical_analysis();
void save_token_and_attribute(token tk,attri a);
int main()
{
	unsigned char chuoi[100];
    printf("Nhap xau x: ");
	gets(chuoi);
	i=0;
	int e=strlen(chuoi);
	strcpy(x,chuoi);

	lexical_analysis();
	for (int m = 0; m < d; m++)
	{
		printf("%s ",list.ds_token[m]);
	}
	for (int m = 0; m < d; m++)
	{
		printf("%s ",list.ds_tt[m]);
	}
	
}

unsigned char readchar(unsigned char* x, unsigned int i){
	int e=strlen(x);
    if(i<e) return (*(x+i));
    else return ('\0');
}

attri attribute(state s)
{
    char *ch;
    ch= (char*)malloc(100* sizeof(char));
    switch (s)
    {
    case 2:
        strcpy(ch, "so sanh lon hon bang");
        break;
    case 3:
        strcpy(ch, "dich phai");
        break;
    case 4:
        strcpy(ch, "so sanh lon hon");
        break;
    case 6:
        strcpy(ch, "so sanh nho hon bang");
        break;
    case 7:
        strcpy(ch, "dich trai");
        break;
    case 8:
        strcpy(ch, "so sanh nho hon");
        break;
    case 10:
        strcpy(ch, "So sanh khong bang");
        break;
    case 11:
        strcpy(ch, "phu dinh");
        break;
    case 13:
        strcpy(ch, "XOR bu roi gan");
        break;
    case 14:
        strcpy(ch, "gan");
        break;
    case 17:
        strcpy(ch, "cong bang");
        break;
    case 18:
        strcpy(ch, "tang 1");
        break;
    case 19:
        strcpy(ch, "cong");
        break;
    case 21:
        strcpy(ch, "tru bang");
        break;
    case 22:
        strcpy(ch, "giam 1");
        break;
    case 23:
        strcpy(ch, "tru");
        break;
    case 25:
        strcpy(ch, "nhan bang");
        break;
    case 26:
        strcpy(ch, "nhan");
        break;
    case 28:
        strcpy(ch, "chia bang");
        break;
    case 29:
        strcpy(ch, "chia");
        break;
    case 30:
        strcpy(ch, "chia lay du");
        break;
    case 33:
        strcpy(ch, "AND");
        break;
    case 34:
        strcpy(ch, "AND tren bit");
        break;
    case 35:
        strcpy(ch, "AND tren bit roi gan");
        break;
    case 37:
        strcpy(ch, "OR");
        break;
    case 38:
        strcpy(ch, "OR tren bit");
        break;
    case 39:
        strcpy(ch, "OR tren bit roi gan");
        break;
    case 41:
        strcpy(ch, "XOR tren bit roi gan");
        break;
    case 42:
        strcpy(ch, "XOR");
        break;
    case 43:
        strcpy(ch, "NOT tren bit");
        break;
    case 45:
        strcpy(ch, "ten bien");
        break;
    case 47:
        strcpy(ch, "chu thich tren 1 dong");
        break;
    case 50:
        strcpy(ch, "chu thich tren nhieu dong");
        break;
    case 53:
        strcpy(ch, "so nguyen he bat phan");
        break;
    case 56:
        strcpy(ch, "so nguyen he thap luc phan");
        break;
    case 58:
        strcpy(ch, "so nguyen he thap phan");
        break;
    case 59:
        strcpy(ch, "so 0");
        break;
    case 61:
        strcpy(ch, "Loi so bat phan khong co 8|9");
        break;
    case 62:
        strcpy(ch, "Loi so nguyen he thap luc phan chi co (0..9|a..f|A..F)");
        break;
    case 63:
        strcpy(ch, "Loi ten khong bat dau bang chu so");
        break;
    case 66:
        strcpy(ch, "so thuc");
        break;
    default:
        strcpy(ch, "token ko duoc doan nhan(tt ko dung) \0");
    }
    return (attri)ch;
}

int nostar_end_state(state s)
{
    switch (s)
    {
    case 2:
    case 3:
    case 6:
    case 7:
    case 10:
    case 13:
    case 17:
    case 18:
    case 21:
    case 22:
    case 25:
    case 28:
    case 30:
    case 33:
    case 35:
    case 37:
    case 39:
    case 41:
    case 43:
    case 47:
    case 50:
    case 62:
    case 63:
        return 1;
    default:
        return 0;
    }
}

int star_end_state(state s)
{
    switch (s)
    {
    case 4:
    case 8:
    case 11:
    case 14:
    case 19:
    case 23:
    case 26:
    case 29:
    case 34:
    case 38:
    case 42:
    case 45:
    case 53:
    case 56:
    case 58:
    case 59:
    case 61:
    case 66:
        return 1;
    default:
        return 0;
    }
}


token  search_token (unsigned  int *i, attri  tt){
   token tk; unsigned char c;
   state s=0, cs;
   int e=strlen(x);
//cắt ký tự trắng bỏ
do {
	c=readchar(x,*i);
	cs=table[s][c];
	if (cs==ERROR_STATE){
		printf("loi tai vi tri %i",*i); tk="";break;	
		} 
	else if (star_end_state(cs)) {
		 strcpy(tt,attribute(cs)); 	
		break;
	}
	else if (nostar_end_state(cs)) {
		catchar_in_token(c,tk);
		*i++;
		 strcpy(tt,attribute(cs));
		break;
	}
	else if (*i>=e-1) {
		printf("het xau vao, ko roi vao TT ket thuc");
		tk=""; break;
	}
	else{
	 catchar_in_token(c,tk);
	*i++;
	s=cs;
	}
}while(1);
return tk;
}

void  catchar_in_token (unsigned char c, token tk){
	// ghep them ky tu c vao cho tu to tk
    int e=strlen(tk);
	*(tk+e)=c;
	*(tk+e+1)='\0';
}

    void create_table(int table[][MAX])
{
    //
    for (int m=0;m<MAX;m++){
        table[0][m] = 100;
    }
    //
    table[0]['>'] = 1;
    table[0]['+'] = 16;
    table[0]['<'] = 5;
    table[0]['-'] = 20;
    table[0]['!'] = 9;
    table[0]['*'] = 24;
    table[0]['='] = 12;
    table[0]['/'] = 27;
    table[0]['%'] = 30;
    table[0]['&'] = 32;
    table[0]['|'] = 36;
    table[0]['^'] = 40;
    table[0]['~'] = 43;
    //
    for (int m=65,j=97;m<=90;m++,j++){
        table[0][m] = 44;
        table[0][j] = 44;
    }
    table[0]['_'] = 44;
    //
    table[0][48] = 51;
    for (int m=49;m<=57;m++){
        table[0][m] = 57;
    }
    table[0]['.'] = 64;
    for (int m = 0; m < MAX; m++)
    {
        //
        table[1][m] = 4;
        table[2][m] = 100;
        table[17][m] = 100;
        table[5][m] = 8;
        table[3][m] = 100;
        table[18][m] = 100;
        table[9][m] = 11;
        table[4][m] = 100;
        table[19][m] = 100;
        table[12][m] = 14;
        table[6][m] = 100;
        table[21][m] = 100;
        table[16][m] = 19;
        table[7][m] = 100;
        table[22][m] = 100;
        table[20][m] = 23;
        table[8][m] = 100;
        table[23][m] = 100;
        table[24][m] = 26;
        table[10][m] = 100;
        table[25][m] = 100;
        table[27][m] = 29;
        table[11][m] = 100;
        table[26][m] = 100;
        table[13][m] = 100;
        table[28][m] = 100;
        table[14][m] = 100;
        table[29][m] = 100;
        table[13][m] = 100;
        table[30][m] = 100;
        //
        table[32][m] = 34;
        table[33][m] = 100;
        table[34][m] = 100;
        table[35][m] = 100;
        table[36][m] = 38;
        table[37][m] = 100;
        table[38][m] = 100;
        table[39][m] = 100;
        table[40][m] = 42;
        table[41][m] = 100;
        table[42][m] = 100;
        table[43][m] = 100;
        //
        table[44][m] = 45;
        table[45][m] = 100;
        //
        table[46][m] = 46;
        table[47][m] = 100;
        table[48][m] = 48;
        table[49][m] = 48;
        table[50][m] = 100;
        //
        table[53][m] = 100;
        table[56][m] = 100;
        table[58][m] = 100;
        table[59][m] = 100;
        table[61][m] = 100;
        table[62][m] = 100;
        table[63][m] = 100;
        table[66][m] = 100;
        table[60][m] = 61;
        table[52][m] = 53;
        table[55][m] = 56;
        table[57][m] = 58;
        table[65][m] = 66;
        table[51][m] = 59;
        table[67][m] = 61;
    }
    //
    table[1]['='] = 2;
    table[1]['>'] = 3;
    table[5]['='] = 6;
    table[5]['<'] = 7;
    table[9]['='] = 10;
    table[12]['='] = 13;
    table[16]['='] = 17;
    table[16]['+'] = 18;
    table[20]['='] = 21;
    table[20]['-'] = 22;
    table[24]['='] = 25;
    table[27]['='] = 28;
    table[32]['&'] = 33;
    table[32]['='] = 35;
    table[36]['|'] = 37;
    table[36]['='] = 39;
    table[40]['='] = 41;
    //
    for (int m=65,j=97;m<=90;m++,j++){
        table[44][m] = 44;
        table[44][j] = 44;
        table[57][j] = 63;
    }
    for (int m=48;m<=57;m++){
        table[44][m] = 44;
    }
    table[44]['_'] = 44;
    //
    table[27]['/'] = 46;
    table[27]['*'] = 48;
    table[46][13] = 47; //Enter
    table[48]['*'] = 49;
    table[49]['*'] = 49;
    table[49]['/'] = 50;
    //
    table[51][56] = 60;
    table[51][57] = 60;
    for (int m=48;m<=57;m++){
        table[54][m] = 55;
        table[57][m] = 57;
        table[64][m] = 65;
        table[65][m] = 65;
        table[55][m] = 55;
        table[60][m] = 60;
        table[67][m] = 67;
    }
    for (int m=48;m<=55;m++){
        table[51][m] = 52;
        table[52][m] = 52;
    }
    table[52][56] = 67;
    table[52][57] = 67;
    table[51]['x'] = 54;
    table[51]['X'] = 54;
    for (int m=65,j=97;m<=70;m++,j++){
        table[54][m] = 55;
        table[54][j] = 55;
        table[55][m] = 55;
        table[55][j] = 55;
    }
    for (int m=71,j=103;m<=90;m++,j++){
        table[55][m] = 62;
        table[55][j] = 62;
    }
    table[51]['.'] = 64;
    table[60]['.'] = 64;
    table[52]['.'] = 64;
    table[57]['.'] = 64;

}
void  lexical_analysis(){
	token tk; attri a;
	create_table(table);
    int e=strlen(x);
	do {
		tk=search_token(&i,a);
		save_token_and_attribute(tk,a);
	}while ((*tk!='\0')&&(i<e));
}
void save_token_and_attribute(token tk,attri a){
	list.ds_token[d]=tk;
	list.ds_tt[d]=a;
}