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
    Mirror mr1;
    Subtract sb1;
    Subtract sb2;
    Rotate rt1;
    Rotate rt2;
    Rotate rt3;
    Rotate rt4;
    TBCombine tb1;
    TBCombine tb2;
    LRCombine lr1;
    LRCombine lr2;
    LRCombine lr3;


    mr1.SetInput(reader.GetOutput());
    sb1.SetInput(reader.GetOutput());
    sb1.SetInput2(mr1.GetOutput());
    rt1.SetInput(sb1.GetOutput());
    rt2.SetInput(rt1.GetOutput());
    tb1.SetInput(sb1.GetOutput());
    tb1.SetInput2(rt2.GetOutput());

    sb2.SetInput(mr1.GetOutput());
    sb2.SetInput2(reader.GetOutput());
    rt3.SetInput(sb2.GetOutput());
    rt4.SetInput(rt3.GetOutput());
    tb2.SetInput(sb2.GetOutput());
    tb2.SetInput2(rt4.GetOutput());

    lr3.SetInput(tb1.GetOutput());
    lr3.SetInput2(tb2.GetOutput());

    /* make "finalImage" be the image at the bottom of your pipeline */
    /* the code below will call update on finalImage                 */
    Image *finalImage = lr3.GetOutput();

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
