#ifndef _API_MAP_H_
#define _API_MAP_H_

typedef char string[256];

struct _LoadImage {
	string filename;
	int sliceX;
	int sliceY;
};
struct _CreateSprite {
	unsigned int imageID;
};
struct _CreateFont {
	unsigned int ID;
	string name;
	int size;
};

struct REPLY {
	char* msg;
	unsigned int len;
};
REPLY API_CALL ( unsigned int funID, char* params, unsigned int len );

#define MAX_FUNCTION_ID 3
#define API_MAP_FUN_SIZE(x) mappingTable[x]
extern const unsigned short mappingTable[4];

#endif // _API_MAP_H_