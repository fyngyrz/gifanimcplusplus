# gifanim.cpp and gifanim.cpp

Skeletal usage example:

```c++
{
GifWriter g;
ganim.GifBegin(&g, fileName, xw, yw, framedelay, loopcount, bitdepth, dither);
ganim.GifWriteFrame(&g, imageA, xw, yw, framedelay, bitdepth, dither);
ganim.GifWriteFrame(&g, imageB, xw, yw, framedelay, bitdepth, dither);
ganim.GifEnd(&g);
}
```
