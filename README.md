# gifanim.cpp and gifanim.h

This c++ class has been derived from Charlie Tangora's public
domain "gif.h" project, which you can find
[here.](https://github.com/charlietangora/gif-h) In that spirit,
this is also [public domain](LICENSE). More of this, less of
requiring people to do, or not do, this or that. :)

Basically, you prepare a series of 32-bit (4 RGBA bytes per pixel) images
arranged as rows going from the top of the image to the bottom. The A (alpha)
channel is ignored, but must be there anyway. Each of the RGBA channels is
one byte, with a range of 0 (dark) to 255 (light.)

After the setup as explained below, you pass each image to `GifWriteFrame()`
and when they've all been submitted, you call `GifEnd()`.`

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
	// ----------------------------------------------------------------------

	// and then:
	// ---------
	ganim.GifBegin(&g, fileName, xw, yw, framedelay, loopcount, bitdepth, dither);

	// For each frame of the animation, set up RGBA-formatted image, then:
	// -------------------------------------------------------------------
	ganim.GifWriteFrame(&g, image, xw, yw, framedelay, bitdepth, dither);
	
	// After all frames, this:
	// -----------------------
	ganim.GifEnd(&g);
}
```

My fervent thanks to Charlie Tangora for his
[original PD c implementation;](https://github.com/charlietangora/gif-h)
he saved me a ton of work on my
[iToolBox Project](http://ourtimelines.com/itdoc/intro.html). Converting
his c to a solid c++ class wasn't bad at all; figuring out GIF... _that_
would have been quite the undertaking!

For the record, I'm using this inside a Qt c++ project for OS&nbsp;X/MacOS, and
it works great there as-is, although I do use a custom memory manager
rather than the bare `calloc()` and `free()` used here. Nothing you have
to worry about, I'm just into firewalling and tracking memory during
development so as to catch as many problems as possible, as early as
possible. But because I _do_ use such a memory manager, this code has
been through rigorous memory behavior validation inside my [iToolBox
Project,](http://ourtimelines.com/itdoc/intro.html) and I think you can
confidently trust it to be memory-safe.
