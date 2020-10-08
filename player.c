#include "player.h"

/**
* Creates a player.
* \return NULL on error (i.e., if the memory allocation is a failure), else a player.
*/
player_t *player_create(){
  player_t *P;
  P = malloc(sizeof(player_t));

  if(P==NULL)
  {
    fprintf(stderr, "Allocation de mémoire erreur\n");
    return NULL;
  }

  P->ac = 0;
  P->cp=0;
  P->gp=0;
  P->hp=0;
  P->sp=0;
  return P;
}
/**
* Frees a player.
* \param player The player.
*/
void player_free(player_t *player){
  free(player->name);
  free(player);/*still need to free all memories*/
}
/*simplification de xmlStrcmp*/
int xml_name_cmp(xmlNodePtr node, char str[]){
  return !xmlStrcmp(node->name, (const xmlChar *) str);
}
/**
* Lecture du contenu de la node
* @param node, le pointeur sur la noeud
* @param le nom du noeud qu'on veut lire son contenu, day, cname, class.
* @return le contenu, (NULL si y'a rien)
**/
xmlChar *xml_children_content(xmlNodePtr node, char name[]){
  while(node != NULL){
    if( xml_name_cmp(node, name))
      return  node->children->content;
    node = node->next;
    }
  return NULL;
}
/**
* Read found players
*\ then put them in the array struct player_1
**\ return number of players found
*/
int read_players(xmlNodePtr node, player_t *player_1[]){
  int i=0;
  char *ptr;
  while(!xml_name_cmp(node, "players"))/*on bouge jusqu'à players*/
    node = node->next;

  node= node->children;/*on entre dans players*/


  while(node->next!=NULL){
    node= node->next;
    if(	xml_name_cmp(node, "player")){
      player_1[i] = player_create(); /* i est le nombre de joueurs va se augmenter a chaque fois qu'on trouve un-*/
      player_1[i]->name = (char *) xmlGetProp(node,(const xmlChar *) "name");
      /* bouger vers les infos du joureur */
      node= node->children;
    player_1[i]->ac = strtol((char *) xml_children_content(node, "ac"), &ptr , 10);
    player_1[i]->hp = strtol((char *) xml_children_content(node, "hp"), &ptr , 10);

    player_1[i]->class = (char *) xml_children_content(node, "class");
    player_1[i]->cname = (char *) xml_children_content(node, "cname");

      while (!xml_name_cmp(node, "money")) /* bouger vers money*/
          node = node->next;

      player_1[i]->cp = strtol((char *) xml_children_content(node->children, "cp"), &ptr , 10);
      player_1[i]->gp = strtol((char *) xml_children_content(node->children, "gp"), &ptr , 10);
      player_1[i]->sp = strtol((char *) xml_children_content(node->children, "sp"), &ptr , 10);


      /*sortir du joueur*/
      node= node->parent;
      i++;
      }
  }
  return i; /* retourne le nombre de  joueurs */
}
/**
* Handles the p command for a player.
* \param player The player.
*/
void player_handle_p(player_t player){/* calcaul de l'aregent */
  float gp = player.gp+(float) player.sp / 10+(float) player.cp / 100;
  printf("%s (%s), %s, AC: %d, HP: %d, GP: %.2f (GP: %d, SP: %d, CP: %d)\n", player.name, player.cname, player.class, player.ac, player.hp, gp, player.gp, player.sp, player.cp);
}
/**
* Handles the pa command for a player.
* \param player The player.
* \param ac The player armor class.
*/
void player_handle_pa(player_t player, int ac){
  if(player.ac == ac)
    player_handle_p(player);
}
/**
* Handles the page command for a player.
* \param player The player.
* \param ac The player armor class.
*/
void player_handle_page(player_t player, int ac){
  if(player.ac >= ac)
    player_handle_p(player);
}
/**
* Handles the pagt command for a player.
* \param player The player.
* \param ac The player armor class.
*/
void player_handle_pagt(player_t player, int ac){
  if(player.ac > ac)
    player_handle_p(player);
}
/**
* Handles the pale command for a player.
* \param player The player.
* \param ac The player armor class.
*/
void player_handle_pale(player_t player, int ac){
  if(player.ac <= ac)
    player_handle_p(player);
}
/**
* Handles the palt command for a player.
* \param player The player.
* \param ac The player armor class.
*/
void player_handle_palt(player_t player, int ac){
  if(player.ac < ac)
    player_handle_p(player);
}
/**
* Handles the pc command for a player.
* \param player The player.
* \param class The player class.
*/
void player_handle_pc(player_t player, const char *class){
  if(strstr(player.class, class))
    player_handle_p(player);
}
/**
* Handles the pcn command for a player.
* \param player The player.
* \param cname The player character name.
*/
void player_handle_pcn(player_t player, const char *cname){
  if(strstr(player.cname, cname))
    player_handle_p(player);
}
/**
* Handles the ph command for a player.
* \param player The player.
* \param hp The player hit points.
*/
void player_handle_ph(player_t player, int hp){
  if(player.hp == hp)
    player_handle_p(player);
}
/**
* Handles the phge command for a player.
* \param player The player.
* \param hp The player hit points.
*/
void player_handle_phge(player_t player, int hp){
  if(player.hp >= hp)
    player_handle_p(player);
}
/**
* Handles the phgt command for a player.
* \param player The player.
* \param hp The player hit points.
*/
void player_handle_phgt(player_t player, int hp){
  if(player.hp > hp)
    player_handle_p(player);
}
/**
* Handles the phle command for a player.
* \param player The player.
* \param hp The player hit points.
*/
void player_handle_phle(player_t player, int hp){
  if(player.hp <= hp)
    player_handle_p(player);
}
/**
* Handles the phlt command for a player.
* \param player The player.
* \param hp The player hit points.
*/
void player_handle_phlt(player_t player, int hp){
  if(player.hp < hp)
    player_handle_p(player);
}
/**
* Handles the pn command for a player.
* \param player The player.
* \param name The player name.
*/
void player_handle_pn(player_t player, const char *name){
  if(strstr(player.name, name))
    player_handle_p(player);
}
