#include "App.hpp"
// IMPORTNANT
// if adding and new fuctions
// (or implementing them)
// remember to:
// 1) make a local copy
//     Mutex::GetInstance().Lock();
//     Image copy = *outputImage;
//     Mutex::GetInstance().Unlock();
// 2.1) [standard] make sure that it can be canleled and auto refreshed
//         Mutex::GetInstance().Lock();
//         // if canceled
//         if (!Mutex::GetInstance().IsThreadRunning())
//         {
//             *outputImage = copy;
//             copy.ClearImage();
//             Mutex::GetInstance().Unlock();
//             return;
//         }
//         // if auto refresh enabled
//         if (Mutex::GetInstance().GetState() == Mutex::AlgorithmThreadRefresh)
//         {
//             *outputImage = copy;
//             Mutex::GetInstance().SetState(Mutex::MainThreadRefresh);
//         }
//         Mutex::GetInstance().Unlock();
// 2.2) [special] refreshed maualy (remember to either set auto refresh off, or prevent it from being used)
//         Mutex::GetInstance().Lock();
//         if (!Mutex::GetInstance().IsThreadRunning())
//         {
//             *outputImage = fullCopy;
//             fullCopy.ClearImage();
//             for (int i = 0; i < h; i++)
//                 pixelsStatus[i].clear();
//             pixelsStatus.clear();
//             Mutex::GetInstance().Unlock();
//             return;
//         }
//         *outputImage = fullCopy;
//         Mutex::GetInstance().SetState(Mutex::MainThreadRefresh);
//         Mutex::GetInstance().Unlock();
// 3) copy back to shared resource
//     // copy back to output
//     Mutex::GetInstance().Lock();
//     Mutex::GetInstance().ThreadStopped();
//     *outputImage = copy;
//     copy.ClearImage();
//     Mutex::GetInstance().Unlock();

void Algorithms::CreateNegative(Image *outputImage)
{
    // local copy
    Mutex::GetInstance().Lock();
    Image copy = *outputImage;
    Mutex::GetInstance().Unlock();

    int w = copy.GetWidth();
    int h = copy.GetHeight();

    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h; y++)
        {
            Mutex::GetInstance().Lock();
            // if canceled
            if (!Mutex::GetInstance().IsThreadRunning())
            {
                *outputImage = copy;
                copy.ClearImage();
                Mutex::GetInstance().Unlock();
                return;
            }
            // if auto refresh enabled
            if (Mutex::GetInstance().GetState() == Mutex::AlgorithmThreadRefresh)
            {
                *outputImage = copy;
                Mutex::GetInstance().SetState(Mutex::MainThreadRefresh);
            }
            Mutex::GetInstance().Unlock();


            Image::Pixel px = copy.GetPixel(x, y);
            px.r = WHITE - px.r;
            px.g = WHITE - px.g;
            px.b = WHITE - px.b;
            copy.SetPixel(x, y, px);
        }
    }
    // copy back to output
    Mutex::GetInstance().Lock();
    Mutex::GetInstance().ThreadStopped();
    *outputImage = copy;
    copy.ClearImage();
    Mutex::GetInstance().Unlock();
}

void Algorithms::BrightenImage(Image *outputImage, ParametersStruct *params)
{
    // local copy
    Mutex::GetInstance().Lock();
    Image copy = *outputImage;
    auto value = params->value;
    Mutex::GetInstance().Unlock();

    int w = copy.GetWidth();
    int h = copy.GetHeight();

    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h; y++)
        {
        Mutex::GetInstance().Lock();
        // if canceled
        if (!Mutex::GetInstance().IsThreadRunning())
        {
            *outputImage = copy;
            copy.ClearImage();
            Mutex::GetInstance().Unlock();
            return;
        }
        // if auto refresh enabled
        if (Mutex::GetInstance().GetState() == Mutex::AlgorithmThreadRefresh)
        {
            *outputImage = copy;
            Mutex::GetInstance().SetState(Mutex::MainThreadRefresh);
        }
        Mutex::GetInstance().Unlock();
        Image::Pixel px = copy.GetPixel(x, y);
        // Jw(x,y) = J(x,y) + b, clamped to [0, 255]
        px.r = (uint8_t)std::max(0, std::min(255, (int)px.r + value));
        px.g = (uint8_t)std::max(0, std::min(255, (int)px.g + value));
        px.b = (uint8_t)std::max(0, std::min(255, (int)px.b + value));
        copy.SetPixel(x, y, px);
        }
    }
 
    // copy back to output
    Mutex::GetInstance().Lock();
    Mutex::GetInstance().ThreadStopped();
    *outputImage = copy;
    copy.ClearImage();
    Mutex::GetInstance().Unlock();
}

void Algorithms::Contrast(Image *outputImage, ParametersStruct *params)
{
    // local copy
    Mutex::GetInstance().Lock();
    Image copy = *outputImage;
    auto contrast = params->contrast;
    Mutex::GetInstance().Unlock();

    int w = copy.GetWidth();
    int h = copy.GetHeight();

    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h; y++)
        {
        Mutex::GetInstance().Lock();
        // if canceled
        if (!Mutex::GetInstance().IsThreadRunning())
        {
            *outputImage = copy;
            copy.ClearImage();
            Mutex::GetInstance().Unlock();
            return;
        }
        // if auto refresh enabled
        if (Mutex::GetInstance().GetState() == Mutex::AlgorithmThreadRefresh)
        {
            *outputImage = copy;
            Mutex::GetInstance().SetState(Mutex::MainThreadRefresh);
        }
        Mutex::GetInstance().Unlock();

        Image::Pixel px = copy.GetPixel(x, y);
        // Jw(x,y) = a * J(x,y), clamped to [0, 255]
        px.r = (uint8_t)std::max(0, std::min(255, (int)(contrast * px.r)));
        px.g = (uint8_t)std::max(0, std::min(255, (int)(contrast * px.g)));
        px.b = (uint8_t)std::max(0, std::min(255, (int)(contrast * px.b)));
        copy.SetPixel(x, y, px);
        }
    }
    // copy back to output
    Mutex::GetInstance().Lock();
    Mutex::GetInstance().ThreadStopped();
    *outputImage = copy;
    copy.ClearImage();
    Mutex::GetInstance().Unlock();
}

void Algorithms::Exponentiation(Image* outputImage, ParametersStruct* params)
{
    // local copy
    Mutex::GetInstance().Lock();
    Image copy = *outputImage;
    auto alfa = params->alfa;
    Mutex::GetInstance().Unlock();

    // budowanie tablicy LUT (Look Up Table) - raz dla wszystkich 256 wartosci
    uint8_t lut[MAX_VAL];
    for (int i = 0; i < MAX_VAL; i++)
    {
        float normalized = (float)i / (float)WHITE;
        float powered = std::pow(normalized, alfa);
        int   result = (int)((float)WHITE * powered);
        lut[i] = (uint8_t)std::clamp(result, BLACK, WHITE);
    }

    // zastosowanie LUT do kazdego piksela
    for (int x = 0; x < copy.GetWidth(); x++)
    {
        for (int y = 0; y < copy.GetHeight(); y++)
        {
            Image::Pixel px = copy.GetPixel(x, y);
            px.r = lut[px.r];
            px.g = lut[px.g];
            px.b = lut[px.b];
            copy.SetPixel(x, y, px);
        }

        Mutex::GetInstance().Lock();
        if (!Mutex::GetInstance().IsThreadRunning())
        {
            *outputImage = copy;
            copy.ClearImage();
            Mutex::GetInstance().Unlock();
            return;
        }
        if (Mutex::GetInstance().GetState() == Mutex::AlgorithmThreadRefresh)
        {
            *outputImage = copy;
            Mutex::GetInstance().SetState(Mutex::MainThreadRefresh);
        }
        Mutex::GetInstance().Unlock();
    }

    // copy back to output
    Mutex::GetInstance().Lock();
    Mutex::GetInstance().ThreadStopped();
    *outputImage = copy;
    copy.ClearImage();
    Mutex::GetInstance().Unlock();
}
// Jw(x,y) = log(1 + J(x,y))
// Wynik skalujemy do zakresu [0, 255]:
//   skala = 255 / log(1 + 255)
//   lut[i] = round(log(1 + i) * skala)
void Algorithms::Logarithm(Image* outputImage)
{
    // local copy
    Mutex::GetInstance().Lock();
    Image copy = *outputImage;
    Mutex::GetInstance().Unlock();

    // budowanie tablicy LUT - skalowanie wyniku do [0,255]
    float scale = (float)WHITE / std::log(1.0f + (float)WHITE);
    uint8_t lut[MAX_VAL];
    for (int i = 0; i < MAX_VAL; i++)
    {
        int result = (int)std::round(std::log(1.0f + (float)i) * scale);
        lut[i] = (uint8_t)std::clamp(result, BLACK, WHITE);
    }

    // zastosowanie LUT do kazdego piksela
    for (int x = 0; x < copy.GetWidth(); x++)
    {
        for (int y = 0; y < copy.GetHeight(); y++)
        {
            Image::Pixel px = copy.GetPixel(x, y);
            px.r = lut[px.r];
            px.g = lut[px.g];
            px.b = lut[px.b];
            copy.SetPixel(x, y, px);
        }

        Mutex::GetInstance().Lock();
        if (!Mutex::GetInstance().IsThreadRunning())
        {
            *outputImage = copy;
            copy.ClearImage();
            Mutex::GetInstance().Unlock();
            return;
        }
        if (Mutex::GetInstance().GetState() == Mutex::AlgorithmThreadRefresh)
        {
            *outputImage = copy;
            Mutex::GetInstance().SetState(Mutex::MainThreadRefresh);
        }
        Mutex::GetInstance().Unlock();
    }

    // copy back to output
    Mutex::GetInstance().Lock();
    Mutex::GetInstance().ThreadStopped();
    *outputImage = copy;
    copy.ClearImage();
    Mutex::GetInstance().Unlock();
}
// Dla kazdego piksela: Jw(x,y) = J(x,y) * Jmask(x,y) / Jmax
// Normalizacja przez 255, wynik w [0,255]
// Jesli obrazy maja rozne rozmiary - przetwarzamy tylko wspolna czesc
void Algorithms::Masking(Image* outputImage, Image* maskImage)
{
    // local copy
    Mutex::GetInstance().Lock();
    Image copy = *outputImage;
    Image maskCopy = *maskImage;
    Mutex::GetInstance().Unlock();

    int w = std::min(copy.GetWidth(), maskCopy.GetWidth());
    int h = std::min(copy.GetHeight(), maskCopy.GetHeight());

    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h; y++)
        {
            Image::Pixel src = copy.GetPixel(x, y);
            Image::Pixel mask = maskCopy.GetPixel(x, y);

            // mnozenie i normalizacja przez Jmax = 255
            int r = (int)src.r * (int)mask.r / WHITE;
            int g = (int)src.g * (int)mask.g / WHITE;
            int b = (int)src.b * (int)mask.b / WHITE;

            src.r = (uint8_t)std::clamp(r, BLACK, WHITE);
            src.g = (uint8_t)std::clamp(g, BLACK, WHITE);
            src.b = (uint8_t)std::clamp(b, BLACK, WHITE);
            copy.SetPixel(x, y, src);
        }

        Mutex::GetInstance().Lock();
        if (!Mutex::GetInstance().IsThreadRunning())
        {
            *outputImage = copy;
            copy.ClearImage();
            maskCopy.ClearImage();
            Mutex::GetInstance().Unlock();
            return;
        }
        if (Mutex::GetInstance().GetState() == Mutex::AlgorithmThreadRefresh)
        {
            *outputImage = copy;
            Mutex::GetInstance().SetState(Mutex::MainThreadRefresh);
        }
        Mutex::GetInstance().Unlock();
    }

    // copy back to output
    Mutex::GetInstance().Lock();
    Mutex::GetInstance().ThreadStopped();
    *outputImage = copy;
    copy.ClearImage();
    maskCopy.ClearImage();
    Mutex::GetInstance().Unlock();
}

// Jwy(x,y) = alpha * J1(x,y) + (1 - alpha) * J2(x,y)
// J1 = outputImage (obraz zrodlowy), J2 = secondImage (np. po maskowaniu)
// alpha ustawiane suwakiem w params->blendAlpha
void Algorithms::BlendImages(Image* outputImage, Image* secondImage, ParametersStruct* params)
{
    // local copy
    Mutex::GetInstance().Lock();
    Image copy = *outputImage;
    Image secondCopy = *secondImage;
    float alpha = params->blendAlpha;
    Mutex::GetInstance().Unlock();

    int w = std::min(copy.GetWidth(), secondCopy.GetWidth());
    int h = std::min(copy.GetHeight(), secondCopy.GetHeight());

    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h; y++)
        {
            Image::Pixel p1 = copy.GetPixel(x, y);
            Image::Pixel p2 = secondCopy.GetPixel(x, y);

            int r = (int)(alpha * (float)p1.r + (1.0f - alpha) * (float)p2.r);
            int g = (int)(alpha * (float)p1.g + (1.0f - alpha) * (float)p2.g);
            int b = (int)(alpha * (float)p1.b + (1.0f - alpha) * (float)p2.b);

            p1.r = (uint8_t)std::clamp(r, BLACK, WHITE);
            p1.g = (uint8_t)std::clamp(g, BLACK, WHITE);
            p1.b = (uint8_t)std::clamp(b, BLACK, WHITE);
            copy.SetPixel(x, y, p1);
        }

        Mutex::GetInstance().Lock();
        if (!Mutex::GetInstance().IsThreadRunning())
        {
            *outputImage = copy;
            copy.ClearImage();
            secondCopy.ClearImage();
            Mutex::GetInstance().Unlock();
            return;
        }
        if (Mutex::GetInstance().GetState() == Mutex::AlgorithmThreadRefresh)
        {
            *outputImage = copy;
            Mutex::GetInstance().SetState(Mutex::MainThreadRefresh);
        }
        Mutex::GetInstance().Unlock();
    }

    // copy back to output
    Mutex::GetInstance().Lock();
    Mutex::GetInstance().ThreadStopped();
    *outputImage = copy;
    copy.ClearImage();
    secondCopy.ClearImage();
    Mutex::GetInstance().Unlock();
}

void Algorithms::LevelHistogram(Image *outputImage)
{
    // local copy
    Mutex::GetInstance().Lock();
    auto copy = *outputImage;
    Mutex::GetInstance().Unlock();

    // Turn to grayscale first (equalization defined for grayscale)
    copy.TurnToGrayScale();

    int w = copy.GetWidth();
    int h = copy.GetHeight();
    int totalPixels = w * h;

    // Build histogram
    int hist[MAX_VAL] = {};
    for (int x = 0; x < w; x++)
        for (int y = 0; y < h; y++)
        {
            Image::Pixel px = copy.GetPixel(x, y);
            hist[px.r]++;  // grayscale: r == g == b
        }

    // Build cumulative distribution function (CDF)
    int cdf[MAX_VAL] = {};
    cdf[0] = hist[0];
    for (int i = 1; i < MAX_VAL; i++)
        cdf[i] = cdf[i - 1] + hist[i];

    // Find cdf_min (first non-zero entry)
    int cdfMin = 0;
    for (int i = 0; i < MAX_VAL; i++)
    {
        if (cdf[i] > 0)
        {
            cdfMin = cdf[i];
            break;
        }
    }

    // Build LUT using equalization formula: lut[v] = round((cdf[v] - cdfMin) / (totalPixels - cdfMin) * 255)
    uint8_t lut[MAX_VAL];
    for (int i = 0; i < MAX_VAL; i++)
    {
        if (totalPixels == cdfMin)
            lut[i] = 0;
        else
            lut[i] = (uint8_t)std::round((float)(cdf[i] - cdfMin) / (totalPixels - cdfMin) * WHITE);
    }

    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h; y++)
        {
        Mutex::GetInstance().Lock();
        // if canceled
        if (!Mutex::GetInstance().IsThreadRunning())
        {
            *outputImage = copy;
            copy.ClearImage();
            Mutex::GetInstance().Unlock();
            return;
        }
        // if auto refresh enabled
        if (Mutex::GetInstance().GetState() == Mutex::AlgorithmThreadRefresh)
        {
            *outputImage = copy;
            Mutex::GetInstance().SetState(Mutex::MainThreadRefresh);
        }
        Mutex::GetInstance().Unlock();

        Image::Pixel px = copy.GetPixel(x, y);
        uint8_t newVal = lut[px.r];
        px.r = newVal;
        px.g = newVal;
        px.b = newVal;
        copy.SetPixel(x, y, px);
        }
    }
 
    // copy back to output
    Mutex::GetInstance().Lock();
    Mutex::GetInstance().ThreadStopped();
    *outputImage = copy;
    copy.ClearImage();
    Mutex::GetInstance().Unlock();
}

void Algorithms::Binarization(Image *outputImage, ParametersStruct *params)
{
    // local copy
    Mutex::GetInstance().Lock();
    auto copy = *outputImage;
    Mutex::GetInstance().Unlock();

  
            //Mutex::GetInstance().Lock();
            //// if canceled
            //if (!Mutex::GetInstance().IsThreadRunning())
            //{
            //    *outputImage = copy;
            //    copy.ClearImage();
            //    Mutex::GetInstance().Unlock();
            //    return;
            //}
            //// if auto refresh enabled
            //if (Mutex::GetInstance().GetState() == Mutex::AlgorithmThreadRefresh)
            //{
            //    *outputImage = copy;
            //    Mutex::GetInstance().SetState(Mutex::MainThreadRefresh);
            //}
            //Mutex::GetInstance().Unlock();
   
    // copt back to output
    Mutex::GetInstance().Lock();
    Mutex::GetInstance().ThreadStopped();
    *outputImage = copy;
    copy.ClearImage();
    Mutex::GetInstance().Unlock();
}

void Algorithms::LinearFilter(Image *outputImage, ParametersStruct *params)
{
    // local copy
    Mutex::GetInstance().Lock();

    auto fullCopy = *outputImage;

    Mutex::GetInstance().Unlock();

   
        //Mutex::GetInstance().Lock();
        //// if canceled
        //if (!Mutex::GetInstance().IsThreadRunning())
        //{
        //    *outputImage = fullCopy;
        //    fullCopy.ClearImage();
        //    Mutex::GetInstance().Unlock();
        //    return;
        //}
        //// if auto refresh enabled
        //if (Mutex::GetInstance().GetState() == Mutex::AlgorithmThreadRefresh)
        //{
        //    *outputImage = fullCopy;
        //    Mutex::GetInstance().SetState(Mutex::MainThreadRefresh);
        //}
        //Mutex::GetInstance().Unlock();
        // 
    // copy back to output
    Mutex::GetInstance().Lock();
    Mutex::GetInstance().ThreadStopped();
    *outputImage = fullCopy;
    fullCopy.ClearImage();
    Mutex::GetInstance().Unlock();
}

void Algorithms::MedianFilter(Image *outputImage, ParametersStruct *params)
{
    // local copy       
    Mutex::GetInstance().Lock();
            
    auto fullCopy = *outputImage;

    Mutex::GetInstance().Unlock();

    
        //Mutex::GetInstance().Lock();
        //// if canceled
        //if (!Mutex::GetInstance().IsThreadRunning())
        //{
        //    *outputImage = fullCopy;
        //    fullCopy.ClearImage();
        //    Mutex::GetInstance().Unlock();
        //    return;
        //}
        //// if auto refresh enabled
        //if (Mutex::GetInstance().GetState() == Mutex::AlgorithmThreadRefresh)
        //{
        //    *outputImage = fullCopy;
        //    Mutex::GetInstance().SetState(Mutex::MainThreadRefresh);
        //}
        //Mutex::GetInstance().Unlock();

    // copy back to output
    Mutex::GetInstance().Lock();
    Mutex::GetInstance().ThreadStopped();
    *outputImage = fullCopy;
    fullCopy.ClearImage();
    Mutex::GetInstance().Unlock();
}

void Algorithms::Erosion(Image *outputImage, ParametersStruct *params)
{
    // local copy
 
    Mutex::GetInstance().Lock();
    auto fullCopy = *outputImage;

    Mutex::GetInstance().Unlock();

   
        //Mutex::GetInstance().Lock();
        //// if canceled
        //if (!Mutex::GetInstance().IsThreadRunning())
        //{
        //    *outputImage = fullCopy;
        //    fullCopy.ClearImage();
        //    Mutex::GetInstance().Unlock();
        //    return;
        //}
        //// if auto refresh enabled
        //if (Mutex::GetInstance().GetState() == Mutex::AlgorithmThreadRefresh)
        //{
        //    *outputImage = fullCopy;
        //    Mutex::GetInstance().SetState(Mutex::MainThreadRefresh);
        //}
        //Mutex::GetInstance().Unlock();

    // copy back to output
    Mutex::GetInstance().Lock();
    Mutex::GetInstance().ThreadStopped();
    *outputImage = fullCopy;
    fullCopy.ClearImage();
    Mutex::GetInstance().Unlock();
}

void Algorithms::Dilatation(Image *outputImage, ParametersStruct *params)
{
    // local copy

    Mutex::GetInstance().Lock();

    auto fullCopy = *outputImage;

    Mutex::GetInstance().Unlock();


        //Mutex::GetInstance().Lock();
        //// if canceled
        //if (!Mutex::GetInstance().IsThreadRunning())
        //{
        //    *outputImage = fullCopy;
        //    fullCopy.ClearImage();
        //    Mutex::GetInstance().Unlock();
        //    return;
        //}
        //// if auto refresh enabled
        //if (Mutex::GetInstance().GetState() == Mutex::AlgorithmThreadRefresh)
        //{
        //    *outputImage = fullCopy;
        //    Mutex::GetInstance().SetState(Mutex::MainThreadRefresh);
        //}
        //Mutex::GetInstance().Unlock();

    // copy back to output
    Mutex::GetInstance().Lock();
    Mutex::GetInstance().ThreadStopped();
    *outputImage = fullCopy;
    fullCopy.ClearImage();
    Mutex::GetInstance().Unlock();
}

void Algorithms::Skeletonization(Image *outputImage)
{
  
    // local copy
    Mutex::GetInstance().Lock();
    auto fullCopy = *outputImage;

    Mutex::GetInstance().Unlock();

 
        //Mutex::GetInstance().Lock();
        //// if canceled
        //if (!Mutex::GetInstance().IsThreadRunning())
        //{
        //    *outputImage = fullCopy;
        //    fullCopy.ClearImage();
        //    Mutex::GetInstance().Unlock();
        //    return;
        //}
        ////manualy refreshed
        //*outputImage = fullCopy;
        //Mutex::GetInstance().SetState(Mutex::MainThreadRefresh);
        //Mutex::GetInstance().Unlock();


    // copy back to output
    Mutex::GetInstance().Lock();
    Mutex::GetInstance().ThreadStopped();
    *outputImage = fullCopy;
    fullCopy.ClearImage();
    Mutex::GetInstance().Unlock();
}

void Algorithms::Hought(Image *outputImage, ParametersStruct *params)
{

    // local copy
    Mutex::GetInstance().Lock();
    auto copy = *outputImage;
    Mutex::GetInstance().Unlock();

  
        //Mutex::GetInstance().Lock();
        //// if canceled
        //if (!Mutex::GetInstance().IsThreadRunning())
        //{      
        //    copy.ClearImage();
        //    Mutex::GetInstance().Unlock();
        //    return;
        //}
        // // refresh for every line
        //Mutex::GetInstance().SetState(Mutex::MainThreadRefresh);
        //Mutex::GetInstance().Unlock();


    // refresh after the end
    // copy back to output
    Mutex::GetInstance().Lock();
    copy.ClearImage();
    Mutex::GetInstance().ThreadStopped();
    Mutex::GetInstance().Unlock();
}
