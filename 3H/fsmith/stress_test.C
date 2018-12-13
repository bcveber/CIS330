#include "PNMreader.h"
#include "PNMwriter.h"
#include "filter.h"
#include "logging.h"
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
    ofstream ofile ("bad_img"); // note: filename must be "../images/image_name.pnm"
    ofile << "P6/n301 396/n 65535/n/n";
    PNMreader reader1("bad_img");
    PNMreader reader2("../images/puddles.pnm");
    Shrinker s1;
    Shrinker s2;
    Shrinker s3;
    Color black(1354, 1742, 0, 0, 0);
    Color black2(424, 270, 0, 0, 0);
    Color white(148, 624, 255, 255, 255);
    Rotate rotate1;
    Blender blendy;
    LRCombine lr1;
    LRCombine lr2;
    TBCombine tb1;
    
    //First Image
    rotate1.SetInput(black.GetOutput());
    lr1.SetInput(rotate1.GetOutput());
    lr1.SetInput2(reader2.GetOutput());
    s2.SetInput(lr1.GetOutput());
    s3.SetInput(s2.GetOutput());
    
    //Second Image
    lr2.SetInput(reader1.GetOutput());
    lr2.SetInput2(black2.GetOutput());
    tb1.SetInput(lr2.GetOutput());
    tb1.SetInput2(white.GetOutput());
    blendy.SetInput(tb1.GetOutput());
    blendy.SetInput2(s3.GetOutput());
    
    /* make "finalImage" be the image at the bottom of your pipeline */
    /* the code below will call update on finalImage                 */
    Image *finalImage = blendy.GetOutput();
    
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
    
    if (argc == 3)
    {
        PNMwriter writer;
        writer.SetInput(finalImage);
        writer.Write("3H.pnm");
    }
    Logger::Finalize();
}
