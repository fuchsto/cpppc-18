struct Vehicle {
  int _vehicle_value;
};
// Personenkraftwagen : Vehicle
struct Personenkraftwagen {
  Vehicle      _vehicle;
  int          _pkw_value;
}
// Benz : Personenkraftwagen
struct Benz {
  Personenkraftwagen   _vehicle;
  int                  _benz_value;
}
//  : Personenkraftwagen
struct Skoda {
  Personenkraftwagen   _vehicle;
  int                  _skoda_value;
}

void print_vehicle_value(const Vehicle * b) {
  printf("_vehicle_value: %d\n", b->_vehicle_value);
}



Skoda skoda_1;
Skoda skoda_2;
Benz  benz_1;
// 0xAAFF : _vehicle_value:32   // Vehicle
//          _pkw_value:32       // Personenkraftwagen
//          _skoda_value:32     // Skoda



Personenkraftwagen *   pkw_skoda_1  = &skoda_1; // 0x00AA
Vehicle            *   base_skoda_1 = &skoda_1;

Personenkraftwagen *   pkw_benz_1   = &benz_1;  // 0xBB00
Vehicle            *   base_benz_1  = &benz_1;

int x = (Skoda*) base_skoda_1->_skoda_value;
int x = (Benz*)  base_benz_1->_benz_value;

// vtable
// =============================================
// Object                  | ConcreteType
// ----------------------- | -------------------
// 0x00AA                  | Skoda
// 0xBB00                  | Benz













