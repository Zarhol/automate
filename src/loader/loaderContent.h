#ifndef _LOADER_CONTENT_H_
#define _LOADER_CONTENT_H_

#define LOADER_PRE_CONTENT "#include \"cell.h\" \n"

#define LOADER_SIGN_RULE "extern \"C\" void apply(Cell* self, Cell** near) { \n"

#define LOADER_SIGN_COLOR "extern \"C\" bool color(Cell* self) { \n"

#define LOADER_PRE_CONTENT_COLOR "#include \"cell.h\" \n\
#include \"color.h\" \n"


#define LOADER_POST_CONTENT "\n}"
#define LOADER_POST_CONTENT_COLOR "\nreturn false;\n}"


#endif // _LOADER_CONTENT_H_

// compiler avec c++ *.c -o *.so -shared -fPIC
