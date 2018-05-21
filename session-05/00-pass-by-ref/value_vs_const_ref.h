
void foo_nonconst_ref(int & val) {
  // val = 23;  => Passing value for `val`
  //               would be a problem,
  //               cannot re-assign values
  //               like 42 = 23;
}
void foo_const_ref(const int & val) {
  // val = 323; forbidden as `val` is const
  //            => no problem if `val` is
  //               value
}


int & x;              // No, need definition
int & a       = 34;   // No.
const int & a = 34;   // No.

foo_nonconst_ref(42); // No.
foo_const_ref(42);    // OK! Values can be
                      // passed as const refs

