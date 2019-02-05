#include <stdio.h>

struct point {
	int x;
	int y;
};



int main() {
	struct point pt = {50};
	struct point *ppt = &pt;
	struct point pt2 = {100, 100};

	printf("%d %d\n", pt.x, pt.y);
	printf("%d %d\n", ppt->x, ppt->y);
	printf("%d %d\n", pt2.x, pt2.y);
}
