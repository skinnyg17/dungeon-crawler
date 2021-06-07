#include "objectequip.h"
#include "object.h"
#include "dungeon.h"
#include "character.h"
#include <ncurses.h>
#include <curses.h>
#include <cstring>

#define win_x 2
#define win_y 2
#define win_w 72
#define win_h 18

WINDOW *popup;

void make_win()
{
  popup = newwin(win_h, win_w, win_y, win_x);
  box(popup, 0, 0);
  wrefresh(popup);
}

void close_win()
{
  delwin(popup);
}

void show_carry(dungeon_t *d)
{
  int i;
  for(i=0; i<10; i++) {
    if(d->PC->carry[i]) {
      mvwprintw(popup, i + 4, 3, "%d %s", i, d->PC->carry[i]->get_name());
    }
    else {
      mvwprintw(popup, i + 4, 3, "%d EMPTY", i);
    }
  }
  wrefresh(popup);
}

void show_equip(dungeon_t *d)
{
  int i;
  for(i=0; i<12; i++) {
    if(d->PC->equipment[i]) {
      mvwprintw(popup, i + 4, 3, "%c %s", i+'a', d->PC->equipment[i]->get_name());
    }
    else {
      mvwprintw(popup, i + 4, 3, "%c EMPTY", i+'a');
    }
  }
  wrefresh(popup);
}

int get_idx_carry(dungeon_t *d)
{
  int i;
  for(i=0; i<10; i++) {
    if(!d->PC->carry[i])
      return i;
  }
  return -1;
}

int get_idx_equip(dungeon_t *d)
{
  int i;
  for(i=0; i<12; i++) {
    if(!d->PC->equipment[i])
      return i;
  }
  return -1;
}

void pick_up(dungeon_t *d)
{
  if(get_idx_carry(d)!=-1) {
    object *to_pick = d->objmap[d->PC->position[dim_y]][d->PC->position[dim_x]];
    d->PC->carry[get_idx_carry(d)] = to_pick;
    if(to_pick->get_next())
      d->objmap[d->PC->position[dim_y]][d->PC->position[dim_x]] = to_pick->get_next();
    else
      d->objmap[d->PC->position[dim_y]][d->PC->position[dim_x]] = 0;
  }
  else
    io_queue_message("Inventory Full!!");
  //   object *pick = d->objmap[d->PC->position[dim_y]][d->PC->position[dim_x]];
  //   d->PC->carry[get_idx_carry(d)] = pick;
  //   while(pick->get_next()){
  //     if(get_idx_carry(d)!=-1) {
	// object *pickn = pick->get_next();
	// d->PC->carry[get_idx_carry(d)] = pickn;
	// pick = pick->get_next();
  //     }
  //     else {
	// io_queue_message("Inventory full!");
	// break;
  //     }
  //   }
  //   d->objmap[d->PC->position[dim_y]][d->PC->position[dim_x]] = 0;

  // else {
  //   object *pick = d->objmap[d->PC->position[dim_y]][d->PC->position[dim_x]];
  //   d->PC->carry[get_idx_carry(d)] = pick;
  //   d->objmap[d->PC->position[dim_y]][d->PC->position[dim_x]] = 0;
}

void display_carry(dungeon_t *d)
{
  make_win();
  char msg[30] = "Inventory List";
  mvwprintw(popup,2, 2, "%s", msg);
  show_carry(d);
  wrefresh(popup);
  while(1) {
    int input = getch();
    if(input == 27) {
      close_win();
      break;
    }
  }
}

void display_equiped(dungeon_t *d)
{
  make_win();
  char msg[30] = "Equipment List";
  mvwprintw(popup,2, 2, "%s", msg);
  show_equip(d);
  wrefresh(popup);
  while(1) {
    int input = getch();
    if(input == 27) {
      close_win();
      break;
    }
  }
}

void expunge_object(dungeon_t *d)
{
  make_win();
  char msg[30] = "Select object to expunge:";
  mvwprintw(popup,2, 2, "%s", msg);
  show_carry(d);
  wrefresh(popup);
  while(1) {
    int input = getch();
    if(input == 27) {
      close_win();
      break;
    }
    else if(input>='0' && input<='9') {
      int index = input-'0';
      if(!d->PC->carry[index]) {
	io_queue_message("Choose again! Not an object -_-");
	continue;
      }
      delete d->PC->carry[index];
      d->PC->carry[index] = 0;
      io_queue_message("Object expunged...");
    }
    break;
  }
}

void drop_object(dungeon_t *d)
{
  make_win();
  char msg[30] = "Select object to drop:";
  mvwprintw(popup,2, 2, "%s", msg);
  show_carry(d);
  wrefresh(popup);
  while(1) {
    int input = getch();
    if(input == 27) {
      close_win();
      break;
    }
    if(input>='0' && input<='9') {
      int index = input-'0';
      if(!d->PC->carry[index]) {
	io_queue_message("Choose again! Not an object -_-");
	continue;
      }
      object *dropped = d->PC->carry[index];
      if(d->objmap[d->PC->position[dim_y]][d->PC->position[dim_x]]) {
	object *last=d->objmap[d->PC->position[dim_y]][d->PC->position[dim_x]];
	while(last->get_next() != 0) {
	  last = last->get_next();
	}
	last->set_next(dropped);
	d->PC->carry[index] = 0;
	wrefresh(popup);
      }
      else {
	d->objmap[d->PC->position[dim_y]][d->PC->position[dim_x]] = dropped;
	d->PC->carry[index] = 0;
      }
    }
    io_queue_message("Object drop done....");
    break;
  }
}

void wear_object(dungeon_t *d)
{
  make_win();
  char msg[30] = "Select object to equip:";
  mvwprintw(popup,2, 2, "%s", msg);
  show_carry(d);
  wrefresh(popup);
  while(1) {
    int input = getch();
    if(input == 27) {
      close_win();
      break;
    }
    else if(input>='0' && input<='9') {
      int index = input-'0';
      if(!d->PC->carry[index]) {
	       io_queue_message("Choose again! Not an object -_-");
	        continue;
      }
      else {
        int index = input - '0';
        if(!d->PC->carry[index]) continue;
        object *to_equip = d->PC->carry[index];
        if(!d->PC->equipment[to_equip->get_type()-1] || (to_equip->get_type()-1 == 10 && !d->PC->equipment[to_equip->get_type()]))
        {
            if(to_equip->get_type()-1==10 && d->PC->equipment[10]) {
              d->PC->equipment[11] = to_equip;
              d->PC->carry[index] = 0;
            }
            else {
              d->PC->equipment[to_equip->get_type()-1] = to_equip;
              d->PC->carry[index] = 0;
            }
        }
        else {
          io_queue_message("Slot object switch!");
          object *temp = d->PC->equipment[to_equip->get_type()-1];
          d->PC->equipment[to_equip->get_type()-1] = to_equip;
          d->PC->carry[index] = temp;
        }
        break;
    }
    break;
  }
  int32_t base_speed = 10;
  for(int i=0; i<12; i++){
    if(d->PC->equipment[i])
      base_speed += d->PC->equipment[i]->get_speed();
  }
  d->PC->update_speed(base_speed);
  }
}

void take_off_object(dungeon_t *d)
{
  make_win();
  char msg[30] = "Select object to take off:";
  mvwprintw(popup, 2, 2, "%s", msg);
  show_equip(d);
  wrefresh(popup);
  while(1) {
    int input = getch();
    if(input == 27) {
      close_win();
      break;
    }
    else if(input >='a' && input<='l') {
      int index = input-'a';
      if(!d->PC->equipment[index]) {
	io_queue_message("Choose again! Not an object -_-");
	continue;
      }
      object *unequip = d->PC->equipment[index];
      if(get_idx_carry(d)!=-1) {
	d->PC->carry[get_idx_carry(d)] = unequip;
	d->PC->equipment[index] = 0;
	wrefresh(popup);
      }
      io_queue_message("Inventory full! You can only drop the object.");
    }
    break;
  }
  //update speed
  int32_t base_speed = 10;
  for(int i=0; i<12; i++){
    if(d->PC->equipment[i])
      base_speed += d->PC->equipment[i]->get_speed();
  }
  d->PC->update_speed(base_speed);
}

void look_object(dungeon_t *d)
{
  make_win();
  while(1){
    wclear(popup);
    char msg[30] = "Select object to inspect:";
    mvwprintw(popup, 2, 2, "%s", msg);
    show_carry(d);
    wrefresh(popup);
    int input = getch();
    if(input == 27) {
      close_win();
      break;
    }
    else if(input >='0' && input <='9') {
      int index = input - '0';
      if(!d->PC->carry[index]) {
	io_queue_message("Invalid input! Again!!!");
	break;
      }
      wclear(popup);
      mvwprintw(popup, 2, 2, "%s", d->PC->carry[index]->get_desc());
      mvwprintw(popup, 0, 0, "%s", "press any key to go back or esc to quit");
      wrefresh(popup);
      input = getch();
      if(input == 27) {
        close_win();
        break;
      }
    }
    continue;
  }
}
