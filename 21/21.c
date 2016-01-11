#include <stdio.h>
#include <stdlib.h>

#define BOSS_HEALTH 109 // Puzzle input
#define BOSS_DAMAGE 8   // Puzzle input
#define BOSS_ARMOR  2   // Puzzle input

#define ATTR_COST    0 // Array index where cost is stored
#define ATTR_DAMAGE  1 // Array index where damage is stored
#define ATTR_ARMOR   2 // Array index where armor is stored

unsigned char weapons[][3] = {
	{ 8, 4, 0}, // Dagger
	{10, 5, 0}, // Shortsword
	{25, 6, 0}, // Warhammer
	{40, 7, 0}, // Longsword
	{74, 8, 9}  // Greataxe
};
unsigned int weapon_count = sizeof(weapons) / sizeof(weapons[0]);
unsigned char armors[][3] = {
	{ 13, 0, 1}, // Leather
	{ 31, 0, 2}, // Chainmail
	{ 53, 0, 3}, // Splintmail
	{ 75, 0, 4}, // Bandedmail
	{102, 0, 5}  // Platemail
};
unsigned int armor_count = sizeof(armors) / sizeof(armors[0]);
unsigned char rings[][3] = {
	{ 25, 1, 0}, // Damage +1
	{ 50, 2, 0}, // Damage +2
	{100, 3, 0}, // Damage +3
	{ 20, 0, 1}, // Defense +1
	{ 40, 0, 2}, // Defense +2
	{ 80, 0, 3}  // Defense +3
};
unsigned int ring_count = sizeof(rings) / sizeof(rings[0]);

int main(void) {
	const unsigned int boss_damage = 8;
	const unsigned int boss_armor = 2;
	unsigned int i, j, k, l; // Weapon, Armor, Ring loop counters
	unsigned int cost, damage, armor, turn, leastgold, mostgold;
	leastgold = -1; // Set to max unsigned int value for later comparisons
	mostgold = 0;
	// Straight-up bruteforce the solution. Try ALL THE THINGS!
	for (i=0; i < weapon_count; i++) {
		for (j=0; j <= armor_count; j++) {
			for (k=0; k <= ring_count; k++) {
				for (l=0; l <= ring_count; l++) {
					if (k == l && k != 0) continue; // Can't have two rings be the same, but can have both no rings
					cost = weapons[i][ATTR_COST];
					damage = weapons[i][ATTR_DAMAGE];
					armor = 0;
					if (j < armor_count) { // j == armor_count means no armor
						cost += armors[j][ATTR_COST];
						armor += armors[j][ATTR_ARMOR];
					}	
					if (k < ring_count) {
						cost += rings[k][ATTR_COST];
						damage += rings[k][ATTR_DAMAGE];
						armor += rings[k][ATTR_ARMOR];
					}
					if (l < ring_count) {
						cost += rings[l][ATTR_COST];
						damage += rings[l][ATTR_DAMAGE];
						armor += rings[l][ATTR_ARMOR];
					}
					turn = 0; // Start with player's turn
					int health = 100;
					int boss_health = BOSS_HEALTH;
					while (1) {
						if (turn == 0) { // Player's turn
							boss_health -= (damage - boss_armor);
							if (boss_health <= 0) { // We won!
								if (cost < leastgold) leastgold = cost;
								break;
							}
							turn = 1;
						}
						else { // Boss turn
							health -= (boss_damage - armor);
							if (health <= 0) { // We lost..
								if (cost > mostgold) mostgold = cost;
								break;
							}
							turn = 0;
						}
					}
				}
			}
		}
	}
	printf("Part One Solution: %d\n", leastgold);
	printf("Part Two Solution: %d\n", mostgold);
	return EXIT_SUCCESS;
}
