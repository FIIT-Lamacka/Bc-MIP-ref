#include <stdio.h>
#include <ctype.h> //pre tolower() funkciu
#include <string.h> //funkcia strlen()
#include <math.h> //funkcia floor()
#define LIMIT_NACITANIA 1000
#define DLZKA_ABECEDY 26


void nacitanie_povodneho_pola(char *p_povodne_pole, int *p_bol_nacitany){
    FILE *fr;
    char znak;

    if ((fr = fopen("sifra.txt", "r")) == NULL) {
		printf("Spravu sa nepodarilo nacitat\n");
		return;
	}
    //nacitanie hodnôt do súboru pomocou pointerovej aritmetiky
	while (znak = getc(fr), feof(fr) == 0){
      *p_povodne_pole=znak;
        p_povodne_pole++;
    }
    *p_bol_nacitany=1;

    if (fclose(fr) == EOF)
      printf("Subor vstup.txt sa nepodarilo zatvorit.\n");



}

void vypis_povodneho_pola(char *p_povodne_pole, int *p_bol_nacitany){
    if(*p_bol_nacitany==0){
        printf("Sprava nie je nacitana\n");
        return;
    }
    printf("%s\n",p_povodne_pole);
}

void uprava_povodneho_pola(char povodne_pole[], char *p_upravene_pole, int povodny_lenght, int *p_bola_upravena, int *p_nacitana){
    int poradie_prvku_pola,poradie_v_upravenom=0;

    if(*p_nacitana==0){
        printf("Sprava nie je nacitana\n");
        return;
    }

    for(poradie_prvku_pola=0;poradie_prvku_pola<povodny_lenght;poradie_prvku_pola++){
       if((povodne_pole[poradie_prvku_pola]>='a'&&povodne_pole[poradie_prvku_pola]<='z')||(povodne_pole[poradie_prvku_pola]>='A'&&povodne_pole[poradie_prvku_pola]<='Z')){ //zistenie ci je znak pismeno
            *p_bola_upravena=1;
            *(p_upravene_pole+poradie_v_upravenom)=toupper(povodne_pole[poradie_prvku_pola]); //konverzia pismen na velke
            poradie_v_upravenom++;
       }
    }
}
void vypis_upravenej_spravy(char povodne_pole[], int bolo_upravene){

    if(bolo_upravene==1){
        printf("%s\n",povodne_pole);
    }
    else{
        printf("Nie je k dispozicii upravena sprava\n");
    }
}
void vypis_slova_dlzky(char povodne_pole[],int dlzka_povodneho_pola, int *p_bola_nacitana){
    int zadana_dlzka, pozicia_povodne=0, slovo_pozicia=0, dlzka_slova=0, reset_pozicia, min=0,max=100;
    char vypis[dlzka_povodneho_pola];

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
            if(dlzka_slova==zadana_dlzka){
                printf("%s\n",vypis);
            }

            dlzka_slova=-1; //-1 lebo sa vo while loope zvyši hodnota, aby bola dlzka_slova potom pri pouziti 0
            for(reset_pozicia=0;reset_pozicia<dlzka_povodneho_pola+1;reset_pozicia++){
                vypis[reset_pozicia]='\0';  //resetovanie pola vypis
            }

            slovo_pozicia=-1;   // -1 lebo sa na konci cikla zvyši hodnota a aby bolo potom slovo_pozicia rovne 0
        }

        dlzka_slova++;
        slovo_pozicia++;
        pozicia_povodne++;
    }

}

void vypis_histogramu(char upravene_pole[], int dlzka_upraveneho,int bola_upravena){
    int pocet_pismen[DLZKA_ABECEDY]={'\0'},for_counter,riadok;
    float priemer[DLZKA_ABECEDY]={'\0'},highest=0;

    if(bola_upravena==0){
        printf("Nie je k dispozicii upravena sprava\n");
        return;
    }

    for(for_counter=0;for_counter<dlzka_upraveneho;for_counter++){
        pocet_pismen[(upravene_pole[for_counter]-'A')]++;
    }

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
void rozsifrovanie_cezara(char upravene_pole[], int dlzka_upraveneho, int bola_upravena){
    int posun,pozicia_rozsifrovane,rozdiel;
    char rozsifrovane[dlzka_upraveneho];

    if(dlzka_upraveneho==0){
        printf("Nie je k dispozicii upravena sprava\n");
        return;
    }

    scanf("%d",&posun);
    if(posun<1||posun>25){
        printf("Cislo musi byt v rozsahu <1-25>\n");
        return;
    }

    for(pozicia_rozsifrovane=0;pozicia_rozsifrovane<dlzka_upraveneho;pozicia_rozsifrovane++){
        rozsifrovane[pozicia_rozsifrovane]=(upravene_pole[pozicia_rozsifrovane]-posun);

        if(rozsifrovane[pozicia_rozsifrovane]<'A'){
            rozdiel=rozsifrovane[pozicia_rozsifrovane]-'A';
            rozsifrovane[pozicia_rozsifrovane]='Z'+(rozdiel+1); //pripocitanie rozdielu k hodnote z
        }

        printf("%c",rozsifrovane[pozicia_rozsifrovane]);
    }
    printf("\n");


}

int main() {
    int i,povodny_l,upraveny_l,bola_upravena=0, nacitany=0;
    char prikaz, povodny[LIMIT_NACITANIA]={'\0'}, upraveny[LIMIT_NACITANIA]={'\0'};


    while(1){

        prikaz = getchar();
        prikaz=tolower(prikaz);

        povodny_l =strlen(povodny);
        upraveny_l =strlen(upraveny);



        switch(prikaz) {
            case 'n' :
                nacitanie_povodneho_pola(povodny,&nacitany);
                break;
            case 'v'  :
                vypis_povodneho_pola(povodny,&nacitany);
                break;
            case 'u'  :
                uprava_povodneho_pola(povodny,upraveny,povodny_l,&bola_upravena,&nacitany);
                break;
            case 's'  :
                vypis_upravenej_spravy(upraveny,bola_upravena);
                break;
            case 'd'  :
                vypis_slova_dlzky(povodny,povodny_l,&nacitany);
                break;
            case 'h'  :
                vypis_histogramu(upraveny, upraveny_l, bola_upravena);
                break;
            case 'c'  :
                rozsifrovanie_cezara(upraveny, upraveny_l, bola_upravena);
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


