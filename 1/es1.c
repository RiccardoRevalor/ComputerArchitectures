int main() {
  int v1[] = {1,2,3,4,5};
  int v2[] = {5,4,3,2,1};
  int v3[5] = {0};
  int v4[5] = {0};
  int r1, r2, r3, r4, i, r6;
  r1 = r2 = r3 = r4 = i = r6 = 0;
  
  r6 = 0 + 5;
  do {
    r1 = v1[i];
    r2 = v2[i];
    r3 = r1 + r2;
    r4 = r1 - r2;
    v3[i] = r3;
    v4[i] = r4;
    i += 1;
    r6 -= 1;
  } while (r6 != 0);
  
  return 0;
}

