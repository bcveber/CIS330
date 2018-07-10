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

    Shrinker s;
    Shrinker s2;
    Grayscale gs;
    Subtract sb_g;
    Subtract sb_b;
    Subtract sb_r;
    Subtract sb_y;
    Subtract sb;
    Subtract sb2;
    Subtract sb3;
    LRCombine lr1;
    LRCombine lr2;
    LRCombine lr3;
    LRCombine lr4;
    TBCombine tb1;
    TBCombine tb2;

    Color green(163,242, 0, 255, 0);
    Color blue(163,242, 0, 0, 255);
    Color red(163,242, 255, 0, 0);
    Color yellow(163,242, 127, 64, 0);
    
    s.SetInput(reader1.GetOutput());  // this test creates a valid image
    sb_g.SetInput(s.GetOutput());
    sb_g.SetInput2(green.GetOutput());
    sb_b.SetInput(s.GetOutput());
    sb_b.SetInput2(blue.GetOutput());
    sb_r.SetInput(s.GetOutput());
    sb_r.SetInput2(red.GetOutput());
    sb_y.SetInput(s.GetOutput());
    sb_y.SetInput2(yellow.GetOutput());

    lr1.SetInput(sb_g.GetOutput());
    lr1.SetInput2(sb_b.GetOutput());
    lr2.SetInput(sb_r.GetOutput());
    lr2.SetInput2(sb_y.GetOutput());

    tb1.SetInput(lr1.GetOutput());
    tb1.SetInput2(lr2.GetOutput());

    sb.SetInput(reader1.GetOutput());
    sb.SetInput2(tb1.GetOutput());

    lr3.SetInput(sb.GetOutput());
    lr3.SetInput2(sb.GetOutput());
    lr4.SetInput(sb.GetOutput());
    lr4.SetInput2(sb.GetOutput());

    tb2.SetInput(lr3.GetOutput());
    tb2.SetInput2(lr4.GetOutput());

    s2.SetInput(tb2.GetOutput());
    sb3.SetInput2(s2.GetOutput());
    sb3.SetInput(reader1.GetOutput());


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
