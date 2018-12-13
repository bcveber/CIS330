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
       
    /*   TODO: fill in fun stuff here   */
   
    PNMreader reader("../images/puddles.pnm");  // note: filename must be "../images/image_name.pnm"

    TBCombine tb;
    TBCombine tb2;
    LRCombine lr; 
    Shrinker s;

    Blender b;
    Blender b2;
    Blender b3;
    Blender b4;
    Blender b5;
    
    b.SetFactor(-1000);
    b2.SetFactor(1000);
    b3.SetFactor(0.0);
    b4.SetFactor(1.0);
    b5.SetFactor(.9999999999999999999999999999999999999);
    
    tb.SetInput(reader.GetOutput());
    tb.SetInput2(reader.GetOutput());

    tb2.SetInput2(reader.GetOutput());
    tb2.SetInput2(reader.GetOutput());

    lr.SetInput(tb.GetOutput());
    lr.SetInput2(tb2.GetOutput());

    s.SetInput(lr.GetOutput());

    b.SetInput(s.GetOutput());
    b.SetInput2(reader.GetOutput());

    b2.SetInput(b.GetOutput());
    b2.SetInput2(s.GetOutput());

    b3.SetInput(b2.GetOutput());
    b3.SetInput2(b.GetOutput());

    b4.SetInput(b3.GetOutput());
    b4.SetInput2(b2.GetOutput());

    b5.SetInput(b4.GetOutput());
    b5.SetInput2(b3.GetOutput());

    /* make "finalImage" be the image at the bottom of your pipeline */
    /* the code below will call update on finalImage                 */
    Image *finalImage = b5.GetOutput();

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
