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
    PNMreader reader2("../images/question_marks.pnm");
    Color color1(326, 484, 0, 0, 0);
    Color color2(326, 242, 64, 29, 78);
    Color color3(326, 242, 0, 0, 0);
    Color color4(357, 132, 255, 255, 255);
    
    Rotate rt1;
    Rotate rt2;
    Subtract sb1;
    Subtract sb2;
    LRCombine lr1;
    LRCombine lr2;
    LRCombine lr3;
    Mirror mr;
    Grayscale gs;
    TBCombine tb1;
    TBCombine tb2;


	rt1.SetInput(reader.GetOutput());
	rt2.SetInput(rt1.GetOutput());
	sb1.SetInput(reader.GetOutput());
	sb1.SetInput2(rt2.GetOutput());
	lr1.SetInput(reader.GetOutput());
	lr1.SetInput2(sb1.GetOutput());
	mr.SetInput(lr1.GetOutput());
	gs.SetInput(mr.GetOutput());
	tb1.SetInput(color2.GetOutput());
	tb1.SetInput2(color3.GetOutput());
	lr2.SetInput(color1.GetOutput());
	lr2.SetInput2(tb1.GetOutput());
	sb2.SetInput(gs.GetOutput());
	sb2.SetInput2(lr2.GetOutput());
	tb2.SetInput(color4.GetOutput());
	tb2.SetInput2(reader2.GetOutput());
	lr3.SetInput(tb2.GetOutput());
	lr3.SetInput2(sb2.GetOutput());
	

    Image *finalImage = lr3.GetOutput();

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
