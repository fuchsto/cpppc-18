

int *    a;
iterator a;

int * buffer    = new int(234);


      int * buf_begin       = buffer;
const int * buf_end         = buf_begin + 234;
const int * const buf_end   = buf_begin + 234;

int *               it_begin = buffer;
iterator<int>       it_begin = buffer.begin();
iterator<const int> it_begin = buffer.begin();


int x = it_begin[23];


self_t & operator=(const self_t & rhs) {
  // ..
}

int   x = 12;
int & a = x;
int   v = a;  // same as int v = x;

a = 23;

a == 23;
x == 23;
v == 12;



int         x = 12;
const int & c = x;
int         v = c;
int       & r = const_cast<int &>(c);

x = 45;



int         x = 12;
const int * c = &x;
int         v = *c;
int       * r = (int *)(c);







sa[34] = 100;

     int a  = sa[34];
//       ^    ^
//       |    |
//       |    '-- proxy_ref<int>
//       |            ^
//       |            |
//       '--- int = --'


