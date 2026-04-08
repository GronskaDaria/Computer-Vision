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

    // copy back to output
    Mutex::GetInstance().Lock();
    Mutex::GetInstance().ThreadStopped();
    *outputImage = copy;
    copy.ClearImage();
    Mutex::GetInstance().Unlock();
}

void Algorithms::Exponentiation(Image *outputImage, ParametersStruct *params)
{
    // loacl copy
    Mutex::GetInstance().Lock();
    Image copy = *outputImage;
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

void Algorithms::LevelHistogram(Image *outputImage)
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
