#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
int main()
{
    FILE *mascaraorig;
    FILE *encodedhtml;
    int tamanyo_buff = 0;
    int i = 0;
    int aux;
    char a;
    char *full_string;
    mascaraorig = fopen("templates/template_texto.html", "r");
    encodedhtml = fopen("templates/template.bin", "wb");

    if(mascaraorig != NULL){
        while(!feof(mascaraorig)){
            fread(&a, 1, 1, mascaraorig);
            tamanyo_buff++;
        }
        printf("el tamanyo del buffer es %d \n", tamanyo_buff);
        fseek(mascaraorig, 0, SEEK_SET);
        full_string = (char*)malloc(tamanyo_buff);
        while(!feof(mascaraorig)){
            fread(&full_string[i], 1, 1, mascaraorig);
            i++;
        }
        printf("\n %s \n", full_string);
    }
    for(i=0; i<strlen(full_string); i++){
        //fwrite(&full_string[i], 1, 1, encodedhtml);
        aux = (int)full_string[i];
        fwrite(&aux, sizeof(int), 1, encodedhtml);
    }

    fclose(mascaraorig);
    fclose(encodedhtml);
    printf("Hello world!\n");
    return 0;
}
*/

int main(){
    int aux;
    char ac;
    char *fafa;

    FILE *origen;
    FILE *destino;
    destino = fopen("templates/salida.html", "w");
    origen = fopen("templates/template.bin", "rb");

    while(!feof(origen)){
        fread(&aux, sizeof(int), 1, origen);
        ac = (char)aux;
        if(ac == '#'){
            strcpy(fafa, "mrenvnerwiuvnuie");
            fwrite(fafa, 15,1,destino);
            fread(&aux, sizeof(int), 1, origen);
            ac = (char)aux;
        }
        fwrite(&ac, 1,1,destino);
    }
    fclose(origen);
    fclose(destino);
}

