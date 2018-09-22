#include <stdio.h>
#include "../modules/Sort/sort.h"
int
main(){
	float a[] = {8,7,6,5,4,3,2,1};
	
	quick_sort(a, 0, 8);

	for(int i = 0 ; i < 8; i++)
		printf("%lf ", a[i]);
}
