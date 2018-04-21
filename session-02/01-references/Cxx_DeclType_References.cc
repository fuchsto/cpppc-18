
// --------------------------------------------------------------------
// A note on #define "functions"
// --------------------------------------------------------------------

// Implementing a robust preprocessor #define macro is tricky!
// You should consider them hazardous for several reasons.
// For the programmer using it, macro functions look just like
// regular functions, so users are unaware that they actually
// disable the type system.
#define square(a)           (a) * (a)
#define square_hazardous(a)  a  *  a

double foo = square_hazardous(4+5) // 4 + 5 * 4 + 5



// --------------------------------------------------------------------
// Using `const` declarations
// --------------------------------------------------------------------

// Qualifying variables as constant has no effect on the
// semantics of your code. Removing `const` would not change
// the result of an implementation.
const int x = 123; 
const int y = 345;
// However its effects on performance is tremendous as `const`
// enables a multitude of compiler optimization techniques!

int var = x + y; // <-- constant folding

// For optimization levels > 0, this function would never
// actually appear in the binary!
inline int foo(const int a) {
  const int b = 123;
  return a + b;
}

// This is why:
int main()
{
// -- What you write in code:
    int result = foo(300);

// -- stage 1: inlining ----------
    const int b = 123;
    int result = 300 + 123;
// -- stage 2: constant folding --
    int result = 423;
}


// --------------------------------------------------------------------
// Effects of `const` on valid expressions on a variable
// --------------------------------------------------------------------

// Read type from right to left:
const int * cip;
// "cip is a pointer to an integer that is const"

// The order of `const` and base type can be switched which is easier
// to "read" with the right-to-left rule, but it is highly uncommon:
int const * icp;
// "cip is a pointer to an integer that is const"


// Basically any expression involving a modification of a `const`-
// declared variable is forbidden and would not compile.

cip++;   // <-- das erlaubt
*cip++;  // <-- le verboten

int * const ipc;
ipc++;   // <-- le verboten
*ipc++;  // <-- das erlaubt

const int * const cipc;

cipc++;   // <-- le verboten
*cipc++;  // <-- le verboten

int foo(int * const var) {
  *var++; // <-- erlaubt
  var++;  // <-- verboten
}



// --------------------------------------------------------------------
// How to avoid null-pointers / invalid pointers in C?
// --------------------------------------------------------------------

int   a       = 45;
int * p_valid = &a;
int * p_inval = p_valid + 1;  // <-- defect cause #1: variable pointers

int foo(int * const p) {
  int * v = p;
  v++;
}

// defect cause #2: null-pointers

// Required: 'pointer' value which
//    1: is const
//    2: cannot be null

int (safe *) sp = 0xff;

// Okayokay, ... AAAANDD:
//   3: that can only be initialized from an
//      existing variable
//      (eliminates requirement #2)

int (safe *) sp = &existing;






/*
 * C++ type declaration and references explained in 100 lines of code or less.
 */
int main()
{
  // Anatomy of an assignment by example:
  //
  //     left-hand side       right-hand side
  //            |                    |
  //  .---------'---------.     .----'---.
  //   const Type * lvalue   =   & rvalue
  //   |     |    | |            | |
  //   |     |    | '- named     | '- named or unnamed
  //   |     |    |              |
  //   |     |    '- type        '- operator
  //   |     |
  //   |     '- referenced type
  //   |
  //   '- cvr
  //
  // CVR is short for the qualifier category "const, volatile, reference".

  int value = 100;

  // This is the *declaration* of variable p_value.
  // On the left hand side *of a declaration*, `*` refers to a type.
  int * p_value;

  // This is a *definition* of variable p_value.
  // On the right hand side, & is an operator.
  p_value = &value;

  // On the left hand side *of an assignment* `*` is the dereference
  // operator:
  *p_value = 222;
  // You actually can't mix this up (more important, neither can the
  // compiler) as `*` is not a complete type:
  //
  //    int * inst = NULL; // declaration/definition, int * is complete type
  //        * inst = NULL; // assignment of value referenced by pointer


  // Pointer values have no restriction whatsoever.
  // Therefore, they cannot be trusted:
  p_value = NULL;

  int segvf = *p_value; // <-- doom

  p_value = (int*)(123); // <-- may I introduce you to the
                         //     horrible, horrible C-style cast?

  // On the right hand size, `*` is an operator ...
  int  deref   = *p_value;
  // ... except when used within type specifiers like casts, of course:
  long deref_l = *((long *)p_value);
  //             ^       ^
  //             |       |
  //             |       '- type specifier, casting to "pointer-to-long*
  //             '- dereference operator

  // On the left hand side, `&` denotes a reference type.
  // References must be initialized (= defined) with their declaration.
  // Think of references as 'variable aliases'.
  // They are always named and can only refer to another named value.
  int & ref = value;

  // For a mental model, you can consider references as quantum-entangled.
  ref = 123;
  assert(value == 123);

  // Semantically identical to:
  int * p_ref = &value;
  *p_ref      = 123;
  assert(value == 123);

  // ref identical or equal to value?
  // (id ~> eq)


  // ------------------------------------------------------------------
  // Basic Rule:
  //    If you can resolve the address of it,
  //    then you can create a reference on it.
  // ------------------------------------------------------------------
  // This implies that you can create a reference on *unnamed* values,
  // that is: values that do not have a variable name.
  //
  // Example:
  // int * int_pointer = address_of_some_int();
  // int & int_ref     = *int_pointer;


  // int & one = 1; // <-- nope, `1` has no address!
  // one = 2;       // <-- you see the problem?

  // Variables `ref` and `value` are *identical*.
  // In C/C++, two variables are *identical* if they represent the same
  // address:
  assert(&ref == &value);

  // int value = 100;
  const int & cref = value;
  
  // const int & const why_though = value;

  // *Equality* refers to the *values* of variables.
  // Obviously, identity implies equality.

  int a, b;
  a = 12;
  b = 12; // a equals b

  // Unfortunately, there is no special operator in C/C++ to test for
  // identity like `===` in other languages.
  // Fortunately, if your concepts are well-defined, you won't need it.

  // In C++ lingo, *named* values are usually called "lvalues", because
  // they can be used at the left hand side of an assignment.
  // *Unnamed* values are called "rvalues" because they can only be used at
  // the right hand side of an assignment.
  //
  // For example, `123` is an rvalue because a statement like:
  //
  //   123 = variable;
  //
  // ... would be nonsensical.

  return EXIT_SUCCESS;
}
