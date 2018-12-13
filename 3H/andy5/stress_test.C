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

    PNMreader reader("../images/puddles.pnm");
    PNMreader reader2("../images/tux.pnm");

    Shrinker sr;
    LRCombine lr1;
    LRCombine lr2;
    LRCombine lr3;
    LRCombine lr4;
    LRCombine lr5;
    LRCombine lr6;
    TBCombine tb1;
    TBCombine tb2;
    TBCombine tb3;
    Blur br1;
    Blur br2;
    Blur br3;
    Subtract sb;
    Rotate rt1;
    Rotate rt2;
    Rotate rt3;
    Rotate rt4;
    Mirror mr;
    Grayscale gs;

    Color green(893, 672, 10, 64, 40);
    Color gold(893, 672, 255, 215, 0);

    br1.SetInput(br1.GetOutput());
    sr.SetInput(br1.GetOutput());

    rt1.SetInput(sr.GetOutput());
    rt2.SetInput(rt1.GetOutput());
    br2.SetInput(rt2.GetOutput());
    rt3.SetInput(br2.GetOutput());
    rt4.SetInput(rt3.GetOutput());
    br3.SetInput(rt4.GetOutput());

    lr1.SetInput(sr.GetOutput());
    lr1.SetInput2(rt2.GetOutput());
    lr2.SetInput(br2.GetOutput());
    lr2.SetInput2(br3.GetOutput());
    tb1.SetInput(lr1.GetOutput());
    tb1.SetInput2(lr2.GetOutput());

    sb.SetInput(br1.GetOutput());
    sb.SetInput2(reader.GetOutput());

    lr3.SetInput(tb1.GetOutput());
    lr3.SetInput2(sb.GetOutput());

    mr.SetInput(sb.GetOutput());

    gs.SetInput(sr.GetOutput());

    lr4.SetInput(gs.GetOutput());
    lr4.SetInput2(green.GetOutput());
    lr5.SetInput(gold.GetOutput());
    lr5.SetInput2(gs.GetOutput());
    tb2.SetInput(lr4.GetOutput());
    tb2.SetInput2(lr5.GetOutput());

    lr6.SetInput(mr.GetOutput());
    lr6.SetInput2(tb2.GetOutput());

    tb3.SetInput(lr3.GetOutput());
    tb3.SetInput2(lr6.GetOutput());


    Image *finalImage = tb3.GetOutput();

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
