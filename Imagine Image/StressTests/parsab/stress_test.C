#include <PNMreader.h>
#include <PNMwriter.h>
#include <filter.h>
#include <logging.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
using std::cerr;
using std::endl;
using std::ofstream;
// using namespace std;

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
    // PNMreader reader("puddles.pnm");  // note: filename must be "../images/image_name.pnm"
    PNMreader reader("../images/image_name.pnm");
    /*   TODO: fill in fun stuff here   */
    Color B(893, 672, 0, 0, 255);
    Color G(893, 672, 0, 255, 0);
    Color R(893, 672, 255, 0, 0);

    // Color c2(893, 672, 10, 64, 40);
    Grayscale gs1;
    Subtract sb1;
    Subtract sb2;
    Subtract sb3;
    Shrinker s1;
    // Shrinker s2;
    Shrinker s3;
    Shrinker s4;
    LRCombine lr1;
    LRCombine lr2;
    LRCombine lr3;
    LRCombine lr4;
    LRCombine lr5;
    Mirror mr1;
    TBCombine tb1;
    TBCombine tb2;
    TBCombine tb3;
    Rotate rt1;
    Rotate rt2;
    Mirror mr2;
    Mirror mr3;

    s1.SetInput(reader.GetOutput());
    gs1.SetInput(s1.GetOutput());
    sb3.SetInput(s1.GetOutput());
    sb3.SetInput2(B.GetOutput());
    lr1.SetInput(gs1.GetOutput());
    lr1.SetInput2(sb3.GetOutput());
    mr1.SetInput(lr1.GetOutput());
    lr2.SetInput(sb2.GetOutput());
    lr2.SetInput2(sb3.GetOutput());
    tb1.SetInput(lr1.GetOutput());
    tb1.SetInput2(mr1.GetOutput());

    // s2.SetInput(reader.GetOutput());
    sb1.SetInput(s1.GetOutput());
    sb1.SetInput2(R.GetOutput());
    sb2.SetInput(s1.GetOutput());
    sb2.SetInput2(G.GetOutput());
    rt2.SetInput(sb1.GetOutput());
    rt1.SetInput(rt2.GetOutput());
    lr3.SetInput(rt1.GetOutput());
    lr3.SetInput2(sb2.GetOutput());
    mr2.SetInput(lr3.GetOutput());
    tb2.SetInput(lr3.GetOutput());
    tb2.SetInput2(mr2.GetOutput());

    s3.SetInput(tb1.GetOutput());
    s4.SetInput(tb2.GetOutput());
    lr4.SetInput(s3.GetOutput());
    lr4.SetInput2(s4.GetOutput());
    // mr3.SetInput(lr4.GetOutput());
    lr5.SetInput(s4.GetOutput());
    lr5.SetInput2(s3.GetOutput());
    tb3.SetInput(lr4.GetOutput());
    tb3.SetInput2(lr5.GetOutput());

    /* make "finalImage" be the image at the bottom of your pipeline */
    /* the code below will call update on finalImage                 */
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
