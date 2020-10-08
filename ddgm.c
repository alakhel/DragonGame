#include <libxml/parser.h>
#include <libxml/tree.h>
#include "ddg.h"
#include "player.h"
#define BUF_SIZE 30
#define MAX_PLAYERS 10

 /**
 * Vérification de l'argument de commande.
 * @param arg c'est argv[0], pour afficher le nom de programme au début de la ligne si le argument est non valide.
 * @param cmd & argument, c'est la commande et l'argument.
 * @return 0 si l'argument est valide, -1 le cas contraire.
**/
int check_cmd_argument(char *arg, char *cmd, char *argument);

 /* Manipulation du commande v */
 void ddgm_handle_v();

 /* Manipulation du commande h */
 void ddgm_handle_h();


int main(int argc, char *argv[])
{
 /* Déclaration des Variables */
	char cmd[BUF_SIZE] = "\0";
  char *argument;
  int i;
  int nplayers;
  char *ptr;

	xmlDocPtr doc;
	xmlNodePtr node;

  ddg_t *ddg_1 = ddg_create();
  player_t *player_1[MAX_PLAYERS];

 /* Vérification de nombre d'Argument */
	if (argc != 2)
	{
	fprintf(stderr, "%s: Invalid Number of Arguments\n", argv[0]);
	return 1;
	}
/* Parse the XML file */
doc = xmlParseFile(argv[1]);
if (doc == NULL){
  printf("I/O warning : failed to load external entity \"%s\"\n", argv[1]);
  xmlFreeDoc(doc);
  return 1;
  }

/* Read the root element */
node = xmlDocGetRootElement(doc);
if (node == NULL){
  printf("%s: Unable to parse the document\n", argv[0]);
  xmlFreeDoc(doc);
  xmlCleanupParser();
  return 1;
  }

/* Move to the 2nd level where date, dmname, players are*/
node = node->children;

nplayers = read_players(node, player_1);

/* Add players to the DDG */
for(i=0; i<nplayers; i++)
  ddg_add_player(ddg_1, player_1[i]);

ddg_1->dmname =read_dmname(node);
ddg_1->day = read_date(node, "day");
ddg_1->month = read_date(node, "month");
ddg_1->year = read_date(node, "year");
ddg_1->name =(char *) xmlGetProp(node->parent, (const xmlChar *) "name");




/* Boucle de programme */
while (1){
  printf("DDGM 2.0> ");

  /* Lecture du commande de l'utilisateur */
  fgets(cmd, BUF_SIZE, stdin);

  if(strlen(cmd)>18){
    printf("%s: Too many characters for the command\n", argv[0]);
    continue;
  }

  argument = strstr(cmd, " ");

  if(argument != NULL){

    argument[strlen(argument)-1]= '\0';
    argument = argument+1;
    cmd[strlen(cmd)-strlen(argument)-1] = '\0';
  }else
    cmd[strlen(cmd)-1] = '\0';

       if(!strcmp(cmd, "q")) break; /* arréter le boucle de programme si la cmd est "q"*/
  else if(!strcmp(cmd, "h")) ddgm_handle_h();
  else if(!strcmp(cmd, "v")) ddgm_handle_v();
  else if(!strcmp(cmd, "p")) ddg_handle_p(*ddg_1);
  else if(!strcmp(cmd, "d")) ddg_handle_d(*ddg_1);
  else if(!strcmp(cmd, "g")) ddg_handle_g(*ddg_1);
  else if(!strcmp(cmd, "m")) ddg_handle_m(*ddg_1);
  else if(!strcmp(cmd, "n")) ddg_handle_n(*ddg_1);
	else if(!strcmp(cmd, "pa")){
    if(check_cmd_argument(argv[0], cmd, argument)==0) ddg_handle_pa(*ddg_1, strtol(argument, &ptr, 10));}

 else if(!strcmp(cmd, "pc")){
   if(argument== NULL) printf("%s: Missing parameter for the %s command\n", argv[0], cmd);
   else ddg_handle_pc(*ddg_1, argument);}

else if(!strcmp(cmd, "pn")){
  if(argument== NULL) printf("%s: Missing parameter for the %s command\n", argv[0], cmd);
  else ddg_handle_pn(*ddg_1, argument);}

else if(!strcmp(cmd, "pcn")){
  if(argument== NULL) printf("%s: Missing parameter for the %s command\n", argv[0], cmd);
  else ddg_handle_pcn(*ddg_1, argument);}

else if(!strcmp(cmd, "ph")){
    if(check_cmd_argument(argv[0], cmd, argument)==0) ddg_handle_ph(*ddg_1, strtol(argument, &ptr, 10));}

  else if(!strcmp(cmd, "page")){
    if(check_cmd_argument(argv[0], cmd, argument)==0) ddg_handle_page(*ddg_1, strtol(argument, &ptr, 10));}

	else if(!strcmp(cmd, "pagt")){
    if(check_cmd_argument(argv[0], cmd, argument)==0) ddg_handle_pagt(*ddg_1, strtol(argument, &ptr, 10));}

	else if(!strcmp(cmd, "pale")){
    if(check_cmd_argument(argv[0], cmd, argument)==0) ddg_handle_pale(*ddg_1, strtol(argument, &ptr, 10));}

	else if(!strcmp(cmd, "palt")){
    if(check_cmd_argument(argv[0], cmd, argument)==0) ddg_handle_palt(*ddg_1, strtol(argument, &ptr, 10));}

	else if(!strcmp(cmd, "phge")){
    if(check_cmd_argument(argv[0], cmd, argument)==0) ddg_handle_phge(*ddg_1, strtol(argument, &ptr, 10));}

	else if(!strcmp(cmd, "phgt")){
    if(check_cmd_argument(argv[0], cmd, argument)==0) ddg_handle_phgt(*ddg_1, strtol(argument, &ptr, 10));}

	else if(!strcmp(cmd, "phle")){
    if(check_cmd_argument(argv[0], cmd, argument)==0) ddg_handle_phle(*ddg_1, strtol(argument, &ptr, 10));}

	else if(!strcmp(cmd, "phlt")){
    if(check_cmd_argument(argv[0], cmd, argument)==0) ddg_handle_phlt(*ddg_1, strtol(argument, &ptr, 10));}

  else printf("%s: Invalid command\n", argv[0]);

   	}/*fin de boucle de programme*/

/* Free allocated memories*/
for(i=0; i<3; i++)
  player_free(player_1[i]);
ddg_free(ddg_1);
xmlFreeDoc(doc);
xmlCleanupParser();

return 0;
}


/**
* Vérification de l'argument de commande.
* @param arg c'est argv[0], pour afficher le nom de programme au début de la ligne si le argument est non valide.
* @param cmd & argument, c'est la commande et l'argument.
* @return: 0 si l'argument est valide, -1 le cas contraire.
**/
int check_cmd_argument(char *arg,char *cmd, char *argument){
  char *ptr;
  if(argument== NULL)
    printf("%s: Missing parameter for the %s command\n", arg, cmd);
  else if(0==strtol(argument, &ptr, 10))
    printf("%s: Invalid parameter for the %s command\n", arg, cmd);
  else
    return 0;
return -1;
}

/* Manipulation du commande h */
void ddgm_handle_h(){
  printf("d: Prints the DDG date\ng: Prints the DDG\nm: Prints the DDG dungeon master name\nh: P");
	printf("rints this ddgm_handle_h\nn: Prints the DDG name\np:Prints the DDG players\npa AC: Prints the D");
	printf("DG players with the armor class equal to AC\npage AC: Prints the DDG players with the ");
	printf("armor class greater than or equal to AC\npagt AC: Prints the DDG players with the armo");
	printf("r class greater than AC\npale AC: Prints the DDG players with the armor class less tha");
	printf("n or equal to AC\npalt AC: Prints the DDG players with the armor class less than AC\np");
	printf("c CLASS: Prints the DDG players with the class containing CLASS\npcn CNAME: Prints the");
	printf(" DDG players with the character name containing CNAME\nph HP: Prints the DDG players w");
	printf("ith the hit points equal to HP\nphge HP: Prints the DDG players with the hit points gr");
	printf("eater than or equal to HP\nphgt HP: Prints the DDG players with the hit points greater");
	printf(" than HP\nphle HP: Prints the DDG players with the hit points less than or equal to HP");
	printf("\nphlt HP: Prints the DDG players with the hit points less than HP\npn NAME: Prints th");
	printf("e DDG players with the name containing NAME\nv: Prints the DDGM version\nq: Quits DDGM");
	printf("\n");
	}

/* Manipulation du commande v */
void ddgm_handle_v(){
	printf("DDGM (Dungeons and Dragons Game Manager) 20191118\n\nCopyright (c) 2019 Amine LAKHEL.\n");
	printf("\nWritten by Amine LAKHEL <a.lakhel@etud.univ-pau.fr>\n");
	}
