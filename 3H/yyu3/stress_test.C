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
    PNMreader reader("../images/puddles.pnm");  
    Shrinker s1;
    s1.SetInput(reader.GetOutput());

    Rotate t1;
    t1.SetInput(s1.GetOutput());        
    
    LRCombine lr1;
    lr1.SetInput(t1.GetOutput());
    lr1.SetInput2(t1.GetOutput());

    TBCombine tb1;
    tb1.SetInput(lr1.GetOutput());
    tb1.SetInput2(lr1.GetOutput());

    //cancel blender use
    // Blender b;
    // b.SetFactor(0.6);
    // b.SetInput(tb1.GetOutput());
    // b.SetInput2(reader.GetOutput());


    PNMreader reader2("../images/tux.pnm");
    
    Blur s2;
    s2.SetInput(reader2.GetOutput());
        
    TBCombine tb2;
    tb2.SetInput(s2.GetOutput());
    tb2.SetInput2(tb1.GetOutput());

    PNMreader reader4("../images/hank.pnm");
    
    Mirror mr;
    mr.SetInput(reader4.GetOutput());
   

    LRCombine lr3;
    lr3.SetInput(mr.GetOutput());
    //should have exception here if not add setinput2
    //lr3.SetInput2(mr.GetOutput());

    TBCombine tb3;
    tb3.SetInput(lr3.GetOutput());
    tb3.SetInput2(lr3.GetOutput());


    // Color cc(279,262,255, 64, 40);


    // Blender b2;
    // b2.SetFactor(0.8);
    // b2.SetInput(tb3.GetOutput());
    // b2.SetInput2(cc.GetOutput());

     Grayscale gr;
     gr.SetInput(tb3.GetOutput());

    // Color sc(652,262,100, 100, 0);
    Subtract sb;
    sb.SetInput(tb3.GetOutput());
    sb.SetInput2(gr.GetOutput());





    /*   TODO: fill in fun stuff here   */


    /* make "finalImage" be the image at the bottom of your pipeline */
    /* the code below will call update on finalImage                 */
    Image *finalImage = sb.GetOutput();

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
