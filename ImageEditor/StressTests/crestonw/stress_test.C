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

    LRCombine lr;
    LRCombine lr2;
    TBCombine tb;
    TBCombine tb1;
    Subtract s;
    Blender b;
    
    Color offset(601*4, 396*4, 255, 255, 0);   

    lr.SetInput(reader.GetOutput());
    lr.SetInput2(reader.GetOutput());

    lr2.SetInput(lr.GetOutput());
    lr2.SetInput2(lr.GetOutput());

    tb.SetInput(lr2.GetOutput());
    tb.SetInput2(lr2.GetOutput());

    tb1.SetInput(tb.GetOutput());
    tb1.SetInput2(tb.GetOutput());

    s.SetInput(offset.GetOutput());
    s.SetInput2(tb1.GetOutput());

    b.SetFactor(.2);
    b.SetInput(s.GetOutput());
    b.SetInput2(tb1.GetOutput());


    /* make "finalImage" be the image at the bottom of your pipeline */
    /* the code below will call update on finalImage                 */
    Image *finalImage = b.GetOutput();

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
