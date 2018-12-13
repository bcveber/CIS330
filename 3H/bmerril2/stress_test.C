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
    PNMreader reader("../images/hank.pnm");
    
    Shrinker sr;
    Shrinker sr2;
    LRCombine lr;
    LRCombine lr2;
    TBCombine tb;
    Blur br1;
    Blur br2;
    Blur br3;
    Subtract sb1;
    Subtract sb2;
    Subtract sb3;
    Subtract sb4;

    Color cb(326,484, 10, 64, 40);
    Color cb2(326,484, 240, 21, 21);

    sr.SetInput(reader.GetOutput());
    sr2.SetInput(reader.GetOutput());
    br1.SetInput(sr.GetOutput());
    br2.SetInput(sr2.GetOutput());
    sb1.SetInput(br1.GetOutput());
    sb1.SetInput2(cb.GetOutput());
    sb2.SetInput(br2.GetOutput());
    sb2.SetInput2(cb2.GetOutput());


    lr.SetInput(sb1.GetOutput());
    lr.SetInput2(sb2.GetOutput());
    lr2.SetInput(sb2.GetOutput());
    lr2.SetInput2(sb1.GetOutput());
    tb.SetInput(lr.GetOutput());
    tb.SetInput2(lr2.GetOutput());
    br3.SetInput(tb.GetOutput());

    sb3.SetInput(tb.GetOutput());
    sb3.SetInput2(reader.GetOutput());

    /* make "finalImage" be the image at the bottom of your pipeline */
    /* the code below will call update on finalImage                 */
    Image *finalImage = sb3.GetOutput();

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
