#include "ddg.h"

/**
* Add a player to a DDG.
* \param ddg The DDG.
* \param player The player.
* \return -1 on error (i.e., if the memory allocation is a failure), else 0.
*/
int ddg_add_player(ddg_t *ddg, player_t *player){
  int np = ddg->nplayers+1;
  if(np==1)
    ddg->players=(player_t**) malloc(sizeof(player_t));
  else
    ddg->players=(player_t**) realloc(ddg->players, np*sizeof(player_t));

/* to verify memory for realloc*/
  ddg->players[np-1] = player;
  ddg->nplayers++;
return 0;
}

/**
* Creates a DDG.s
* \return NULL on error (i.e., if the memory allocation is a failure), else a DDG.
*/
ddg_t *ddg_create(){
  ddg_t *D;
  D = malloc(sizeof(ddg_t));
  if (D == NULL)
  {
    fprintf(stderr, "Allocation de mémoire erreur\n");
    return NULL;
  }

  D->day = 0;
  D->month = 0;
  D->year = 0;
  D->nplayers = 0;

  /*manque initialisation à NULL*/
  return D;
}

/**
* Frees a DDG.
* \param ddg The DDG.
*/
void ddg_free(ddg_t *ddg){
free(ddg->name);
free(ddg->players);
free(ddg);
}

/**
* read dmname
* @param node The node
*/
 char *read_dmname(xmlNodePtr node){

     while (!xml_name_cmp(node, "dmname"))
      node = node->next;
    /* if( xml_name_cmp(node, "dmname"))*/
        return (char *) node->children->content; /* bad syntaxe :( */
     /*return NULL;*/
   }


 /** read node date ** param node enfant*/
 int read_date(xmlNodePtr node,char x[]){
   char *ptr;
   while (!xml_name_cmp(node, "date"))  node = node->next;
   node = node->children; /* qu'on trouve date on desent*/

   while(node != NULL){
     if( xml_name_cmp(node, x)) /* les prints would be affectation ou retourner si je met 3func*/
      return  strtol((const char *) node->children->content , &ptr, 10);
     node = node->next;
    }/*while*/
    return 0;
  }
/*-----------------------------*/
/**
* Handles the d command for a DDG.
* \param ddg The DDG.
*/
void ddg_handle_d(ddg_t ddg){
printf("%d-0%d-0%d\n", ddg.year, ddg.month, ddg.day);
}
/**
* Handles the g command for a DDG.
* \param ddg The DDG.
*/
void ddg_handle_g(ddg_t ddg){
  printf("%s, %s, %d-0%d-0%d, %d player(s)\n", ddg.name, ddg.dmname,ddg.year, ddg.month, ddg.day, ddg.nplayers);
}
/**
* Handles the m command for a DDG.
* \param ddg The DDG.
*/
void ddg_handle_m(ddg_t ddg){
printf("%s\n", ddg.dmname);
}
/**
* Handles the n command for a DDG.
* \param ddg The DDG.
*/
void ddg_handle_n(ddg_t ddg){
printf("%s\n", ddg.name);
}
/**
* Handles the p command for a DDG.
* \param ddg The DDG.
*/
void ddg_handle_p(ddg_t ddg){
  int i;
  for(i=0; i<ddg.nplayers; i++){
    player_handle_p(*ddg.players[i]);

    }
}
/**
* Handles the pa command for all the players of a DDG.
* \param ddg The DDG.

* \param ac The player armor class.
*/
void ddg_handle_pa(ddg_t ddg, int ac){

  int i;
  for(i=0; i<ddg.nplayers; i++){
    player_handle_pa(*ddg.players[i], ac);

    }

}
/**
* Handles the page command for all the players of a DDG.
* \param ddg The DDG.
* \param ac The player armor class.
*/
void ddg_handle_page(ddg_t ddg, int ac){

  int i;
  for(i=0; i<ddg.nplayers; i++){
    player_handle_page(*ddg.players[i], ac);

    }
}
/**
* Handles the pagt command for all the players of a DDG.
* \param ddg The DDG.
* \param ac The player armor class.
*/
void ddg_handle_pagt(ddg_t ddg, int ac){
  int i;
  for(i=0; i<ddg.nplayers; i++){
    player_handle_pagt(*ddg.players[i], ac);

    }
}
/**
* Handles the pale command for all the players of a DDG.
* \param ddg The DDG.
* \param ac The player armor class.
*/
void ddg_handle_pale(ddg_t ddg, int ac){
  int i;
  for(i=0; i<ddg.nplayers; i++){
    player_handle_pale(*ddg.players[i], ac);

    }
}
/**
* Handles the palt command for all the players of a DDG.
* \param ddg The DDG.
* \param ac The player armor class.
*/
void ddg_handle_palt(ddg_t ddg, int ac){
  int i;
  for(i=0; i<ddg.nplayers; i++){
    player_handle_palt(*ddg.players[i], ac);

    }
}
/**
* Handles the pc command for all the players of a DDG.
* \param ddg The DDG.
* \param class The player class.
*/
void ddg_handle_pc(ddg_t ddg, const char *class){
  int i;
  for(i=0; i<ddg.nplayers; i++){
    player_handle_pc(*ddg.players[i], class);

    }
}
/**
* Handles the pcn command for all the players of a DDG.
* \param ddg The DDG.
* \param cname The player character name.
*/
void ddg_handle_pcn(ddg_t ddg, const char *cname){
  int i;
  for(i=0; i<ddg.nplayers; i++){
    player_handle_pcn(*ddg.players[i], cname);

    }
}
/**
* Handles the ph command for all the players of a DDG.
* \param ddg The DDG.
* \param hp The player hit points.
*/
void ddg_handle_ph(ddg_t ddg, int hp){
  int i;
  for(i=0; i<ddg.nplayers; i++){
    player_handle_ph(*ddg.players[i], hp);

    }
}
/**
* Handles the phge command for all the players of a DDG.
* \param ddg The DDG.
* \param hp The player hit points.
*/
void ddg_handle_phge(ddg_t ddg, int hp){
  int i;
  for(i=0; i<ddg.nplayers; i++){
    player_handle_phge(*ddg.players[i], hp);

    }
}
/**
* Handles the phgt command for all the players of a DDG.
* \param ddg The DDG.
* \param hp The player hit points.
*/
void ddg_handle_phgt(ddg_t ddg, int hp){
  int i;
  for(i=0; i<ddg.nplayers; i++){
    player_handle_phgt(*ddg.players[i], hp);

    }
}
/**
* Handles the phle command for all the players of a DDG.
* \param ddg The DDG.
* \param hp The player hit points.
*/
void ddg_handle_phle(ddg_t ddg, int hp){
  int i;
  for(i=0; i<ddg.nplayers; i++){
    player_handle_phle(*ddg.players[i], hp);

    }
}
/**
* Handles the phlt command for all the players of a DDG.
* \param ddg The DDG.
* \param hp The player hit points.
*/
void ddg_handle_phlt(ddg_t ddg, int hp){
  int i;
  for(i=0; i<ddg.nplayers; i++){
    player_handle_phlt(*ddg.players[i], hp);

    }
}
/**
* Handles the pn command for all the players of a DDG.
* \param ddg The DDG.
* \param name The DDG name.
*/
void ddg_handle_pn(ddg_t ddg, const char *name){
  int i;
  for(i=0; i<ddg.nplayers; i++){
    player_handle_pn(*ddg.players[i], name);
    }
}
