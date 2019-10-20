#include <stdio.h>
#include <stdlib.h>

#define DICE 20
#define PICK 10
#define SIDES 12
#define TARGET 70

long factorial(long i) {
  long j, r = 1;
  for(j = 1; j <= i; j++) {
    r *= j;
  }
  return r;
}

long sum = 0;

void iterate_dice_reentrant(int index, int *dice) {
  if(index == DICE) {
    int i;
    int counts[SIDES] = {0};
    for(i = 0; i < DICE; i++) {
      counts[dice[i]-1]++;
    }
    long n_perms = factorial(DICE);
    for(i = 0; i < SIDES; i++) {
      if(counts[i] == 0) continue;
      n_perms /= factorial(counts[i]);
    }
    sum += (long) n_perms;
    return;
  }
  if(index == PICK) {
    int sum = 0, i;
    for(i = 0; i < index; i++) sum += dice[i];
    if(sum != TARGET) return;
  }
  int last = SIDES;
  if(index > 0) last = dice[index-1];
  int i;
  for(i = 1; i <= last; i++) {
    dice[index] = i;
    iterate_dice_reentrant(index + 1, dice);
  }
}

int main(void) {
  int *current_dice = calloc(DICE, sizeof(int));
  iterate_dice_reentrant(0, current_dice);
  printf("%ld\n", sum);
}