#include "cell.h" 
#include "color.h" 
extern "C" bool color(Cell* self) { 
if(self->isSet(0)) {
Color c;
c.r = 255;
c.g = 255;
c.b = 255;
self->setColor(c);
return true;}

return false;
}extern "C" void apply(Cell* self, Cell** near) { 
if(self->isSet(0)) {
near[0]->set(0);
}

}