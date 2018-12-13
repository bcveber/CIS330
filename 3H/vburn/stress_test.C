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
    PNMreader reader("../images/puddles.pnm");  // note: filename must be "../images/image_name.pnm"
    PNMreader reader2("../images/hank.pnm");
    PNMreader reader3("../images/deschutes.pnm");
    Color color(326, 484, 77, 63, 185);
    Color color2(601, 396, 231, 147, 97);
    Color color3(275, 484, 243, 74, 69);
    Color color4(1344, 1786, 23, 249, 165);
    Color color5(601, 906, 123, 123, 123);
    LRCombine lr1;
    LRCombine lr2;
    LRCombine lr3;
    LRCombine lr4;
    TBCombine tb1;
    TBCombine tb2;
    TBCombine tb3;
    Mirror m1;
    Mirror m2;
    Subtract sb1;
    Subtract sb2;
    Subtract sb3;
    Grayscale g1;
    Rotate r1;
    Rotate r2;
    Blur b1;

    sb1.SetInput(reader2.GetOutput());
    sb1.SetInput2(color.GetOutput());
    m1.SetInput(sb1.GetOutput());
    lr1.SetInput(m1.GetOutput());
    lr1.SetInput2(color3.GetOutput());
    sb2.SetInput(reader3.GetOutput());
    sb2.SetInput2(color2.GetOutput());
    tb1.SetInput(lr1.GetOutput());
    tb1.SetInput2(sb2.GetOutput());
    r1.SetInput(reader.GetOutput());
    g1.SetInput(r1.GetOutput());
    sb3.SetInput(color4.GetOutput());
    sb3.SetInput2(g1.GetOutput());
    tb3.SetInput(tb1.GetOutput());
    tb3.SetInput2(color5.GetOutput());
    lr3.SetInput(sb3.GetOutput());
    lr3.SetInput2(tb3.GetOutput());
    lr4.SetInput(color.GetOutput());
    lr4.SetInput2(reader3.GetOutput());
    r2.SetInput(lr4.GetOutput());
    b1.SetInput(lr3.GetOutput());
    m2.SetInput(b1.GetOutput());




    /* make "finalImage" be the image at the bottom of your pipeline */
    /* the code below will call update on finalImage                 */
    Image *finalImage = m2.GetOutput();

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
