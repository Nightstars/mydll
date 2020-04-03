#include "mydll.h"
#include "pch.h"

void add(int* num) {
	*num *= *num;
}
void add1(int* num) {
	*num += *num;
}
void add2(int a, int b, int* result) {
	*result = (a + b) * a;
}