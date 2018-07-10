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
    PNMreader reader1("../images/hank.pnm");  // note: filename must be "../images/image_name.pnm"

    /*   TODO: fill in fun stuff here   */
    
    TBCombine tb1;
    LRCombine lr1;
    LRCombine lr2;
    Blur blur1;
    Blur blur2;
    Blur blur3;
    Blur blur4;
    Blur blur5;
    Blur blur6;	
    Blur blur7;	
    Blur blur8;	
    Blur blur9;	
    Rotate rot1;
    Rotate rot2;
    Mirror mir1;
    Color green(500, 968, 0, 68, 0);   

    //Create a water-like reflection of hank
    rot1.SetInput(reader1.GetOutput());
    rot2.SetInput(rot1.GetOutput());
    blur1.SetInput(rot2.GetOutput());
    blur2.SetInput(blur1.GetOutput());
    blur3.SetInput(blur2.GetOutput());
    blur4.SetInput(blur3.GetOutput());
    blur5.SetInput(blur4.GetOutput());
    blur6.SetInput(blur5.GetOutput());
    blur7.SetInput(blur6.GetOutput());
    blur8.SetInput(blur7.GetOutput());
    blur9.SetInput(blur8.GetOutput());
    mir1.SetInput(blur9.GetOutput());

    tb1.SetInput(reader1.GetOutput());
    tb1.SetInput2(mir1.GetOutput());
    lr1.SetInput(green.GetOutput());
    lr1.SetInput2(tb1.GetOutput());
    
    lr2.SetInput(lr1.GetOutput());
    lr2.SetInput2(green.GetOutput());

    /* make "finalImage" be the image at the bottom of your pipeline */
    /* the code below will call update on finalImage                 */
    Image *finalImage = lr2.GetOutput();

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
