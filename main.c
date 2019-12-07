#include <stdio.h>
#include <ctype.h> //pre tolower() funkciu
//#include <stdlib.h>
#include <string.h> //funkcia strlen()
#include <math.h> //funkcia floor()
#define LIMIT_NACITANIA 1000
#define DLZKA_ABECEDY 26


void nacitanie(char *p_povodne_pole, int *p_bol_nacitany){
    FILE *fr;
    int i=0;
    char c;

    if ((fr = fopen("sifra.txt", "r")) == NULL) {
		printf("Spravu sa nepodarilo nacitat\n");
		return 0;
	}
    //nacitanie hodnôt do súboru pomocou pointerovej aritmetiky
	while (c = getc(fr), feof(fr) == 0 && i<LIMIT_NACITANIA){
      *p_povodne_pole=c;
        p_povodne_pole++;
    }
    *p_bol_nacitany=1;
    //zo suroborom viac pracovat nebudeme cize rovno ho môzeme zatvori
    if (fclose(fr) == EOF)
      printf("Subor vstup.txt sa nepodarilo zatvorit.\n");



}

void vypis(char *p_povodne_pole, int *p_bol_nacitany){
    if(*p_bol_nacitany==0){
        printf("Sprava nie je nacitana\n");
        return;
    }
    printf("%s\n",p_povodne_pole);
}

void uprava(char povodne_pole[], char *p_upravene_pole, int povodny_lenght, int *p_bola_upravena, int *p_nacitana){
    int poradie_prvku_pola,poradie_v_upravenom=0,lenght;
    char help=0;

    if(*p_nacitana==0){
        printf("Sprava nie je nacitana\n");
        return;
    }

    for(poradie_prvku_pola=0;poradie_prvku_pola<povodny_lenght;poradie_prvku_pola++){
       if(povodne_pole[poradie_prvku_pola]>='a'&&povodne_pole[poradie_prvku_pola]<='z'||povodne_pole[poradie_prvku_pola]>='A'&&povodne_pole[poradie_prvku_pola]<='Z'){ //zistenie ci je znak pismeno
            *p_bola_upravena=1; //kontrolna premenna pre ine funkcie
            *(p_upravene_pole+poradie_v_upravenom)=toupper(povodne_pole[poradie_prvku_pola]); //konverzia pismen na velke
            poradie_v_upravenom++;
       }
    }
}
void vypis_upravena(char povodne_pole[], int bolo_upravene){

    if(bolo_upravene==1){ //kontrola ci bolo povodne pole upravene
        printf("%s\n",povodne_pole);
    }
    else{
        printf("Nie je k dispozicii upravena sprava\n");
    }
}
void dana_dlzka(char povodne_pole[],int dlzka_povodneho_pola, int *p_bola_nacitana){
    int zadana_dlzka, pozicia_povodne=0, slovo_pozicia=0, dlzka_slova=0, reset_pozicia, min=0,max=100;
    char vypis[dlzka_povodneho_pola]; //nebudeme potrebovat dlzku pola vacsiu ako pôvodne

    if(*p_bola_nacitana==0){
        printf("Sprava nie je nacitana\n");
        return;
    }

    scanf("%d",&zadana_dlzka);

    if(zadana_dlzka<min||zadana_dlzka>max){
        printf("Cislo musi byt v rozsahu <1-100>\n");
        return;
    }


    while(pozicia_povodne<(dlzka_povodneho_pola+1)){ //dlzka +1 aby sa nacital aj posledny znak \0 a na konci nemusel byt medzernik
        vypis[slovo_pozicia]=povodne_pole[pozicia_povodne];

        if(povodne_pole[pozicia_povodne]=='\0' || povodne_pole[pozicia_povodne]==' ' || povodne_pole[pozicia_povodne]=='\n' ){
            if(dlzka_slova==zadana_dlzka){ //ak ma pocitadlo znakou taku istu hodnotu ako pozadovana
                printf("%s\n",vypis);
            }

            dlzka_slova=-1; //-1 lebo sa vo while loope zvyši hodnota, aby bol count potom pri pouziti 0
            for(reset_pozicia=0;reset_pozicia<dlzka_povodneho_pola+1;reset_pozicia++){
                vypis[reset_pozicia]='\0';  //resetovanie pola vypis
            }

            slovo_pozicia=-1;   // -1 lebo sa na konci cikla zvyši hodnota a aby bolo potom j rovne 0
        }

        dlzka_slova++;
        slovo_pozicia++;
        pozicia_povodne++;
    }

}

void histogram(char upravene_pole[], int dlzka_upraveneho,int bola_upravena){
    int pocet_pismen[DLZKA_ABECEDY], total,for_counter,riadok, highest_zaok=0;
    float priemer[DLZKA_ABECEDY],highest=0;

    if(bola_upravena==0){
        printf("Nie je k dispozicii upravena sprava\n");
        return;
    }
    //NULOVANIE POLA
    for(for_counter=0;for_counter<DLZKA_ABECEDY;for_counter++){
        pocet_pismen[for_counter]=0;
        priemer[for_counter]=0;
    }
    //NACITANIE HODNOT Z UPRAVENEHO DO POLA POCET
    for(for_counter=0;for_counter<dlzka_upraveneho;for_counter++){
        pocet_pismen[(upravene_pole[for_counter]-'A')]++;
    }
    //VYPOCET PERCENT
    for(for_counter=0;for_counter<DLZKA_ABECEDY;for_counter++){
        priemer[for_counter]=((float)pocet_pismen[for_counter]/(float)dlzka_upraveneho)*100;
    }

    //zistenie najvyssieho priemeru
    for(for_counter=0;for_counter<DLZKA_ABECEDY;for_counter++){
        if(priemer[for_counter]>highest){
            highest=priemer[for_counter];
        }
    }
    //ak by bol priemer mensi ako 10 nastavi sa hodnota 11, kvoli vykresleniu hviezdiciek
    if(highest<10){
        highest=11;
    }
    //zaokruhlenie primeru nadol na cislo od 1-10 --> 59.6 = 5
    highest/=10;
    highest=floor(highest);


    for(for_counter=1;for_counter<(highest)+1;for_counter++){
        for(riadok=0;riadok<DLZKA_ABECEDY;riadok++){
            if(priemer[riadok]/10>(highest-for_counter)){
                printf("*");
            }
            else{
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("ABCDEFGHIJKLMNOPQRSTUVWXYZ\n");

}
void cezar(char upraveny[], int upraveny_l, int bola_upravena){
    int n,i,rozdiel;
    char rozsifrovane[upraveny_l];

    if(upraveny_l==0){
        printf("Nie je k dispozicii upravena sprava\n");
        return;
    }

    scanf("%d",&n);
    if(n<1||n>25){
        printf("Cislo musi byt v rozsahu <1-25>\n");
        return;
    }

    for(i=0;i<upraveny_l;i++){
        rozsifrovane[i]=(upraveny[i]-n); //odpocitavanie charu cize "desifrovanie"

        if(rozsifrovane[i]<'A'){    //kontrola ci nie je hodnota mensia ako A,
            rozdiel=rozsifrovane[i]-'A'; //vypocitanie rozdielu medzi A a hodnotou, rozdiel vracia zapornu hodnotu
            rozsifrovane[i]='Z'+(rozdiel+1); //pripocitanie rozdielu k hodnote z
        }

        printf("%c",rozsifrovane[i]);
    }
    printf("\n");


}

int main() {
    int end=0,right,i,povodny_l,upraveny_l,bola_upravena=0, nacitany=0;
    char prikaz, povodny[LIMIT_NACITANIA], upraveny[LIMIT_NACITANIA];

    //Nulovanie polí
    for(i=0;i<LIMIT_NACITANIA;i++){
        upraveny[i]='\0';
        povodny[i]='\0';
    }

    while(1){ //Nekoneèna sluèka èo skonèí pri k

        //Nacitanie prikazu a prevod na male pismeno
        prikaz = getchar();
        prikaz=tolower(prikaz);

        //opakovane zistenie dlzok pola, pre prípad upravy suboru sifra.txt
        povodny_l =strlen(povodny);
        upraveny_l =strlen(upraveny);



        switch(prikaz) {
            case 'n' :
                nacitanie(povodny,&nacitany);
                break;
            case 'v'  :
                vypis(povodny,&nacitany);
                break;
            case 'u'  :
                uprava(povodny,upraveny,povodny_l,&bola_upravena,&nacitany);
                break;
            case 's'  :
                vypis_upravena(upraveny,bola_upravena);
                break;
            case 'd'  :
                dana_dlzka(povodny,povodny_l,&nacitany);
                break;
            case 'h'  :
                histogram(upraveny, upraveny_l, bola_upravena);
                break;
            case 'c'  :
                cezar(upraveny, upraveny_l, bola_upravena);
                break;
            case 'k'  :
                return 0;
                break;
        }


        //kontrola spravneho pismena a ošetrenie aby gerchar nebral do buffera aj znak konca riadku
        if(prikaz != '\n' && prikaz != 'n' && prikaz != 'v' && prikaz != 'u' && prikaz != 's' && prikaz != 'd' && prikaz != 'h' && prikaz != 'c'){
            printf("Zadali ste zle pismeno\n");
        }
    }
    return 0;
}


