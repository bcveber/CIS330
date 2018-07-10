#include <PNMreader.h>
#include <PNMwriter.h>
#include <filter.h>
#include <logging.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>

using std::cerr;
using std::endl;
using std::ofstream;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cerr << "Usage: " << argv[0] << " <username>" << endl;
        exit(EXIT_FAILURE);
    }

    char event[1024];
    sprintf(event, "Entered program from %s\n", argv[1]);
    Logger::LogEvent(event);



    /* ================================ */
    /* START STUDENT MODIFIABLE SECTION */
    /* ================================ */

    /* you may want one or more readers! */
    PNMreader tuxReader("../images/tux.pnm");  // note: filename must be "../images/image_name.pnm"
    PNMreader gnuReader("../images/gnu.pnm");

    // Adjust for quicker runtimes or sicker images. . .
    #define N_BLURS 10

    Blur b[N_BLURS];

    b[0].SetInput(tuxReader.GetOutput());
    for (int i = 1; i < N_BLURS; i++) {
      b[i].SetInput(b[i-1].GetOutput());
    }

    Color pad1(166,438,255,244,233);
  
    LRCombine lr1;
    lr1.SetInput(pad1.GetOutput());
    lr1.SetInput2(b[N_BLURS-1].GetOutput());
    
    TBCombine tb1;
    tb1.SetInput(lr1.GetOutput());
    tb1.SetInput2(gnuReader.GetOutput());
  
    Color subMask(691,881,255,255,255);

    Subtract sub1;

    sub1.SetInput(subMask.GetOutput());
    sub1.SetInput2(tb1.GetOutput());
    
    Blur b2[N_BLURS];
    b2[0].SetInput(sub1.GetOutput());
    for (int i = 1; i < N_BLURS; i++) {
      b2[i].SetInput(b2[i-1].GetOutput());
    }

    Shrinker shrnk1;
    Rotate rot1;

    shrnk1.SetInput(b2[N_BLURS-1].GetOutput());
    rot1.SetInput(shrnk1.GetOutput());

    Color padX(251,345,0,0,255);
    Rotate rot2;
    rot2.SetInput(rot1.GetOutput()); 
    
    Shrinker shrnk2;
    shrnk2.SetInput(rot2.GetOutput());

    Color pad2(79,220,0,0,255);
    LRCombine lr1_1;
    lr1_1.SetInput(pad2.GetOutput());
    lr1_1.SetInput2(shrnk2.GetOutput());

    Color pad3(251,125,255,0,0);
    TBCombine tb1_1;
    tb1_1.SetInput(lr1_1.GetOutput());
    tb1_1.SetInput2(pad3.GetOutput());

    Color subMask1_1(251,345,100,200,255);
    Subtract sub1_1;
    sub1_1.SetInput(subMask1_1.GetOutput());
    sub1_1.SetInput2(tb1_1.GetOutput());    

    LRCombine lr2;
    lr2.SetInput(sub1_1.GetOutput());
    lr2.SetInput2(rot1.GetOutput());

    Color subMask2(691,345,255,200,100);
    Subtract sub2;
    sub2.SetInput(subMask2.GetOutput());
    sub2.SetInput2(lr2.GetOutput());

    TBCombine tb2;
    tb2.SetInput(b2[N_BLURS-1].GetOutput());
    tb2.SetInput2(sub2.GetOutput());


    /* make "finalImage" be the image at the bottom of your pipeline */
    /* the code below will call update on finalImage                 */
    Image *finalImage = tb2.GetOutput();


    /* ================================ */
    /*  END STUDENT MODIFIABLE SECTION  */
    /* ================================ */



    try
    {
        finalImage->Update();
    }
    catch (DataFlowException &)
    {
        ofstream ofile("my_exception");
        if (ofile.fail())
        {
             cerr << "Something is wrong ... can't open my_exception"
                  << " for opening" << endl;
             exit(EXIT_FAILURE);
        }
        ofile << "Exception found!" << endl;
        exit(EXIT_SUCCESS);
    }

    CheckSum cs;
    cs.SetInput(finalImage);
    cs.OutputCheckSum("my_checksum");

/**************************************************************************
    Modification to see resulting image
**************************************************************************/
/*
    PNMwriter writer;
    writer.SetInput(finalImage);
    writer.Write("test.pnm");

*/

    if (argc == 3)
    {
        PNMwriter writer;
        writer.SetInput(finalImage);
        writer.Write("3H.pnm");
    }
    Logger::Finalize();
}
