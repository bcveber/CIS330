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

    Shrinker s;
    Grayscale g;
    Mirror m, m2;
    LRCombine lr, lr2;
    TBCombine tb;
    Rotate r, r2;
    Subtract sb;
    Blur b;

    // this test creates a valid image
    // start to mess up Hank
    s.SetInput(reader.GetOutput());
    r.SetInput(reader.GetOutput());
    m.SetInput(r.GetOutput());
    lr.SetInput(m.GetOutput());
    lr.SetInput2(reader.GetOutput());
    r2.SetInput(lr.GetOutput());
    tb.SetInput(r2.GetOutput());
    tb.SetInput2(m.GetOutput());
    sb.SetInput(lr.GetOutput());
    sb.SetInput2(r2.GetOutput());
    lr2.SetInput(sb.GetOutput());
    b.SetInput(lr2.GetOutput());
    m2.SetInput(b.GetOutput());

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
