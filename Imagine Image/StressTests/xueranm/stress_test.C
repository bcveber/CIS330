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
    PNMreader reader("../images/deschutes.pnm");  // note: filename must be "../images/image_name.pnm"
 

    Mirror mr;
    mr.SetInput(reader.GetOutput());
    
    Color gold(601,396,255,215,0);

    LRCombine lr;
    lr.SetInput(mr.GetOutput());
    lr.SetInput2(reader.GetOutput());
    
    LRCombine lr1;
    lr1.SetInput(lr.GetOutput());
    lr1.SetInput2(gold.GetOutput());

    LRCombine lr2;
    lr2.SetInput(gold.GetOutput());
    lr2.SetInput2(lr1.GetOutput());


    Color gold2(2404,396,255,215,0);
    TBCombine tb1;
    TBCombine tb2;

    tb1.SetInput(gold2.GetOutput());
    tb1.SetInput2(lr2.GetOutput());

    tb2.SetInput(tb1.GetOutput());
    tb2.SetInput2(gold2.GetOutput());
    // these tests creates a valid image


    


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

    if (argc == 3)
    {
        PNMwriter writer;
        writer.SetInput(finalImage);
        writer.Write("3H.pnm");
    }
    Logger::Finalize();
}
