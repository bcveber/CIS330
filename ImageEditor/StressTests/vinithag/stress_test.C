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
    Shrinker sr1, sr2, sr3, sr4;
    Rotate r1, r2, r3, r4, r5, r6;
    Mirror m1;
    LRCombine lr1, lr2, lr3, lr4;
    TBCombine tb1, tb2, tb3, tb4;
    Blur b1;
    Subtract s1, s2;
    Grayscale gs;
    /* you may want one or more readers! */
    PNMreader reader("../images/puddles.pnm");  // note: filename must be "../images/image_name.pnm"
    sr1.SetInput(reader.GetOutput());
    sr2.SetInput(sr1.GetOutput());

    r1.SetInput(sr2.GetOutput());
    r2.SetInput(r1.GetOutput());

    m1.SetInput(r2.GetOutput());

    lr1.SetInput(sr2.GetOutput());
    lr1.SetInput2(r2.GetOutput());
    
    r3.SetInput(lr1.GetOutput());
    r4.SetInput(r3.GetOutput());
    gs.SetInput(r4.GetOutput());

    tb1.SetInput(lr1.GetOutput());
    tb1.SetInput2(gs.GetOutput());

    r5.SetInput(tb1.GetOutput());
    r6.SetInput(r5.GetOutput());
    b1.SetInput(r6.GetOutput());

    Color gold(893, 672, 255, 215, 0);
    s2.SetInput(gold.GetOutput());
    s2.SetInput2(sr1.GetOutput());

    Color green(893, 672, 10, 64, 40);
    Color custom(893, 672, 120, 64, 140);
    s1.SetInput(custom.GetOutput());
    s1.SetInput2(green.GetOutput());

    lr2.SetInput(s2.GetOutput());
    lr2.SetInput2(tb1.GetOutput());
    
    sr3.SetInput(reader.GetOutput());
    sr4.SetInput(sr3.GetOutput());
    lr3.SetInput(sr4.GetOutput());
    lr3.SetInput2(sr4.GetOutput());

    tb3.SetInput(lr3.GetOutput());
    tb3.SetInput2(lr3.GetOutput());

    lr4.SetInput(custom.GetOutput());
    lr4.SetInput2(tb3.GetOutput());

    tb4.SetInput(lr2.GetOutput());
    tb4.SetInput2(lr4.GetOutput());

    tb4.GetOutput()->Update();

    /* make "finalImage" be the image at the bottom of your pipeline */
    /* the code below will call update on finalImage                 */
    Image *finalImage = tb4.GetOutput();

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
