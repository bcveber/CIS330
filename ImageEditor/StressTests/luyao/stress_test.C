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
    PNMreader reader("../images/hank.pnm");  // note: filename must be "../images/image_name.pnm"
    PNMreader reader1("../images/tux.pnm");

    Shrinker sr1; //done
    Shrinker sr2; //done
    LRCombine lr1;
    LRCombine lr2;
    LRCombine lr3;
    TBCombine tb1;
    TBCombine tb2;
    Blur br1; //done
    Blur br2; //done
    Blur br3;
    Subtract sb;
    Rotate rt1;
    Rotate rt2;
    Rotate rt3;
    Mirror mr;
    Grayscale gs;
    //
    Color pink(163,242,225,182,193);
    //or you can use sourcce 2.
    sr1.SetInput(reader.GetOutput());
    sr2.SetInput(reader1.GetOutput());
    //
    br1.SetInput(sr1.GetOutput());
    //one image mirrored
    mr.SetInput(sr1.GetOutput());
//--------------------------------------------
    br2.SetInput(sr1.GetOutput());
    rt1.SetInput(br2.GetOutput());
    //one with 180 rotatation
    rt2.SetInput(rt1.GetOutput());
//----------------------------------
    lr1.SetInput(mr.GetOutput());
    lr1.SetInput2(rt2.GetOutput());

    br3.SetInput(mr.GetOutput());
    sb.SetInput(mr.GetOutput());
    sb.SetInput2(reader.GetOutput());

    gs.SetInput(sb.GetOutput());
    lr2.SetInput(gs.GetOutput());
    lr2.SetInput2(pink.GetOutput());

    tb1.SetInput(lr1.GetOutput());
    tb1.SetInput2(lr2.GetOutput());

    lr3.SetInput(reader.GetOutput());
    lr3.SetInput2(tb1.GetOutput());


    // Shrinker s;
    // s.SetInput(reader.GetOutput());
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
