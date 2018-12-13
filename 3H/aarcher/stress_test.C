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
    PNMwriter writer;
    PNMreader reader((char *)"../images/hank.pnm");

    Color red(326, 484, 255, 0, 0); 
    Color green(326, 484, 0,255,0);
    Color yellow(326,484,255,255,0);  //red + green = yellow 
    Color blue(326,484,0,0,255);

    Blender b1;  //red hank
    b1.SetInput(reader.GetOutput());
    b1.SetInput2(red.GetOutput());
    b1.SetFactor(.60);
  
    Blender b2; //gren hank
    b2.SetInput(reader.GetOutput());
    b2.SetInput2(green.GetOutput());
    b2.SetFactor(.60);
    
    Blender b3; //red + green = yellow hank
    b3.SetInput(b1.GetOutput());
    b3.SetInput2(b2.GetOutput());
    b3.SetFactor(.60);
    
    LRCombine lr; // red + green hank
    lr.SetInput(b1.GetOutput());
    lr.SetInput2(b2.GetOutput());

    LRCombine lr1;// (red + green) + yellow hank
    lr1.SetInput(lr.GetOutput());
    lr1.SetInput2(b3.GetOutput());

    Blender b4; //blue hankd
    b4.SetInput(reader.GetOutput());
    b4.SetInput2(blue.GetOutput());
    b4.SetFactor(.60);

    Blender b5; //blue + yellow hank
    b5.SetInput(b4.GetOutput());
    b5.SetInput2(b3.GetOutput());
    b5.SetFactor(.60);

    
    LRCombine lr2;
    lr2.SetInput(b4.GetOutput());
    lr2.SetInput2(b3.GetOutput());
    
    LRCombine lr3;
    lr3.SetInput(lr2.GetOutput());
    lr3.SetInput2(b5.GetOutput());

    TBCombine tb;
    tb.SetInput(lr1.GetOutput());
    tb.SetInput2(lr3.GetOutput());
    

    
    Blender b6; // red + blue hank
    b6.SetInput(b1.GetOutput());
    b6.SetInput2(b4.GetOutput());
    b6.SetFactor(.60);

    Blender b7; //green + yellow hank
    b7.SetInput(b2.GetOutput());
    b7.SetInput2(b3.GetOutput());
    b7.SetFactor(.60);
    
    Blender b8; //yellow hank + ... other blue hank... = ???
    b8.SetInput(b3.GetOutput());
    b8.SetInput2(b5.GetOutput());
    b8.SetFactor(.60);
    
    LRCombine lr4;
    lr4.SetInput(b6.GetOutput());
    lr4.SetInput2(b7.GetOutput());
    LRCombine lr5;
    lr5.SetInput(lr4.GetOutput());
    lr5.SetInput2(b8.GetOutput());

    TBCombine tb2;
    tb2.SetInput(tb.GetOutput());
    tb2.SetInput2(lr5.GetOutput());    


    


    /* make "finalImage" be the image at the bottom of your pipeline */
    /* the code below will call update on finalImage                 */
    Image *finalImage = tb2.GetOutput();

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
