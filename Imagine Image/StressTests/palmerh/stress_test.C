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
    
    PNMreader reader("../images/hank.pnm");
    
    Subtract sub;
    LRCombine lr1, lr2;
    TBCombine tb;
    Mirror mr;
    Blur br1, br2;
    Rotate rot1;
    
    mr.SetInput(reader.GetOutput());
    lr1.SetInput(reader.GetOutput());
    lr1.SetInput2(mr.GetOutput());
    lr2.SetInput(mr.GetOutput());
    lr2.SetInput2(reader.GetOutput());
    
    br1.SetInput(lr1.GetOutput());
    br2.SetInput(br1.GetOutput());
    
    sub.SetInput2(br2.GetOutput());
    sub.SetInput(lr1.GetOutput());
    
    
    tb.SetInput(sub.GetOutput());
    tb.SetInput2(lr2.GetOutput());
    
    rot1.SetInput(tb.GetOutput());
    
    Image* finalImage = rot1.GetOutput();
    
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
