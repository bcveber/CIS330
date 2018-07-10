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

    /*START*/
    PNMreader reader("../images/puddles.pnm");
    PNMreader reader2("../images/hank.pnm");
    
    Shrinker shrinker1;
    Shrinker shrinker2;
    LRCombine lrcombine1;
    TBCombine tbcombine1;
    TBCombine tbcombine2;
    Blender  blender;
    blender.SetFactor(0.25);
    
    shrinker1.SetInput(reader.GetOutput());
    shrinker2.SetInput(reader2.GetOutput());
    tbcombine1.SetInput(shrinker1.GetOutput());
    tbcombine1.SetInput(shrinker2.GetOutput());
    shrinker1.SetInput(tbcombine1.GetOutput());
    lrcombine1.SetInput(shrinker1.GetOutput());
    lrcombine1.SetInput(lrcombine1.GetOutput());
    blender.SetInput(lrcombine1.GetOutput());
    
    Image *finalImage = shrinker1.GetOutput();

   /*END*/

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
