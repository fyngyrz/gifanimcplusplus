# gifanim.cpp and gifanim.cpp

Skeletal usage example:

```c++
#include "gifanim.h"
{
GifAnim ganim;
GifWriter g;
	// Set up filename,
	// xw=N, yw=N,
	// framedelay=1...1000 or so,
	// loopcount =0 means infinite, otherwise as specified
	// bitdepth=8,
	// dither=false (most likely, but you pick)
	// each image is an array of bytes 0-255, in order ((R G B A) x xw) x yw)

	// and then:
	// ---------
	ganim.GifBegin(&g, fileName, xw, yw, framedelay, loopcount, bitdepth, dither);

	// For each frame of the animation, set up image, then:
	// ----------------------------------------------------
	ganim.GifWriteFrame(&g, image, xw, yw, framedelay, bitdepth, dither);
	
	// After all frames, this:
	ganim.GifEnd(&g);
}
```
