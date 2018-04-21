
// T is huuuge
int equals(T * a, T * b) {
  if (a == b) { return 1; }   // <-- identity
  // ...
  if (*a == *b) { return 1; } // <-- equality
  return 0;
}
