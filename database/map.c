#include "database.h"

// Print a concat map.
static void printConcatMap(xyMap map) {
    xyMap left = xyMapGetFirstMap(map);
    xyMap right = xyMapGetNextMapMap(left);
    xyPrintMap(left);
    putchar('+');
    xyPrintMap(right);
}

// Print an append map.
static void printAppendMap(xyMap map) {
    xyMap left = xyMapGetFirstMap(map);
    xyMap right = xyMapGetNextMapMap(left);
    xyPrintMap(left);
    putchar('.');
    xyPrintMap(right);
}

// Print a list map.
static void printListMap(xyMap map) {
    putchar('(');
    bool firstTime = true;
    xyMap child;
    xyForeachMapMap(map, child) {
        if(!firstTime) {
            putchar(' ');
        }
        firstTime = false;
        xyPrintMap(child);
    } xyEndMapMap;
    putchar(')');
}

// Print a map object.
void xyPrintMap(xyMap map) {
    switch(xyMapGetType(map)) {
    case XY_MAP_CONCAT:
        printConcatMap(map);
        break;
    case XY_MAP_APPEND:
        printAppendMap(map);
        break;
    case XY_MAP_LIST:
        printListMap(map);
        break;
    case XY_MAP_TOKEN: case XY_MAP_IDFUNC: case XY_MAP_IDTYPE: case XY_MAP_IDSCOPE: case XY_MAP_IDVAR:
        printf("$%u", xyMapGetPosition(map) + 1);
        break;
    case XY_MAP_KEYWORD:
        printf("\"%s\"", utSymGetName(xyMapGetSym(map)));
        break;
    case XY_MAP_NULL:
        printf("null");
        break;
    default:
        utExit("Unknown map type");
    }
}

// Make a map object.
xyMap xyMapCreate(xyParser parser, xyMapType type) {
    xyMap map = xyMapAlloc();
    xyMapSetType(map, type);
    xyParserAppendMap(parser, map);
    return map;
}

