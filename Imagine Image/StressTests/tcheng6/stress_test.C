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


    // note: filename must be "../images/image_name.pnm"
    PNMreader reader("../images/deschutes.pnm");  
    Rotate rt1;
    Rotate rt2;
    TBCombine tb;
    Mirror mr;
    LRCombine lr;

    rt1.SetInput(reader.GetOutput());
    rt2.SetInput(rt1.GetOutput());

    tb.SetInput(reader.GetOutput());
    tb.SetInput2(rt2.GetOutput());

    mr.SetInput(tb.GetOutput());

    lr.SetInput(tb.GetOutput());
    lr.SetInput2(mr.GetOutput());

    Image *finalImage = lr.GetOutput();


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
