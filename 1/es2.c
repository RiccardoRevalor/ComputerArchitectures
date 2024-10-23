int main() {
  int v1[] = {1,2,3,4,5};
  int v2[] = {5,4,3,2,1};
  int v3[] = {6,7,8,9,10};
  int v4[] = {10,9,8,7,6};
  int v5[40] = {0};
  int v6[40] = {0};
  int r1, r2;
  r1 = r2 = 0;
  double f1, f2, f3, f4;
  f1 = f2 = f3 = f4 = 0;

  r2 = 0 + 5;
  do {
    f1 = v1[r1];
    f2 = v2[r1];
    f3 = v3[r1];
    f4 = v4[r1];
    f5 = f1 * f2;
    f6 = f3 * f4;
    v5[r1] = f5;
    v6[r1] = f6;
    r1 += 8;
    r2 -= 1;
  } while (r2 != 0);
  
  return 0;
}

