#include "..\include\image.hpp"

ostream& operator<<(ostream& stream, const RGBPixel& pix){
    stream << (int)pix.r << " ";
    stream << (int)pix.g << " ";
    stream << (int)pix.b << " ";
    return stream;
}

ostream& operator<<(ostream& stream, const GrayPixel& pix){
    stream << (int)pix.c;
    return stream;
}

istream& operator>>(istream& stream, RGBPixel& pix){
    int v;    
    stream >> v;
    pix.r = v;
    stream >> v;
    pix.g = v;
    stream >> v;
    pix.b = v;
    return stream;
}

istream& operator>>(istream& stream, GrayPixel& pix){
    int v;    
    stream >> v;
    pix.c = v;
    return stream;
}

ostream& operator<<(ostream& stream, const ImageRGB& imag){
    // fill the metadata header 
    stream << "P3" << endl;
    stream << imag.w << " " << imag.h << endl;
    stream << 255 << endl;
    for  (int i=0; i<imag.h; i++){
        for (int j=0; j<imag.w; j++){
            stream << imag(i+1,j+1) << " ";
        }
        stream << endl;
    }
    return stream;
}

istream& operator>>(istream& stream, ImageRGB& imag){
    string type;
    stream >> type;
    if (type != "P3") {
        cout << "file type must be P3. Got " << type << endl;
        exit(-1);
    }
    stream >> imag.w;
    stream >> imag.h;
    int max_val;
    stream >> max_val;
    int num_pix =  imag.w*imag.h;
    imag.data.resize(num_pix);
    for (int i = 0; i < num_pix; i++)
    {
        stream >> imag[i];
    }
    return stream;
}

ImageGrayscale::ImageGrayscale(const ImageRGB& rgb){
    w = rgb.w; h = rgb.h;
    data.resize(w*h);
    for (int cc = 0; cc < w*h; cc++){
        data[cc] = GrayPixel(rgb[cc]);
    }
}

ostream& operator<<(ostream& stream, const ImageGrayscale& imag){
    // fill the metadata header 
    stream << "P2" << endl;
    stream << imag.w << " " << imag.h << endl;
    stream << 255 << endl;
    for  (int i=0; i<imag.h; i++){
        for (int j=0; j<imag.w; j++){
            stream << imag(i+1,j+1) << " ";
        }
        stream << endl;
    }
    return stream;
}

istream& operator>>(istream& stream, ImageGrayscale& imag){
    string type;
    stream >> type;
    if (type != "P5") {
        cout << "file type must be P5. Read " << type << endl;
        exit(-1);
    }
    stream >> imag.w;
    stream >> imag.h;
    int max_val;
    stream >> max_val;
    int num_pix =  imag.w*imag.h;
    imag.data.resize(num_pix);
    for (int i = 0; i < num_pix; i++)
    {
        stream >> imag[i];
    }
    return stream;
}