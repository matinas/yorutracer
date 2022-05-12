#include <stdlib.h>
#include <stdio.h>

#include <FreeImage.h>

using namespace std;

int main()
{
	printf("Hello World");

	FreeImage_Initialise();

	FIBITMAP *bitmap = FreeImage_Allocate(320, 240, 32);

	if (FreeImage_Save(FIF_JPEG, bitmap, "mybitmap.jpeg", 0)) {
		// bitmap successfully saved!
	}

	if (bitmap) {
		// bitmap successfully created!
		FreeImage_Unload(bitmap);
	}

	return 0;
}