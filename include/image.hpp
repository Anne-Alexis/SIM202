#include <iostream>
#include <fstream>
#include <vector>

#pragma once

typedef unsigned char uchar;

using namespace std;

struct RGBPixel{
    uchar r, g, b; // one byte per color
};

struct GrayPixel{
    uchar c;
    GrayPixel(){c=0;}
    GrayPixel(const RGBPixel& rgb){c = (0.3*rgb.r+0.59*rgb.g+0.11*rgb.b);} // weighted average
    // GrayPixel(const RGBPixel& rgb){c = (rgb.r+rgb.g+rgb.b)/3;} // weighted
    // average
};

// double operator+(double a, GrayPixel pix){
//     a + (double)(pix.c)
// }

ostream& operator<<(ostream&, const RGBPixel&);
istream& operator>>(istream&, RGBPixel&);

class ImageRGB{
    public :    
    int w, h;
    vector<RGBPixel> data;
    RGBPixel& operator[](int i){return data[i];}
    const RGBPixel& operator[](int i) const {return data[i];}
    RGBPixel& operator()(int i){return data[i-1];}
    RGBPixel& operator()(int i,int j){return data[(j-1)*w + (i-1)];}
    const RGBPixel& operator()(int i,int j) const {return data[(i-1)*w + (j-1)];}
};

ostream& operator<<(ostream&, const ImageRGB&);
istream& operator>>(istream&, ImageRGB&);

class ImageGrayscale{
    public : 
    int w, h;
    vector<GrayPixel> data;
    ImageGrayscale(const ImageRGB&); // transform to grayscale
    // ImageGrayscale(const LevelSet&); // TODO: map levelset to image
    GrayPixel& operator[](int i){return data[i];}
    const GrayPixel& operator[](int i) const {return data[i];}
    GrayPixel& operator()(int i){return data[i-1];}
    GrayPixel& operator()(int i,int j){return data[(j-1)*w + (i-1)];}
    const GrayPixel& operator()(int i,int j) const {return data[(i-1)*w + (j-1)];}
};

ostream& operator<<(ostream&, const ImageGrayscale&);
istream& operator>>(istream&, ImageGrayscale&);


