#include "PNMreader.h"
#include "PNMwriter.h"
#include "filter.h"
#include "logging.h"
#include "iostream"
#include "fstream"
#include "stdlib.h"

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

    
    Blender blend;
    blend.SetFactor(0.60);
    Blender b2;
    b2.SetFactor(0.30);
    Subtract sb;
    Mirror mr;
 
    Color teal(601,396,89,198,204);
    Color magenta(601,396,173,2,119);
    Color orange(601,396,255,145,12);
    Color white(601,396,255,255,255);    

    blend.SetInput(reader.GetOutput());
    blend.SetInput2(white.GetOutput());

    sb.SetInput(blend.GetOutput());
    sb.SetInput2(magenta.GetOutput());

    mr.SetInput(sb.GetOutput());

    b2.SetInput(mr.GetOutput());
    b2.SetInput2(teal.GetOutput());

/* make "finalImage" be the image at the bottom of your pipeline */
    /* the code below will call update on finalImage                 */
    Image *finalImage = b2.GetOutput();

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
