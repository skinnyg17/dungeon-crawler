#ifndef OBJECTEQUIP_H
#define OBJECTEQUIP_H

#include "dungeon.h"
#include "character.h"
#include "pc.h"
#include "io.h"
#include "descriptions.h"


void make_win();
void close_win();
void show_carry(dungeon_t *d);
void show_equip(dungeon_t *d);
int get_idx_carry(dungeon_t *d);
int get_idx_equip(dungeon_t *d);
void pick_up(dungeon_t *d);
void display_carry(dungeon_t *d);
void display_equiped(dungeon_t *d);
void expunge_object(dungeon_t *d);
void drop_object(dungeon_t *d);
void wear_object(dungeon_t *d);
void take_off_object(dungeon_t *d);
void look_object(dungeon_t *d);


#endif
